/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/06 17:10:20 $
   End CVS Header */

#include "copasi.h"

#include "COptItem.h"

COptItem::COptItem() :
    CCopasiParameterGroup()
{}

COptItem::COptItem(const std::string & name,
                   const CCopasiContainer * pParent) :
    CCopasiParameterGroup(name, pParent)
{}

COptItem::COptItem(const COptItem & src) :
    CCopasiParameterGroup(src)
{}

COptItem::~COptItem()
{}
