/*
 * ServerSocketReader.h
 */

#ifndef _ServerSocketReader_h_included_
#define _ServerSocketReader_h_included_

#include <stdio.h>
#include <pthread.h>
#include <string>
#include <iostream>

class ClientConnection;

/**The Reader class runs as a seperate thread and 
 * informs the ServerManager if the
 * client has sent a message. 
 * It remains blocked on a socket read for most of the time. 
 * It gets unblocked when it recieves a message from the server and calls the 
 * gotMessageFromClient(Message msg) of the ServerNetwork.
 */
class ServerSocketReader
{
protected:
    /**ClientConnection object (containing the socket ID) from where 
     * this Reader will read.
     */
    ClientConnection *connection;
    /**The thread ID of the ServerSocketReader thread.*/
    pthread_t a_thread;

public:
    /**Build the Reader using the ClientConnection object.
     * @param c This is the ClientConnection object 
     * (containing the socket ID) from which this Reader is to be built.
     */
    ServerSocketReader(ClientConnection *c);
    /**Spawns a new ServerSocketReader thread.*/
    void start();
    /**Returns the ID of the ServerSocketReader thread.
     * @return ID of the ServerSocketReader thread.
     */
    pthread_t getReaderThreadID();
    friend void *reader_thread_function(void *arg);
    /**Stops the ServerSocketReader thread.*/
    void stop();

private:
    /**A small function to display messages.
     * @param msg The message string to show.
     */
    void showMessage(string msg)
  	{
            cerr << "ServerSocketReader: " << msg << endl;
  	}
};


/**New Reader thread, gets blocked while reading from the socket.
 * Unblocks when the client sends a message.
 * @param The "this" pointer to the ServerSocketReader object.
 */
void *reader_thread_function(void *arg);

/**A small function to display messages.
 * @param msg The message string to show.
 */
void showMessage(string msg);

#endif
