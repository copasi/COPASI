// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/04 18:13:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CTABWIDGET_H
#define CTABWIDGET_H

/**This class is the container for the two widgets - the entity widget
 * and the associated MIRIAM object widget.
 */
class CTabWidget : public QTabWidget
  {
  public:
    CTabWidget(QWidget* parent = 0, QWidget* Tab1Widget,
               QString& label1, QWidget* Tab2Widget, QString& label2 = "MIRIAM Info",
               const char* name = 0, WFlags f = 0);
    ~CTabWidget();
    QWidget* getTab1Widget();
    QWidget* getTab2Widget();

  protected:
    QWidget* Tab1Widget;
    QWidget* Tab2Widget;

  protected slots:

  private slots:
  };

#endif // CTABWIDGET_H
