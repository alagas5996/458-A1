#My standard macros
EXEC = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic
FILE = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic -c

#Compile
all: telnetserv telnetcli

telnetserv: telnetserv.cpp
	g++ $(EXEC) telnetserv.cpp -o telnetserv

telnetcli: telnetcli.cpp
	g++ $(FILE) telnetcli.cpp -o telnetcli

#Test
test: all
	./telnetserv #<port_number>
	./telnetcli #<server_machine> <server_port>

#Cleanup
clean:
	rm -rf *.o telnetserv telnetcli

cleaner: clean
	reset
