// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListView.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/11 13:00:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFListView
#define COPASI_CRDFListView

#include <map>
#include <qlistview.h>

class CRDFNode;
class CRDFListViewItem;

class CRDFListView : public QListView
  {
    Q_OBJECT

  public:
    /**
     * Default Constructor
     * @param QWidget * pParent (default: NULL)
     * @param const char * name (default: NULL)
     * @param WFlags flag (default: 0)
     */
    CRDFListView(QWidget * pParent = NULL, const char * name = NULL, WFlags flag = 0);

    /**
     * Destructor
     */
    virtual ~CRDFListView();

  public slots:
    /**
     * Clear the listeview
     */
    virtual void clear();

    /**
     * Returns the list view item for node if it exists otherwise NULL.
     * @param const CRDFNode * pSubject
     * @return CRDFListViewItem * listViewItem
     */
    CRDFListViewItem * find(const CRDFNode * pNode);

    /**
     * Insert a map from a CRDFNode to a CRDFListView
     * @param const CRDFNode * pSubject
     * @param CRDFListViewItem * pItem
     */
    void insert(const CRDFNode * pNode, CRDFListViewItem * pItem);

    // Attributes
  private:
    /**
     * A map to look up items associated with a node.
     */
    std::map< const CRDFNode *, CRDFListViewItem * > mNode2Item;
  };

#endif // COPASI_CRDFListView
