GCC = g++
objs := main.o listCopy.o myTestFuncs.o
debugFlags = -O0 -Wall -ggdb3
releaseFlags = -O3

all: debug

valgrind:
	valgrind --leak-check=full --track-origins=yes ./main

release: $(objs)
	$(GCC) -o main $(objs) $(releaseFlags)

debug: $(objs)
	$(GCC) -o main $(objs) $(debugFlags)

%.o: %.cpp
	$(GCC) $(debugFlags) -c -o $@ $<

.PHONY : clean

clean:
	@rm -f $(objs) main