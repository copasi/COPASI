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

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
#include <qtextbrowser.h>
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
    CModel *mModel;
    void loadModel(CModel *model);
    QString name;

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
    //QFrame* Line4_3;

  public slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  signals:

  protected:
    QGridLayout* ModelWidgetLayout;
    QHBoxLayout* Layout5;
  };

#endif // MODELWIDGET_H
