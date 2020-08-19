// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H

#include "copasi/UI/ui_FunctionWidget1.h"

class CFunction;

template <class CType> class CDataVectorN;

/*!
  \brief A widget class for Functions branch

  This widget shows detailed description of an individual function
 */
class FunctionWidget1 : public CopasiWidget, public Ui::FunctionWidget1
{
  Q_OBJECT

public:
  FunctionWidget1(QWidget *parent, const char * name = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~FunctionWidget1();

protected slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();

  virtual void slotFcnDescriptionChanged(bool);
  virtual void slotReversibilityChanged();

  void slotTableValueChanged(const QString &);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  bool loadFromFunction(const CFunction* = NULL);
  bool loadParameterTable();
  bool loadUsageTable(/*const CDataVectorN<CUsageRange>& usages*/);
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

  CCommonName mObjectCNToCopy;
};

#endif // FunctionWidget1
