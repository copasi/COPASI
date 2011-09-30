// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CLNAResultSubwidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:41 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CLNAResultSubwidget.h
 *
 *
 *  Created by Juergen Pahle on 2010-06-01.
 *
 */

#ifndef CLNARESULTSUBWIDGET_H
#define CLNARESULTSUBWIDGET_H

#include <QtCore/QVariant>

#include "ui_CLNAResultSubwidget.h"

#include "CQArrayAnnotationsWidget.h"

class CLNAMethod;

class CLNAResultSubwidget : public CopasiWidget, public Ui::CLNAResultSubwidget
{
  Q_OBJECT

public:
  CLNAResultSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CLNAResultSubwidget();

  virtual void loadAll(const CLNAMethod * lnaMethod);
  virtual void loadCovarianceMatrix(const CLNAMethod * lnaMethod);
  virtual void loadCovarianceMatrixReduced(const CLNAMethod * lnaMethod);
  virtual void loadBMatrixReduced(const CLNAMethod * lnaMethod);
  virtual void clear();

protected:
  virtual void init();

protected slots:

  virtual void slotSave();
  virtual void slotScaled();


private:
  const CLNAMethod * mLNAMethod;

};

#endif // CLNARESULTSUBWIDGET_H
