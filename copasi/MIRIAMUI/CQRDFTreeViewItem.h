// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQRDFTreeViewItem.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/13 01:40:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CQRDFTreeViewItem
#define COPASI_CQRDFTreeViewItem

#include <QTreeWidgetItem>

#include "copasi/MIRIAM/CRDFTriplet.h"

class CQRDFTreeView;
class CRDFNode;
class CRDFEdge;

class CQRDFTreeViewItem: public QTreeWidgetItem
{
  // Operations
public:
  /**
   * Default Constructor
   * @param QTreeWidget * pParent
   * @param CQRDFTreeViewItem * pAfter (default: NULL)
   */
  CQRDFTreeViewItem(QTreeWidget * pParent, CQRDFTreeViewItem * pAfter = NULL);

  /**
   * Specific Constructor
   * @param CQRDFTreeViewItem * pParent
   * @param CQRDFTreeViewItem * pAfter (default: NULL)
   */
  CQRDFTreeViewItem(CQRDFTreeViewItem * pParent, CQRDFTreeViewItem * pAfter = NULL);

  /**
   * Destructor
   */
  virtual ~CQRDFTreeViewItem();

  /**
   * Set the RDF triplet represented by this item
   * @param const CRDFTriplet & triplet
   */
  void setTriplet(const CRDFTriplet & triplet);

  // Attributes
private:
  /**
   * The triplet represneted by this item.
   */
  CRDFTriplet mTriplet;
};

#endif // COPASI_CQRDFTreeViewItem
