/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 09/20 
Comment : COptFunction for optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef COPASI_COptExpression
#define COPASI_COptExpression

#include "function/CKinFunction.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"

class COptMethod;
class COptProblem;

class COptFunction: public CCopasiContainer
  {
  public:
    std::vector<CCopasiObject*> mParaList;
    std::vector<std::string> mMinList;
    std::vector<std::string> mMaxList;
    std::vector<CKinFunction*> mFunctionList;

    // check if a parameter already existing inside the mParaList
    bool bExisted(const std::string & name);

    // add a new item inside
    int addItem(CCopasiObject* pObject);

    //remove an item with the existing name
    bool removeItem(const std::string & name);
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptFunction(const std::string & name = "NoName",
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const COptFunction &" src
     * @param "CReadConfig *" configBuffer (Default = NULL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptFunction(const COptFunction & src,
                 CReadConfig * configBuffer = NULL,
                 const CCopasiContainer * pParent = NULL);

    ~COptFunction();

  protected:

    void cleanup();
    COptProblem* mpProblem;
    COptMethod* mpMethod;

  public:
    std::string mKey;

    COptProblem* getProblem()
    {return mpProblem;}

    COptMethod* getMethod()
    {return mpMethod;}
  };
#endif
