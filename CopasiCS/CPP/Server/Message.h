#ifndef _Message_h_included_
#define _Message_h_included_


/**IMPORTANT: Remember to comment this define if the machine you are compiling
 * for is Big Endian.
 */
#define __MACHINE_IS_SMALL_ENDIAN



#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "Constants.h"
#include "Mutex.h"

#define PARAMETER_SIZE 10
#define FULL_SIMULATION_SPEC_SIZE 100
#define PARTIAL_SIMULATION_SPEC_SIZE 100
#define ERROR_MESSAGE_SIZE 100

/**The data members of this class are the fields which
 * are to be passed between the client and the server.
 */
class Message
{
public:
	/**The ID of this message. */
	int uniqueID;
	/**Running object ID. */
	int runningObject;
	/**Type of message*/
	int messageType;
	/**Number of Elements that the vector (of doubles) contains.*/
	int noOfElements;
	/**The vector containing the doubles which would be
	 * passed as parameters to the corresponding function.
	 */
	vector<double> parameters;
	/**The full simulation specification.*/
	string fullSimulationSpec;
        /**The partial simulation specification.*/
	string partialSimulationSpec;
        /**Error message if there is an error*/
	string errorMessage;

       	/**Mutexes used for synchronization*/
	static Mutex readMutex;
       	static Mutex writeMutex;

	/**No argument constructor. Sets up the default values for the
	 * different fields.
	 */
	Message();

	/**Reads the fields of this message from the socket.
	 * Uses the writeMutex lock before
 	 * reading so that some other thread does not corrupt the
 	 * stream.
 	 * @param in The ID of the socket to read from.
 	 */
	void readObject(int in);
	/**Writes the fields of this message to the socket.
	 * Uses the writeMutex lock before
 	 * writing so that some other thread does not corrupt the
 	 * stream.
 	 * @param out The ID of the socket to write to.
 	 */
	void writeObject(int out);
	
	/**Makes a string containing the values of all the fields
	 * of this message.
	 * @return The string containing the values of all the fields
	 * of this message.
	 */
	string printMessageDetails();
        
	/**Reads the values from the keyboard
	 * and assigns them to the corresponding
	 * fields of this message.
	 */
	void readMessageFromKeyboard();

private:
	/**Reads an integer from a socket for a Big Endian machine.
	* @param in The ID of the socket from which the integer is to be read.
	*/
	int readInt(int in);
#ifdef __MACHINE_IS_SMALL_ENDIAN
	/**Reads a double from a socket for a Small Endian machine.
	* @param in The ID of the socket from which the double is to be read.
	*/
	double readDoubleForSmallEndianMachines(int in);

	/**Writes a double to a socket for a Small Endian machine.
	* @param in The ID of the socket from which the double is to be read.
	*/
	void writeDoubleForSmallEndianMachines(int out, double doubleToWrite);
#else
	/**Reads a double from a socket for a Big Endian machine.
	* @param in The ID of the socket from which the double is to be read.
	*/
	double readDouble(int in);
#endif

	/**A small function to display messages.
	 * @param msg The message string to show.
	 */
	void showMessage(string msg)
	{
		cerr << "Message: " << msg;
	}

};

#endif



