/****************************************************************************
 **  $ CopasiUI/MetabolitesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolites Widget, i.e the First level 
 ** of Metabolites.
 *****************************************************************************/

#ifndef FIXED_METABOLITE_SYMBOLS_H
#define FIXED_METABOLITE_SYMBOLS_H

#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"
#include "mathmodel/CMathModel.h"
#include "mathmodel/CMathConstant.h"
#include <qtable.h>
#include <qpushbutton.h>

class FixedMetaboliteSymbols : public QWidget
  {
    Q_OBJECT

  protected:
    const CModel * mModel;
    CMathModel *mathmodel;
    CMathConstantMetab *metablist;
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  signals:
    void name(QString &);

  public:
    FixedMetaboliteSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFixedMetaboliteSymbols(CModel *model);
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
