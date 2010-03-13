// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/04/11 15:21:36 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#ifndef CUNITINTERFACESBML
#define CUNITINTERFACESBML

#include <vector>
#include <map>
#include <set>
#include "CUnit.h"

class Model;
class ASTNode;

/**
 * This class contains a copy of the unit information of an sbml model in the
 * data structures the unit conversion algorithm can deal with.
 * It contains lists of all objects/numbers that potentially can have units, and
 * a list of all mathematical expressions in the sbml model that impose constraints
 * on the units.
 */
class CUnitInterfaceSBML
{
private:
  // disable the assignment operator and the copy constructor
  // because right now I am too lazy to implement it. R.G.
  CUnitInterfaceSBML(const CUnitInterfaceSBML& src);

  CUnitInterfaceSBML& operator=(const CUnitInterfaceSBML& src);

public:

  /**
   * initialize the unit interface from an sbml model, extracting all
   * the unit information from the model
   */
  CUnitInterfaceSBML(Model * model, bool unitsFromModel);

  /**
   * Destructor.
   */
  ~CUnitInterfaceSBML();

  /**
   * initialize the unit interface from an sbml model, without using
   * any unit information from the model
   */
  //CUnitInterfaceSBML(Model * model, std::vector<CUnit> setOfUnits);

  //void initializeSetOfUnits(std::vector<CUnit> setOfUnits);

  void debugOutput() const;
  void calculateStatistics();

  /**
   * retrieve the SBML model
   */
  Model * getModel() {return mpModel;};
  const Model * getModel() const {return mpModel;};

  void setAssumeDimensionlessOne(bool f) {mAssumeDimensionlessOne = f;};

  /**
   *  Tries to determine unknown units by considering the known units
   *  and all the contrains imposed by the mathmatical expressions.
   */
  void determineUnits();

  /**
   *  Writes the units information back to an sbml model (without any unit conversions).
   * The most common use case for this will be to annotate the model with units of
   * objects that did not have explicit units before, e.g. parameters.
   */
  void writeBackToModel();

  class Statistics
  {
  public:
    std::vector<unsigned int> global, local, numbers, all;
  };

  /**
   * get statistics of the units of the model.
   * In each of the vectors:
   * 0: unknown
   * 1: default
   * 2: model wide provided units
   * 3: provided units
   * 4: derived units
   * 5: conflict
   */
  const Statistics & getStatistics() const {return mStatistics;};

  static void outputStatistics(const Statistics & stat, bool flag);

  /**
   * returns a list of sbml id corresponding to all global sbml objects that match
   * the given unit status (as explained above)
   */
  std::vector<std::string> getListOfObjectsWithGivenUnitStatus(int status) const;

  /**
   * returns a list of pairs of sbml IDs corresponding to all local parameters that match
   * the given unit status (as explained above)
   */
  std::vector<std::pair<std::string, std::string> > getListOfLocalParametersWithGivenUnitStatus(int status) const;

  /**
   * generates a message containing a list of the objects with unknown units.
   * The message should be suitable for presentation in a user interface.
   */
  std::string getMessageAboutUnknownUnits() const;

  /**
   * after determineUnits() was called this contains a set of terminal ASTNodes
   * in which a conflict was detected.
   * Note that is not necessarily where one would intuitively locate the conflict,
   * i's just where it was detected.
   */
  const std::set<const ASTNode *> & getListOfConflictingNodes() const;

  /**
    * This class contains the information about one mathematical expression
    * from an sbml model and how it relates to units constraints.
    */
  class CExpressionInformation
  {
  public:
    /// root node of an expression in the sbml model
    const ASTNode* mpExpression;

    /// specifies whether the units of the result of the expression are some unit divided by time
    bool mPerTime;

    /// if this is not "" then the root of the expression should have the units of the referenced object
    std::string mRootObject;

