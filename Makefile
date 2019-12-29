CC = g++ -std=c++11 -pthread
CFLAGS = -g -Wall
OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)
INC = inc/addr.h

all: server client

client: client.c video.cpp $(INC)
	$(CC) $(CFLAGS) $^ -o client $(LIBS)

server: server.c $(INC)
	gcc $^ -o server
test:
	gcc us.c -o us
	gcc uc.c -o uc	
clean:
	rm client server 
