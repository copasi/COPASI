package Server;

/*
 * Server.java
 */

import java.io.*;
import java.net.*;
import java.util.*;
import Common.*;


/**This is the main GUI class of the Server. 
 * The GUI should be built in this class.
 */
public class Server
{
	/**This is the Network Component this Server GUI uses 
	 * for sending and receiving messages.
	 */	
	protected ServerNetwork myServerNetwork; 
	
	/**Constructor to build the Server.
	 * @param p The port number where the host/server is listening.
	 */
	public Server(int p)
	{
		this.myServerNetwork = new ServerNetwork(this, p);
	}
	
	
	/**This method is called by the ServerNetwork whenever 
	 * the ServerSocketReader receives a message from the client.
	 * @param msg The message which the server received from the client.
	 */
	public void gotMessageFromClient(Message msg)
	{
		showMessage("\nMESSAGE RECEIVED FROM THE CLIENT: " + msg.printMessageDetails());
		showMessage("\nSENDING THE MESSAGE BACK TO CLIENT...");
		this.myServerNetwork.sendMessageToClient(msg);
	}
	

	

	 /** Main function taking one or two arguments
    * @param arg[0] The Port number to listen on.
    */
    public static void main (String args[]) 
    {
        int hostPort;
        if (args.length < 1 || args.length > 1)
        {
            error("Usage: java Server port_number");
        }
        
        try 
        {
			hostPort = Integer.parseInt(args[0]);
			if (hostPort < 0 || hostPort > 65535)
			{
				error("Port number out of range (0, 65535): " + hostPort);
			}
			
			Server server = new Server(hostPort);
		}
		catch (NumberFormatException e) 
		{
			error("Port number not in valid format: " + args[0]);
		}
    }
        
    /**A small function to display errors. 
     * System exits after showing the error message
	 * @param msg The message string to show.
	 */
	private static void error(String message) 
	{
		System.out.println("Server error: " + message);
		System.exit(1);
	}
	
	/**A small function to display warnings.
	 * @param msg The message string to show.
	 */
	private static void warning(String message)
	{
		System.out.println("Server warning: " + message);
	}
	
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private void showMessage(String msg)
  	{
  		System.err.println("Server: " + msg);
  	}
}







