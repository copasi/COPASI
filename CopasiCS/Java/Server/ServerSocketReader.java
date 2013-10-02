// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package Server;

/*
 * ServerSocketReader.java
 */

import java.io.*;
import java.net.*;
import java.util.*;
import Common.*;

/**The Reader class runs as a seperate thread and 
 * informs the ServerManager if the
 * client has sent a message. 
 * It remains blocked on a socket read for most of the time. 
 * It gets unblocked when it recieves a message from the server and calls the 
 * gotMessageFromClient(Message msg) of the ServerNetwork.
 */
public class ServerSocketReader extends Thread
{
	/**ClientConnection object (containing the socket) from where 
	 * this Reader will read.
	 */
	protected ClientConnection connection;
	
	/**Build the Reader using the ClientConnection object.
	* @param c This is the ClientConnection object 
	* (containing the socket) from which this Reader is to be built.
	*/
	public ServerSocketReader(ClientConnection c)
	{
		connection = c;
		this.start();
	}

	/**New Reader thread, gets blocked while reading from the socket.
	 * Unblocks when the client sends a message.
	 */
	public synchronized void run() 
	{
		try 
		{
	       	while (true)
	      	{
		        try
		        {
		        	
		        	showMessage(connection.toString());
		        	showMessage(connection.input.toString());
		        	
		        	connection.message.readDataObject(connection.input);
		        	//connection.message = (Message) connection.input.readObject();
		        }
		        catch(java.lang.ClassNotFoundException cnfe)
		        {
		        	showMessage("A ClassNotFoundException occured. Details...");
		        	cnfe.printStackTrace();
		        }
		        
		        connection.update = true;
	        
	        	synchronized (connection.manager) 
	        	{
	          		connection.manager.notify();
	        	}
	      	}
    	}
    	catch(IOException e) 
    	{
    		showMessage("An input or output exception occured while reading from socket");
    		System.exit(1);
    	}
    	catch(NullPointerException npe)
		{
			npe.getMessage();
		    npe.printStackTrace();
		}
  	}
  	
	/**A small function to display messages.
	* @param msg The message string to show.
	*/
  	private void showMessage(String msg)
  	{
  		System.err.println("ServerSocketReader: " + msg);
  	}
}
	
