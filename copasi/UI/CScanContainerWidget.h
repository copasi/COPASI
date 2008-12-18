// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanContainerWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCONTAINERWIDGET_H
#define CCONTAINERWIDGET_H

#include <vector>
//#include <qvariant.h>
#include <q3table.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3Frame>
#include <Q3GridLayout>
#include <Q3HBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class Q3Frame;
class QLineEdit;
class QToolButton;
class Q3VBox;

class CUpDownSubwidget;

/**
 *  This widget is a table that contains other widgets (arranged vertically)
 *  it adds buttons to delete, move up or down the widgets
 */
class CScanContainerWidget : public Q3Table
  {
    Q_OBJECT

  public:
    CScanContainerWidget(QWidget* parent = 0, const char* name = 0 /*, WFlags fl = 0*/);
    ~CScanContainerWidget();

    std::vector<QWidget*> getWidgetList() const;
    void clearWidgetList();
    void addWidget(QWidget* widget, bool controls = true);

    //insert before row, if row=-1 insert before the last row
    void insertWidget(QWidget* widget, int row = -1);
    void enableCopy(const bool & enable);

  protected slots:
    void slotUp(int index);
    void slotDown(int index);
    void slotDel(int index);
    void slotCopy(int index);

  protected:
    void updateIndices();
    bool mCopyEnabled;

  signals:
    void itemDeleted();
    void copyWidget(int);
  };

#endif
