all:clienet.c add1.c main_server.c
	gcc -g clienet.c add1.c -lpthread -o cli
	gcc -g main_server.c add1.c -lpthread -o serv