    /// if mRootObject is "" then this member specifies the units of the root of the expression
    CUnitInformation mRootUnit;

    /// id of a reaction. If this is set the local parameters of the reaction are in scope for the expression
    std::string mReactionId;

    /// error code after run
    int mErrorCode;

    /// this indicates the origin of the expression for display purposes, e.g. "kinetic law"
    std::string mTypeDescription;

    /// display name of the object that either contains the expression or the the expression applies to.
    std::string mObjectDisplayString;

    /// Default constructor
    CExpressionInformation(unsigned int sbmlLevel, unsigned int sbmlVersion)
        : mpExpression(NULL), mPerTime(false), mRootObject(), mRootUnit(CUnitInformation(sbmlLevel, sbmlVersion)), mReactionId(), mErrorCode(0)
    {};
  };

  /**
   * return the list of all mathematical expressions including additional information
   */
  const std::vector<CExpressionInformation> & getExpressions() const {return mSBMLExpressions;};

  /**
   * describes the local environment for the recursive unit analysis.
   * It can either be empty, in this case only the global objects are accessible.
   * If a reaction is provided the local parameters of this reaction are accessible.
   * If a stack of function variables is provided, the top level of this stack describes
   * the accessible variables in the frame. Local parameters and function variables
   * are never simultaneously accessible.
   */
  class CEnvironmentInformation
  {
  public:
    CEnvironmentInformation() {};
    CEnvironmentInformation(const std::string & ri): mReactionID(ri) {};

    ///tells if the current scope involves a reaction (local parameters)
    bool isReactionScope() const
    {return mReactionID != "" && mFrameStack.size() == 0;}

    ///drop the top level of the function variables frame stack
    void drop()
    {if (mFrameStack.size() > 0) mFrameStack.pop_back() ;};

    ///push a mapping for function variables onto the frame stack
    void push(std::map<std::string, ASTNode*> & frame)
    {mFrameStack.push_back(frame);};

    std::string mReactionID;
    std::vector<std::map<std::string, ASTNode*> > mFrameStack;
  };

  /**
   * provided with an identifier from an object node, this method tries to find the
   * mapped unit information. According to the provided environment, this could be
   * a local parameter or a global object.
   */
  CUnitInformation* getMappedUnitFromIdentifier(const std::string & node,
      const CEnvironmentInformation & ei);
  /**
   * find the unit information corresponding to a number node
   */
  CUnitInformation* getMappedUnitFromNumberNode(const ASTNode* node);

private:

  /**
   * initialize from sbml model. If unitsFromModel is true the unit information
   * is extracted from the model. Otherwise the units are constructed from a
   * set of base units that was provided by initializeSetOfUnits(). .
   */
  void initializeFromSBMLModel(bool unitsFromModel);

  ///initializes the base units with the defaults (moles, seconds, l, m, m^2)
  void initializeDefaultUnits();

  ///the sbml model from which this interface was initialized
  Model * mpModel;

  unsigned int mSBMLLevel;

  unsigned int mSBMLVersion;

  /**
    * This maps the id of any sbml object that can be referenced by one id to a copy
    * of its units information.
    */
  std::map<std::string, CUnitInformation> mSBMLObjectsMap;

  /**
    * This maps the id of a reaction and the id of a local parameter to a copy
    * of its units information. (Local parameters are the only objects in sbml that
    * need two ids for their identification)
    */
  std::map<std::string, std::map<std::string, CUnitInformation> > mSBMLLocalParametersMap;

  /**
    * This maps number nodes to units information
    */
  std::map<const ASTNode*, CUnitInformation> mSBMLNumbersMap;

  /**
    * a list of all mathematical expressions in the sbml model along with the
    * units information for their root node.
    */
  std::vector<CExpressionInformation> mSBMLExpressions;

  /**
   * indicated whether a number 1.0 and -1.0 is considered to be dimensionless
   */
  bool mAssumeDimensionlessOne;

