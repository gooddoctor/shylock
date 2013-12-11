CC=i686-w64-mingw32-c++
CXX=i686-w64-mingw32-c++

CXXFLAGS=-mthreads -DHAVE_W32API_H -D__WXMSW__ -DNDEBUG -D_UNICODE 
CXXFLAGS+=-I../wxWidgets-2.9.5/lib/gcc_dll/mswu 
CXXFLAGS+=-I../wxWidgets-2.9.5/include -DWXUSINGDLL -Wno-ctor-dtor-privacy -pipe 
CXXFLAGS+=-fmessage-length=0  -fno-keep-inline-dllexport
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
