# This makefile only makes the unit test, benchmark and pngdetail and showpng
# utilities. It does not make the PNG codec itself as shared or static library.
# That is because:
# LodePNG itself has only 1 source file (lodepng.cpp, can be renamed to
# lodepng.c) and is intended to be included as source file in other projects and
# their build system directly.


CC ?= gcc
CXX ?= g++

NAME := lodepng.a

override CFLAGS := -W -Wall -Wextra -ansi -pedantic -O3 -Wno-unused-function $(CFLAGS)
override CXXFLAGS := -W -Wall -Wextra -ansi -pedantic -O3 $(CXXFLAGS)

all: $(NAME)

$(NAME): lodepng.o
	$(AR) rcs $@ $^

loadpng.o: loadpng.cpp lodepng.h
	$(CXX) -I ./ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f lodepng.o $(NAME)
