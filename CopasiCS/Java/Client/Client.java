package Client;
/*
 * Client.java
 */

import java.io.*;
import java.net.*;
import Common.*;

/**This is the main GUI class of the Client. 
 * The GUI should be built in this class.
 */
public class Client
{
    /**This is the Network Component this Client GUI uses 
     * for sending and receiving messages.
     */
    protected ClientNetwork myClientNetwork;
	
    /**Constructor to build the Client.
     * @param host The host which this client needs to connect to.
     * @param port The port number where the host/server is listening.
     */
    public Client(String host, int port)
        {
		
            this.myClientNetwork = new ClientNetwork(this, host, port);
      	      	
            String choice = "Y";
            while (choice.trim().equals("y") || choice.trim().equals("Y"))
            {
                Message msg = new Message();
                msg.readMessageFromKeyboard();			
                myClientNetwork.sendMessageToServer(msg);
			
                System.out.println("\tWant to send Another Message(Y/N): " );
                choice = getLine();
			
            }
	
	}
    /**This method is called by the ClientNetwork whenever 
	 * the ClientSocketReader receives a message from the server.
	 * @param msg The message which the client received from the server.
	 */
    public void gotMessageFromServer(Message msg)
	{
            showMessage("\nMESSAGE RECEIVED FROM THE SERVER: " + msg.printMessageDetails());
	}

    /**A small function to display messages.
	 * @param msg The message string to show.
	 */
    private static void showMessage(String msg)
	{
            System.err.println("Client: " + msg);
	}
	
    /**Gets a line from the keyboard.
	 * @return The line input by the user from the keyboard
	 */
    private String getLine()
	{
            BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
            String line = null;
            try
            {
                line = keyboard.readLine();
            }
            catch(IOException ioe)
            {
                showMessage("Error reading from keyboard.");
            }
            return line;
	}
	
	
    /**
	* Main function which demonsrates the working of the Client class
	* @param args[0] The name (or IP) of the host to connect to.
	* @param args[1] The port number where the server is listening.
	*/
    public static void main(String[] args) 
	{
            int port = 2000;

            if (args.length < 1 || args.length > 2)
            {
                showMessage("Usage: java Client host_name port_number");
                System.exit(1);
            }
            try 
            {
                port = Integer.parseInt(args[1]);
            }
            catch (NumberFormatException e) 
            {
        	showMessage("Cannot Recognize Port Number...Defaulting to port " + port);
            } 
            catch (IndexOutOfBoundsException iobe)
            {
                showMessage("Port Number not specified...Defaulting to port " + port);
            }
      	
            Client myClient = new Client(args[0], port);
      	
        }

}
