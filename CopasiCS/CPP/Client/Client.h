

#ifndef _Client_h_included_
#define _Client_h_included_

#include <string>

#include "ClientNetwork.h"
#include "Message.h"

/**This is the main GUI class of the Client.
 * The GUI should be built in this class.
 */
class Client
{
protected:
 	/**This is the Network Component this Client GUI uses
	 * for sending and receiving messages.
	 */
	ClientNetwork myClientNetwork;
public:
	/**Constructor to build the Client.
	 * @param host The host which this client needs to connect to.
	 * @param port The port number where the host/server is listening.
	 */
	Client(string host, int port);

 	/**This method is called by the ClientNetwork whenever
	 * the ClientSocketReader receives a message from the server.
	 * @param msg The message which the client received from the server.
	 */
	void gotMessageFromServer(Message msg);

private:
 	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
	{
		cerr << "Client: " << msg << endl;
	}

};


#endif