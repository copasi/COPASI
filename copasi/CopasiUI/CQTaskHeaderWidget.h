/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskHeaderWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskHeaderWidget.ui'
 **
 ** Created: Tue Oct 4 17:05:38 2005
 **      by: The User Interface Compiler ($Id: CQTaskHeaderWidget.h,v 1.1 2005/10/05 16:24:07 shoops Exp $)
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
    QCheckBox* mpBoxExecutable;

    bool setTaskName(const std::string & name);
    bool saveExecutable(CCopasiTask * pTask);
    bool loadExecutable(const CCopasiTask * pTask);

  protected:
    QHBoxLayout* CQTaskHeaderWidgetLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKHEADERWIDGET_H
