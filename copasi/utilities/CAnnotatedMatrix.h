/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/11/26 16:54:26 $
   End CVS Header */

#ifndef CANNOTATEDMATRIX_H
#define CANNOTATEDMATRIX_H

#include <utilities/CMatrix.h>
#include "report/CCopasiContainer.h"

//preliminary
#include <string>
#define C_KEYTYPE std::string

#include "CCopasiVector.h"

/**
 */
class CAnnotatedMatrix : public CMatrix<C_FLOAT64>, public CCopasiContainer
  {
  private:
    C_KEYTYPE mKey;

    C_KEYTYPE mRowsReference;
    C_KEYTYPE mColumnsReference;

    std::vector<C_KEYTYPE> mRowsReferences;
    std::vector<C_KEYTYPE> mColumnsReferences;

  public:
    CAnnotatedMatrix(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL);

    CAnnotatedMatrix(const CAnnotatedMatrix & src,
                     const CCopasiContainer * pParent = NULL);

    ~CAnnotatedMatrix();

    const C_KEYTYPE & getRowsReference() const
      {return mRowsReference;}

    const C_KEYTYPE & getColumnsReference() const
      {return mRowsReference;}

    const std::vector<C_KEYTYPE> & getRowsReferences() const
      {return mRowsReferences;}

    const std::vector<C_KEYTYPE> & getColumnsReferences() const
      {return mColumnsReferences;}

    template <class CType1, class CType2>
          void setup(const CCopasiVector<CType1> & rows, const CCopasiVector<CType2> & columns)
      {
        resize(rows.size(), columns.size());
        //all the references
      }
  };

#endif
