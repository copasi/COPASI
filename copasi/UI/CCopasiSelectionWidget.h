// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionWidget.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionWidget_H__
#define CCopasiSelectionWidget_H__

#include <vector>

#include <q3widgetstack.h>

#include "UI/CCopasiSimpleSelectionTree.h"

class ObjectBrowserWidget;
class CModel;
class CCopasiObject;

class CCopasiSelectionWidget: public Q3WidgetStack
{
  Q_OBJECT

public:
  CCopasiSelectionWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CCopasiSelectionWidget();

  void populateTree(const CModel * model,
                    const CCopasiSimpleSelectionTree::ObjectClasses & classes);
  void setOutputVector(std::vector< const CCopasiObject * > * outputVector);
  void setSingleSelection(bool singleSelection);
  bool isSingleSelection() const;
  void setExpertMode(bool expertMode);
  bool expertMode() const;
  void commit();

protected:
  CCopasiSimpleSelectionTree* mpSimpleTree;
  ObjectBrowserWidget* mpObjectBrowser;
  std::vector< const CCopasiObject * > * mpOutputVector;
  bool mSingleSelect;
  bool mExpertMode;
};

#endif
