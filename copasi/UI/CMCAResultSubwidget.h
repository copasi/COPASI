// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/21 15:21:13 $
// End CVS Header
// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CMCAResultSubwidget.h
 *
 *
 *  Created by Paul on 4/2/10.
 *
 */

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <qvariant.h>

#include "ui_CMCAResultSubwidget.h"

#include "CQArrayAnnotationsWidget.h"

class CMCAMethod;

class CMCAResultSubwidget : public CopasiWidget, public Ui::CMCAResultSubwidget
{
  Q_OBJECT

public:
  CMCAResultSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CMCAResultSubwidget();

  virtual void loadAll(const CMCAMethod * mcaMethod);
  virtual void loadElasticities(const CMCAMethod * mcaMethod);
  virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
  virtual void loadFluxCCs(const CMCAMethod * mcaMethod);
  virtual void clear();

protected:
  virtual void init();

protected slots:
  virtual void languageChange();

  virtual void slotSave();
  virtual void slotScaled();


private:
  const CMCAMethod * mMCAMethod;

};

#endif // CMCARESULTSUBWIDGET_H
