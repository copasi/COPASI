// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CCopasiParameter.h"

%}

%ignore operator<<;

%ignore CCopasiParameter::getValue() const;
%ignore CCopasiParameter::getValue();
%ignore CCopasiParameter::XMLType;
%ignore CCopasiParameter::TypeName;
%ignore CCopasiParameter::print;
%ignore operator==;
%ignore CCopasiParameter::getValuePointer;
%ignore CCopasiParameter::CCopasiParameter(const std::string & , const Type & , const void * , const CCopasiContainer * , const std::string & );
%ignore CCopasiParameter::CCopasiParameter(const std::string & , const Type & , const void * , const CCopasiContainer * );
%ignore CCopasiParameter::CCopasiParameter(const std::string & , const Type & , const void *);


#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CCopasiParameter::operator =;

#endif // SWIGJAVA || CSHARP

#ifdef SWIGR
%ignore CCopasiParameter::getType() const;
#endif // SWIGR

// suppress warnings on nested structures
%warnfilter(325) Value;

%include "utilities/CCopasiParameter.h"

#ifdef SWIGR
%rename(getType) CCopasiParameter::getType() const;
#endif // SWIGR


%extend CCopasiParameter
{
    
  C_FLOAT64 getDblValue()
  {
    return *self->getValue().pDOUBLE;
  }

  C_FLOAT64 getUDblValue()
  {
    return *self->getValue().pUDOUBLE;
  }

  C_INT32 getIntValue()
  {
    return *self->getValue().pINT;
  }

  unsigned C_INT32 getUIntValue()
  {
    return *self->getValue().pUINT;
  }

  bool getBoolValue()
  {
    return *self->getValue().pBOOL;
  }

  std::vector<CCopasiParameter*> getGroupValue()
  {
    return *self->getValue().pGROUP;
  }

  std::string getStringValue()
  {
    return *self->getValue().pSTRING;
  }

  CRegisteredObjectName getCNValue()
  {
    return *self->getValue().pCN;
  }

  std::string getKeyValue()
  {
    return *self->getValue().pKEY;
  }

  std::string getFileValue()
  {
    return *self->getValue().pFILE;
  }

  /**
   * Returning a pointer to void in the bindings doesn't make sense I
   * think. 
  void* getVoidValue()
  {
    return self->getValue().pVOID;
  }
  */

  bool setDblValue(const C_FLOAT64& v)
  {
    return self->setValue(v);
  }

  bool setUDblValue(const C_FLOAT64& v)
  {
    return self->setValue(v);
  }

  bool setUIntValue(const unsigned C_INT32& v)
  {
    return self->setValue(v);
  }

  bool setIntValue(const C_INT32& v)
  {
    return (self->setValue(v) || self->setValue((const unsigned C_INT32&)v));
  }

  bool setBoolValue(const bool& v)
  {
    return self->setValue(v);
  }

  bool setGroupValue(const std::vector<CCopasiParameter*>& v)
  {
    return self->setValue(v);
  }

  bool setStringValue(const std::string& v)
  {
    return self->setValue(v);
  }

  bool setCNValue(const CRegisteredObjectName& v)
  {
    return self->setValue(v);
  }

  bool setKeyValue(const std::string& v)
  {
    return self->setValue(v);
  }

  bool setFileValue(const std::string& v)
  {
    return self->setValue(v);
  }

#ifdef SWIGR
  CCopasiParameter::Type getType() const
  {
    return $self->getType();
  }
#endif // SWIGR

}


