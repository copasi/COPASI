/*
 * ServerManager.h
 */


#ifndef _ServerManager_h_included_
#define _ServerManager_h_included_


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "ClientConnection.h"
#include "Message.h"
//#include "ServerNetwork.h"

class ServerNetwork;

/**This class runs as a separate thread and remains blocked most of the time.
 * The ServerSocketReader informs this class when it reads a message from 
 * the client. On such a notification, this thread then calls 
 * gotMessageFromClient(Message msg) of the ServerNetwork class.
 */
class ServerManager
{
	
protected:
	
    /**ServerNetwork object which this ServerManager object will manage.*/
    ServerNetwork *serverNetwork;

    /**Needed for synchronization with the ServerSocketReader. ServerSocketReader
     * notifies the manager on recieving a message.
     */
    sem_t bin_sem;
    /**The thread ID for the manager thread.*/
    pthread_t a_thread;

public:
    /**Constructor taking ServerNetwork object
     * @param sn ServerNetwork object to use to build the Manager
     */
    ServerManager(ServerNetwork *s);
    //void setMembersAndStartManager(ServerNetwork sn, sem_t bin_sem);
	
    /**Spawns a new ServerManager Thread.*/
    void start();
    /**When this method is called the manager gets unblocked from its wait position.
     * Used by ServerSocketReader to notify the manager.
     */
    void notify();
    /**Used to put the ServerManager thread in the wait position.*/
    void wait();
    /***/
    friend void *manager_thread_function(void *arg);
    ClientConnection* getClientConnection();
    /**Stops the ServerManager Thread.*/
    void stop();
	
    /**Destructor. Destroys the semaphore that was created during construction.*/
    ~ServerManager();

private:
    /**A small function to display messages.
     * @param msg The message string to show.
     */
    void showMessage(string msg)
  	{
            cerr << "ServerManager: "  << msg;
  	}
};

/**New Manager thread, blocks itself to start with.
 * Unblocks when the ServerReader notifies it. 
 * @param The "this" pointer to the ServerManager object.
 */
void *manager_thread_function(void *arg);

#endif
