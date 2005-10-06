/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/06 19:19:18 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Wed Oct 5 16:43:27 2005
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.h,v 1.2 2005/10/06 19:19:18 shoops Exp $)
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
class QPushButton;
class QFrame;

class CQTaskBtnWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTaskBtnWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTaskBtnWidget();

    QPushButton* mpBtnRun;
    QPushButton* mpBtnAssistant;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnReport;
    QFrame* mpLine;

  protected:
    QVBoxLayout* CQTaskBtnWidgetLayout;
    QGridLayout* mpGridLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKBTNWIDGET_H
