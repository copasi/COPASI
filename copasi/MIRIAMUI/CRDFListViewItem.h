// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListViewItem.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/24 16:08:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFListViewItem
#define COPASI_CRDFListViewItem

#include <qlistview.h>

class CRDFListView;
class CRDFNode;

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

    /**
     * Set the RDF node represented by this item
     * @param const CRDFNode * pNode
     */
    void setNode(const CRDFNode * pNode);
  };

#endif // COPASI_CRDFListViewItem
