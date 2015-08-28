// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CFixLocalReactionParameters
#define COPASI_CFixLocalReactionParameters

#include <map>

class CModel;
class CCopasiParameter;
class CExpression;

class CFixLocalReactionParameters
{
  // Operations
public:
  /**
   * Constructor
   */
  CFixLocalReactionParameters();

  /**
   * Constructor
   */
  ~CFixLocalReactionParameters();

  /**
   * Check and fix the given model if needed
   * @param CModel * pModel
   */
  void fixModel(CModel * pModel);

private:
  /**
   * Checks whether the model needs to be fixed and builds
   * the listed of needed changes
   */
  void checkModel();

  /**
   * Change the model
   */
  void changeModel();

  // Attributes
private:
  /**
   * The model which needs to be fixed.
   */
  CModel * mpModel;

  /**
   *
   */
  std::multimap< CCopasiParameter *, const CExpression * > mChanges;
};

#endif // COPASI_CFixLocalReactionParameters
