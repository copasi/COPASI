// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 


%{

#include "copasi/utilities/CCopasiParameter.h"

%}

%ignore operator<<;

%ignore CCopasiParameter::getValue() const;
%ignore CCopasiParameter::getValue();
%ignore CCopasiParameter::XMLType;
%ignore CCopasiParameter::TypeName;
%ignore CCopasiParameter::print;
%ignore operator==;
%ignore CCopasiParameter::getValuePointer;
%ignore CCopasiParameter::CCopasiParameter(const std::string & , const Type & , const void * , const CDataContainer * , const std::string & );
%ignore CCopasiParameter::CCopasiParameter(const std::string & , const Type & , const void * , const CDataContainer * );
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

%include "copasi/utilities/CCopasiParameter.h"

#ifdef SWIGR
%rename(getType) CCopasiParameter::getType() const;
#endif // SWIGR


%extend CCopasiParameter
{
    
  C_FLOAT64 getDblValue()
  {
    C_FLOAT64 val = self->getValue<C_FLOAT64>();
    return val;
  }

  C_FLOAT64 getUDblValue()
  {
    C_FLOAT64 val = self->getValue<C_FLOAT64>();
    return val;
  }

  C_INT32 getIntValue()
  {
    C_INT32 val = self->getValue<C_INT32>();    
    return val;
  }

  unsigned C_INT32 getUIntValue()
  {
    unsigned C_INT32 val = self->getValue<unsigned C_INT32>();    
    return val;
  }

  bool getBoolValue()
  {
    bool val = self->getValue<bool>();    
    return val;
  }

  std::vector<CCopasiParameter*> getGroupValue()
  {
    if (self->getType() != CCopasiParameter::Type::GROUP)
      return std::vector<CCopasiParameter*>();

    std::vector<CCopasiParameter*> val = self->getValue< std::vector<CCopasiParameter*> >();
    return val;
  }

  std::string getStringValue()
  {
    if (self->getType() != CCopasiParameter::Type::STRING && 
      self->getType() != CCopasiParameter::Type::KEY &&
      self->getType() != CCopasiParameter::Type::FILE && 
      self->getType() != CCopasiParameter::Type::CN &&
      self->getType() != CCopasiParameter::Type::EXPRESSION)
      return "";

    std::string val = self->getValue<std::string>();
    return val;
  }

  CCommonName getCNValue()
  {
    if (self->getType() != CCopasiParameter::Type::CN)
      return CCommonName();

    CCommonName val = self->getValue<CCommonName>();
    return val;
  }

  std::string getKeyValue()
  {
    if (self->getType() != CCopasiParameter::Type::STRING && 
      self->getType() != CCopasiParameter::Type::KEY &&
      self->getType() != CCopasiParameter::Type::FILE && 
      self->getType() != CCopasiParameter::Type::CN &&
      self->getType() != CCopasiParameter::Type::EXPRESSION)
      return "";

    std::string val = self->getValue<std::string>();
    return val;
  }

  std::string getFileValue()
  {
    if (self->getType() != CCopasiParameter::Type::STRING && 
      self->getType() != CCopasiParameter::Type::KEY &&
      self->getType() != CCopasiParameter::Type::FILE && 
      self->getType() != CCopasiParameter::Type::CN &&
      self->getType() != CCopasiParameter::Type::EXPRESSION)
      return "";
      
    std::string val = self->getValue<std::string>();
    return val;
  }

  void* getVoidValue()
  {
    void* val = self->getValue<void*>();
    return val;
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

  bool setCNValue(const CCommonName& v)
  {
    return self->setValue(v);
  }
  
  bool setCNValue(const std::string& v)
  {
    return self->setValue(CCommonName(v));
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


