// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLayoutsWidget.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:45 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQLayoutsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qregexp.h>
#include <qvalidator.h>

#include <iostream>

#include "CQMessageBox.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#ifdef USE_CRENDER_EXTENSION
#include "copasi/layoutUI/CQNewMainWindow.h"
#else
#include "copasi/layoutUI/CQLayoutMainWindow.h"
#endif // USE_CRENDER_EXTENSION

#define COL_MARK         0
#define COL_NAME         1
#define COL_SHOW         2

std::vector<const CCopasiObject*> CQLayoutsWidget::getObjects() const
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CListOfLayouts* pListOfLayouts = (*CCopasiRootContainer::getDatamodelList())[0]->getListOfLayouts();
  std::vector<const CCopasiObject*> ret;

  size_t i, imax = pListOfLayouts->size();

  for (i = 0; i < imax; ++i)
    ret.push_back((*pListOfLayouts)[i]);

  return ret;
}

void CQLayoutsWidget::init()
{
  this->btnNew->hide();
  mOT = ListViews::LAYOUT;
  numCols = 3;
  table->setNumCols((int) numCols);

  //Setting table headers
  Q3Header *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_SHOW, "Show");
}

void CQLayoutsWidget::updateHeaderUnits()
{
  // no units, so we do nothing
}

void CQLayoutsWidget::tableLineFromObject(const CCopasiObject* obj, size_t row)
{
  if (!obj) return;

  const CLayout * pLayout = static_cast< const CLayout * >(obj);

  // Name
  table->setText((int) row, COL_NAME, FROM_UTF8(pLayout->getObjectName()));
  CQShowLayoutButton* pButton = new CQShowLayoutButton((int) row, NULL);
  pButton->setText("Show");
  table->setCellWidget((int) row, COL_SHOW, pButton);
  connect(pButton, SIGNAL(signal_show(int)), this, SLOT(slot_show(int)));
#ifdef USE_CRENDER_EXTENSION
  std::map<std::string, CQNewMainWindow*>::iterator pos = this->mLayoutWindowMap.find(obj->getKey());
#else
  std::map<std::string, CQLayoutMainWindow*>::iterator pos = this->mLayoutWindowMap.find(obj->getKey());
#endif  // USE_CRENDER_EXTENSION
  // if this layout does not have an entry in the layout window map, add one
  if (pos == this->mLayoutWindowMap.end())
    {
#ifdef USE_CRENDER_EXTENSION
      this->mLayoutWindowMap.insert(std::pair<std::string, CQNewMainWindow*>(obj->getKey(), NULL));
#else
      this->mLayoutWindowMap.insert(std::pair<std::string, CQLayoutMainWindow*>(obj->getKey(), NULL));
#endif // USE_CRENDER_EXTENSION
    }
}

void CQLayoutsWidget::tableLineToObject(size_t /*row*/, CCopasiObject* /*obj*/)
{
  // I don't know what this is supposed to do, but right now it does nothing
  //if (!obj) return;
  //CLayout * pLayout = static_cast< CLayout * >(obj);
}

void CQLayoutsWidget::defaultTableLineContent(size_t /*row*/, size_t /*exc*/)
{
  // nothin to do here
}

QString CQLayoutsWidget::defaultObjectName() const
{
  return "layout";
}

CCopasiObject* CQLayoutsWidget::createNewObject(const std::string & /*name*/)
{
  /*
   * Can't create layouts yet.
  std::string nname = name;
  int i = 0;
  CLayout* playout;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  while (!(pLayout = (*CCopasiRootContainer::getDatamodelList())[0]->createLayout(nname)))
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  return pLayout;
  */
  return NULL;
}

void CQLayoutsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (keys.size() == 0)
    return;

  QString layoutList = "Are you sure you want to delete listed LAYOUT(S) ?\n";

  size_t i, imax = keys.size();

  for (i = 0; i < imax; i++) //all compartments
    {
      CLayout* pLayout =
        dynamic_cast< CLayout *>(CCopasiRootContainer::getKeyFactory()->get(keys[i]));

      layoutList.append(FROM_UTF8(pLayout->getObjectName()));
      layoutList.append(", ");
    }

  layoutList.remove(layoutList.length() - 2, 2);

  QString msg = layoutList;

  C_INT32 choice = 0;

  switch (choice)
    {
      case 0:                    // Yes or Enter
      {
        assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

        for (i = 0; i < imax; i++)
          {
            (*CCopasiRootContainer::getDatamodelList())[0]->removeLayout(keys[i]);
#ifdef USE_CRENDER_EXTENSION
            std::map<std::string, CQNewMainWindow*>::iterator pos = this->mLayoutWindowMap.find(keys[i]);
#else
            std::map<std::string, CQLayoutMainWindow*>::iterator pos = this->mLayoutWindowMap.find(keys[i]);
#endif // USE_CRENDER_EXTENSION

            if (pos != this->mLayoutWindowMap.end() && pos->second != NULL)
              {
                // close the window
                pos->second->close();
              }
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::LAYOUT, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }

      default:                    // No or Escape
        break;
    }
}

