
#include "base.hpp"
#include "xml/xml.hpp"

CXML::CXML()
{
	throw_if(! is_init());

	tag = "";
	value = "";
}

CXML::CXML(const string __tag)
{
	throw_if(! is_init());

	tag = __tag;
	value = "";
}

CXML & CXML::append(const string ind)
{
	throw_if(exist(ind));

	childs[ind].tag = ind;

	return childs[ind];
}

void CXML::add(CXML & node, const CXML & add_node)
{
	for(auto & elem : add_node.childs)
	{
		CXML & child = node.get(elem.first);

		add(child, elem.second);
	}

	node.value = add_node.value;
}

void CXML::pack(rapidxml::xml_document<> & doc, rapidxml::xml_node<> * node) const
{
	if(childs.size())
	{
		for(auto & child : childs)
		{
			xml_node<> * sub_node = doc.allocate_node(node_element, child.first.c_str(), child.second.value.c_str());
			node->append_node(sub_node);

			child.second.pack(doc, sub_node);
		}
	}
}

CXML CXML::operator+(const CXML & op)
{
	CXML ret(tag);

	add(ret, (* this));
	add(ret, op);
	
	return ret;
}

CXML & CXML::operator[](const string ind)
{
	throw_if(! exist(ind));

	return childs[ind];
}

CXML & CXML::get(const string ind)
{
	if(exist(ind))
		return (* this)[ind];

	return append(ind);
}

string CXML::pack() const
{
	stringstream stream;
	xml_document<> doc;
	xml_node<> * root = doc.allocate_node(node_element, tag.c_str());

	doc.append_node(root);

	pack(doc, root);

	stream << * doc.first_node();
	
	return stream.str();
}

CXML CXML::load_from_file(const string fname)
{
	FILE * fl = NULL;

	try
	{
		size_t size;
		shared_ptr<uint8_t> buf;
		uint8_t * p_buf;

		throw_null(fl = fopen(fname.c_str(), "r"));
		throw_if(fseek(fl, 0, SEEK_END));
		throw_if((size = ftell(fl)) < 0);
		throw_if(fseek(fl, 0, SEEK_SET));

		buf.reset(new uint8_t[size + 1], std::default_delete<uint8_t[]>());
		throw_null(p_buf = buf.get());

		throw_if(fread(p_buf, 1, size, fl) != size);
		p_buf[size] = '\0';

		fclose(fl);
		fl = NULL;

		return load_from_string(string((char *) p_buf));
	}
	catch(...)
	{
		if(fl != NULL)
			fclose(fl);

		throw_;
	}
}

CXML CXML::load_from_string(const string str)
{
	shared_ptr<char> buf(strdup(str.c_str()));
	char * p_buf = buf.get();

	throw_null(p_buf);

	xml_document<> doc;
	doc.parse<0>(p_buf);
	xml_node<> * root = doc.first_node();
	CXML tree(root->name());

	function<void(CXML & elem, xml_node<> * node)>
		unpack = [ & unpack ](CXML & elem, xml_node<> * node)
	{
		xml_node<> * next = node->first_node();

		if(next && ! string(next->name()).empty())
			for(; next; next = next->next_sibling())
				unpack(elem.append(next->name()), next);
		else
			elem.value = next->value();
	};

	unpack(tree, root);

	return tree;
}

