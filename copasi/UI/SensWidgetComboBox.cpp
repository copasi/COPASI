// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensWidgetComboBox.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/06 16:14:09 $
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

//#include <q3filedialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
//#include <qcombobox.h>
//#include <q3frame.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
//#include <q3table.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>
#include <qimage.h>
//Added by qt3to4:
//#include <Q3GridLayout>

#include <QFrame>
#include <QFileDialog>
#include <QTableWidget>

#include <algorithm>

#include "SensWidgetComboBox.h"
#include "qtUtilities.h"

/*
#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CCopasiSelectionDialog.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"
#include "sensitivities/CSensMethod.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "CQSensResultWidget.h"
 */

SensWidgetComboBox::SensWidgetComboBox(QWidget * parent, const char * name)
    : QComboBox(false, parent, name)
{}

void SensWidgetComboBox::fillFromList(const std::vector<CObjectLists::ListType> & list)
{
  //store old selection
  CObjectLists::ListType oldItem = getCurrentObjectList();

  mIndexTable = list;

  //fill combobox
  clear();
  std::vector<CObjectLists::ListType>::const_iterator it, itEnd = mIndexTable.end();

  for (it = mIndexTable.begin(); it != itEnd; ++it)
    insertItem(FROM_UTF8(CObjectLists::ListTypeName[*it]));

  //restore old selection, if possible
  if (!setCurrentObjectList(oldItem))
    setCurrentItem(0);
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

  setCurrentItem(it - mIndexTable.begin());
  return true;
}