void CQLayoutsWidget::valueChanged(size_t /*row*/, size_t /*col*/)
{
  /*
   * Does nothing at the moment.
  switch (col)
    {
    default:
      break;
    }
  */
  return;
}

/**
 * We overwrite the slotDoubleClicked from CopasiTableWidget since we don't
 * want to switch to another folder in the ListView but we want to open or display a layout window.
 */
void CQLayoutsWidget::slotDoubleClicked(int row, int C_UNUSED(col),
                                        int C_UNUSED(m), const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (mRO && (row == table->numRows() - 1)) return;

  std::string key = mKeys[row];
  bool flagNew = false;

  if (mFlagNew[row])
    {
      saveTable();
      fillTable();
      return;
      //TODO: When double clicking on a new object the object should be created.
    }

  if (mFlagDelete[row])
    {
      return;
    }

  if (row == table->numRows() - 1) //new Object
    {
      //we have no default way to create a layout at the moment
      /*      flagNew = true;
            resizeTable(table->numRows() + 1);
            mFlagNew[row] = true;
            table->setText(row, 1, createNewName(defaultObjectName()));
            defaultTableLineContent(row, 0);*/
    }

  saveTable();

  if (flagNew)
    {
      key = mKeys[row];
    }

  fillTable();

  this->slot_show(row);
}

void CQLayoutsWidget::slot_show(int row)
{
  std::string key = mKeys[row];
  CLayout* pLayout = dynamic_cast<CLayout*>(CCopasiRootContainer::getKeyFactory()->get(key));

  if (pLayout != NULL)
    {
      // check if we already have a widget for the layout
      // if yes, open it, else create one and add it to the map
      bool createNew = false;
#ifdef USE_CRENDER_EXTENSION
      std::map<std::string, CQNewMainWindow*>::iterator pos = this->mLayoutWindowMap.find(key);
#else
      std::map<std::string, CQLayoutMainWindow*>::iterator pos = this->mLayoutWindowMap.find(key);
#endif // USE_CRENDER_EXTENSION

      if (pos != this->mLayoutWindowMap.end())
        {
          if (pos->second == NULL)
            {
              createNew = true;
            }
          else
            {
#ifdef USE_CRENDER_EXTENSION
              pos->second->slotLayoutChanged(row);
#endif // USE_CRENDER_EXTENSION
              pos->second->show();
              pos->second->showNormal();
              pos->second->setActiveWindow();
            }
        }
      else
        {
          createNew = true;
        }

      if (createNew)
        {
#ifdef USE_CRENDER_EXTENSION
          CQNewMainWindow* pWin = new CQNewMainWindow((*CCopasiRootContainer::getDatamodelList())[0]);
          pWin->slotLayoutChanged(row);
#else
          CQLayoutMainWindow* pWin = new CQLayoutMainWindow(pLayout);
#endif // USE_CRENDER_EXTENSION
          pWin->setWindowTitle(pLayout->getObjectName().c_str());
          pWin->resize(900, 600);
          pWin->show();

          this->mLayoutWindowMap[key] = pWin;
        }
    }
  else
    {
      //std::cerr << "Could not find layout." << std::endl;
    }
}

void CQShowLayoutButton::slot_clicked()
{
  emit signal_show(this->mRow);
}

CQShowLayoutButton::CQShowLayoutButton(unsigned int row, QWidget* pParent, const char* name): QToolButton(pParent, name), mRow(row)
{
  this->setTextLabel("Show");
  connect(this, SIGNAL(clicked()), this, SLOT(slot_clicked()));
}

void CQLayoutsWidget::deleteLayoutWindows()
{
#ifdef USE_CRENDER_EXTENSION
  std::map<std::string, CQNewMainWindow*>::iterator it = this->mLayoutWindowMap.begin(), endit = this->mLayoutWindowMap.end();
#else
  std::map<std::string, CQLayoutMainWindow*>::iterator it = this->mLayoutWindowMap.begin(), endit = this->mLayoutWindowMap.end();
#endif // USE_CRENDER_EXTENSION

  while (it != endit)
    {
      delete it->second;
      ++it;
    }

  this->mLayoutWindowMap.clear();
}
