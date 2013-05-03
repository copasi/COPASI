// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();

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

  std::string mKeyToCopy;
};

#endif // FunctionWidget1
