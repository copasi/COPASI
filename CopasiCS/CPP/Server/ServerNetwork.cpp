/*
 * ServerNetwork.cpp
 */

#include <sys/types.h>
#include <sys/socket.h>
#include "Server.h"
#include "ServerNetwork.h"


/**
* Constructor for running the server so that it listens on port p
* and runs on directory d
* @param p The port on which to listen for a new client.
*/
ServerNetwork::ServerNetwork(Server *myServer, int p):serverManager(this)
{
    this->myServer = myServer;
    port = p;
	

    socklen_t server_len;
    struct sockaddr_in server_address;
    /*  Remove any old socket and create an unnamed socket for the server.  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /*  Name the socket.  */

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    /*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 1);
    //The second parameter is the maximum no of connections at one time.


    //serverManager = new ServerManager(this);
    serverManager.start();
    this->acceptClient();
    //this->start();
}


void ServerNetwork::acceptClient()
{
    /*  Accept a connection.  */
    int clientSocket;
    struct sockaddr_in client_address;
    socklen_t client_len;
    client_len = sizeof(client_address);
    cerr << "Main Thread: About to accept connection" << endl;
    clientSocket = accept(server_sockfd,
                          (struct sockaddr *)&client_address, &client_len);

    //cerr << "Accepted connection: " << clientSocket << "Now going to start reader" << endl;
    clientConnection.setMembersAndStartReader(clientSocket, &this->serverManager);
    cerr << "Accepted connection:" << clientConnection.getClientSocketFileDescriptor();

}


void ServerNetwork::gotMessageFromClient(Message &msg)
{
    this->myServer->gotMessageFromClient(msg);
}

void ServerNetwork::sendMessageToClient(Message &msg)
{
    msg.writeObject(this->clientConnection.getClientSocketFileDescriptor());
}



ClientConnection* ServerNetwork::getClientConnection()
{
    return &this->clientConnection;
}


ServerNetwork::~ServerNetwork()
{
    serverManager.stop();
}
