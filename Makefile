__start__: obj __lines_for_space__ obj/MobileObj.o obj/Scene.o obj/Configuration.o obj/xmlinterp.o obj/Client.o obj/LibInterface.o obj/Parser.o obj/Set4LibInterfaces.o obj/Executor.o interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/main.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/MobileObj.o obj/Scene.o obj/Configuration.o obj/LibInterface.o obj/Set4LibInterfaces.o obj/Parser.o obj/xmlinterp.o obj/Executor.o obj/Client.o -ldl -lxerces-c -lpthread

obj/main.o: src/main.cpp inc/Executor.hh inc/Client.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Executor.o: src/Executor.cpp inc/Executor.hh inc/Interp4Command.hh inc/LibInterface.hh\
	inc/Parser.hh inc/Set4LibInterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/Executor.o src/Executor.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh\
	 inc/Interp4Command.hh inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/Parser.o: src/Parser.cpp inc/Parser.hh inc/xmlinterp.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/Parser.o obj/xmlinterp.o  obj/Configuration.o src/Parser.cpp 

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/Client.o: src/Client.cpp inc/Client.hh inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Client.o obj/Scene.o src/Client.cpp 

obj/Scene.o: src/Scene.cpp inc/Scene.hh inc/MobileObj.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o obj/MobileObj.o src/Scene.cpp

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh inc/Scene.hh 
	g++ -c ${CPPFLAGS} -o obj/Configuration.o obj/Scene.o src/Configuration.cpp

obj/MobileObj.o : src/MobileObj.cpp inc/MobileObj.hh
	g++ -c ${CPPFLAGS} -o obj/MobileObj.o src/MobileObj.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
