/*
 * ServerNetwork.h
 */


#ifndef _ServerNetwork_h_included_
#define _ServerNetwork_h_included_

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>

#include "Message.h"
#include "ClientConnection.h"
#include "ServerManager.h"

class Server;

/**This class is the Network component used by the server GUI
 * to communicate with the client. It uses sendMessageToClient(Message)
 * to send a message to the client. It calls gotMessageFromClient(Message)
 * of its "Server" (GUI Component) when a message is recieved
 * by its reader
 */
class ServerNetwork
{
protected:
	/**The Server UI for this Network component*/
    Server *myServer;
	/**Port on which the server listens*/
	int port;
	/**This is server socket file descriptor to accept new clients*/
	int server_sockfd;
	/**Connection object which contains the socket ID to communicate with the client*/
	ClientConnection clientConnection;
	/**This thread listens for any updates and takes action accordingly*/
	ServerManager serverManager;
	
	/** Accepts a new client.*/
	void acceptClient();
 
public:
 	
    /** Constructor for running the server so that it listens on port p
	* and runs on directory d
	* @param myServer The (GUI) Server of this Network Component.
	* @param p The port on which to listen for a new client.
	*/
    ServerNetwork(Server *myServer, int p);
        
	/**Method for accessing the connection object contained by this 
	 * ServerNetwork object
	 * @return Pointer to the ClientConnection object contained by this 
	 * ServerNetwork object.
	 */
	ClientConnection* getClientConnection();
    /**Method that is called by the ServerManager when the ServerSocketReader 
	 * recieves a message from the server. 
	 * This method in turn calls the Server (GUI Component) version of this method.
	 * @param The message recieved from the client.
	 */
	void gotMessageFromClient(Message &msg);
	
	/**Method to call when the server needs to send a message 
	 * to the client.
	 * @param msg The message that is to be sent to the server by the client.
	 */
	void sendMessageToClient(Message &msg);

	/**Destructor. Stops the Manager thread.*/
	~ServerNetwork();


	//void start();

};

/**Method to show error Messages which terminates the application
 * after showing the message.
 * @param message The error message which is to be displayed.
 */
void error(string message);

/**Method to show warning Messages which does not terminate the application 
 * after showing the message.
 * @param message The warning message which is to be displayed.
 */
void warning(string message);

#endif



