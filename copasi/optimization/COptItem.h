/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/06 17:10:20 $
   End CVS Header */

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include "utilities/CCopasiParameterGroup.h"

class COptItem : public CCopasiParameterGroup
  {
    //Operations
  private:
    /**
     * Default Constructor
     */
    COptItem();

  public:
    /**
     * Specific Constructor
     */
    COptItem(const std::string & name,
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy Constructor
     * @param 
     */
    COptItem(const COptItem & src);

    /**
     * Destructor
     */
    ~COptItem();
  };

#endif // COPASI_COptItem