  /// try to find out as much as possible about the units from one expression
  void handleOneExpression(CExpressionInformation & ei);

  CUnitInformation recursion(const ASTNode* node, const CUnitInformation & ui,
                             const CEnvironmentInformation & ei);

  /**
   *  This handles the units assignment/comparison/query for terminal node of the tree.
   * ui is the unit information that is passed from above, pNodeUnit is the unit information
   * that is already present in the terminal node, and the return value is the units of the node
   * after the assignment/comparison/querying. mError is set to 1 if a conflict appears.
   * The node is optional (it can be NULL), it is only used for reporting conflicts.
   * If a new conflict appears the node pointer is added to the mConflictingNodes set.
   */
  CUnitInformation handleTerminalNode(const CUnitInformation & ui, CUnitInformation *pNodeUnit, const ASTNode* node);

  /**
   * handle the case of a node where the units are supposed to be equal.
   * This includes plus, minus, choice, comparison operators
   */
  CUnitInformation recursionEqual(const ASTNode* node, const CUnitInformation & ui,
                                  const CEnvironmentInformation & ei);

  /**
   * handle a multiplication node. If one unit is unknown it can be calculated.
   * If no unit is unknown a consistency check can be made. If more than one unit
   * is unknown, nothing can be done.
   */
  CUnitInformation recursionTimes(const ASTNode* node, const CUnitInformation & ui,
                                  const CEnvironmentInformation & ei);

  /**
   * handle a division node. If one unit is unknown it can be calculated.
   * If no unit is unknown a consistency check can be made. If more than one unit
   * is unknown, nothing can be done.
   */
  CUnitInformation recursionDivide(const ASTNode* node, const CUnitInformation & ui,
                                   const CEnvironmentInformation & ei);

  CUnitInformation recursionPower(const ASTNode* node, const CUnitInformation & ui,
                                  const CEnvironmentInformation & ei);

  /**
   * handle the case of a pieewise node
   */
  CUnitInformation recursionPiecewise(const ASTNode* node, const CUnitInformation & ui,
                                      const CEnvironmentInformation & ei);

  class EvaluationResult
  {
  public:
    double result;
    bool known;
  };

  EvaluationResult evaluate(const ASTNode* node);

  /**
   * provided with an identifier from an object node, this method checks if it
   * corresponds to a function variable from the current environment.
   * If it does, the ASTNode* is returned, else NULL.
   */
  ASTNode* resolveVariableName(const std::string & node,
                               const CEnvironmentInformation & ei);

  /**
   * provided with an identifier from an object node, this method checks if it
   * corresponds to a function definition in the current model.
   * If it does, the FunctionDefinition* is returned, else NULL.
   */
  FunctionDefinition* resolveFunctionName(const std::string & node);

  //**** wrapper functions for node class *************************

  static bool isObject(const ASTNode* node);

  static bool isOperator(const ASTNode* node);

  ///determines if the node represents a number (integer, real, or rational)
  static bool isNumber(const ASTNode* node);

  ///determines if the node contains a call to a function definition
  static bool isFunctionCall(const ASTNode* node);

  ///determines if the node contains a call to a built in function
  static bool isBuiltInFunctionCall(const ASTNode* node);

  ///return the value of a number node
  static double getValueFromNumberNode(const ASTNode* node);

  static std::string getIdentifier(const ASTNode* node);

  //***********************************************

  CUnitInformation* mpSBMLTimeUnit;
  CUnitInformation* mpSBMLAmountUnit;
  CUnitInformation* mpSBMLVolumeUnit;
  CUnitInformation* mpSBMLAreaUnit;
  CUnitInformation* mpSBMLLengthUnit;

  CUnitInformation* mpSBMLConflictUnit;

  int mError;

  ///contains the (terminal) nodes where a conflict appeared
  std::set<const ASTNode *> mConflictingNodes;

  Statistics mStatistics;
};

#endif
