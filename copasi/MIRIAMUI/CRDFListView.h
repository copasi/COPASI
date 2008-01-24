// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListView.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/24 16:08:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFListView
#define COPASI_CRDFListView

#include <qlistview.h>

class CRDFListView : public QListView
  {
    Q_OBJECT

  public:
    CRDFListView(QWidget * pParent = NULL, const char * name = NULL, WFlags flag = 0);
    virtual ~CRDFListView();
  };

#endif // COPASI_CRDFListView
