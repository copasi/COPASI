package Server;

/*
 * ServerManager.java
 */

import java.io.*;
import java.net.*;
import java.util.*;
import Common.*;

/**This class runs as a separate thread and remains blocked most of the time.
 * The ServerSocketReader informs this class when it reads a message from 
 * the client. On such a notification, this thread then calls 
 * gotMessageFromClient(Message msg) of the ServerNetwork class.
 */
public class ServerManager extends Thread 
{
	/**ServerNetwork object which this ServerManager object will manage.*/
	protected ServerNetwork serverNetwork;

	/**Constructor taking ServerNetwork object
	* @param sn ServerNetwork object to use to build the Manager
	*/
	public ServerManager(ServerNetwork sn) 
	{
		serverNetwork = sn;
		this.start();
	}

	/**A new thread which initially gets blocked. When there is an update, the ServerReader
	 * unblocks this and this thread takes the appropriate action.
	 */
	public synchronized void run() 
	{
    	while (true) 
    	{
      		try 
      		{
          		//this.wait(1000);
          		this.wait();
        	}
	        catch (InterruptedException e) 
	        {
	        }
	        ClientConnection c = serverNetwork.clientConnection;
	                          
	        if (c.update)
	        {
				this.serverNetwork.gotMessageFromClient(c.message);
				c.update = false;
			}
      	
    	}
  	}
  	
  	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private void showMessage(String msg)
  	{
  		System.err.println("ServerManager: " + msg);
  	}
}
	