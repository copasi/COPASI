

#ifndef _Server_h_included_
#define _Server_h_included_

#include <string>

#include "ServerNetwork.h"
#include "Message.h"

/**This is the main GUI class of the Server.
 * The GUI should be built in this class.
 */
class Server
{
protected:
     /**This is the Network Component this Server GUI uses
	 * for sending and receiving messages.
	 */
	 ServerNetwork myServerNetwork;
public:
     /**Constructor to build the Server.
	 * @param p The port number where the host/server is listening.
	 */
	Server(int p);
	/**This method is called by the ServerNetwork whenever
	 * the ServerSocketReader receives a message from the client.
	 * @param msg The message which the server received from the client.
	 */
	void gotMessageFromClient(Message &msg);

private:
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
	{
		cerr << "Server: " << msg << endl;
	}

};


#endif