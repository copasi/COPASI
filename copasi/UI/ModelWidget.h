/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelWidget.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/09/23 15:33:57 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/ModelWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Model Widget
 *****************************************************************************/
#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"
#include <qtextbrowser.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLineEdit;
class QLabel;
class QComboBox;
class QPushButton;
class CModel;

class ModelWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ModelWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ModelWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  protected:
    bool loadModel(CModel *model);
    bool saveToModel();
    std::string objKey;

    QGridLayout* ModelWidgetLayout;
    QHBoxLayout* Layout5;
    QLineEdit* LineEdit;
    QTextBrowser* textBrowser;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QComboBox* ComboBox1;
    QComboBox* ComboBox2;
    QComboBox* ComboBox3;

    QPushButton* commitChanges;
    QPushButton* cancelChanges;
  };

#endif // MODELWIDGET_H
