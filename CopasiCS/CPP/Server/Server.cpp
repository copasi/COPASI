
#include "Server.h"
#include "Message.h"

#include <string>


Server::Server(int p):myServerNetwork(this, p)
{
	while(1)
        {
		cerr << "Server Still Runnning..." << endl;
                sleep(20);
        }
}

void Server::gotMessageFromClient(Message &msg)
{
	showMessage("\nMESSAGE RECEIVED FROM THE CLIENT: " + msg.printMessageDetails());
	showMessage("\nSENDING THE MESSAGE BACK TO CLIENT...");
        this->myServerNetwork.sendMessageToClient(msg);
}


/** Main function taking one or two arguments
* @param arg[0] The Port number to listen on.
*/
int main(int argc, char *args[])
{
	int hostPort;
        if (argc < 2 || argc > 2)
        {
        	error("Usage: Server port_number");
        }

	hostPort = atoi(args[1]);
	if (hostPort <= 0 || hostPort > 65535)
	{
		error("Port number out of range (0, 65535): " + hostPort);
	}
        Server server(hostPort);

 }


/**A small function to display errors.
* System exits after showing the error message
* @param msg The message string to show.
*/
void error(string message)
{
	cerr << "Server error: " << message << endl;
	exit(EXIT_FAILURE);
}

/**A small function to display warnings.
 * @param msg The message string to show.
 */
void warning(string message)
{
	cerr << "Server warning: " << message << endl;
}
