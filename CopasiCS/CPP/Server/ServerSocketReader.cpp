/*
 * ServerSocketReader.cpp
 */

#include <unistd.h>
#include "ServerSocketReader.h"

#include "ClientConnection.h"
#include "ServerManager.h"
#include "Message.h"




/**Build the reader using the ClientConnection object.
* @param c This is the ClientConnection object
* (containing the socket) from which this Reader is to be built.
*/
ServerSocketReader::ServerSocketReader(ClientConnection *c)
{
	connection = c;
}


void ServerSocketReader::start()
{
        cerr << "Inside ServerSocketReader::start" << endl;
	int res;

	res = pthread_create(&this->a_thread, NULL, reader_thread_function, (void *) this);
        if (res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
        //cerr << endl <<"Leaving ServerSocketReader::start";

}






/**New thread which gets blocked while reading the socket. As soon as the client writes
* anything on its socket this thread gets unblocked and notifies the manager.
*/
//public synchronized void run()
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


	ServerSocketReader *thisPointer = (ServerSocketReader *) arg;
	int in = thisPointer->connection->getClientSocketFileDescriptor();
       	cerr << "Inside Reader Thread Function: Reading FD: " << in << endl;


	while (TRUE)
 	{
		Message msg;
		msg.readObject(in);
		showMessage("Just Read Something...");

		sleep(5);

                thisPointer->connection->updateConnection(TRUE);
                thisPointer->connection->setMessage(msg);
        	thisPointer->connection->getManager()->notify();


	}

}

pthread_t ServerSocketReader::getReaderThreadID()
{
        return this->a_thread;
}

void ServerSocketReader::stop()
{
        pthread_cancel(this->a_thread);
}
void showMessage(string msg)
{
  	cerr << "ServerSocketReader: " << msg << endl ;
}

