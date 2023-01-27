all: server.out client.out

server.out: Server.o Distance.o InputValidation.o DataBase.o KNN.o DefaultIO.o SocketIO.o UploadCommand.o Command.o SettingsCommand.o DisplayResults.o ClassifyData.o FlowControl.o DownloadResults.o CLI.o
	g++ -o $@ $^ -std=c++11 -pthread

client.out: Client.o Distance.o InputValidation.o DataBase.o KNN.o DefaultIO.o SocketIO.o UploadCommand.o Command.o SettingsCommand.o DisplayResults.o ClassifyData.o FlowControl.o DownloadResults.o CLI.o
	g++ -o $@ $^ -std=c++11 -pthread

%.o: %.cpp
	g++ -c $< -std=c++11 -pthread -o $@

clean:
	rm -f *.o a.out
