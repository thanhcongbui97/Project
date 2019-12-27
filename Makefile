CC = g++ -std=c++11 -pthread
CFLAGS = -g -Wall
OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

all: server client

client: src/cli.cpp video.cpp
	$(CC) $(CFLAGS) -o client src/cli.cpp video.cpp $(LIBS)

server: src/srv.cpp
	$(CC) $(CFLAGS) -o server src/srv.cpp  $(LIBS) -lpthread
clean:
	rm -f *.o 
test: test.cpp
	g++ test.cpp -o test `pkg-config opencv4 --cflags --libs`

