#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Message.h"

#define BUFFER_SIZE 1000
#define MESSAGE_HEADER_SIZE 3


//Initializing static members
Mutex Message::readMutex = Mutex();
Mutex Message::writeMutex = Mutex();

Message::Message()
{
    uniqueID = Constants::MESSAGE_START;
    runningObject = Constants::MESSAGE_STOP;
    messageType = Constants::MESSAGE_PAUSE;
    noOfElements = 0;
    //parameters;
    fullSimulationSpec = "FSS";

    partialSimulationSpec = "PSS";
    errorMessage = "EM";
}


void Message::readObject(int in)
{

    Message::readMutex.lock();

    showMessage("Inside readObject: " );
    cerr << in << endl;

    /*cerr << endl << "Header: " << endl;
      for (int i = 0; i < 0; i++)
      {
      read(in, &ch, sizeof(ch));
      cerr << "Char " << i << ": " << ch <<" " << (int)ch << '\t';
      }*/


    uniqueID = this->readInt(in);
    //showMessage("Read uniqueID" );
    cerr << uniqueID << endl;




    runningObject = this->readInt(in);
    //showMessage("Read RunningObject" );
    cerr << runningObject << endl;

    messageType = this->readInt(in);
    //showMessage("Read MessageType" );
    cerr << messageType << endl;

    noOfElements = this->readInt(in);
    //showMessage("Read noOfElements" );
    cerr << noOfElements << endl;

    for (int i = 0; i < noOfElements; i++)
    {
#ifdef __MACHINE_IS_SMALL_ENDIAN
        double tmpDouble = this->readDoubleForSmallEndianMachines(in);
#else
        double tmpDouble = this->readDouble(in);
#endif


        //this->parameters.push_back(ntohd(tmpDouble));
        cerr << "Read double: " << tmpDouble << endl;
        this->parameters.push_back(tmpDouble);
    }


    char *tmpCharBuffer;
    int strLen;

    strLen = this->readInt(in);
    tmpCharBuffer = new char[strLen + 1];
    read(in, tmpCharBuffer, strLen);
    *(tmpCharBuffer + strLen) = '\0';
    fullSimulationSpec = tmpCharBuffer;
    delete [] tmpCharBuffer;




    /*
      tmpInt = 0;
      cerr<< "Reading " << sizeof(tmpInt) << " chars..." << endl;
      cerr << "Chars are: " << endl;
      //read(in, &tmpInt, sizeof(tmpInt));
      for (unsigned int i = 0; i < sizeof(tmpInt); i++)
      {
      read(in, &ch, sizeof(ch));
      cerr << "Char " << i << ": " << ch <<" " << (int)ch << '\t';
      *(p + i) = ch;
      }

      cerr << endl << "String Length: " << tmpInt << endl;
      strLen = ntohl(tmpInt);
      cerr << endl << "String Length: " << strLen << endl;

      tmpCharBuffer = new char[strLen + 1];
      read(in, tmpCharBuffer, strLen);
      *(tmpCharBuffer + strLen) = '\0';

      for (int i = 0; i < strLen; i++)
      {
      cerr << "Char " << i << ": " << *(tmpCharBuffer + i) << " " << (int) *(tmpCharBuffer + i)<< '\t';
      if (i > 100)
      break;
      }
      cerr << endl << "String Read: " << tmpCharBuffer << endl;
    */

    strLen = this->readInt(in);
    tmpCharBuffer = new char[strLen + 1];
    read(in, tmpCharBuffer, strLen);
    *(tmpCharBuffer + strLen) = '\0';
    partialSimulationSpec = tmpCharBuffer;
    delete [] tmpCharBuffer;


    strLen = this->readInt(in);
    tmpCharBuffer = new char[strLen + 1];
    read(in, tmpCharBuffer, strLen);
    *(tmpCharBuffer + strLen) = '\0';
    errorMessage = tmpCharBuffer;
    delete [] tmpCharBuffer;

    Message::readMutex.unlock();

}


void Message::writeObject(int out)
{
    Message::writeMutex.lock();

    showMessage("Inside writeObject: ");
    cerr << out << endl;
    int tmpInt;
    tmpInt = htonl(uniqueID);
    write(out, &tmpInt, sizeof(tmpInt));
    tmpInt = htonl(runningObject);
    write(out, &tmpInt, sizeof(tmpInt));
    tmpInt = htonl(messageType);
    write(out, &tmpInt, sizeof(tmpInt));

    tmpInt = htonl(noOfElements);
    write(out, &tmpInt, sizeof(tmpInt));

    for (int i = 0; i < noOfElements; i++)
    {
        //double tmpDouble = htond(this->parameters[i]);
        double tmpDouble = this->parameters[i];
        cerr << "Writing Double: " << tmpDouble << endl;

#ifdef __MACHINE_IS_SMALL_ENDIAN
        this->writeDoubleForSmallEndianMachines(out, tmpDouble);
#else
        write(out, &tmpDouble, sizeof(tmpDouble));
#endif

    }


    char *tmpCharBuffer;
    int strLen;

    strLen = fullSimulationSpec.length();
    tmpInt = htonl(strLen);
    write(out, &tmpInt, sizeof(tmpInt));
    tmpCharBuffer = new char[strLen];
    strcpy(tmpCharBuffer, fullSimulationSpec.c_str());
    write(out, tmpCharBuffer, strLen);
    delete [] tmpCharBuffer;


    strLen = partialSimulationSpec.length();
    tmpInt = htonl(strLen);
    write(out, &tmpInt, sizeof(tmpInt));
    tmpCharBuffer = new char[strLen];
    strcpy(tmpCharBuffer, partialSimulationSpec.c_str());
    write(out, tmpCharBuffer, strLen);
    delete [] tmpCharBuffer;


    strLen = errorMessage.length();
    tmpInt = htonl(strLen);
    write(out, &tmpInt, sizeof(tmpInt));
    tmpCharBuffer = new char[strLen];
    strcpy(tmpCharBuffer, errorMessage.c_str());
    write(out, tmpCharBuffer, strLen);
    delete [] tmpCharBuffer;

    Message::writeMutex.unlock();
}



