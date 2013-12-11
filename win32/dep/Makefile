CPP_FILES := $(wildcard *.cpp)
H_FILES := $(wildcard *.h)
CC=i686-w64-mingw32-c++
CXX=i686-w64-mingw32-c++

.PHONE : clean all

all : $(CPP_FILES) $(H_FILES)
	for cpp in $(CPP_FILES); do \
		$(CC) -c $$cpp; \
	done
clean :
	rm -rf *.o 
