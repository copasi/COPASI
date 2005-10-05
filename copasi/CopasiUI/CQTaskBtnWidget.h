/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskBtnWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Tue Oct 4 17:05:38 2005
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.h,v 1.1 2005/10/05 16:24:07 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTASKBTNWIDGET_H
 #define CQTASKBTNWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QPushButton;

class CQTaskBtnWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTaskBtnWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTaskBtnWidget();

    QFrame* mpLine;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnRun;
    QPushButton* mpBtnReport;
    QPushButton* mpBtnAssistant;

  protected:
    QGridLayout* CQTaskBtnWidgetLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKBTNWIDGET_H