string Message::printMessageDetails()
{
    string temp;
    temp.append("\nThe message fields are as follows: ");
    temp.append("\nUnique ID: ");
    char buf[BUFFER_SIZE];
    sprintf(buf, "%d", this->uniqueID);
    temp.append(buf);
    temp.append("\nRunning Object: ");
    sprintf(buf, "%d", this->runningObject);
    temp.append(buf);
    temp.append("\nMessage Type: ");
    sprintf(buf, "%d", this->messageType);
    temp.append(buf);
    temp.append("\nNumber Of Elements in vector: ");
    sprintf(buf, "%d", this->noOfElements);
    temp.append(buf);
    temp.append("\nVector Elements are: ");
    for (int i = 0; i < this->noOfElements; i++)
    {
        double tmpDouble = (double) parameters[i];
        temp.append("\n\tParameter ");
        sprintf(buf, "%d", i);
        temp.append(buf);
        temp.append(": ");
        sprintf(buf, "%f", tmpDouble);
        temp.append(buf);
    }
    temp.append("\nFull Simulation Specification: ");
    //temp += fullSimulationSpec;
    temp.append(this->fullSimulationSpec.c_str());

    temp.append("\nPartial Simulation Specification: ");
    //temp += partialSimulationSpec;
    temp.append(this->partialSimulationSpec.c_str());

    temp.append("\nError Message: ");
    //temp += errorMessage;
    temp.append(this->errorMessage.c_str());

    return temp;
}


void Message::readMessageFromKeyboard()
{
    showMessage("\nEnter the message fields: ");
    cout << "Unique ID: ";

    cin >> this->uniqueID;
    cout << "Running Object: ";

    cin >> this->runningObject;


    cout << "Message Type: ";
    cin >> this->messageType;


    cout << "Enter Vector Elements (Doubles): ";
    string choice = "Y";
    int i = 1;
    while ((choice.substr(0, 1) == "y") || choice.substr(0, 1) == "Y")
    {
        double tmpDouble = 0.0;
        cout << "Enter Vector Element " << i << ": ";

        cin >> tmpDouble;
        this->parameters.push_back(tmpDouble);
        //this->parameters.insert(i-1, tmpDouble);
        cout << "\tAdd Another (Y/N): ";
        cin >> choice;
        i++;
        this->noOfElements++;
    }
    //this->noOfElements = this->parameters.size();

    cout << "Full Simulation Specification : ";
    cin >> this->fullSimulationSpec;

    cout << "Partial Simulation Specification : ";
    cin >> this->partialSimulationSpec;

    cout << "Error Message: ";
    cin >> this->errorMessage;
}


/** Reads a (4 byte) integer from a stream given as in.
*   Result returned as int after Network to Host Conversion.
*/

int Message::readInt(int in)
{
    int tmpInt = 0;
    char *p = (char *) &tmpInt;
    char ch;
    for (unsigned int i = 0; i < sizeof(tmpInt); i++)
    {
        read(in, &ch, sizeof(ch));
        //cerr << "Char " << i << ": " << ch <<" " << (int)ch << '\t';
        *(p + i) = ch;
    }
    return (ntohl(tmpInt));
}

#ifdef __MACHINE_IS_SMALL_ENDIAN
double Message::readDoubleForSmallEndianMachines(int in)
{
    double tmpDouble = 0.0;
    char *p = (char *) &tmpDouble;
    char ch;
    for (int i = (sizeof(tmpDouble) - 1); i >= 0; i--)
    {

        read(in, &ch, sizeof(ch));
        cerr << "Char " << i << ": " << ch <<" " << (int)ch << '\t';
        *(p + i) = ch;
    }
    //return (ntohl(tmpInt));
    //Double conversion(ntohd) to do
    return (tmpDouble);
}

void Message::writeDoubleForSmallEndianMachines(int out, double doubleToWrite)
{
    char *p = (char *) &doubleToWrite;
    char ch;
    for (int i = (sizeof(doubleToWrite) - 1); i >= 0 ; i--)
    {
        ch = *(p + i);
        write(out, &ch, sizeof(ch));
    }
}

#else
double Message::readDouble(int in)
{
    double tmpDouble = 0.0;
    char *p = (char *) &tmpDouble;
    char ch;
    for (unsigned int i = 0; i < sizeof(tmpDouble); i++)
    {

        read(in, &ch, sizeof(ch));
        cerr << "Char " << i << ": " << ch <<" " << (int)ch << '\t';
        *(p + i) = ch;
    }
    //return (ntohl(tmpInt));
    //Double conversion(ntohd) to do
    return (tmpDouble);
}
#endif
