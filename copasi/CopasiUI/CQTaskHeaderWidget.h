/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskHeaderWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/07 14:15:11 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskHeaderWidget.ui'
 **
 ** Created: Fri Oct 7 13:39:32 2005
 **      by: The User Interface Compiler ($Id: CQTaskHeaderWidget.h,v 1.4 2005/10/07 14:15:11 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTASKHEADERWIDGET_H
 #define CQTASKHEADERWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>
 #include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class CCopasiTask;

class CQTaskHeaderWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTaskHeaderWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTaskHeaderWidget();

    QLabel* mpLblName;
    QCheckBox* mpUpdateModel;
    QCheckBox* mpBoxExecutable;

    bool setTaskName(const std::string & name);

  protected:
    QHBoxLayout* CQTaskHeaderWidgetLayout;
    QSpacerItem* mpSpacer1;
    QSpacerItem* mpSpacer2;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKHEADERWIDGET_H
