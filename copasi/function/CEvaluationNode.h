/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 21:02:52 $
   End CVS Header */

#ifndef COPASI_CEvaluationNode
#define COPASI_CEvaluationNode

#include "utilities/CCopasiNode.h"

/**
 * This is the base class for nodes used in an evaluation trees
 */
class CEvaluationNode : public CCopasiNode< std::string >
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum Type
    {
      INVALID = -1,
      NUMBER = 0,
      CONSTANT,
      OPERATOR,
      OBJECT,
      FUNCTION,
      CALL,
      PARENTHESIS,
      CHOICE,
      VARIABLE
    };

    // Methods
    /**
     * Creates an evaluation node of type and subtype
     * @param const Type & type
     * @param const Data & data
     * @return CEvaluationNode * evaluationNode
     */
    static CEvaluationNode * create(const Type & type,
                                    const Data & data);

  private:
    /**
     * Default constructor
     */
    CEvaluationNode();

  protected:
    /**
     * Specific constructor
     * @param const Type & type
     */
    CEvaluationNode(const Type & type);

  public:
    /**
     * Copy constructor
     * @param const CEvaluationNode & src
     */
    CEvaluationNode(const CEvaluationNode & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNode();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual const C_FLOAT64 & value() const = 0;

    /**
     * Retrieve the value of the node. This method is superceded
     * value() which will perform faster.
     * @return const Data & value
     */
    virtual Data getData() const;

    // Attributes
  private:
    /**
     * The type the node
     */
    Type mType;

  protected:
    /**
     * The numerical value of the node
     */
    C_FLOAT64 mValue;

    /**
     * The data of the node
     */
    Data mData;
  };

#include "CEvaluationNodeNumber.h"
#include "CEvaluationNodeConstant.h"

#endif // COPASI_CEvaluationNode
