// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQRDFTreeView_h
#define CQRDFTreeView_h

#include <map>
#include <QtCore/QVariant>

#include "copasi/MIRIAMUI/ui_CQRDFTreeView.h"
#include "copasi/UI/copasiWidget.h"

class CRDFNode;
class CQRDFTreeViewItem;
class CRDFGraph;
class CAnnotation;

class CQRDFTreeView : public CopasiWidget, public Ui::CQRDFTreeView
{
  Q_OBJECT

public:
  CQRDFTreeView(QWidget* parent = 0, const char* name = 0);
  virtual ~CQRDFTreeView();

  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;

protected:
  virtual bool enterProtected();

protected slots:

public slots:
  /**
   * Clear the listeview
   */
  virtual void clear();

  /**
   * Returns the list view item for node if it exists otherwise NULL.
   * @param const CRDFNode * pSubject
   * @return CQRDFTreeViewItem * listViewItem
   */
  CQRDFTreeViewItem * find(const CRDFNode * pNode);

  /**
   * Insert a map from a CRDFNode to a CRDFListView
   * @param const CRDFNode * pSubject
   * @param CQRDFTreeViewItem * pItem
   */
  void insert(const CRDFNode * pNode, CQRDFTreeViewItem * pItem);

  // Attributes
private:
  /**
   * A map to look up items associated with a node.
   */
  std::map< const CRDFNode *, CQRDFTreeViewItem * > mNode2Item;

  /**
   * The RDF Graph
   */
  CRDFGraph * mpGraph;

  CAnnotation * mpAnnotation;

  void load();
};

#endif // CQRDFTreeView_h
