package Client;

/*
 * ClientSocketReader.java
 */

import java.io.*;
import java.net.*;
import Common.*;
/**The Reader class runs as a seperate thread and informs the ClientNetwork if the
 * server has sent a message. It remains blocked on a socket read for most of the time. 
 * It gets unblocked when it recieves a message from the server and calls the 
 * gotMessageFromServer(Message msg) of the ClientNetwork.
 */
public class ClientSocketReader extends Thread 
{
	/**The ClientNetwork whose reader this thread is.*/
	protected ClientNetwork clientNetwork;

	/**The constructor
	* @param c The ClientNetwork whose reader this thread is.
	*/
	public ClientSocketReader(ClientNetwork cn) 
	{
    	clientNetwork = cn;
  	}

	/**New reader thread, just gets blocked while reading from the socket. 
	 * Unblocks when the server sends a message.*/
	public void run() 
	{
    	try 
    	{
      		showMessage("Getting Instream....");
      		//ObjectInputStream in = new ObjectInputStream(clientNetwork.socket.getInputStream());
      		DataInputStream in = new DataInputStream(clientNetwork.socket.getInputStream());
      		showMessage("Got Instream...." + in.toString());
      		while (true)
      		{
		        Message msg = new Message();
		        try
		        {
		        	//msg = (Message) in.readObject();
		        	msg.readDataObject(in);
		        	
		        }
		    	catch (IOException e) 
	    		{
	    			showMessage("Inside Reader while: An input or output exception occured while reading from socket");
	    			e.printStackTrace();
	    		}
		    	catch(java.lang.ClassNotFoundException cnfe)
		        {
		        	showMessage("A ClassNotFoundException occured. Details...");
		        	cnfe.printStackTrace();
		        }
		        this.clientNetwork.gotMessageFromServer(msg);
			}
    	}
    	catch (IOException e) 
    	{
    		showMessage("An input or output exception occured while reading from socket");
    		e.printStackTrace();
    	}
  	}
	
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private void showMessage(String msg)
  	{
  		System.err.println("ClientSocketReader: " + msg);
  	}
  	
}
	