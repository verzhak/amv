
MIPS_DNAME = /home/amv/trash/mips/
BASE_DNAME = $(MIPS_DNAME)/CodeSourcery/Sourcery_CodeBench_Lite_for_MIPS_GNU_Linux/
BIN_BASE = $(BASE_DNAME)/bin
SDK_BASE = $(MIPS_DNAME)/work/
BROOT = $(SDK_BASE)/build_root

CC = $(BIN_BASE)/mips-linux-gnu-gcc
CXXC = $(BIN_BASE)/mips-linux-gnu-g++
LD = $(BIN_BASE)/mips-linux-gnu-gcc
AR = $(BIN_BASE)/mips-linux-gnu-ar

CFLAGS = -Wall -march=xlp -O3 -mplt -std=c++11 -shared -fPIC -DIS_BUILD
LDFLAGS = -L$(BROOT)/usr/lib/ -lm -lamv -liconv
INCLUDE_DIRS = \
	-Wno-poison-system-directories\
	-I. -I$(BROOT)/usr/include/ -I$(BROOT)/usr/include/libdrm/
SRC = \
	base.cpp debug.cpp xml/xml.cpp image/image.cpp file/file.cpp

PREFIX = $(BROOT)/usr/
BUILD_DIR = build/
OUTPUT_FNAME = libamv.so

release: clean

	mkdir -p $(BUILD_DIR)

	$(CXXC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC) $(LDFLAGS) -o $(BUILD_DIR)/$(OUTPUT_FNAME)

install: release

	cp $(BUILD_DIR)/$(OUTPUT_FNAME) $(PREFIX)/lib

	mkdir -p $(PREFIX)/include/amv
	mkdir -p $(PREFIX)/include/amv/xml
	mkdir -p $(PREFIX)/include/amv/image
	mkdir -p $(PREFIX)/include/amv/file

	cp amv.hpp base.hpp exception.hpp debug.hpp $(PREFIX)/include/amv
	cp xml/xml.hpp $(PREFIX)/include/amv/xml
	cp image/image.hpp $(PREFIX)/include/amv/image
	cp file/file.hpp $(PREFIX)/include/amv/file

clean:

	rm -f $(OUTPUT_FNAME)

