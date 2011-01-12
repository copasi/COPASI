/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDimension.h,v $
 $Revision: 1.9.4.1 $
 $Name:  $
 $Author: shoops $
 $Date: 2011/01/12 19:13:21 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_DIMENSION
#define COPASI_DIMENSION

#include <string>
#include <vector>
#include "copasi.h"

class CCopasiDataModel;

/**
 * CDimension class.
 * The class describes the dimension of a value, usually a CFunctionParameter.
 *
 * The dimension is given as a quintuple of real numbers: (amount of substance, volume, time, area, length).
 * It can also be "unknown" or "contradiction". The actual unit can be constructed from the
 * dimension and the 5 basic units from the CModel class (which is done in the
 * getDisplayString() method).
 */
class CDimension
{
public:

  CDimension();

  void setUnknown();
  bool isUnknown() const;

  void setContradiction();
  bool isContradiction() const;

  void setDimension(const C_FLOAT64 & d1, const C_FLOAT64 & d2, const C_FLOAT64 & d3,
                    const C_FLOAT64 & d4, const C_FLOAT64 & d5);

  std::string getDisplayString(const CCopasiDataModel* pDataModel) const;
  std::string getDebugString() const;

  bool operator==(const CDimension & rhs) const;
  CDimension operator+(const CDimension & rhs) const;
  CDimension operator-(const CDimension & rhs) const;
  CDimension operator*(const C_FLOAT64 & rhs) const;

  CDimension compare(const CDimension & rhs) const;

  /**
   * If one of the base units is dimensionless, the corresponding exponent is
   * adjusted to be 0.0.
   * d1,d2,d3, d4, d5 indicate whether the base units are dimensionless
   */
  void fixDimensionless(bool d1, bool d2, bool d3, bool d4, bool d5);

  /**
   * insert operator
   */
  //friend std::ostream & operator<<(std::ostream &os, const CDimension & d);
  std::string print(const CCopasiDataModel* pDataModel) const;

private:

  ///exponent of quantity base unit
  C_FLOAT64 mD1;
  ///exponent of volume base unit
  C_FLOAT64 mD2;
  ///exponent of time base unit
  C_FLOAT64 mD3;
  ///exponent of area base unit
  C_FLOAT64 mD4;
  ///exponent of length base unit
  C_FLOAT64 mD5;

  bool mUnknown;
  bool mContradiction;

  static std::string constructDisplayElement(const std::string & base, C_FLOAT64 exponent);
};

//******************************************************************+

class CFunction;
class CReaction;
class CEvaluationNode;
class CChemEq;

/**
 * CFindDimensions class.
 * The class tries to find the dimensions of the "PARAMETER" variable nodes
 * in a function tree.
 *
 * The function is specified in the constructor. After that the dimension of the root node
 * has to be specified. This can be done with either of the two public findDimensions()
 * methods.
 * The result can be retrieved using the getDimensions() method.
 */
class CFindDimensions
{
private:
  CFindDimensions();

public:

  /**
   * construct the class for a given function.
   * d1,d2,d3, d4, d5 indicate if the base unit (for quantity, volume, time, area, length) is dimensionless
   */
  CFindDimensions(const CFunction* function, bool d1, bool d2, bool d3, bool d4, bool d5);

  /**
   * initialize the known dimensions (from the parameter roles) and
   * set the others to "unknown". This is called by the constructor.
   */
  void setupDimensions();

  /**
   * find the dimensions from explicitly given root node dimension
   */
  void findDimensions(CDimension rootDim);

  /**
   * find the dimensions for a function that is used in a reaction
   * the dimension of the root node depends on the number of compartments
   * that are involved in the reaction
   */
  void findDimensions(bool isMulticompartment);

  /**
   * find the dimensions for both a one-compartment and a multi-compartment reaction
   */
  std::vector<std::string> findDimensionsBoth(const CCopasiDataModel* pDataModel);

  const std::vector<CDimension> & getDimensions() const;

  //print the content of mDimensions to cout
#ifdef COPASI_DEBUG
  void printDebugOutput(const CCopasiDataModel* pDataModel) const;
#endif // COPASI_DEBUG

  void setUseHeuristics(bool flag);

  /**
   * tell about chemical equation. This is needed only for mass action kinetics.
   * It is ignored otherwise.
   */
  void setChemicalEquation(const CChemEq* eq);

  void setMolecularitiesForMassAction(const size_t & m1,
                                      const size_t & m2);

private:

  const CFunction * mpFunction;
  std::vector<CDimension> mDimensions;
  CDimension mRootDimension;
  bool mUseHeuristics;
  //const CChemEq* mpChemEq;
  C_FLOAT64 mM1;
  C_FLOAT64 mM2;

  bool mD1;
  bool mD2;
  bool mD3;
  bool mD4;
  bool mD5;

  ///find dim for all parameters
  void findDimensions();

  ///determine dimensions for mass action kinetics
  ///chemical equation needs to be known
  void findDimensionsMassAction();

  ///find dim for one parameter
  void findDimension(size_t index);

  CDimension findDimension(const CEvaluationNode * node,
                           const CEvaluationNode * requestingNode = NULL);
};

#endif
