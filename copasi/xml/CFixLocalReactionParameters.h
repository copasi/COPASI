// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CFixLocalReactionParameters.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:34:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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
    std::multimap< CCopasiParameter *, CExpression * > mChanges;
  };

#endif // COPASI_CFixLocalReactionParameters
