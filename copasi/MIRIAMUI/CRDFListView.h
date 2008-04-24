// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListView.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/29 15:01:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFListView
#define COPASI_CRDFListView

#include <set>

#include <qlistview.h>

class CRDFNode;

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

    /**
     * Clear the set of visited nodes
     */
    void clearVisitedNodes();

    /**
     * Checks wether a node has already been visited. If not
     * the node is added to the set of visited nodes.
     * @param const CRDFNode * pNode
     * @return bool visited
     */
    bool visited(const CRDFNode * pNode);

    // Attributes
  private:
    /**
     * A set of visited nodes to prevent infinite recursion in cyclic graphs
     */
    std::set< const CRDFNode * > mVisitedNodes;
  };

#endif // COPASI_CRDFListView
