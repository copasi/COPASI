/**
 *  CReadConfig class. A more elaborate class description.
 */

// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001


#ifndef COPASI_CCopasiMessage
#define COPASI_CCopasiMessage

typedef enum COPASI_MESSAGE_TYPE
{
    RAW = 0,
    TRACE,
    WARNING,
    ERROR
};

class CCopasiMessage
{
public:
    /**
     *  Default consructor. 
     *  This creates a default error messages.
     *  "Unexpected Error".
     */
    CCopasiMessage();

    /**
     *  Specified consructor. 
     *  This creates the error messages specified as the argument.
     *  @param text error messages.
     */
    CCopasiMessage(string text, enum COPASI_MESSAGE_TYPE type);

    /**
     *  Destructor. 
     */
    ~CCopasiMessage();

    /**
     *  Assignement operator. 
     */
    CCopasiMessage &operator=(CCopasiMessage &);

    /**
     *  Retrieves the error message.
     *  @return mMessage
     */
    string GetText();

    /**
     *  Retrieves the error message.
     *  @return mMessage
     */
    enum COPASI_MESSAGE_TYPE GetType();

private:
    /**
     *  Name of the configuration file.
     */
    string mText;               // Message text

    /**
     *  Name of the configuration file.
     */
    COPASI_MESSAGE_TYPE mType;  // Message type

};
#endif // COPASI_CCopasiMessage

