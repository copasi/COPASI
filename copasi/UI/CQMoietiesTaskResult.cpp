// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CQMoietiesTaskResult.h"

#include "copasi/copasi.h"

#include "CQPushButtonDelegate.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"
#include "copasi/moieties/CMoietiesTask.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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
  pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  mpMoieties->setHorizontalHeaderItem(COL_SPECIES, pItem);

  pItem = new QTableWidgetItem("Total Particle Number");
  pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  mpMoieties->setHorizontalHeaderItem(COL_NUMBER, pItem);

  pItem = new QTableWidgetItem("Total Amount");
  pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  mpMoieties->setHorizontalHeaderItem(COL_AMOUNT, pItem);

  pItem = new QTableWidgetItem("");
  mpMoieties->setHorizontalHeaderItem(COL_BTN, pItem);

  pItem = new QTableWidgetItem("Expression");
  pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  mpMoieties->setHorizontalHeaderItem(COL_EQUATION, pItem);

  CQPushButtonDelegate * pDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::unknown), QString(), CQPushButtonDelegate::PushButton, this, "When pressed the selected total amount will be created as global quantity.");
  // CQPushButtonDelegate * pDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::tool), "",  CQPushButtonDelegate::ToolButton,
  //     this, "When pressed the selected total amount will be created as global quantity.");
  mpMoieties->setItemDelegateForColumn(COL_BTN, pDelegate);

  connect(pDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotCreateGlobalQuantity(const QModelIndex &)));

  // Initialize the stoichiometry tab
  mpStoichiometry->setLegendEnabled(true);

  // Initialize the stoichiometry tab
  mpLinkMatrix->setLegendEnabled(true);

  // Initialize the stoichiometry tab
  mpReducedStoichiometry->setLegendEnabled(true);

  setFramework((int)CCore::Framework::Concentration);
}

bool CQMoietiesTaskResult::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  // :TODO:
  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        switch (action)
          {
            case ListViews::ADD:
            case ListViews::DELETE:
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

bool CQMoietiesTaskResult::leaveProtected()
{return true;}

bool CQMoietiesTaskResult::enterProtected()
{
  mpMoietiesTask = dynamic_cast< CMoietiesTask * >(mpObject);

  load();

  return true;
}

void CQMoietiesTaskResult::load()
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL) return;

  // Set the units for the amount column
  QString AmountUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(pModel->getQuantityUnit())) + "]";

  mpMoieties->horizontalHeaderItem(COL_AMOUNT)->setText("Total Amount" + AmountUnits);

  // Fill the moieties table
  int i = 0;

  if (pModel->getMoieties().size() > 0)
    {
      CDataVector< CMoiety >::const_iterator it = pModel->getMoieties().begin();
      CDataVector< CMoiety >::const_iterator end = pModel->getMoieties().end();
      mpMoieties->setRowCount(pModel->getMoieties().size());
      mpMoieties->setSortingEnabled(false);

      QTableWidgetItem * pItem;

      for (; it != end; ++it, i++)
        {
          pItem = new QTableWidgetItem(FROM_UTF8(it->getObjectName()));
          pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
          mpMoieties->setItem(i, COL_SPECIES, pItem);;

          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
          pItem->setData(Qt::DisplayRole, it->getNumber());
          mpMoieties->setItem(i, COL_NUMBER, pItem);

          it.constCast()->refreshAmount();
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
          pItem->setData(Qt::DisplayRole, it->getAmount());
          mpMoieties->setItem(i, COL_AMOUNT, pItem);

          pItem = new QTableWidgetItem("...");
          mpMoieties->setItem(i, COL_BTN, pItem);

          // Show the Button
          pItem = mpMoieties->item(i, COL_BTN);
          pItem->setFlags(pItem->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
          mpMoieties->openPersistentEditor(pItem);

          pItem = new QTableWidgetItem(FROM_UTF8(it->getDescription(pModel)));
          pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
          mpMoieties->setItem(i, COL_EQUATION, pItem);
        }
    }

  mpTabWidget->setTabText(mpTabWidget->indexOf(mpMoieties), "Moieties (" + QString::number(i) + ")");

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpMoieties->resizeColumnsToContents();
      mpMoieties->resizeRowsToContents();
    }

  mpMoieties->setSortingEnabled(true);

  // Fill the stoichiometry matrix
  CColorScaleBiLog * tcs = NULL;
  const CDataArray * pAnnotation =
    static_cast< const CDataArray * >(pModel->getObject(CCommonName("Array=Stoichiometry(ann)")));
  tcs = new CColorScaleBiLog();
  mpStoichiometry->setColorCoding(tcs);
  mpStoichiometry->setColorScalingAutomatic(true);
  mpStoichiometry->setArrayAnnotation(pAnnotation);

  // Fill the link matrix
  pAnnotation =
    static_cast< const CDataArray * >(pModel->getObject(CCommonName("Array=Link matrix(ann)")));
  tcs = new CColorScaleBiLog();
  mpLinkMatrix->setColorCoding(tcs);
  mpLinkMatrix->setColorScalingAutomatic(true);
  mpLinkMatrix->setArrayAnnotation(pAnnotation);

  // Fill the reduced stoichiometry matrix
  pAnnotation =
    static_cast< const CDataArray * >(pModel->getObject(CCommonName("Array=Reduced stoichiometry(ann)")));
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
                                          CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

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

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL) return;

  const CDataVector< CMoiety > & Moieties = pModel->getMoieties();

  if (row >= (C_INT32) Moieties.size()) return;

  const CMoiety * pMoiety = &Moieties[row];

  CModelValue * pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalParticleAmount");

  int i = 0;

  while (pMV == NULL)
    pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalParticleAmount_" + TO_UTF8(QString::number(++i)));

  pMV->setInitialExpression(pMoiety->getExpression());

  pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalAmount");

  i = 0;

  while (pMV == NULL)
    pMV = pModel->createModelValue("Moiety[" + pMoiety->getObjectName() + "].TotalAmount_" + TO_UTF8(QString::number(++i)));

  pMV->setInitialExpression("(" + pMoiety->getExpression() + ")/<" +
                            pModel->getObject(CCommonName("Reference=Quantity Conversion Factor"))->getCN() + ">");

  protectedNotify(ListViews::ObjectType::MODELVALUE, ListViews::ADD);
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
