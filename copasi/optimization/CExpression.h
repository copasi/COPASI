/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 09/20 
Comment : CExpression for optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef COPASI_COptExpression
#define COPASI_COptExpression

#include "function/CKinFunction.h"
#include "utilities/readwrite.h"

class CExpression: public CKinFunction
  {
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
     * @param "const CFunction &" src
     * @param "CReadConfig *" configBuffer (Default = NULL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const CFunction & src,
                CReadConfig * configBuffer = NULL,
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CKinFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const CKinFunction & src,
                const CCopasiContainer * pParent = NULL);

    ~CExpression();

  protected:

    void cleanup();
  };
#endif
