/*
 * ClientNetwork.CPP
 *
 */

#include "Message.h"
#include "ClientNetwork.h"
#include "Client.h"


ClientNetwork::ClientNetwork(Client *myClient, string host, int port): reader(this), writer(this)
{

    this->myClient = myClient;
    /*  Create a socket for the client.  */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    cout << endl << "Got Socket FileDiscriptor " << sockfd;

    /*  Name the socket, as agreed with the server.  */
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host.c_str());
    //address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //address.sin_port = htons(9734);
    address.sin_port = htons(port);

    int len;
    len = sizeof(address);

    /*  Now connect our socket to the server's socket.  */
    int result;
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1)
    {
        this->showMessage("Cannot connect to the server.");
        exit(EXIT_FAILURE);
    }

    /*Note that the reader and writer objects have already been initialized
      in the "Initializer List" of the constructor*/
    reader.start();
    //writer.start();
}


int ClientNetwork::getSocketFileDescriptor()
{
    return this->sockfd;
}

void ClientNetwork::sendMessageToServer(Message &msg)
{
    writer.writeMessageToServer(msg);
}

void ClientNetwork::gotMessageFromServer(Message &msg)
{
    showMessage("Inside ClientNetwork::gotMessageFromServer");
    cerr << (void *) myClient;
    this->myClient->gotMessageFromServer(msg);
}

ClientNetwork::~ClientNetwork()
{
    reader.stop();
    //writer.stop();
}

