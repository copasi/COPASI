// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef SENSWIDGETCOMBOBOX_H
#define SENSWIDGETCOMBOBOX_H

#include <QComboBox>

#include <vector>
#include "copasi/model/CObjectLists.h"

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
  void fillFromList(const std::vector< CObjectLists::ListType > & list);

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
