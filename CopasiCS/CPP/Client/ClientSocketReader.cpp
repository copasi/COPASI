/*
 * ClientSocketReader.cpp
 *
 */

#include "Message.h"
#include "ClientSocketReader.h"
#include "ClientNetwork.h"



void *reader_thread_function(void *arg)
{
        int res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (res != 0)
	{
		perror("Thread pthread_setcancelstate failed");
		exit(EXIT_FAILURE);
    	}
	res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	if (res != 0)
	{
        	perror("Thread pthread_setcanceltype failed");
	        exit(EXIT_FAILURE);
	}

	ClientSocketReader *thisPointer = (ClientSocketReader *) arg;
        cerr << endl << endl << "Received Pointer Address 2 " << arg;
	int in = thisPointer->clientNetwork->getSocketFileDescriptor();
        cerr << endl << "Inside Reader::threadfunction...Reading from SocketDescriptor " << in;
	while (true)
	{
		Message msg;
		msg.readObject(in);
        	cerr << endl << "Inside ClientSocketReader::reader_thread_function...Just Read Something";
		cerr<< (void *) thisPointer->clientNetwork;
	        thisPointer->clientNetwork->gotMessageFromServer(msg);
	}
}

void showMessage(string msg)
{
	cerr << "ClientSocketReaderGlobal: " << msg << endl;
}


void ClientSocketReader::start()
{
	int res;
        cerr << endl << endl << "Passed Pointer Address 1.1 " << (void *) this;
	res = pthread_create(&a_thread, NULL, reader_thread_function, (void *) this);
	if (res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	cerr << endl <<"Leaving ClientSocketReader::start";

}

pthread_t ClientSocketReader::getReaderThreadID()
{
        return this->a_thread;
}

void ClientSocketReader::stop()
{
        pthread_cancel(this->a_thread);
}

