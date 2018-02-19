#My standard macros
EXEC = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic
FILE = -g -std=c++11 -pthread -O2 -Wall -Wextra -Wundef -pedantic -c

#Compile
all: telnetserv telnetcli

telnetserv: telnetserv.cpp
	g++ $(EXEC) serEx.cpp -o telnetserv

telnetcli: telnetcli.cpp
	g++ $(EXEC) cliEx.cpp -o telnetcli

#git
git:
	git add *
	git commit -m "Testing"
	git push origin master

#Test
test: all
	./telnetserv 8080
	./telnetcli 198.255.145.243 8080

#Cleanup
clean:
	rm -rf *.o telnetserv telnetcli

cleaner: clean
	reset
