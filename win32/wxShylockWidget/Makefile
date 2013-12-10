CC=clang++
CXX=clang++

CXXFLAGS=$(shell wx-config --cppflags)
CXXFLAGS+=-I/home/gooddocteur/Programs/include
CXXFLAGS+=-std=c++11

CPP_FILES := $(wildcard *.cpp)
H_FILES := $(wildcard *.h)

.PHONE : clean all

all : $(CPP_FILES) $(H_FILES)
	for cpp in $(CPP_FILES); do \
		$(CC) $(CXXFLAGS) -c $$cpp; \
	done

clean :
	rm -rf *.o
