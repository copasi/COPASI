/* Begin CVS Header
$Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.h,v $
$Revision: 1.59 $
$Name:  $
$Author: shoops $
$Date: 2012/05/09 21:32:17 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H

#include "ui_FunctionWidget1.h"

class CFunction;

template <class CType> class CCopasiVectorN;

/*!
  \brief A widget class for Functions branch

  This widget shows detailed description of an individual function
 */
class FunctionWidget1 : public CopasiWidget, public Ui::FunctionWidget1
{
  Q_OBJECT

public:
  FunctionWidget1(QWidget *parent, const char * name = 0, Qt::WFlags f = 0);
  virtual ~FunctionWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  virtual void slotBtnNew();
  virtual void slotBtnDelete();

  virtual void slotFcnDescriptionChanged(bool);
  virtual void slotReversibilityChanged();

  void slotTableValueChanged(const QString &);

protected:
  virtual bool enterProtected();
  bool loadFromFunction(const CFunction* = NULL);
  bool loadParameterTable();
  bool loadUsageTable(/*const CCopasiVectorN<CUsageRange>& usages*/);
  bool loadReversibility(TriLogic rev);
  void updateApplication();
  bool saveToFunction();
  bool copyFunctionContentsToFunction(const CFunction* src, CFunction* target);

  bool functionParametersChanged();

  bool flagChanged;
  bool isValid;
  bool mIgnoreFcnDescriptionChange;

  CFunction * mpFunction;

private:
  void init();

  bool mReadOnly;
};

#endif // FunctionWidget1
