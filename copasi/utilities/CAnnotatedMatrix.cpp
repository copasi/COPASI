/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/11/26 15:45:59 $
   End CVS Header */

#include "CAnnotatedMatrix.h"
#include "report/CKeyFactory.h"

CAnnotatedMatrix::CAnnotatedMatrix(const std::string & name,
                                   const CCopasiContainer * pParent):
    CMatrix<C_FLOAT64>(),
    CCopasiContainer(name, pParent, "AnnotatedMatrix",
                     CCopasiObject::Container |
                     CCopasiObject::NonUniqueName),
    mKey(GlobalKeys.add("AnnotatedMatrix", this))
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CAnnotatedMatrix::CAnnotatedMatrix(const CAnnotatedMatrix & src,
                                   const CCopasiContainer * pParent):
    CMatrix<C_FLOAT64>(),
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("AnnotatedMatrix", this))
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CAnnotatedMatrix::~CAnnotatedMatrix()
{}
