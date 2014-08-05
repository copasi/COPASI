// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

#include "CQMoietiesTaskResult.h"

#include "copasi.h"

#include "resourcesUI/CQIconResource.h"
#include "CQPushButtonDelegate.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "function/CExpression.h"
#include "model/CModel.h"
#include "moieties/CMoietiesTask.h"
#include "report/CKeyFactory.h"
#include "utilities/utility.h"
#include "report/CCopasiRootContainer.h"
#include "commandline/CLocaleString.h"

#define COL_SPECIES  0
#define COL_NUMBER   1
#define COL_AMOUNT   2
#define COL_BTN      3
#define COL_EQUATION 4

/*
 *  Constructs a CQMoietiesTaskResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskResult::CQMoietiesTaskResult(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskResult::~CQMoietiesTaskResult()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMoietiesTaskResult::init()
{
  mpMoietiesTask = NULL;

  QImage ToolBtn;

  // Initialize the moieties tab
  mpMoieties->setColumnCount(5);

  QTableWidgetItem * pItem = new QTableWidgetItem("Dependent Species");
  mpMoieties->setHorizontalHeaderItem(COL_SPECIES, pItem);
  pItem = new QTableWidgetItem("Total Particle Number");
  mpMoieties->setHorizontalHeaderItem(COL_NUMBER, pItem);
  pItem = new QTableWidgetItem("Total Amount");
  mpMoieties->setHorizontalHeaderItem(COL_AMOUNT, pItem);
  pItem = new QTableWidgetItem("");
  mpMoieties->setHorizontalHeaderItem(COL_BTN, pItem);
  pItem = new QTableWidgetItem("Expression");
  mpMoieties->setHorizontalHeaderItem(COL_EQUATION, pItem);

  CQPushButtonDelegate * pDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::tool), "",  CQPushButtonDelegate::ToolButton, this);
  mpMoieties->setItemDelegateForColumn(COL_BTN, pDelegate);

  connect(pDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotCreateGlobalQuantity(const QModelIndex &)));

  // Initialize the stoichiometry tab
  mpStoichiometry->setLegendEnabled(true);

  // Initialize the stoichiometry tab
  mpLinkMatrix->setLegendEnabled(true);

  // Initialize the stoichiometry tab
  mpReducedStoichiometry->setLegendEnabled(true);
}

bool CQMoietiesTaskResult::update(ListViews::ObjectType objectType,
                                  ListViews::Action action,
                                  const std::string & /* key */)
{
  // :TODO:
  switch (objectType)
    {
      case ListViews::MODEL:

        switch (action)
          {
            case ListViews::ADD:
              clear();
              break;

            case ListViews::CHANGE:
              break;

            default:
              break;
          }

        break;

      default:
        break;
    }

  return true;
}

void CQMoietiesTaskResult::clear()
{
  mpMoieties->setRowCount(0);
  mpStoichiometry->setArrayAnnotation(NULL);
  mpLinkMatrix->setArrayAnnotation(NULL);
  mpReducedStoichiometry->setArrayAnnotation(NULL);
}

bool CQMoietiesTaskResult::leave()
{return true;}

bool CQMoietiesTaskResult::enterProtected()
{
  mpMoietiesTask = dynamic_cast< CMoietiesTask * >(mpObject);

  load();

  return true;
}

void CQMoietiesTaskResult::load()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  // Set the units for the amount column
  QString AmountUnits = FROM_UTF8(pModel->getQuantityUnitsDisplayString());

  if (!AmountUnits.isEmpty())
    AmountUnits = "\n(" + AmountUnits + ")";

  mpMoieties->horizontalHeaderItem(COL_AMOUNT)->setText("Total Amount" + AmountUnits);

  // Fill the moieties table
  CCopasiVector< CMoiety >::const_iterator it = pModel->getMoieties().begin();
  CCopasiVector< CMoiety >::const_iterator end = pModel->getMoieties().end();
  mpMoieties->setRowCount(end - it);

  QTableWidgetItem * pItem;
  int i = 0;

  for (; it != end; ++it, i++)
    {
      pItem = new QTableWidgetItem(FROM_UTF8((*it)->getObjectName()));
      mpMoieties->setItem(i, COL_SPECIES, pItem);;

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, (*it)->getNumber());
      mpMoieties->setItem(i, COL_NUMBER, pItem);

      (*it)->refreshAmount();
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, (*it)->getAmount());
      mpMoieties->setItem(i, COL_AMOUNT, pItem);

      pItem = new QTableWidgetItem("");
      mpMoieties->setItem(i, COL_BTN, pItem);

      // Show the Button
      pItem = mpMoieties->item(i, COL_BTN);
      pItem->setFlags(pItem->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
      mpMoieties->openPersistentEditor(pItem);

      pItem = new QTableWidgetItem(FROM_UTF8((*it)->getDescription(pModel)));
      mpMoieties->setItem(i, COL_EQUATION, pItem);
    }

  mpTabWidget->setTabText(mpTabWidget->indexOf(mpMoieties), "Moieties (" + QString::number(i) + ")");

  mpMoieties->resizeColumnsToContents();
  mpMoieties->resizeRowsToContents();

  // Fill the stoichiometry matrix
  CColorScaleBiLog * tcs = NULL;
  const CArrayAnnotation * pAnnotation =
    static_cast< const CArrayAnnotation * >(pModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)")));
  tcs = new CColorScaleBiLog();
  mpStoichiometry->setColorCoding(tcs);
  mpStoichiometry->setColorScalingAutomatic(true);
  mpStoichiometry->setArrayAnnotation(pAnnotation);

  // Fill the link matrix
  pAnnotation =
    static_cast< const CArrayAnnotation * >(pModel->getObject(CCopasiObjectName("Array=Link matrix(ann)")));
  tcs = new CColorScaleBiLog();
  mpLinkMatrix->setColorCoding(tcs);
  mpLinkMatrix->setColorScalingAutomatic(true);
  mpLinkMatrix->setArrayAnnotation(pAnnotation);

  // Fill the reduced stoichiometry matrix
  pAnnotation =
    static_cast< const CArrayAnnotation * >(pModel->getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)")));
  tcs = new CColorScaleBiLog();
  mpReducedStoichiometry->setColorCoding(tcs);
  mpReducedStoichiometry->setColorScalingAutomatic(true);
  mpReducedStoichiometry->setArrayAnnotation(pAnnotation);

  return;
}

void CQMoietiesTaskResult::slotSave(void)
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  if (mpMoietiesTask != NULL)
    file << mpMoietiesTask->getResult();

  return;
}

void CQMoietiesTaskResult::slotCreateGlobalQuantity(const QModelIndex & index)
{
  int row = index.row();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CMoiety > Moieties = pModel->getMoieties();

  if (row >= (C_INT32) Moieties.size()) return;

  const CMoiety * pMoiety = Moieties[row];

  CModelValue * pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalAmount");

  int i = 0;

  while (pMV == NULL)
    pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalAmount_" + TO_UTF8(QString::number(++i)));

  pMV->setInitialExpression(pMoiety->getExpression());
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD);
}

// virtual
void CQMoietiesTaskResult::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  switch (mFramework)
    {
      case 0: // Concentration
        mpMoieties->showColumn(COL_AMOUNT);
        mpMoieties->hideColumn(COL_NUMBER);
        break;

      case 1: // Particle Number
        mpMoieties->hideColumn(COL_AMOUNT);
        mpMoieties->showColumn(COL_NUMBER);
        break;
    }
}
