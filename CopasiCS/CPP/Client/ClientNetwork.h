/*
 * ClientNetwork.h
 *
 */


#ifndef _ClientNetwork_h_included_
#define _ClientNetwork_h_included_

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>


#include "ClientSocketReader.h"
#include "ClientSocketWriter.h"
#include "Message.h"


class ClientSocketReader;
class ClientSocketWriter;
class Client;

/**This class is the Network component used by the client GUI
 * to communicate with the server. It uses sendMessageToServer(Message)
 * to send a message to the server. It calls gotMessageFromServer(Message)
 * of its "Client" (GUI Component) when a message is recieved
 * by its reader
 */
class ClientNetwork
{

protected:
	/**This it the GUI Client of this network component*/
	Client *myClient;
	
	/**This is the Socket the client will use to communicate with the server*/
	int sockfd;

	/**A new thread which is created to read messages sent from the server.
	 * Remains blocked most of the time on a socket read call. Gets unblocked
	 * on recieving a message.
	 */
	ClientSocketReader reader;
	
	/**Writes messages to be sent to the server on the socket.*/
	ClientSocketWriter writer;



public:
	/**Constructor taking the host to connect to and the port number
	* @param host The name (or IP) of the server to connect to.
	* @param port The port number on which the server is listening.
	*/
	ClientNetwork(Client *myClient, string host, int port);

    /**A method to get the Descriptor of the socket of this network component
	* @return value of descriptor of the socket being used for communication with
	* the server
	*/
	int getSocketFileDescriptor();

	/**Method to call when the Client needs to send message a message
	 * to the server.
	 * @param msg The message that is to be sent to the server by the Client.
	 */
     void sendMessageToServer(Message &msg);
     /**Method that is called by the Reader when it recieves a message
	 * from the server. This method in turn calls the Client (GUI Component)
	 * version of this method.
	 * @param The message recieved from the server.
	 */
	void gotMessageFromServer(Message &msg);

	/**Destructor. Stops its reader thread.*/
	ClientNetwork::~ClientNetwork();



 private:
 	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
	{
		cerr << "ClientNetwork: " << msg << endl;
	}

};

#endif




