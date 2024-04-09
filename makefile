# you can change the install path with this varibale
install = /usr/local/bin

virtualfish : main.o fish.o
	g++ main.o fish.o -lcurses -o ./virtualfish

main.o : main.cpp fish.hpp
	g++ -c ./src/main.cpp -o main.o -std=c++11 -Wall

fish.o : fish.cpp fish.hpp
	g++ -c ./src/fish.cpp -o fish.o -std=c++11 -Wall

main.cpp : ./src/main.cpp

fish.hpp : ./src/fish.hpp

fish.cpp : ./src/fish.cpp

install : virtualfish
	cp ./virtualfish $(install)/virtualfish

clean :
	rm ./*.o ./virtualfish
