// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensWidgetComboBox.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:58 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef SENSWIDGETCOMBOBOX_H
#define SENSWIDGETCOMBOBOX_H

#include <QtGui/QComboBox>

#include <vector>

#include "copasi/copasi.h"
#include "copasi/sensitivities/CSensProblem.h"

/**
  * This class handles a combobox to choose from lists of object lists
  */
class SensWidgetComboBox : public QComboBox
{
  Q_OBJECT

public:

  SensWidgetComboBox(QWidget * parent = 0, const char * name = 0);

  /**
   * this fills the combobox with a new list of entries. If the
   * old current value is still allowed in the new list, it is set.
   * Otherwise the box shows the first item.
   */
  void fillFromList(const std::vector<CObjectLists::ListType> & list);

  CObjectLists::ListType getCurrentObjectList() const;

  /**
   * set current selection (if possible). It returns true
   * if the operation was successful.
   */
  bool setCurrentObjectList(CObjectLists::ListType lt);

protected:

  std::vector<CObjectLists::ListType> mIndexTable;
};

#endif // SENSWIDGETCOMBOBOX_H
