/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:52 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/MetabolitesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolites Widget, i.e the First level 
 ** of Metabolites.
 *****************************************************************************/

#ifndef METABOLITES_WIDGET_H
#define METABOLITES_WIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "copasiWidget.h"

class QPushButton;
class QTable;
class MyTable;

class MetabolitesWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnSwitchCols; //By G
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    MetabolitesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void tableValueChanged(int, int);

    virtual void slotBtnSwitchColsClicked(); //By G
    virtual void MyCurrentChanged(int, int); //By G

  private:
    void fillTable();
    void createNewObject();

    int m_SavedCol; //By G
    int m_SavedRow; //By G
    int prev_row; //By G
    int prev_col; //By G
    int btn_flag; //By G
  };

#endif
