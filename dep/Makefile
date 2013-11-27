CPP_FILES := $(wildcard *.cpp)
H_FILES := $(wildcard *.h)
CC := clang++

.PHONE : clean all

all : $(CPP_FILES) $(H_FILES)
	for cpp in $(CPP_FILES); do \
		$(CC) -DENABLE_BINRELOC -c $$cpp; \
	done
clean :
	rm -rf *.o 
