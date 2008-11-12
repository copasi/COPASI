// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiParameter.i,v $ 
//   $Revision: 1.7.6.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
// End CVS Header 

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

%ignore CCopasiParameter::getValue() const;
%ignore CCopasiParameter::getValue();
%ignore CCopasiParameter::XMLType;
%ignore operator==;

%include "utilities/CCopasiParameter.h"

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

  void* getVoidValue()
  {
    return self->getValue().pVOID;
  }

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

}


