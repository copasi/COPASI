package Client;

/*
 * ClientSocketWriter.java
 */

import java.io.*;
import java.net.*;
import Common.*;

/**Writes messages to be sent to the server on the socket.
 */
public class ClientSocketWriter
{
	/**The ClientNetwork whose writer this component is.*/
	ClientNetwork clientNetwork;
	//ObjectOutputStream output;
	DataOutputStream output;

	/**The constructor
	* @param cn The ClientNetwork whose reader this thread is.
	*/
	public ClientSocketWriter(ClientNetwork cn) 
	{
    	try
    	{
    		clientNetwork = cn;
    		//output = new ObjectOutputStream(clientNetwork.socket.getOutputStream()); 
    		output = new DataOutputStream(clientNetwork.socket.getOutputStream()); 
    		showMessage("Got Outstream..." + output.toString());
    	}
    	catch (IOException e) 
    	{
    		showMessage("An input or output exception occured while creating ObjectOutputStream");
    	}
  	}

  	
  	public void writeMessageToServer(Message msg)
  	{
  		try
  		{
  			//output.writeObject(msg);
  			msg.writeDataObject(output);
  		}
  		catch(IOException e) 
  		{
  			showMessage("An input or output exception occured while writing to socket");
  		}
  	}
  	
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private void showMessage(String msg)
  	{
  		System.err.println("ClientSocketWriter: " + msg);
  	}

}
	