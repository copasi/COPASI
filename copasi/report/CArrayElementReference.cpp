// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CArrayElementReference.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/23 06:22:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CArrayElementReference.h"
#include "CCopasiContainer.h"

CArrayElementReference::CArrayElementReference(const std::string & name,
    const CCopasiContainer * pParent,
    CCopasiAbstractArray::data_type & reference,
    const unsigned C_INT32 & flag)
    : CCopasiObject(name, pParent, "Reference",
                    CCopasiObject::Reference |
                    CCopasiObject::NonUniqueName |
                    CCopasiObject::ValueDbl |
                    flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
}

std::string CArrayElementReference::getObjectDisplayName(bool regular, bool richtext) const
  {
    //supress "Value"
    if (getObjectParent() && getObjectName() == "Value")
      return getObjectParent()->getObjectDisplayName(regular, richtext);

    //special treatment of metab children
    if (getObjectParent()->getObjectType() == "Metabolite")
      {
        if (getObjectName() == "Concentration")
          {
            if (richtext)
              {
                return "<font color=\"#2222cc\">[</font>"
                + getObjectParent()->getObjectDisplayName(regular, richtext)
                + "<font color=\"#2222cc\">]</font>";
              }
            else
            {return "[" + getObjectParent()->getObjectDisplayName(regular, richtext) + "]";}
          }

        if (getObjectName() == "InitialConcentration")
          {
            if (richtext)
              {
                return "<font color=\"#2222cc\">[</font>"
                + getObjectParent()->getObjectDisplayName(regular, richtext)
                + "<font color=\"#2222cc\">]<sub>0</sub></font>";
              }
            else
            {return "[" + getObjectParent()->getObjectDisplayName(regular, richtext) + "]_0";}
          }
      }

    return CCopasiObject::getObjectDisplayName(regular, richtext);
  }
