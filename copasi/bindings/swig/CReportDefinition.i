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

#include "report/CReportDefinition.h"

%}

%ignore CReportDefinition::getBodyAddr() const;
%ignore CReportDefinition::getHeaderAddr() const;
%ignore CReportDefinition::getFooterAddr() const;
%ignore CReportDefinition::getTableAddr() const;

%extend CReportDefinition{

  void setSeparator(const CCopasiReportSeparator& separator)
  {
    self->setSeparator(separator.getStaticString());
  }
  
  int getNumBodyItems() 
  {
    std::vector<CRegisteredObjectName>* items = self->getBodyAddr();
    return (int)(items == NULL ? 0 : items->size());
  }
  
  CRegisteredObjectName getNthBodyItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getBodyAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredObjectName("");
    return items->at(index);
  }

  void removeNthBodyItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getBodyAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  int getNumHeaderItems() 
  {
    std::vector<CRegisteredObjectName>* items = self->getHeaderAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredObjectName getNthHeaderItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getHeaderAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredObjectName("");
    return items->at(index);
  }

  void removeNthHeaderItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getHeaderAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  int getNumFooterItems() 
  {
    std::vector<CRegisteredObjectName>* items = self->getFooterAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredObjectName getNthFooterItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getFooterAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredObjectName("");
    return items->at(index);
  }
  
  void removeNthFooterItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getFooterAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }


  int getNumTableItems() 
  {
    std::vector<CRegisteredObjectName>* items = self->getTableAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredObjectName getNthTableItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getTableAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredObjectName("");
    return items->at(index);
  }

  void removeNthTableItem(int index)
  {
    std::vector<CRegisteredObjectName>* items = self->getTableAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  

}


%include "report/CReportDefinition.h"


