/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSProblem.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/22 15:42:42 $
   End CVS Header */

/**
 *  CTSSProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTSSProblem
#define COPASI_CTSSProblem

#include <string>

#include "utilities/CCopasiProblem.h"

class CTSSProblem: public CCopasiProblem
  {
  public:
    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSProblem(const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     *  @param "const CTSSProblem &" src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CTSSProblem(const CTSSProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CTSSProblem();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */ 
    //virtual bool setModel(CModel * pModel);

    /**
     * Retrieve the model the problem is dealing with.
     * @return "CModel *" pModel
     */ 
    //CModel * getModel() const;
  };

#endif // COPASI_CTSSProblem
