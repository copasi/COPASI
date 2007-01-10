// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CCopasiObject.h"
%}


class CCopasiObject
{
  public:
    CCopasiObject(const CCopasiObject & src,
                  const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiObject();

    bool setObjectName(const std::string& name);
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;
    const std::string& getObjectType() const;
    CCopasiContainer* getObjectParent() const;
    virtual CCopasiObjectName getCN() const;

    bool isContainer() const; 
    bool isVector() const; 
    bool isMatrix() const; 
    bool isNameVector() const; 
    bool isReference() const; 
    bool isValueBool() const; 
    bool isValueInt() const; 
    bool isValueDbl() const; 
    bool isNonUniqueName() const; 
    bool isStaticString() const; 
    bool isValueString() const; 
    bool isSeparator() const; 

    virtual const std::string& getKey() const;
    virtual const std::string& getObjectName() const;

};



