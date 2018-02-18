#My standard macros
EXEC = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic
FILE = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic -c

#Compile
all: mono

mono: mono.o
	g++ $(EXEC) mono.o -o mono

mono.o: mono.cpp
	g++ $(FILE) mono.cpp -o mono.o

#Test
test: all
	./mono testIn.txt testOut.txt 1

#Cleanup
clean:
	rm -rf *.o mono

cleaner: clean
	reset
