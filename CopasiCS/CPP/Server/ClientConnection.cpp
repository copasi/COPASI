
#include "ClientConnection.h"
#include "ServerSocketReader.h"


ClientConnection::ClientConnection():serverSocketReader(this)
{
	this->update = FALSE;
    this->readerRunning = FALSE;
}


/**to build a new connection
* @param clientSocket This is the socket which is to be used for communication
* with the client.
* @param m This is the ServerManager object which this connection will
* use for synchronization.
*/
void ClientConnection::setMembersAndStartReader(int clientSocket, ServerManager *m)
{
 	this->clientSocket = clientSocket;
	manager = m;

    	cerr << "Inside ClientConnection::setMembersAndStartReader: Calling SSR" << endl;
	//ServerSocketReader *serverSocketReaderPtr;
        this->startReader();


}

int ClientConnection::getClientSocketFileDescriptor()
{
        return this->clientSocket;
}
void ClientConnection::updateConnection(boolean updateTo)
{
        this->update = updateTo;
}

Message ClientConnection::getMessage()
{
        return this->message;
}

void ClientConnection::setMessage(Message msg)
{
        this->message = msg;
}


boolean ClientConnection::getUpdateStatus()
{
        return this->update;
}

ServerManager* ClientConnection::getManager()
{
        return manager;
}

string ClientConnection::printMessageDetails()
{
        return message.printMessageDetails();
}


void ClientConnection::startReader()
{
	if(this->readerRunning == FALSE)
        {
		serverSocketReader.start();
        	this->readerRunning = TRUE;
        }
}
void ClientConnection::stopReader()
{
 	if(this->readerRunning)
        {
		serverSocketReader.stop();
                this->readerRunning = FALSE;

        }
}

ClientConnection::~ClientConnection()
{
        this->stopReader();
}

