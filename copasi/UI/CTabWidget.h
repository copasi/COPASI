// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/10 20:33:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <qtabwidget.h>

#include "copasiWidget.h"

class CopasiWidget;
/**This class is the container for the two widgets - the entity widget
 * and the associated MIRIAM object widget.
 */
class CTabWidget : public CopasiWidget
  {
  public:
    CTabWidget(QString& label1, QString& label2,
               QWidget* parent = 0, const char* name = 0, WFlags f = 0);
    ~CTabWidget();
    CopasiWidget* getTab1Widget();
    CopasiWidget* getTab2Widget();

  protected:
    QTabWidget *mTabWidget;
    CopasiWidget* Tab1Widget;
    CopasiWidget* Tab2Widget;
  };

#endif // CTABWIDGET_H
