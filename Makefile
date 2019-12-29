CC = g++ -std=c++11 -pthread
CFLAGS = -g -Wall
OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)
INC = inc/addr.h

all: server client

client: client.c video.cpp $(INC)
	$(CC) $(CFLAGS) $^ -o client $(LIBS)

server: server.c $(INC)
	gcc $^ -pthread -o server

test: test_client.c test_server.c
	gcc us.c -o us
	gcc uc.c -o uc	

test_client: test_client.c video.cpp $(INC)
	$(CC) $(CFLAGS) $^ -o client $(LIBS)

test_server: test_server.c $(INC)
	gcc $^ -pthread -o server
clean:
	rm client server 
