all: server.out client.out

server.out:
	g++ -pthread server.cpp CLI.cpp SocketIO.cpp Command.cpp Utills.cpp KNN.cpp Calculator.cpp -o server.out

client.out:
	g++ -std=c++11 client.cpp SocketIO.cpp -o client.out

clean:
	rm *.out
