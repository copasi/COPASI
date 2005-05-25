/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/25 15:55:42 $
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
      INVALID = 0xFF000000,
      NUMBER = 0x01000000,
      CONSTANT = 0x02000000,
      OPERATOR = 0x03000000,
      OBJECT = 0x04000000,
      FUNCTION = 0x05000000,
      CALL = 0x06000000,
      STRUCTURE = 0x07000000,
      CHOICE = 0x08000000,
      VARIABLE = 0x09000000
    };

    // Methods
    /**
     * Creates an evaluation node of type with the given data
     * @param const Type & type
     * @param const Data & data
     * @return CEvaluationNode * evaluationNode
     */
    static CEvaluationNode * create(const Type & type,
                                    const Data & data);

    /**
     * Retrieve the subtype part of type
     * @param const Type & type
     * @return Type subType
     */
    static Type subType(const Type & type);

    /**
     * Retrieve the type part of type
     * @param const Type & type
     * @return Type type
     */
    static Type type(const Type & type);

  private:
    /**
     * Default constructor
     */
    CEvaluationNode();

  protected:
    /**
     * Specific constructor
     * @param const Type & type
     * @param const Data & data
     */
    CEvaluationNode(const Type & type,
                    const Data & data);

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

    /**
     * Set the data of the Node.
     * @param const Data & data
     * @return bool success
     */
    virtual bool setData(const Data & data);

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
