#ifndef _Constants_h_included_
#define _Constants_h_included_

/**These constants should be the same for both the client and
 * the server. Contains the IDs of the different types of messages
 * that would be exchanged between the client and the server.
 */
class Constants
{
public:
	static const int MESSAGE_START = 1;
	static const int MESSAGE_STOP = 2;
	static const int MESSAGE_PAUSE = 3;
	static const int MESSAGE_CONTINUE = 4;

};

#endif