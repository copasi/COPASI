// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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
