// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionWidget_H__
#define CCopasiSelectionWidget_H__

#include <vector>

#include <QtGui/QStackedWidget>

#include "UI/CQSimpleSelectionTree.h"

class ObjectBrowserWidget;
class CModel;
class CCopasiObject;

class CCopasiSelectionWidget: public QStackedWidget
{
  Q_OBJECT

public:
  CCopasiSelectionWidget(QWidget* parent = 0);
  ~CCopasiSelectionWidget();

  void populateTree(const CModel * model,
                    const CQSimpleSelectionTree::ObjectClasses & classes);
  void setOutputVector(std::vector< const CCopasiObject * > * outputVector);
  void setSingleSelection(bool singleSelection);
  bool isSingleSelection() const;
  void setExpertMode(bool expertMode);
  bool expertMode() const;
  void commit();

protected:
  CQSimpleSelectionTree* mpSimpleTree;
  ObjectBrowserWidget* mpObjectBrowser;
  std::vector< const CCopasiObject * > * mpOutputVector;
  bool mSingleSelect;
  bool mExpertMode;
};

#endif
