package Server;

/*
 * ClientConnection.java
 */

import java.io.*;
import java.net.*;
import java.util.*;
import Common.*;

/**This class maintains the connection information of the client including the
 * socket for communicating with the client.
 * It also has fields which act as a temporary storage space for messages
 * received by the ServerSocketReader.
 */
public class ClientConnection extends Thread
{
	/**The socket which the server reads from and writes to*/
	protected Socket connection;
	/**Manager object used for synchronization 
	 * (The reader unblocks the blocked manager
	 * thread using this object).
	 */
	protected ServerManager manager;
	/**Output Stream obtained from the socket*/
	protected DataOutputStream output;
	/**Input Stream for writing to the socket*/
	protected DataInputStream input;
	/**Temporary place where the "ServerReader" stores its messages read 
	 * from the socket.*/
	protected Message message;
	/**ServerReader updates (sets) this flag when it reads something 
	 * from the socket.
	 * The ServerManager resets this flag when it has taken an action on it.
	 */
	protected boolean update = false;
	
	
	/**Constructor that builds a new connection and starts the 
	 * ServerSocketReader to recieve messages from the client.
	 * @param clientSocket This is the socket which is to be used for communication
	 * with the client.
	 * @param m This is the ServerManager object which this connection will
	 * use for synchronization.
	 */
	public ClientConnection(Socket clientSocket, ServerManager m)
	{
	    connection = clientSocket;
	    manager = m;
		try 
		{
		  	//output = new ObjectOutputStream(connection.getOutputStream());
		  	output = new DataOutputStream(connection.getOutputStream());
		  	showMessage("Got Output Stream..." + output);
		}
		catch (IOException e) 
		{
			showMessage("Exception while getting Output Stream.");
		}
    	try 
    	{
      		showMessage("About to get Input Stream...");
      		//input = new ObjectInputStream(connection.getInputStream());
      		input = new DataInputStream(connection.getInputStream());
      		showMessage("Got Input Stream..." + input);
    	}
    	catch (IOException e) 
    	{
    		showMessage("Exception while getting Input Stream.");
    	}
    	message = new Message();
    	new ServerSocketReader(this);
    	this.start();
	}
    
	/**Null function does nothing.
	 */
	public void run()
	{
	}
	
	/**A small function to display messages.
	 * @param msg The message string to show.
     */
	private void showMessage(String msg)
  	{
  		System.err.println("ClientConnection: " + msg);
  	}
	
}
	