src = ./src
obj = ./obj
bin = ./bin
install = /usr/bin

virtualfish : main.o fish.o
	g++ $(obj)/main.o $(obj)/fish.o -lcurses -o $(bin)/virtualfish

main.o : main.cpp fish.hpp
	g++ -c $(src)/main.cpp -o $(obj)/main.o -std=c++11 -Wall

fish.o : fish.cpp fish.hpp
	g++ -c $(src)/fish.cpp -o $(obj)/fish.o -std=c++11 -Wall

main.cpp: $(src)/main.cpp

fish.hpp: $(src)/fish.hpp

fish.cpp: $(src)/fish.cpp

install : virtualfish
	cp $(bin)/virtualfish $(install)/virtualfish

clean :
	rm $(obj)/*.o $(bin)/virtualfish