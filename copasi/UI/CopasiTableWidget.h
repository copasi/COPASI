// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CopasiTableWidget.h,v $
//   $Revision: 1.28 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h
 **  $ Author  : Mudita Singhal
 **
 ** This is the header file for the Compartments Widget, i.e the First level
 ** of Compartments.
 *****************************************************************************/

#ifndef COPASI_TABLE_WIDGET_H
#define COPASI_TABLE_WIDGET_H

#include <vector>

#include <qtable.h>
#include <qevent.h>

#include "copasi.h"
#include "UI/copasiWidget.h"

class QPushButton;
class QGridLayout;
//class QTable;
class QHBoxLayout;
//class MyTable;
class CCopasiObject;

class CopasiTableWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CopasiTableWidget(QWidget *parent, bool ro, const char * name = 0, WFlags f = 0, bool showButtons = true);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    bool isTableInFocus();
    bool isChanged();
    virtual void saveTable();

  protected slots:
    virtual void slotTableSelectionChanged();
    virtual void slotCurrentChanged(int, int);
    virtual void slotTableDelKey();

  public slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnDeleteClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnClearClicked();
    virtual void slotDoubleClicked(int, int, int, const QPoint &);
    virtual void slotValueChanged(int, int);

    //void resizeEvent(QResizeEvent * re);

  protected:
    void fillTable();
    //void createNewObject();
    void updateRow(const C_INT32 row);
    void handleSBMLId(const CCopasiObject* obj, unsigned C_INT32 row);
    QString createNewName(const QString name);
    void resizeTable(const unsigned C_INT32 numRows);
    bool isTableChanged();

    QTable* table;

    QPushButton* btnOK;
    QPushButton* btnCancel;
    QPushButton* btnDelete;
    QPushButton* btnNew;
    QPushButton* btnClear;
    //    QHBoxLayout* mHLayout;
    QHBoxLayout* mExtraLayout;
    std::vector<std::string> mKeys;

    C_INT32 numCols;

    std::vector<bool> mFlagChanged;
    std::vector<bool> mFlagDelete;
    std::vector<bool> mFlagNew;
    std::vector<bool> mFlagRenamed;
    std::vector<bool> mFlagRO;

    bool mChanged;

    //bool mIgnoreUpdates;
    bool mRO;
    bool mShowButtons;
    ListViews::ObjectType mOT;

    /**
     The flag to be set if columns in the table need to be justified
    */
    bool flagtoAdjust;

    /*Flag for showing or hiding 'object renamed to No Name' warning.*/
    bool mShowNewObjectWarning;

    /*Whether to call saveTable() when leave() is called.*/
    bool mSaveOnLeave;

    //These are the methods that need to be implemented by specialized widgets:

    /**
     * This initializes the widget
     */
    virtual void init() = 0;

    /**
     * Update the units in column headers
     */
    virtual void updateHeaderUnits();

    /**
     * returns a list of objects that should be displayed
     */
    virtual std::vector<const CCopasiObject*> getObjects() const = 0;

    /**
     * fills one table row with the data from one object
     */
    virtual void tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row) = 0;

    /**
     * reads the contents of one row of the table and writes it to the object
     */
    virtual void tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj) = 0;

    /**
     * creates a new object
     */
    virtual CCopasiObject* createNewObject(const std::string & name) = 0;

    /**
     * deletes objects. Performs all additional tasks, like asking the user, ...
     */
    virtual void deleteObjects(const std::vector<std::string> & keys) = 0;

    /**
     * this is used to fill a row of the table when a new object is added to the table.
     * it fills only the data columns, not the name. It should not fill column exc.
     */
    virtual void defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc) = 0;

    /**
     * the prefix that is used to construct new object names
     */
    virtual QString defaultObjectName() const = 0;

    /**
     * This method provides a hook for derived classes to act on changes in
     * the table.
     * @param unsigned C_INT32 row
     * @param unsigned C_INT32 col
     */
    virtual void valueChanged(unsigned C_INT32 /*row*/, unsigned C_INT32 /*col*/)
    {return;}

    /**
     * to catch the delKeyEvent
     */
    virtual void keyPressEvent (QKeyEvent * e);

  signals:
    void setEnableOKAndCancel(bool e);
    void delKeyPressed();
  };

#endif
