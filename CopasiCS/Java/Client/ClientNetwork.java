package Client;

/*
 * ClientNetwork.java
 */

import java.io.*;
import java.net.*;
import Common.*;

/**This class is the Network component used by the server GUI
 * to communicate with the client. It uses sendMessageToClient(Message)
 * to send a message to the client. It calls gotMessageFromClient(Message)
 * of its "Server" (GUI Component) when a message is recieved
 * by its reader
 */
public class ClientNetwork 
{
	
	/**This it the GUI Client of this network component*/
	protected Client myClient;
	
	/**This is the Socket the client will use to communicate with the server*/
	protected Socket socket;
	/**A new thread which is created to read messages sent from the server.
	 * Remains blocked most of the time on a socket read call. Gets unblocked
	 * on recieving a message.
	 */
	protected ClientSocketReader reader; 
	
	/**Writes messages to be sent to the server on the socket.*/
	protected ClientSocketWriter writer;
	
	/**Constructor taking the host to connect to and the port number
	* @param host The name (or IP) of the server to connect to.
	* @param port The port number on which the server is listening.
	*/
	public ClientNetwork(Client myClient, String host, int port) 
	{
		this.myClient = myClient;
		try
		{
			socket = new Socket(host, port);
			reader = new ClientSocketReader(this);
			writer = new ClientSocketWriter(this);
			showMessage("About to start Reader...");
			reader.start();
			//writer.start();
    	}
    	catch (UnknownHostException uhe)
    	{
    		showMessage("The host: " + host + " was not found...Quitting now.");
    		System.exit(1);
    	}
    	catch (IOException e) 
    	{
      		System.err.println(e);
      		System.exit(1);
    	}
	}
	
	
	/**Method to call when the Client needs to send message a message 
	 * to the server.
	 * @param msg The message that is to be sent to the server by the Client.
	 */
	public void sendMessageToServer(Message msg)
	{
		this.writer.writeMessageToServer(msg);		
	}
	
	/**Method that is called by the Reader when it recieves a message
	 * from the server. This method in turn calls the Client (GUI Component) 
	 * version of this method.
	 * @param The message recieved from the server.
	 */
	public void gotMessageFromServer(Message msg)
	{
		this.myClient.gotMessageFromServer(msg);
	}

	
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private static void showMessage(String msg)
	{
		System.err.println("ClientNetwork: " + msg);
	}
	
}
	