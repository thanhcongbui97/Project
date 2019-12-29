CC = g++ -std=c++11 -pthread
CFLAGS = -g -Wall
OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

all: server client

client: client.c video.cpp
	$(CC) $(CFLAGS) -o client client.c video.cpp $(LIBS)

server: server.c
	gcc server.c -o server
test:
	gcc us.c -o us
	gcc uc.c -o uc	
clean:
	rm client server 
