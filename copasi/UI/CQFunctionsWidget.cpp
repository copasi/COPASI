// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFunctionsWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/22 17:19:07 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>
#include <QClipboard>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"

#include "CQFunctionsWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

/*
 *  Constructs a CQFunctionsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFunctionsWidget::CQFunctionsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpFunctionDM = new CQFunctionDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(COL_NAME_FUNCTIONS);

  mpTblFunctions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblFunctions->verticalHeader()->hide();
  mpTblFunctions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  // Connect the table widget
  connect(mpFunctionDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFunctionsWidget::~CQFunctionsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpFunctionDM);
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFunctionsWidget::languageChange()
{
  retranslateUi(this);
}

void CQFunctionsWidget::slotBtnDeleteClicked()
{
  if (mpTblFunctions->hasFocus())
    {deleteSelectedFunctions();}
}

void CQFunctionsWidget::deleteSelectedFunctions()
{
  QModelIndexList selRows = mpTblFunctions->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpProxyModel->mapToSource(*i));}

  if (mpFunctionDM->removeRows(mappedSelRows))
    protectedNotify(ListViews::FUNCTION, ListViews::DELETE, "");
}

void CQFunctionsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Functions?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpFunctionDM->clear();
      protectedNotify(ListViews::FUNCTION, ListViews::DELETE, "");
    }
}

bool CQFunctionsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQFunctionsWidget::leave()
{
  return true;
}

bool CQFunctionsWidget::enter(const std::string & C_UNUSED(key))
{
  mpProxyModel->setSourceModel(mpFunctionDM);
  //Set Model for the TableView
  mpTblFunctions->setModel(NULL);
  mpTblFunctions->setModel(mpProxyModel);
  mpTblFunctions->resizeColumnsToContents();

  return true;
}

void CQFunctionsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                    const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblFunctions->resizeColumnsToContents();
}

void CQFunctionsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpFunctionDM->isDefaultRow(index))
    return;

  std::string key = CCopasiRootContainer::getFunctionList()->loadedFunctions()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQFunctionsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && ev->modifiers() & Qt::ControlModifier)
    {
      QModelIndexList selRows = mpTblFunctions->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpFunctionDM->columnCount(); ++x)
            {
              if (!mpTblFunctions->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpFunctionDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQFunctionsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|No Name", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}
