// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListViewItem.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/22 16:57:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFListViewItem
#define COPASI_CRDFListViewItem

#include <qlistview.h>

class CRDFListView;

class CRDFListViewItem: public QListViewItem
  {
    // Operations
  public:
    /**
     * Default Constructor
     * @param CRDFListView * pParent (default: NULL)
     * @param CRDFListViewItem * pAfter (default: NULL)
     */
    CRDFListViewItem(CRDFListView * pParent = NULL, CRDFListViewItem * pAfter = NULL);

    /**
     * Specific Constructor
     * @param CRDFListViewItem * pParent (default: NULL)
     * @param CRDFListViewItem * pAfter (default: NULL)
     */
    CRDFListViewItem(CRDFListViewItem * pParent, CRDFListViewItem * pAfter = NULL);

    /**
     * Destructor
     */
    virtual ~CRDFListViewItem();
  };

#endif // COPASI_CRDFListViewItem
