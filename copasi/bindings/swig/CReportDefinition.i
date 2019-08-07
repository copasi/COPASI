// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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

#include "copasi/report/CReportDefinition.h"

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
    std::vector<CRegisteredCommonName>* items = self->getBodyAddr();
    return (int)(items == NULL ? 0 : items->size());
  }
  
  CRegisteredCommonName getNthBodyItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getBodyAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredCommonName("");
    return items->at(index);
  }

  void removeNthBodyItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getBodyAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  int getNumHeaderItems() 
  {
    std::vector<CRegisteredCommonName>* items = self->getHeaderAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredCommonName getNthHeaderItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getHeaderAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredCommonName("");
    return items->at(index);
  }

  void removeNthHeaderItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getHeaderAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  int getNumFooterItems() 
  {
    std::vector<CRegisteredCommonName>* items = self->getFooterAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredCommonName getNthFooterItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getFooterAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredCommonName("");
    return items->at(index);
  }
  
  void removeNthFooterItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getFooterAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }


  int getNumTableItems() 
  {
    std::vector<CRegisteredCommonName>* items = self->getTableAddr();
    return (int)(items == NULL ? 0 : items->size());
  }

  CRegisteredCommonName getNthTableItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getTableAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return CRegisteredCommonName("");
    return items->at(index);
  }

  void removeNthTableItem(int index)
  {
    std::vector<CRegisteredCommonName>* items = self->getTableAddr();
    if (items == NULL || index < 0 || (int)items->size() <= index) 
      return;
    items->erase(items->begin() + index);
  }

  void addHeaderItem(std::string item)
  {
    self->getHeaderAddr()->push_back(CRegisteredCommonName(item));
  }
  
  void addFooterItem(std::string item)
  {
    self->getFooterAddr()->push_back(CRegisteredCommonName(item));
  }
  
  void addBodyItem(std::string item)
  {
    self->getBodyAddr()->push_back(CRegisteredCommonName(item));
  }
  
  void addTableItem(std::string item)
  {
    self->getTableAddr()->push_back(CRegisteredCommonName(item));
  }
  

}


%include "report/CReportDefinition.h"


