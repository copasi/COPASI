all: Client

# Which compiler
CC = g++

# Where are include files kept
INCLUDE = .

# Options for development
CFLAGS = -g -Wall -ansi

# Options for release
# CFLAGS = -O -Wall -ansi


Client: Client.o ClientNetwork.o ClientSocketReader.o\
	ClientSocketWriter.o Message.o
	$(CC) -o Client Client.o ClientNetwork.o ClientSocketReader.o\
		 ClientSocketWriter.o Message.o -lpthread

Client.o: Client.cpp\
	  ClientNetwork.h\
	  Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Client.cpp

ClientNetwork.o:\
			ClientNetwork.cpp\
			Client.h\
			ClientSocketReader.h\
			ClientSocketWriter.h\
			Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ClientNetwork.cpp


ClientSocketReader.o:\
			ClientSocketReader.cpp\
			ClientNetwork.h\
			Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ClientSocketReader.cpp



ClientSocketWriter.o:\
			ClientSocketWriter.cpp\
			ClientNetwork.h\
			Message.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ClientSocketWriter.cpp

Message.o:\
		Message.cpp\
		Constants.h\
                Mutex.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Message.cpp

