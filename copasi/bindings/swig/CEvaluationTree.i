// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "function/CEvaluationTree.h"

%}

%newobject CEvaluationTree::create(CEvaluationTree::Type type);
%newobject CEvaluationTree::copy(const CEvaluationTree& src);


class CEvaluationTree : public CCopasiContainer
{
  public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
      Function = 0,
      MassAction,
      PreDefined,
      UserDefined,
      Expression
    };


    /**
     * Create an EvaluationTree of the specified type.
     * Note: the returned object has to be released after use with delete.
     * @param CEvaluationTree::Type type
     * @return EvaluationTree * pEvaluationTree
     */
    static CEvaluationTree *
    create(CEvaluationTree::Type type);

    /**
     * Copy an EvaluationTree of the specified type.
     * Note: the returned object has to be released after use with delete.
     * @param const EvaluationTree & src
     * @return EvaluationTree * pEvaluationTree
     */
    static CEvaluationTree *
    copy(const CEvaluationTree & src);

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const CEvaluationTree::Type & type (default: Function)
     */
    CEvaluationTree(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL,
                    const Type & type = Function);

    /**
     * Copy constructor
     * @param const CEvaluationTree & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEvaluationTree(const CEvaluationTree & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CEvaluationTree();

    /**
     * Retrieves the type of the function
     * @return const CEvaluationTree::Type & type
     */
    const CEvaluationTree::Type & getType() const;

    /**
     * Set the type of the function
     * @param const CEvaluationTree::Type & type
     */
    void setType(const CEvaluationTree::Type & type);

    /**
     * Retrieves the key of the EvaluationTree
     * @return const std::string & key
     */
    const std::string & getKey() const;

    /**
     * Set the infix description of the tree and compile it.
     * @param const std::string & infix
     * @return bool success
     */
    virtual bool setInfix(const std::string & infix);

    /**
     * Retrieve the infix description of the tree
     * @return const std::string & infix
     */
    const std::string & getInfix() const;

    /**
     * Retrieve the index to the value of the named variable.
     * @param const std::string & name
     * @return unsigned C_INT32
     */
    virtual unsigned C_INT32 getVariableIndex(const std::string & name) const;


    /**
     * Sets the SBMLId.
     */
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;

    %extend
    {
      /**
       * Retrieve the position of the error in the string description.
       * std::string::npos indicates no error.
       * @return std::string::size_type errorPosition
       */
      C_INT32 getErrorPosition() const
      {
        return (C_INT32)self->getErrorPosition();
      }

    }

};


