package Common;

import java.lang.*;
import java.util.*;
import java.io.*;

/**The data members of this class are the fields which 
 * are to be passed between the client and the server.
 */
public class Message implements Serializable
{
	/**The ID of this message. */
	public int uniqueID;
	/**Running object ID. */
	public int runningObject;
	/**Type of message*/
	public int messageType;
	/**Number of Elements that the vector (of doubles) contains.*/
	public int noOfElements;
	/**The vector containing the doubles which would be 
	 * passed as parameters to the corresponding function.
	 */
	public Vector parameters;
	/**The full simulation specification.*/
	public String fullSimulationSpec;
	/**The partial simulation specification.*/
	public String partialSimulationSpec;
	/**Error message if there is an error*/
	public String errorMessage;
	

	/**No argument constructor. Sets up the default values for the
	 * different fields.
	 */
	public Message()
	{
		
        uniqueID = Constants.MESSAGE_START;
		runningObject = 0;
		messageType = 0;
		noOfElements = 0;
		parameters = new Vector();
		fullSimulationSpec = null;
		String partialSimulationSpec = null;
		String errorMessage = null;
				
	}
	

 	/**Writes the fields of this message to the socket through
 	 * a DataOutputStream. Locks the DataOutputStream before
 	 * writing so that some other thread does not corrupt the
 	 * stream.
 	 * @param out The DataOutputStream constructed from the 
 	 * socket output stream. 
 	 */
	public void writeDataObject(java.io.DataOutputStream out) throws IOException
 	{
 			
 		synchronized (out)
 		{
	 		out.writeInt(uniqueID);
			out.writeInt(runningObject);
			out.writeInt(messageType);
			
			out.writeInt(noOfElements);
			for (int i = 0; i < noOfElements; i++)
			{
				Double tmpDouble = (Double) this.parameters.get(i);
				out.writeDouble(tmpDouble.doubleValue());
			}
			
			out.writeInt(fullSimulationSpec.length());
			out.writeBytes(fullSimulationSpec);
			
			out.writeInt(partialSimulationSpec.length());
			out.writeBytes(partialSimulationSpec);
	 		
	 		
	 		out.writeInt(errorMessage.length());
	 		//showMessage("Writing Length: "  + errorMessage.length());
	 		out.writeBytes(errorMessage);
	 	}
 		 		
  	}
 	
 	
 	/**Reads the fields for this message from the socket through
 	 * a DataInputStream. Locks the DataInputStream before
 	 * writing so that some other thread does not corrupt the
 	 * stream.
 	 * @param in The DataInputStream constructed from the 
 	 * socket input stream. 
 	 */
	public void readDataObject(java.io.DataInputStream in) throws IOException, ClassNotFoundException
 	{
 		
 		synchronized (in)
 		{
	 		this.uniqueID = in.readInt();
			this.runningObject = in.readInt();
			this.messageType = in.readInt();
			
			this.noOfElements = in.readInt();
			this.parameters = new Vector(noOfElements);
			for (int i = 0; i < noOfElements; i++)
			{
				Double tmpDouble = new Double(in.readDouble());
				this.parameters.add(tmpDouble);
			}
				
			int tmpSize;
			byte[] byteString = null;
					
			tmpSize = in.readInt();
			byteString = new byte[tmpSize];
	 		for (int i = 0; i < tmpSize; i++)
	 		{
	 			byteString[i] = in.readByte();
	 		}
	 		this.fullSimulationSpec = new String(byteString);
	 		
	 		
	 		tmpSize = in.readInt();
			byteString = new byte[tmpSize];
	 		for (int i = 0; i < tmpSize; i++)
	 		{
	 			byteString[i] = in.readByte();
	 		}
	 		this.partialSimulationSpec = new String(byteString);
	 				
	 		
	 		
	 		tmpSize = in.readInt();
			byteString = new byte[tmpSize];
	 		for (int i = 0; i < tmpSize; i++)
	 		{
	 			byteString[i] = in.readByte();
	 		}
	 		this.errorMessage = new String(byteString);
	 	}
		
 	}
 		
 
	/**Makes a string containing the values of all the fields 
	 * of this message. 
	 * @return The string containing the values of all the fields
	 * of this message.
	 */
	public String printMessageDetails()
	{
		StringBuffer temp = new StringBuffer();
		temp.append("\nThe message fields are as follows: ");
		temp.append("\nUnique ID: " + this.uniqueID);
		temp.append("\nRunning Object: " + this.runningObject);
		temp.append("\nMessage Type: " + this.messageType);
		temp.append("\nNumber Of Elements in Vector: " + this.noOfElements);
		temp.append("\nVector Elements are: ");
		for (int i = 0; i < this.parameters.size(); i++)
		{
			Double tmpDouble = (Double) this.parameters.get(i);
			temp.append("\n\tParameter " + i + ": " + tmpDouble.toString());
		}
		
		temp.append("\nFull Simulation Specification: " + this.fullSimulationSpec);
		temp.append("\nPartial Simulation Specification: " + this.partialSimulationSpec);
		temp.append("\nError Message: " + this.errorMessage);
	
		return temp.toString();
	}
	
	
	/**Reads the values from the keyboard 
	 * and assigns them to the corresponding 
	 * fields of this message.
	 */
	public void readMessageFromKeyboard()
	{
		String line = null;
      	
		showMessage("\nEnter the message fields: ");
		System.out.println("Unique ID: ");
		line = 	getLine();
		try
		{
			this.uniqueID = Integer.parseInt(line);
		}
		catch(NumberFormatException nfe)
		{
			showMessage("Unique ID not proper Integer");
			uniqueID = 0;
		}
		
		System.out.println("Running Object: ");
		line = 	getLine();
		try
		{
			this.runningObject = Integer.parseInt(line);
		}
		catch(NumberFormatException nfe)
		{
			showMessage("Running Object not proper Integer");
			this.runningObject = 0;
		}
		
		System.out.println("Message Type: ");
		line = 	getLine();
		try
		{
			this.messageType = Integer.parseInt(line);
		}
		catch(NumberFormatException nfe)
		{
			showMessage("Message Type not proper Integer");
			this.messageType = 0;
		}
		
				
		System.out.println("Enter Vector Elements (Doubles): ");
		String choice = "Y";
		int i = 1;
		while (choice.trim().equals("y") || choice.trim().equals("Y"))
		{
			double tmpDouble = 0.0;
			System.out.println("Enter Vector Element " + i + ": ");
			line = 	getLine();
			try
			{
				tmpDouble = Double.parseDouble(line);
			}
			catch(NumberFormatException nfe)
			{
				showMessage("Running Object not proper Double");
			}
			
			this.parameters.add(new Double(tmpDouble));
			System.out.println("\tAdd Another (Y/N): " );
			choice = getLine();
			i++;
		}
		this.noOfElements = this.parameters.size();
		
		System.out.println("Full Simulation Specification : ");
		this.fullSimulationSpec = getLine();
		
		System.out.println("Partial Simulation Specification : ");
		this.partialSimulationSpec = getLine();
		
		System.out.println("Error Message: ");
		this.errorMessage  = getLine();
	}

		
	
	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	private void showMessage(String msg)
	{
		System.out.println("Message: " + msg);
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
}
