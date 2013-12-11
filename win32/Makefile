CC=i686-w64-mingw32-c++
CXX=i686-w64-mingw32-c++

CXXFLAGS=-mthreads -DHAVE_W32API_H -D__WXMSW__ -DNDEBUG -D_UNICODE -IwxWidgets-2.9.5/lib/gcc_dll/mswu 
CXXFLAGS+=-IwxWidgets-2.9.5/include  -Wno-ctor-dtor-privacy -pipe 
CXXFLAGS+=-fmessage-length=0  -fno-keep-inline-dllexport
CXXFLAGS+=-I/home/gooddocteur/Programs/include
CXXFLAGS+=-std=c++11
CXXFLAGS+=-fpermissive


LIBS=-L/usr/i686-w64-mingw32/sys-root/mingw/lib/
LIBS+=-lwx_baseu-2.8-i686-w64-mingw32
LIBS+=-lwx_baseu_net-2.8-i686-w64-mingw32
LIBS+=-lwx_baseu_xml-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_adv-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_aui-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_core-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_html-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_qa-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_richtext-2.8-i686-w64-mingw32
LIBS+=-lwx_mswu_xrc-2.8-i686-w64-mingw32
LIBS+=-lwxregexu-2.8-i686-w64-mingw32
LIBS+=-static-libgcc -static-libstdc++
LIBS+=-L.	
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




