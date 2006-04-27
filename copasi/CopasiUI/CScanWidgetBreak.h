/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetBreak.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetBreak.ui'
 **
 ** Created: Tue Mar 28 14:23:44 2006
 **      by: The User Interface Compiler ($Id: CScanWidgetBreak.h,v 1.4 2006/04/27 01:27:42 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETBREAK_H
#define CSCANWIDGETBREAK_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QComboBox;
class QLabel;
class CCopasiParameterGroup;
class CScanProblem;

class CScanWidgetBreak : public QWidget
  {
    Q_OBJECT

  public:
    CScanWidgetBreak(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CScanWidgetBreak();

    QFrame* frame;
    QComboBox* comboBoxReport;
    QLabel* textLabelReport;
    QComboBox* comboBoxPlot;
    QLabel* labelTitle;
    QLabel* textLabelPlot;

    virtual bool initFromScanItem(CCopasiParameterGroup * pg);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected:
    QVBoxLayout* CScanWidgetBreakLayout;
    QGridLayout* frameLayout;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CSCANWIDGETBREAK_H
