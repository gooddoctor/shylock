CC=clang++
CXX=clang++

CXXFLAGS=$(shell wx-config --cppflags)
CXXFLAGS+=-I/home/gooddocteur/Programs/include
CXXFLAGS+=-std=c++11
CXXFLAGS+=-DENABLE_BINRELOC

LIBS=$(shell wx-config --libs)
LIBS+=-lX11
LIBS+=-lboost_date_time

PRG=shylock
OBJ=window.o  main.o data.o

$(PRG): $(OBJ) wxShylockWidget dep
	$(MAKE) -w -C wxShylockWidget
	$(MAKE) -w -C dep
	$(CC) wxShylockWidget/*.o dep/*.o $(OBJ) $(LIBS) -o $@ 

main.o: main.h engine.h

window.o: window.h  engine.h

data.o: data.h engine.h

.PHONE : clean find run deps

deps: 
	$(MAKE) all -w -C dep
find:
	find -name '*.cpp' -or -name '*.c' -or -name '*.h' | xargs grep -n -H $(NAME) --color=auto
run:
	./$(PRG)
clean:
	rm -rf $(OBJ) $(PRG)
	$(MAKE) clean -w -C wxShylockWidget
	$(MAKE) clean -w -C dep




