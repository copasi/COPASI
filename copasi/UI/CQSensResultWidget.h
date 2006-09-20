/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
   $Revision: 1.1.2.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/20 12:00:36 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

#include "qvbox.h"
#include "copasiWidget.h"
//#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CAnnotatedMatrix.h"

class QGridLayout;
class QLineEdit;
class QLabel;
class QTable;

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class ArrayAnnotationsWidget : public QVBox
  {
    Q_OBJECT

  public:
    ArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ArrayAnnotationsWidget();

    void setArrayAnnotation(const CArrayAnnotation * pArray);

  protected slots:

    void selectionTableChanged(int row, int col);

  protected:

    void fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable(unsigned C_INT32 rowIndex,
                   CCopasiAbstractArray::index_type & index);

    /**
     *  only for dimensionality > 2
     */
    void initSelectionTable();

    /**
     *  get the active item from the combo box in the specified
     *  row in the mpSelectionTable
     */
    C_INT32 currentItem(C_INT32 row);

    /**
     *  set the active item of the combo box in the specified
     *  row in the mpSelectionTable
     */
    void setCurrentItem(C_INT32 row, C_INT32 index);

    /**
     *  store the current state of all the combo boxes
     */
    void storeCurrentCombos();

    void clearWidget();

    QTable* mpSelectionTable;
    QTable* mpContentTable;

    const CArrayAnnotation * mpArray;

    /**
     * the current active item of all the combo boxes
     */
    std::vector<C_INT32> combos;
  };

class CQSensResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSensResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQSensResultWidget();

    void newResult();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    bool loadFromBackend();

    QGridLayout* mWidgetLayout;

    QLabel* mLabelTitle;

    ArrayAnnotationsWidget* mArrayWidget;

    const CArrayAnnotation * mpResult;

    //QLabel* mLabelSum;
    //QLabel* mLabelDivergence;
    //QLabel* mLabelComment;

    //QTable* mTableExponents;
    //QLineEdit* mLineEditSum;
    //QLineEdit* mLineEditDivergence;
  };

#endif
