/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TableDefinition.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:13:02 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/TableDefinition.h               
 **  $ Author  : Liang Xu
 **  
 ** This is the header file for the TableDefinition Widget, i.e the First level 
 ** of TableDefinition.
 *****************************************************************************/

#ifndef TableDefinition_WIDGET_H
#define TableDefinition_WIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "copasiWidget.h"

class QPushButton;
class QGridLayout;
class QTable;
class MyTable;

class TableDefinition : public CopasiWidget
  {
    Q_OBJECT

  protected:
    MyTable* table;
    QPushButton* btnOK;
    QPushButton* btnCancel;
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    TableDefinition(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);
    void createNewObject();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void tableValueChanged(int, int);

  private:
    void fillTable();
  };

#endif
