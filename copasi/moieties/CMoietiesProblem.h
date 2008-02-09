// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesProblem.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:58:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMoietiesProblem
#define COPASI_CMoietiesProblem

#include "copasi/utilities/CCopasiProblem.h"

class CMoietiesProblem : public CCopasiProblem
  {
    // Implementation

  public:

    /**
     * Default constructor
     * @param const CCopasiTask::Type & type (default: moieties)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesProblem(const CCopasiTask::Type & type = CCopasiTask::moieties,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CMoietiesProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesProblem(const CMoietiesProblem & src,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CMoietiesProblem();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Do all neccessary initialization so that calls to caluclate will
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Do all neccessary restore procedures so that the
     * model is in the same state as before
     * @parem const bool & updateModel
     * @result bool succes
     */
    virtual bool restore(const bool & updateModel);

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * This is the output method for any result of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implmented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;
  };

#endif  // COPASI_CMoietiesProblem
