/****************************************************************************
 **  $ CopasiUI/MoietyWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Moiety Widget, i.e the second level 
 ** of Moieties.
 *****************************************************************************/
#ifndef MOIETYWIDGET1_H
#define MOIETYWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"
#include <qtextbrowser.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class CModel;
class MoietyWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    MoietyWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MoietyWidget1();
    CModel *mModel;
    void loadMoieties(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);
    QString *Moiety1_Name;

    QLabel* TextLabel1;
    QLineEdit* LineEdit2;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;
    QTextBrowser* textBrowser;

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  signals:
    void signal_emitted(const QString &);
    void leaf(CModel*);
    void updated();

  protected:
    QGridLayout* MoietyWidget1Layout;
  };

#endif // MOIETYWIDGET1_H
