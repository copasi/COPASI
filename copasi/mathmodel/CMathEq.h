/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathEq.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:24:29 $
   End CVS Header */

/**
 * CMathEq class.
 * The class CMathEq is describes the right hand side of an equation describing
 * a CMathVariable.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathEq
#define COPASI_CMathEq

#include "utilities/CCopasiTree.h"
#include "CMathNode.h"

class CMathVariable;

/** @dia:pos 27.7959,-3.77715 */
class CMathEq
  {
    // Attributes
  private:
    const CMathVariable * mpVariable;

    CCopasiTree< CMathNode > mLeft;

    CCopasiTree< CMathNode > mRight;

    // Operation
  public:
    CMathEq();

    CMathEq(const CMathEq & src);

    ~CMathEq();

    bool setVariable(const CMathVariable * pVariable);

    const CMathVariable * getVariable() const;

    CCopasiTree< CMathNode > & getLeft();

    CCopasiTree< CMathNode > & getRight();

    std::string getLeftText() const;

    std::string getRightText() const;
  };

#endif // COPASI_CMathEq
