// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CReferencesWidget.h,v $
//   $Revision: 1.5.6.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/27 13:55:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CReferencesWidget
#define COPASI_CReferencesWidget

#include <vector>

#include "UI/CopasiTableWidget.h"

#include "copasi.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

class CReferencesWidget : public CopasiTableWidget
  {
    Q_OBJECT
  private:
    QStringList mResources;

  public:
    CReferencesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    ~CReferencesWidget();
    /**
    * This initializes the widget
    */
    virtual void init();

    /**
     * returns a list of objects that should be displayed
     */
    virtual std::vector<const CCopasiObject*> getObjects() const;

    /**
     * fills one table row with the data from one object
     */
    virtual void tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row);

    /**
     * reads the contents of one row of the table and writes it to the object
     */
    virtual void tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj);

    /**
     * creates a new object
     */
    virtual CCopasiObject* createNewObject(const std::string & name);

    /**
     * deletes objects. Performs all additional tasks, like asking the user, ...
     */
    virtual void deleteObjects(const std::vector<std::string> & keys);

    /**
     * this is used to fill a row of the table when a new object is added to the table.
     * it fills only the data columns, not the name. It should not fill column exc.
     */
    virtual void defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc);

    /**
     * the prefix that is used to construct new object names
     */
    virtual QString defaultObjectName() const;

    void updateResourcesList();

    virtual void slotDoubleClicked(int, int, int, const QPoint &);
    virtual void slotValueChanged(int row, int col);
  };

#endif // COPASI_CReferencesWidget
