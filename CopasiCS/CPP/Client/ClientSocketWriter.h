
/*
 * ClientSocketWriter.h
 *
 */

#ifndef _ClientSocketWriter_h_included_
#define _ClientSocketWriter_h_included_


#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string>

#include "Message.h"

class ClientNetwork;

/**Writes messages to be sent to the server on the socket.
 */
class ClientSocketWriter
{
protected:
	/**The ClientNetwork whose writer this component is.*/
	ClientNetwork *clientNetwork;

private:
	/**A thread ID*/
	pthread_t a_thread;

public:
	/**Writer constructor
	* @param cn The ClientNetwork class to which this thread belongs.
	*/
	ClientSocketWriter(ClientNetwork *cn)
	{
	    	clientNetwork = cn;
                //writer_thread_function_ptr = &ClientSocketWriter::thread_function;
  	}

	 /**Spawns a new thread*/
	void start();
	friend void *writer_thread_function(void *arg);
	/**Function to get the Thread ID.
	* @return The ID of the writer thread
	*/
	pthread_t getWriterThreadID();
        /**Writes a message to the socket so that it is sent to the server.*/
	void writeMessageToServer(Message &msg);
       	/**Stops the thread*/
	void stop();



 private:
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
  	{
  		cerr << "ClientSocketWriter: " << msg << endl;
  	}



};

/**This function is run as a new thread if start() is called. 
 * Reads message from the Keyboard (in a new thread) and sends this message to the server.
 * @param arg The "this" pointer to the ClientSocketWriter object.
 */
void *writer_thread_function(void *arg);

#endif