/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MetabolitesWidget.h,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/01/24 16:20:54 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget, i.e the First level 
 ** of Compartments.
 *****************************************************************************/

#ifndef METABOLITES_WIDGET_H
#define METABOLITES_WIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "CopasiTableWidget.h"

class MetabolitesWidget : public CopasiTableWidget
  {
    Q_OBJECT

  public:
    MetabolitesWidget(QWidget *parent, const char * name = 0, WFlags f = 0)
        : CopasiTableWidget(parent, false, name, f)
    {init();}

  protected slots:
    virtual void slotBtnToggleClicked();

  protected:

    bool mFlagConc;
    QPushButton* btnToggle;

    /**
     * This initializes the widget 
     */
    virtual void init();

    /**
     * shows units for the quantities 
     */
    void showHeaders();

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
  };

#endif
