/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CompartmentsWidget.h,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2003/10/16 20:37:53 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget, i.e the First level 
 ** of Compartments.
 *****************************************************************************/

#ifndef COMPARTMENTS_WIDGET_H
#define COMPARTMENTS_WIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "copasiWidget.h"

class QPushButton;
class QGridLayout;
class QTable;
class MyTable;

class CompartmentsWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    MyTable* table;
    QPushButton* btnOK;
    QPushButton* btnCancel;
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    CompartmentsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
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

    virtual void CurrentValueChanged(int, int);

  private:
    void fillTable();
    void createNewObject();

    int m_SavedCol;
    int m_SavedRow;
    int prev_row;
    int prev_col;
  };

#endif
