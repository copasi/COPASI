/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 17:59:10 $
   End CVS Header */

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <qlistbox.h>
#include "report/CCopasiObjectName.h"

class CCopasiObject;

class CQReportListItem : public QListBoxText
  {
    // Operations
  public:
    CQReportListItem(QListBox * listbox,
                     const std::string & cn);

    CQReportListItem(QListBox * listbox,
                     const CCopasiObject * pObject);

    ~CQReportListItem();

    void setText(const QString & text);

    const CCopasiObjectName & getCN() const;

    void refreshText();

    // Attributes
  private:
    CRegisteredObjectName mCN;
  };

#endif // COPASI_CQReportListItem
