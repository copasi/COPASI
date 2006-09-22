/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.h,v $
   $Revision: 1.9.2.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/22 15:06:48 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CExpression
#define COPASI_CExpression

#include "CEvaluationTree.h"
#include "report/CCopasiContainer.h"

class CExpression:
      public CEvaluationTree

  {
    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CExpression &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const CExpression & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CExpression();

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

  public:
    /**
     * Set the infix description of the tree and compile it.
     * @param const std::string & infix
     * @return bool success
     */
    virtual bool setInfix(const std::string & infix);

    /**
     * Compile the function.
     * @param std::vector< CCopasiContainer * > listOfContainer (Default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

    /**
     * Calculates the value of the function
     * @return const C_FLOAT64 & result
     */
    virtual const C_FLOAT64 & calcValue();

    /**
     * Refresh the value of the expression
     */
    void refresh();

    /**
     * Write display mathml of the expression into the ostream "out"
     * level specifies indentation
     * fullExpand==true means function calls are expanded
     */
    void writeMathML(std::ostream & out, bool fullExpand, unsigned C_INT32 l) const;

  private:
    /**
     * Retrieve a pointer to the object defined by CN. This method may only be called
     * during compile() sinces the list mpListOfContainer is only valid then.
     * @param const CCopasiObjectName & CN
     * @return const CCopasiObject * value
     */
    virtual const CCopasiObject * getNodeObject(const CCopasiObjectName & CN) const;

    // This is needed so that the tree compiles
    friend bool CEvaluationNodeObject::compile(const CEvaluationTree * pTree);

  public:
    /**
     * Retrieve the list of container used for compile
     * @return const std::vector< CCopasiContainer * > & listOfContainer
     */
    const std::vector< CCopasiContainer * > & getListOfContainer() const;

    /**
     * This method performa an infix update if a referenced object has been renamed
     * @return bool success
     */
    bool updateInfix();

    /**
     * Retrieve the human readable display string.
     * Note, the expression must be compiled for this return a displayable
     * string.
     * @return const std::string & displayString
     */
    const std::string & getDisplayString() const;

    // Attribute
  protected:
    /**
     * Pointer to the list of containers used for compilation.
     */
    const std::vector< CCopasiContainer * > * mpListOfContainer;

    /**
     * Human readable display string.
     */
    std::string mDisplayString;
  };

#endif // COPASI_CExpression
