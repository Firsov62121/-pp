GCC = g++
objs := main.o destination.o audit.o cargo_vessel.o NavalFreightCompany.o passenger_vessel.o ship_properties.o vessel.o
debugFlags = -O0 -lstdc++ -Wall -ggdb3 
releaseFlags = -O3

all: debug

valgrind:
	valgrind --leak-check=full --track-origins=yes ./main

release: $(objs)
	$(GCC) -o main $(releaseFlags) $(objs)

debug: $(objs)
	$(GCC) -o main $(debugFlags) $(objs)

%.o: %.cpp
	$(GCC) $(debugFlags) -c -o $@ $<

.PHONY : clean

clean:
	@rm -f $(objs) valgrindBuild main