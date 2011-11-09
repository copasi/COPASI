/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/copasimathml.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/11/09 16:45:26 $
   End CVS Header */

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_MATHML
#define COPASI_MATHML

#include "model/CModelValue.h"
//#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "report/CCopasiObjectReference.h"
#include "xml/CCopasiXMLInterface.h"

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

  static std::string getMMLName(const CCopasiObject* obj)
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
