// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

#ifndef CSCANWIDGET_PARAMETER_SETS_H
#define CSCANWIDGET_PARAMETER_SETS_H

#include <map>

#include "copasi/model/CModelParameterSet.h"

#include "copasi/UI/ui_CQScanWidgetParameterSet.h"
#include "copasi/UI/CScanItemData.h"

class CModel;
class CDataObject;

class CCopasiParameterGroup;

class CQScanWidgetParameterSet : public QWidget, public CScanItemData, public Ui::CQScanWidgetParameterSet
{
  Q_OBJECT

public:
  CQScanWidgetParameterSet(QWidget * parent = 0);

  CQScanWidgetParameterSet(const CQScanWidgetParameterSet & src, QWidget * parent = 0);

  virtual ~CQScanWidgetParameterSet();

  virtual void load(const CCopasiParameterGroup * pItem);

  virtual bool save(CCopasiParameterGroup * pItem) const;

  void initFromSelection(std::map< QString, const CModelParameterSet * > & selection);

protected:

  std::map< QString, const CModelParameterSet * > mSelection;

protected slots:

  virtual void slotChooseParameterSets();
  

private:
  void init();
};

#endif // CSCANWIDGET_PARAMETER_SETS_H
