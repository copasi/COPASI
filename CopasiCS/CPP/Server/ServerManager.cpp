/*
 * ServerManager.cpp
 */

#include "ServerManager.h"
#include "ServerNetwork.h"
#include "Message.h"


/**function taking ServerNetwork object and a semaphore.
* @param s to use to build the Manager
*/
/* void setMembersAndStartManager(ServerNetwork *s)
 {
        this->serverNetwork = s;
      	this->start();
 }*/

ServerManager::ServerManager(ServerNetwork *sn)
{
	serverNetwork = sn;
	int res;
	res =  sem_init(&this->bin_sem, 0, 0);
	if (res != 0)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	//this.start();
 }

 void ServerManager::notify()
 {
	sem_post(&this->bin_sem);
 }

 void ServerManager::wait()
 {
	sem_wait(&this->bin_sem);
 }


ClientConnection* ServerManager::getClientConnection()
{
	return this->serverNetwork->getClientConnection();
}


 void ServerManager::start()
 {
        //cerr << endl <<"Inside ServerManager::start";
        int res;
        res = pthread_create(&this->a_thread, NULL, manager_thread_function,
					(void *) this);
        if (res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	//cerr << endl <<"Leaving ServerManager::start";

 }


 /**A new thread which initially gets blocked. When there is an update, the ServerReader
 * unblocks this and this thread takes the appropriate action.
 */

void *manager_thread_function(void *arg)
//public synchronized void run()
{

 	int res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (res != 0)
	{
		perror("ServerManagerThread  pthread_setcancelstate failed");
		exit(EXIT_FAILURE);
    	}
	res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	if (res != 0)
	{
        	perror("ServerManagerThread pthread_setcanceltype failed");
	        exit(EXIT_FAILURE);
	}

	ServerManager *thisPointer = (ServerManager *)arg;
    	while (TRUE)
    	{
        	//this.wait(1000);
          	cerr << "Manager Thread: About to Wait..." << endl;
		thisPointer->wait();
                cerr << "Manager wait over..." << endl;
		//ClientConnection *c = (ClientConnection *)arg;
		ClientConnection *c = thisPointer->getClientConnection();


	        if (c->getUpdateStatus())
	        {
			Message msg = c->getMessage();
			thisPointer->serverNetwork->gotMessageFromClient(msg);
			c->updateConnection(FALSE);
 	        }

   	}
}

/*void ServerManager::sendMessageToClient(Message msg)
{
	cerr << "Writing Message to Client..." << endl;
	msg.writeObject(this->serverNetwork->getClientConnection()->getClientSocketFileDescriptor());
	//write(this->serverNetwork->getClientConnection()->getClientSocketFileDescriptor(), &msg, sizeof(msg));
}
*/


void ServerManager::stop()
{
	pthread_cancel(this->a_thread);
}

ServerManager::~ServerManager()
{
	sem_destroy(&this->bin_sem);
}