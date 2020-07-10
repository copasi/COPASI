// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description:
Date: 04/03
Comment : Copasi Object Browser:
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OBJECTBROWSERWIDGET_H
#define OBJECTBROWSERWIDGET_H

#include <QWidget>
#include <vector>

template <class CType> class CDataVector;

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;
class QTextEdit;
class ObjectBrowserItem;
class ObjectList;
class QFrame;
class CDataContainer;
class CDataObject;
class CopasiUI3Window;
class QPixmap;

enum pageIndex {LISTVIEWPAGE = 0, SELECTEDITEMPAGE};

class ObjectBrowserWidget : public QWidget
{
  Q_OBJECT

public:
  ObjectBrowserWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags(), int state = 0);
  virtual ~ObjectBrowserWidget();

  ObjectList *objectItemList;
  ObjectList *refreshList;

  QGridLayout *ObjectBrowserLayout;
  QPushButton *clearButton;
  QPushButton *toggleViewButton;
  QPushButton *commitButton;
  QTreeWidget *ObjectListView;
  QFrame *Line1;
  QSpacerItem *spacer;
  QTextEdit *ObjectItemText;

  void eXport(ObjectBrowserItem *pCurrent, std::vector< const CDataObject * > *outputVector);
  void removeDuplicate(ObjectList *objectItemList);
  void setCheck(ObjectBrowserItem *pCurrent);
  void setUncheck(ObjectBrowserItem *pCurrent);
  void clickToReverseCheck(ObjectBrowserItem *pCurrent);
  void setCheckMark(ObjectBrowserItem *pCurrent);

  void loadData();
  void loadChild(ObjectBrowserItem *parent, const CDataContainer *copaParent, bool nField);
  void loadField(ObjectBrowserItem *parent, CDataVector<CDataObject> *copaParent);

  CDataObject *getFieldCopasiObject(CDataContainer *pCurrent, const char *name);
  void setOutputVector(std::vector< const CDataObject * > *pObjectVector);
  void selectObjects(std::vector< const CDataObject * > *pObjectVector);
  void updateUI();
  void loadUI();

  void swap(int, int, ObjectBrowserItem **);
  int partition(int, int, int, ObjectBrowserItem **);
  void quick_sort(int, int, ObjectBrowserItem **);

public slots:
  virtual void clearClicked();
  virtual void toggleViewClicked();
  virtual void commitClicked();
  virtual void listviewChecked(QTreeWidgetItem *, int);

private:
  std::vector< const CDataObject * > *mOutputObjectVector;
  pageIndex currentPage;
  void selectObjects(ObjectBrowserItem *browserItem, const CDataObject *selectObject);
  void updateSelectedItemsView();
  void cleanup();
};
#endif // OBJECTBROWSERWIDGET_H
