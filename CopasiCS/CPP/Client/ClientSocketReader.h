/*
 * ClientSocketReader.h
 *
 */

#ifndef _ClientSocketReader_h_included_
#define _ClientSocketReader_h_included_


#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string>

class ClientNetwork;

/**The Reader class runs as a seperate thread and informs the ClientNetwork if the
 * server has sent a message. It remains blocked on a socket read for most of the time.
 * It gets unblocked when it recieves a message from the server and calls the
 * gotMessageFromServer(Message msg) of the ClientNetwork.
 */
class ClientSocketReader
{
protected:
 	/**The clientNetwork whose reader this thread is.*/
	ClientNetwork *clientNetwork;

private:
	/**A thread ID*/
	pthread_t a_thread;

public:
	/**The constructor
	* @param c The ClientNetwork whose reader this thread is.
	*/
	ClientSocketReader(ClientNetwork *c)
	{
		this->clientNetwork = c;
	}

    /**Spawns a new thread*/
	void start();
    friend void *reader_thread_function(void *arg);
    /**Function to get the Thread ID.
	* @return The ID of the reader thread
	*/
	pthread_t getReaderThreadID();

	/**Stops the thread*/
	void stop();


private:

	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
  	{
  		cerr << "ClientSocketReader: " << msg << endl;
  	}

};


/**New Reader thread, gets blocked while reading from the socket.
 * Unblocks when the server sends a message.
 * @param The "this" pointer to the ClientSocketReader object.
 */
void *reader_thread_function(void *arg);

/**A small function to display messages.
 * @param msg The message string to show.
 */
void showMessage(string msg);

#endif