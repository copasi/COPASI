/****************************************************************************
 ** Form interface generated from reading ui file '.\MoietyWidget1.ui'
 **
 ** Created: Tue Mar 4 01:38:30 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef MOIETYWIDGET1_H
#define MOIETYWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class CModel;
class MoietyWidget1 : public QWidget
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
    QLineEdit* LineEdit1;
    QLineEdit* LineEdit2;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  signals:
    void signal_emitted(QString &);
  protected:
    QGridLayout* MoietyWidget1Layout;
  };

#endif // MOIETYWIDGET1_H
