/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMessage.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/12/06 19:58:13 $
   End CVS Header */

/**
 *  CCopasiMessage class.
 *  New Class for COPASI message handling. (C) Stefan Hoops 2001.
 */

#ifndef COPASI_CCopasiMessage
#define COPASI_CCopasiMessage

#include <string>
#include <stack>

#include "copasi.h"

typedef struct MESSAGES {unsigned C_INT32 No; const char * Text;}
Message;

#define MCopasiBase           5000
#define MCReadConfig          MCopasiBase + 100
#define MCWriteConfig         MCopasiBase + 200
#define MCRange               MCopasiBase + 300
#define MCKinFunction         MCopasiBase + 400
#define MCCopasiVector        MCopasiBase + 500
#define MCFunctionParameters  MCopasiBase + 600
#define MCMassAction          MCopasiBase + 700
#define MCCopasiMethod        MCopasiBase + 800
#define MCReaction            MCopasiBase + 900
#define MCParameter           MCopasiBase + 1000
#define MCChemEq              MCopasiBase + 1100
#define MCTrajectoryMethod    MCopasiBase + 1200
#define MCXML                 MCopasiBase + 1300
#define MCCopasiMessage       MCopasiBase + 1400

/**
 *  This throws an exception with information where the error occured.
 */
#define fatalError() {CCopasiMessage(CCopasiMessage::ERROR,"%s (%d) compiled: %s %s", __FILE__, __LINE__, __DATE__, __TIME__);}

class CCopasiMessage
  {
  public:
    enum Type
    {
      RAW = 0,
      TRACE,
      WARNING,
      // In the case that ERROR is defined we have to remove its definition
      // temporarely.
#ifdef ERROR
# define COPASI_ERROR_BACKUP ERROR
# undef ERROR
#endif
      ERROR
#ifdef COPASI_ERROR_BACKUP
# define ERROR COPASI_ERROR_BACKUP
# undef COPASI_ERROR_BACKUP
#endif
    };

    // Attributes

  private:
    /**
     *  Message text.
     */
    std::string mText;

    /**
     *  Message type.
     */
    CCopasiMessage::Type mType;

    /**
     *  Message Number
     */
    unsigned C_INT32 mNumber;

    /**
     *  The stack of messages. Each message created with one of 
     *  the specific constructors is automically added to the stack.
     */
    static std::stack< CCopasiMessage > mMessageStack;

    // Operations

  public:
    /**
     *  This function retrieves the last message created in COPASI.
     *  Consecutive calls allow for the retrieval of all generated 
     *  messages. If no more messages are on the stack
     *  @return CCopasiMessage
     */
    static CCopasiMessage getLastMessage();

    /**
     *  Default consructor. 
     *  This creates a default error messages, which actually does nothing.
     */
    CCopasiMessage();

    /**
     *  Copy consructor. 
     *  @param const CCopasiMessage & src
     */
    CCopasiMessage(const CCopasiMessage & src);

    /**
     *  Specified consructor. 
     *  This creates a formated message.
     *  @param CCopasiMessage::Type type (RAW|TRACE|WARNING|ERROR)
     *  @param const char * format (printf like format string)
     *  @param ... arguments like in printf
     */
    CCopasiMessage(Type type, const char *format, ...);

    /**
     *  Specified consructor. 
     *  This creates a formated message.
     *  @param CCopasiMessage::Type type (RAW|TRACE|WARNING|ERROR)
     *  @param unsigned C_INT32 number (message number see message.h)
     *  @param ... arguments like in printf
     */
    CCopasiMessage(Type type, unsigned C_INT32 number, ...);

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
     *  @return "const string &" mMessage
     */
    const std::string & getText() const;

    /**
     *  Retrieves thetype of the message.
     *  @return "const CCopasiMessage::Type &" mType
     */
    const CCopasiMessage::Type & getType() const;

    /**
     *  Retrieves the number of the message.
     *  @return "const unsigned C_INT32 &" mNumber
     */
    const unsigned C_INT32 & getNumber() const;

  private:
    /**
     *  The actual constructor of a message.
     *  @param type message type (RAW|TRACE|WARNING|ERROR)
     *  @param text message text
     */
    void handler();

    /**
     *  Inserts line breaks in the message text.
     */
    void lineBreak();
  };

#endif // COPASI_CCopasiMessage
