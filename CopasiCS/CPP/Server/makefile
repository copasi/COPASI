all: Server

# Which compiler
CC = g++

# Where are include files kept
INCLUDE = .

# Options for development
CFLAGS = -g -Wall -ansi

# Options for release
# CFLAGS = -O -Wall -ansi


Server: Server.o ServerNetwork.o ServerSocketReader.o ServerManager.o ClientConnection.o Message.o
	$(CC) -o Server Server.o ServerNetwork.o ServerSocketReader.o ServerManager.o \
					ClientConnection.o Message.o -lpthread


Server.o:\
			Server.cpp\
			ServerNetwork.h\
			Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Server.cpp


ServerNetwork.o:\
			ServerNetwork.cpp\
                        ClientConnection.h\
			ServerManager.h\
                        Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ServerNetwork.cpp


ServerSocketReader.o:\
			ServerSocketReader.cpp\
			ServerManager.h\
			ClientConnection.h\
			Message.h

	$(CC) -I$(INCLUDE) $(CFLAGS) -c ServerSocketReader.cpp



ServerManager.o:\
			ServerManager.cpp\
			ClientConnection.h\
                        ServerNetwork.h

	$(CC) -I$(INCLUDE) $(CFLAGS) -c ServerManager.cpp


ClientConnection.o:\
			ClientConnection.cpp\
			ServerSocketReader.h\
                        Message.h

	$(CC) -I$(INCLUDE) $(CFLAGS) -c ClientConnection.cpp


Message.o:\
		Message.cpp\
		Constants.h\
                Mutex.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Message.cpp

