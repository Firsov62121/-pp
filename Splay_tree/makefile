all:
	g++ -o main -lstdc++ -Wall -ggdb3 main.cpp
valgrind:
	valgrind --leak-check=full --track-origins=yes ./main
final:
	g++ main.cpp -o main -O3
start:
	./main