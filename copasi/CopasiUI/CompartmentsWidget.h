/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CompartmentsWidget.h,v $
   $Revision: 1.31 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/19 10:07:44 $
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
    QPushButton* btnDelete;
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    CompartmentsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotDoubleClicked(int, int, int, const QPoint &);
    virtual void slotTableSelectionChanged();
    virtual void slotValueChanged(int, int);
    virtual void slotCurrentChanged(int, int);

    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnDeleteClicked();

  private:
    void fillTable();
    void saveTable();
    //void createNewObject();
    void updateRow(const C_INT32 row);
    QString createNewName(const QString name);
    void resizeTable(const unsigned C_INT32 numRows);

    //specific
    void init();
    void tableLineFromObject(const CCopasiObject* obj, std::vector<QString>& list);
    void tableLineToObject(const C_INT32 row, CCopasiObject* obj);
    CCopasiObject* createNewObject(const std::string & name);
    void deleteObjects(const std::vector<std::string> & keys);

    void defaultTableLineContent(std::vector<QString>& list);
    QString defaultObjectName();

    C_INT32 numCols;
    std::vector<bool> mFlagChanged;
    std::vector<bool> mFlagDelete;
    std::vector<bool> mFlagNew;
    std::vector<bool> mFlagRenamed;

    bool mIgnoreUpdates;

    int m_SavedCol;
    int m_SavedRow;
    int prev_row;
    int prev_col;
  };

#endif
