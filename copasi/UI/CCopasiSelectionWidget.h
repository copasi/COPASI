// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionWidget_H__
#define CCopasiSelectionWidget_H__

#include <vector>

#include <QStackedWidget>

#include "copasi/UI/CQSimpleSelectionTree.h"

class ObjectBrowserWidget;
class CModel;
class CDataObject;

class CCopasiSelectionWidget: public QStackedWidget
{
  Q_OBJECT

public:
  CCopasiSelectionWidget(QWidget* parent = 0);
  ~CCopasiSelectionWidget();

  void populateTree(const CModel * model,
                    const CQSimpleSelectionTree::ObjectClasses & classes);
  void populateTree(const std::vector< const CDataObject * > & objectList);
  void setOutputVector(std::vector< const CDataObject * > * outputVector);
  void setSingleSelection(bool singleSelection);
  bool isSingleSelection() const;
  void setExpertMode(bool expertMode);
  void setAllowExpressions(bool allowExpressions);
  bool expertMode() const;
  void commit();

public slots:
  void commitSelection();

signals:
  void selectionCommitted();

protected:

  CQSimpleSelectionTree* mpSimpleTree;
  ObjectBrowserWidget* mpObjectBrowser;
  std::vector< const CDataObject * > * mpOutputVector;
  bool mSingleSelect;
  bool mExpertMode;
};

#endif
