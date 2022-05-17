// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 


%{

#include "copasi/core/CDataArray.h"

%}

%ignore CArrayInterface::operator[] (const index_type & index); 
%ignore CArrayInterface::operator[] (const index_type & index) const;
%ignore CArray::operator[] (const index_type & index); 
%ignore CArray::operator[] (const index_type & index) const;
%ignore CMatrixInterface::operator[] (const index_type & index); 
%ignore CMatrixInterface::operator[] (const index_type & index) const;
%ignore CVectorInterface::operator[] (const index_type & index) ;
%ignore CVectorInterface::operator[] (const index_type & index) const;
%ignore CDataArray::operator=(const CDataArray&);
%ignore CDataArray::array() const;
%ignore operator<<(std::ostream &os, const CDataArray & o);


#ifdef SWIGPERL
// we need a new typemap for the get function below
// to accept a reference to a cell array as the index argument
%typemap (in) const CArrayInterface::index_type & MY_FUNNY_INDEX {
  // this typemap is almost identical with the one that
  // is described for handling char** values in section 30.8.1
  // of the SWIG manual  

  // first we check if the argument is a reference
  if (!SvROK($input)) {
    croak("Argument $argnum is not a reference.");
  }
  // the argument has to be an array
  if (SvTYPE(SvRV($input)) != SVt_PVAV) {
    croak("Argument $argnum is not an array.");
  }

  // now we convert the array to a index type which should always be 
  // a std::vector with size_t values
  AV* tmpav = (AV*)SvRV($input);
  // av_len returns the index of the last element, not the length
  I32 len = av_len(tmpav);

  // the object that we dynamically allocate here
  // has to be deleted by a separate freearg typemap
  // (see below)
  $1 = new CArrayInterface::index_type;
  SV **tv;
  for(I32 i=0;i <= len;++i)
  {
    tv = av_fetch(tmpav,i,0);
    assert(*tv != NULL);
    $1->push_back(SvIV(*tv));
  }
};

// Since we allocate the temporary vector in the in typemap above on the heap,
// we need to make sure the object is deleted after the call.
%typemap (freearg) const CArrayInterface::index_type & MY_FUNNY_INDEX {
 delete $1;
}
#endif // SWIGPERL


%include "copasi/core/CDataArray.h"
%include "copasi/core/CMatrix.h"
%include "copasi/core/CArray.h"

%extend CArrayInterface {
   /* convert the operator[] to get methods */
   /* The argument needs a name that is unique so that I can write a specific typemap 
      (see above).    
   */ 
   virtual CArrayInterface::data_type get(const CArrayInterface::index_type & MY_FUNNY_INDEX)
   {
      return (*($self))[MY_FUNNY_INDEX];
   }

   /** overload for easy access of 2d arrays */
   virtual CArrayInterface::data_type get(int index1, int index2)
   {  
      CArrayInterface::index_type MY_FUNNY_INDEX(2);
      MY_FUNNY_INDEX[0] = index1;
      MY_FUNNY_INDEX[1] = index2;
      return (*($self))[MY_FUNNY_INDEX];
   }

   /** overload for easy access of 2d arrays */
   virtual CArrayInterface::data_type get(int index1, int index2, int index3)
   {  
      CArrayInterface::index_type MY_FUNNY_INDEX(3);
      MY_FUNNY_INDEX[0] = index1;
      MY_FUNNY_INDEX[1] = index2;
      MY_FUNNY_INDEX[2] = index3;
      return (*($self))[MY_FUNNY_INDEX];
   }


};

%template(AnnotatedFloatMatrix) CMatrixInterface<CMatrix<C_FLOAT64> >;
typedef CMatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;

