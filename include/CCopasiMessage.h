/**
 *  CCopasiMessage class. A more elaborate class description.
 */

// New Class for COPASI message handling
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

#define FatalError() {CCopasiMessage(ERROR,"%s (%d) compiled: %s %s", __FILE__, __LINE__, __DATE__, __TIME__);}

class CCopasiMessage
{
public:
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
    CCopasiMessage(COPASI_MESSAGE_TYPE type, const char *format, ... );

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
    COPASI_MESSAGE_TYPE GetType();

private:
    /**
     *  The actual constructor of a message.
     *  @param type message type (RAW|TRACE|WARNING|ERROR)
     *  @param text message text
     */
    void Handler(COPASI_MESSAGE_TYPE type, string text);
    
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

};
#endif // COPASI_CCopasiMessage



