
#include "Client.h"
#include "Message.h"

#include <string>


Client::Client(string host, int port):myClientNetwork(this, host, port)
{
    string choice = "Y";
    while ((choice.substr(0, 1) == "y") || choice.substr(0, 1) == "Y")
    {
        sleep(2);
        Message msg;
        msg.readMessageFromKeyboard();
        myClientNetwork.sendMessageToServer(msg);
        sleep(8);
        cout << "\tSend Another Message (Y/N): ";
        cin >> choice;
    }

}


void Client::gotMessageFromServer(Message msg)
{
    showMessage("Inside Client::gotMessageFromServer");
    cerr << (void *) this;
    showMessage("\nMESSAGE RECEIVED FROM THE SERVER: " 
                + msg.printMessageDetails());
}



/**
* Main function which demonsrates the working of the Client class
* @param args[1] The name (or IP) of the host to connect to.
* @param args[2] The port number where the server is listening.
*/
int main(int argc, char *args[])
{
    int port = 2000;

    if (argc < 2 || argc > 3)
    {
        cout << "Usage: Client host_name port_number" << endl;
        exit(1);
    }
    port = atoi(args[2]);
    if (port == 0)
    {
        cout << "\nInvalid port specified...defaulting to port " << port << endl;
    }

    Client client(args[1], port);

    cout << endl <<"CLIENT MAIN FUNCTION ENDING"<< endl;
    exit(EXIT_SUCCESS);
}


