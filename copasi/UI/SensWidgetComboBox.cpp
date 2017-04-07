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

#include <QtCore/QVariant>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QLayout>
#include <QToolTip>
#include <QWhatsThis>
#include <QMessageBox>
#include <QToolButton>
#include <QImage>

#include <QFrame>
#include <QFileDialog>
#include <QTableWidget>

#include <algorithm>

#include "SensWidgetComboBox.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "copasi/sensitivities/CSensProblem.h"

SensWidgetComboBox::SensWidgetComboBox(QWidget * parent, const char * name)
  : QComboBox(parent)
{
  setObjectName(QString::fromUtf8(name));
}

void SensWidgetComboBox::fillFromList(const std::vector<CObjectLists::ListType> & list)
{
  //store old selection
  CObjectLists::ListType oldItem = getCurrentObjectList();

  mIndexTable = list;

  //fill combobox
  clear();
  std::vector<CObjectLists::ListType>::const_iterator it, itEnd = mIndexTable.end();

  for (it = mIndexTable.begin(); it != itEnd; ++it)
    insertItem(this->count(), FROM_UTF8(CObjectLists::ListTypeName[*it]));

  //restore old selection, if possible
  if (!setCurrentObjectList(oldItem))
    setCurrentIndex(0);
}

CObjectLists::ListType SensWidgetComboBox::getCurrentObjectList() const
{
  unsigned int index = currentIndex();

  if (index < mIndexTable.size())
    return mIndexTable[currentIndex()];
  else
    return CObjectLists::EMPTY_LIST;
}

bool SensWidgetComboBox::setCurrentObjectList(CObjectLists::ListType lt)
{
  std::vector<CObjectLists::ListType>::const_iterator it;
  it = std::find(mIndexTable.begin(),
                 mIndexTable.end(),
                 lt);

  if (it == mIndexTable.end()) return false;

  setCurrentIndex(it - mIndexTable.begin());
  return true;
}
