package Server;

/*
 * ServerNetwork.java
 */

import java.io.*;
import java.net.*;
import java.util.*;
import Common.*;

/**This class is the Network component used by the server GUI
 * to communicate with the client. It uses sendMessageToClient(Message)
 * to send a message to the client. It calls gotMessageFromClient(Message)
 * of its "Server" (GUI Component) when a message is recieved
 * by its reader
 */
public class ServerNetwork extends Thread 
{

	/**The Server UI for this Network component*/
	protected Server myServer;
	
	/**Port on which the server listens*/
	protected int port;
		
	/**This is the serverSocket which accepts a new client*/
	protected ServerSocket server;
	/**Connection object which contains the sockets and the Input and Output Streams*/
	protected ClientConnection clientConnection;
	/**This thread listens for any updates and takes action accordingly*/
	protected ServerManager serverManager;
	
	/**
	* Constructor for running the server so that it listens on port p
	* and runs on directory d
	* @param myServer The (GUI) Server of this Network Component.
	* @param p The port on which to listen for a new client.
	*/
	public ServerNetwork(Server myServer, int p)
	{
		this.myServer = myServer;
		port = p;
		try 
		{
        	server = new ServerSocket(port);
        }
        catch (IOException e)
        {
        	error("Unable to open server socket.");
        }
        
        serverManager = new ServerManager(this);
        this.start();
    }
    
    
    /**Method that is called by the ServerManager when the ServerSocketReader 
	 * recieves a message from the server. 
	 * This method in turn calls the Server (GUI Component) version of this method.
	 * @param The message recieved from the client.
	 */
    public void gotMessageFromClient(Message msg)
	{
		this.myServer.gotMessageFromClient(msg);
	}
	

	
	/**Method to call when the server needs to send a message 
	 * to the client.
	 * @param msg The message that is to be sent to the server by the client.
	 */
	public void sendMessageToClient(Message msg)
	{
		try
	  	{
	  		//c.output.writeObject(c.message);
	  		msg.writeDataObject(this.clientConnection.output);
	  	}
	  	catch(IOException ioe)
	  	{
	  		showMessage("Unable to write object: " + msg.toString());
	  		ioe.printStackTrace();
	  	}
	}

    
    
    /** A new thread which excepts a new client.*/
    public void run() 
    {
    	//while (true){
		try 
		{
        	showMessage("About to accept Connection...");
        	Socket clientSocket = server.accept();
            clientConnection = new ClientConnection(clientSocket, serverManager);
            System.err.println("Accepted connection:" + clientConnection);
		}
        catch (IOException e) 
        {
			warning("Unable to accept connection.");
        }
        //}
    }
    
	/**Method to show error Messages which terminates the application
	 * after showing the message.
	 * @param message The error message which is to be displayed.
	 */
	private static void error(String message) 
	{
		System.out.println("Server error: " + message);
		System.exit(1);
	}
	
	/**Method to show warning Messages which does not terminate the application
	 * after showing the message.
	 * @param message The warning message which is to be displayed.
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
  		System.err.println("ServerNetwork: " + msg);
  	}
}
	