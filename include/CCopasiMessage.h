/**
 *  CCopasiMessage class.
 *  New Class for COPASI message handling. (C) Stefan Hoops 2001.
 */

#ifndef COPASI_CCopasiMessage
#define COPASI_CCopasiMessage

#include <string>

/**
 *  This throws an exception with information where the error occured.
 */
#define FatalError() {CCopasiMessage(CCopasiMessage::ERROR,"%s (%d) compiled: %s %s", __FILE__, __LINE__, __DATE__, __TIME__);}

class CCopasiMessage
{
public:
    enum COPASI_MESSAGE_TYPE
    {
        RAW = 0,
        TRACE,
        WARNING,
        ERROR
    };

    /**
     *  Default consructor. 
     *  This creates a default error messages, which actually does nothing.
     */
    CCopasiMessage();

    /**
     *  Specified consructor. 
     *  This creates a formated message.
     *  @param type message type (RAW|TRACE|WARNING|ERROR)
     *  @param format printf like format string.
     *  @param ... arguments like in printf
     */
    CCopasiMessage(const COPASI_MESSAGE_TYPE type, const char *format, ... );
    CCopasiMessage(const COPASI_MESSAGE_TYPE type, unsigned long number, ...);
    
    /**
     *  Destructor. 
     */
    ~CCopasiMessage();

    /**
     *  Assignement operator. 
     */
    CCopasiMessage &operator=(CCopasiMessage &);

    /**
     *  Retrieves the text of the message.
     *  @return mMessage
     */
    string GetText();

    /**
     *  Retrieves thetype of the message.
     *  @return mType
     */
    long GetType();

private:
    /**
     *  The actual constructor of a message.
     *  @param type message type (RAW|TRACE|WARNING|ERROR)
     *  @param text message text
     */
    void Handler();
    
    /**
     *  Inserts line breaks in the message text.
     */
    void LineBreak();
    
    /**
     *  Message text.
     */
    string mText;               // Message text

    /**
     *  Message type.
     */
    COPASI_MESSAGE_TYPE mType;  // Message type

    /**
     *  Message Number
     */
    unsigned long mNumber;
};
#endif // COPASI_CCopasiMessage
