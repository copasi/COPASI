// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_MATHML
#define COPASI_MATHML

#include "copasi/model/CModelValue.h"
#include "copasi/model/CCompartment.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/xml/CCopasiXMLInterface.h"

#define SPC(level) std::string(level, ' ')

class CMathMl
{
public:

  static std::string fixName(const std::string & name)
  {
    std:: string Fixed;

    if (name.find_first_of(" ()*+-") == std::string::npos)
      Fixed = name;
    else
      Fixed = "\"" + name + "\"";

    return CCopasiXMLInterface::encode(Fixed, CCopasiXMLInterface::character);
  }

  static std::string getMMLName(const CDataObject* obj)
  {
    if (!obj) return "no object";

    //model value
    const CModelValue* mv = dynamic_cast<const CModelValue*>(obj);

    if (mv) return "<mi>" + fixName(mv->getObjectName()) + "</mi>";

    //metabolite
    //const CMetab* met = dynamic_cast<const CMetab*>(obj);
    //if (met) return "<mi>[" + met->getObjectName() + "]</mi>";

    //compartment
    const CCompartment* comp = dynamic_cast<const CCompartment*>(obj);

    if (comp) return "<msub><mi>V</mi><mi>" + fixName(comp->getObjectName())
                       + "</mi></msub>";

    //reference
    if (obj->getObjectType() == "Reference")
      {
        //model value
        if (obj->getObjectName() == "Value")
          {
            mv = dynamic_cast<const CModelValue*>(obj->getObjectParent());

            if (mv) return "<mi>" + fixName(mv->getObjectName()) + "</mi>";
          }

        //compartment
        if (obj->getObjectName() == "Volume")
          {
            comp = dynamic_cast<const CCompartment*>(obj->getObjectParent());

            if (comp) return "<msub><mi>V</mi><mi>" + fixName(comp->getObjectName())
                               + "</mi></msub>";
          }
      }

    return "<mi>" + fixName(obj->getObjectDisplayName()) + "</mi>";
  }
};

#endif
