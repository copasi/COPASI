// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
//   $Revision: 1.12.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:58 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

#include "ui_CQSensResultWidget.h"

#include "CQArrayAnnotationsWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

class CQSensResultWidget : public CopasiWidget, public Ui::CQSensResultWidget
{
  Q_OBJECT

public:
  CQSensResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQSensResultWidget();

  void newResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:


  void saveToFile();

protected:
  virtual bool enterProtected();
  //bool loadFromBackend();
  void clearArrays();

  const CArrayAnnotation * mpResult;
  const CArrayAnnotation * mpScaledResult;
  const CArrayAnnotation * mpCollapsedResult;

private:
  void init();
};

#endif
