/*
 * ClientConnection.h
 */


#ifndef _ClientConnection_h_included_
#define _ClientConnection_h_included_

#include "ServerSocketReader.h"
#include "Message.h"

#define TRUE 1
#define FALSE 0
typedef unsigned int boolean;

class ServerManager;

/**This class maintains the connection information of the client including the
 * socket ID for communicating with the client.
 * It also has fields which act as a temporary storage space for messages
 * received by the ServerSocketReader.
 */
class ClientConnection
{
protected:
	/**The Reader object which this connection will set up 
	 * to start receiving messages from the client.*/
	ServerSocketReader serverSocketReader;
	/**Keeps the status of the Reader (whether reader is running or not.*/
	boolean readerRunning;

	/**The socket ID which the server reads from and writes to*/
	int clientSocket;

	/**Manager object used for synchronization 
	 * (The reader unblocks the blocked manager
	 * thread using this object).
	 */
	ServerManager *manager;

    /**Temporary place where the "ServerReader" stores its messages read 
	 * from the socket.*/
	Message message;
	
	/**ServerReader updates (sets) this flag when it reads something 
	 * from the socket.
	 * The ServerManager resets this flag when it has taken an action on it.
	 */
	boolean update;

private:
	/**Spawns a new ServerSocketReader thread.*/
	void startReader();
    void stopReader();
    
public:

	/**Constructor - initializes its members with default values.*/
	ClientConnection();
	/**Sets its members and starts the 
	 * ServerSocketReader to recieve messages from the client.
	 * @param clientSocket This is the socket ID which is to be used for communication
	 * with the client.
	 * @param m This is the ServerManager object which this connection will
	 * use for synchronization.
	 */
	void setMembersAndStartReader(int clientSocket, ServerManager *m);
    /**Method to get access to the socket file descriptor of the client.
	* @return The socket file descriptor of 
	* the client (contained by this connection object).
	*/
	int getClientSocketFileDescriptor();
	/**Sets or Resets the update flag.
	 * @param updateTo The boolean value to set the flag to.
	 */
	void updateConnection(boolean updateTo);
    /**Returns the status of the update flag.
	 * @return Boolean value of the update flag.
	 */
	boolean getUpdateStatus();
	/**Returns the Message member of this ClientConnection object. 
	 * A new Message is set by the ServerSocketReader when it receives a 
	 * new message from the client.
	 * @return Message member of this ClientConnection object. 
	 */
	Message getMessage();
	/**Sets the Message member of this ClientConnection object.
	 * @param msg The new message which the Message member is to be set to.
	 */
	void setMessage(Message msg);
    
	/**Gives access to the ServerManager object contained by 
	 * this ClientConnection object.
	 * @return Pointer to the ServerManager object contained by 
	 * this ClientConnection object.
	 */
	ServerManager* getManager();
    
	/**Returns a string containing the values of the fields of the Message member
	 * which this ClientConnection object contains.
	 * @return String containing the Message object fields.
	 */
	string printMessageDetails();
    /**Destructor - Checks to see if the Reader thread has been stopped. If not this destructor 
	 * stops the ServerSocketReader thread.
	 */
	~ClientConnection();


};

#endif


