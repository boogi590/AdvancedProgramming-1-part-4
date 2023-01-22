all: server.out client.out

server.out: Server.o Distance.o InputValidation.o DataBase.o KNN.o DefaultIO.o SocketIO.o UploadCommand.o Command.o
	g++ -o $@ $^ -std=c++11

client.out: Client.o Distance.o InputValidation.o DataBase.o KNN.o DefaultIO.o SocketIO.o UploadCommand.o Command.o
	g++ -o $@ $^ -std=c++11

%.o: %.cpp
	g++ -c $< -std=c++11 -o $@

clean:
	rm -f *.o a.out
