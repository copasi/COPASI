/*
 * ClientSocketWriter.cpp
 *
 */

#include "Message.h"
#include "ClientSocketWriter.h"
#include "ClientNetwork.h"

/** Writer thread. Reads from the keyboard and writes whatever its read
to the socket.	*/


//public void run()
void *writer_thread_function(void *arg)
{
	int res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (res != 0)
	{
		perror("ClientSocketWriter Thread pthread_setcancelstate failed");
		exit(EXIT_FAILURE);
    	}
	res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	if (res != 0)
	{
        	perror("ClientSocketWriter pthread_setcanceltype failed");
	        exit(EXIT_FAILURE);
	}


	ClientSocketWriter *thisPointer = (ClientSocketWriter *) arg;
	int output = thisPointer->clientNetwork->getSocketFileDescriptor();
        cerr << endl << "Inside ClientSocketWriter::writer_thread_function. Recieved FD: " << output;

	//BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
	while (true)
	{
                sleep(2);
		Message msg;
		msg.readMessageFromKeyboard();
		cerr << "Sending the following message read from Keyboard..." << endl;
                showMessage(msg.printMessageDetails());
                write(output, &msg, sizeof(msg));
                sleep(3);
        }

}



void ClientSocketWriter::start()
{
        int res;

	res = pthread_create(&a_thread, NULL, writer_thread_function, (void *)this);
	if (res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
        cerr << endl << "Leaving ClientSocketWriter::start()";

}


pthread_t ClientSocketWriter::getWriterThreadID()
{
	return this->a_thread;
}



void ClientSocketWriter::writeMessageToServer(Message &msg)
{
      int output = clientNetwork->getSocketFileDescriptor();
      msg.writeObject(output);
      //write(output, &msg, sizeof(msg));
}


void ClientSocketWriter::stop()
{
 	pthread_cancel(this->a_thread);
}





