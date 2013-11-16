CC=clang++
CXX=clang++

CXXFLAGS=$(shell wx-config --cppflags)
CXXFLAGS+=-I/home/gooddocteur/Programs/include
CXXFLAGS+=-std=c++11

LIBS=$(shell wx-config --libs)
LIBS+=-lX11

PRG=shylock
OBJ=window.o engine.o

$(PRG): $(OBJ) wxShylockWidget
	$(MAKE) -w -C wxShylockWidget
	$(CC) $(OBJ) wxShylockWidget/*.o $(LIBS) -o $@ 

window.o: window.h  engine.o

engine.o: engine.h

.PHONE : clean find run

find:
	find -name '*.cpp' -or -name '*.c' -or -name '*.h' | xargs grep -n -H $(NAME) --color=auto
run:
	./$(PRG)
clean:
	rm -rf $(OBJ) $(PRG)
	$(MAKE) clean -w -C wxShylockWidget




