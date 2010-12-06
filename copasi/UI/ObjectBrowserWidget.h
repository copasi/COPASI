// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ObjectBrowserWidget.h,v $
//   $Revision: 1.11.4.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/12/06 16:17:26 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include <qvariant.h>
#include <qwidget.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>
#include <vector>

template <class CType> class CCopasiVector;

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListView;
class Q3ListViewItem;
class Q3TextEdit;
class ObjectBrowserItem;
class ObjectList;
class Q3Frame;
class CCopasiContainer;
class CCopasiObject;
class CopasiUI3Window;
class QPixmap;

enum pageIndex {LISTVIEWPAGE = 0, SELECTEDITEMPAGE};

class ObjectBrowserWidget : public QWidget
{
  Q_OBJECT

public:
  ObjectBrowserWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0, int state = 0);
  virtual ~ObjectBrowserWidget();

  ObjectList* objectItemList;
  ObjectList* refreshList;

  Q3GridLayout* ObjectBrowserLayout;
  QPushButton* clearButton;
  QPushButton* toggleViewButton;
  QPushButton* commitButton;
  Q3ListView* ObjectListView;
  Q3Frame* Line1;
  QSpacerItem* spacer;
  Q3TextEdit* ObjectItemText;

  void eXport(ObjectBrowserItem* pCurrent, std::vector< const CCopasiObject * > * outputVector);
  void removeDuplicate(ObjectList* objectItemList);
  void setCheck(ObjectBrowserItem* pCurrent);
  void setUncheck(ObjectBrowserItem* pCurrent);
  void clickToReverseCheck(ObjectBrowserItem* pCurrent);
  void setCheckMark(ObjectBrowserItem* pCurrent);

  void loadData();
  void loadChild(ObjectBrowserItem* parent, const CCopasiContainer * copaParent, bool nField);
  void loadField(ObjectBrowserItem* parent, CCopasiVector<CCopasiObject>* copaParent);

  CCopasiObject* getFieldCopasiObject(CCopasiContainer * pCurrent, const char* name);
  void setOutputVector(std::vector< const CCopasiObject * > * pObjectVector);
  void selectObjects(std::vector< const CCopasiObject * > * pObjectVector);
  void updateUI();
  void loadUI();

  void swap(int, int, ObjectBrowserItem**);
  int partition(int, int, int, ObjectBrowserItem**);
  void quick_sort(int, int, ObjectBrowserItem**);

public slots:
  virtual void clearClicked();
  virtual void toggleViewClicked();
  virtual void commitClicked();
  virtual void listviewChecked(Q3ListViewItem*);

private:
  std::vector< const CCopasiObject * > * mOutputObjectVector;
  pageIndex currentPage;
  void selectObjects(ObjectBrowserItem* browserItem, const CCopasiObject * selectObject);
  void updateSelectedItemsView();
  void cleanup();
};
#endif // OBJECTBROWSERWIDGET_H
