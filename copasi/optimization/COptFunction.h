/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/Attic/COptFunction.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/10/18 16:39:46 $
   End CVS Header */

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
  public:       //function
    std::vector<CCopasiObject*> mParaList;
    std::vector<std::string> mMinList;
    std::vector<std::string> mMaxList;
    std::vector<std::string> mMinOperList;
    std::vector<std::string> mMaxOperList;
    std::vector<CKinFunction*> mMinFunctionList;
    std::vector<CKinFunction*> mMaxFunctionList;

    // check if a parameter already existing inside the mParaList
    int Index(const std::string & name);

    // add a new item inside
    int addItem(CCopasiObject* pObject);

    //remove an item with the existing name
    bool removeItem(const std::string & name);

    //get key function of a COptFunction
    inline std::string getKey()
    {return mKey;}

    COptProblem* getProblem()
    {return mpProblem;}

    COptMethod* getMethod()
    {return mpMethod;}

  public:       // constructor and deconstuctor
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

  private:
    void cleanup();
    COptProblem* mpProblem;
    COptMethod* mpMethod;
    std::string mKey;
  };
#endif
