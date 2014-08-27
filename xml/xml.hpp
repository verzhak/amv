
#ifndef AMV_XML_HPP
#define AMV_XML_HPP

#include <map>
#include <string>
#include <sstream>
#include <cstdlib>

class CXML
{
	std::map<std::string, CXML> childs;

	CXML & append(const std::string ind);
	void add(CXML & node, const CXML & add_node);

	#ifdef IS_BUILD
			
		void pack(xml_document<> & doc, xml_node<> * node) const;

	#endif

	public:

		std::string tag, value;

		CXML();
		CXML(const std::string __tag);

		CXML operator+(const CXML & op);
		CXML & operator[](const std::string ind);
		CXML & get(const std::string ind);
		std::string pack() const;

		inline void operator=(const std::string __value) { value = __value; };
		inline void operator=(const unsigned __value) { set<unsigned>(__value); };
		inline void operator=(const double __value) { set<double>(__value); };
		inline unsigned uint() const { return std::atoi(value.c_str()); };
		inline double real() const { return std::atof(value.c_str()); };
		inline bool exist(const std::string ind) const { return childs.find(ind) != childs.end(); };

		static CXML load_from_file(const std::string fname);
		static CXML load_from_string(const std::string str);

		template<typename tp>
		void set(const tp __value)
		{
			std::stringstream stream;

			stream << __value;
			value = stream.str();
		};
};

#endif

