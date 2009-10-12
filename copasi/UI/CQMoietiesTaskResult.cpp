// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQMoietiesTaskResult.h"

//#include <qvariant.h>
//#include "CQMoietiesTaskResult.ui.h"

//#include <q3table.h>
#include <q3header.h>
#include <qregexp.h>
#include <qimage.h>
#include <qsignalmapper.h>
#include <qtoolbutton.h>

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
//#include <q3picture.h>

#include "copasi.h"

#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "function/CExpression.h"
#include "model/CModel.h"
#include "moieties/CMoietiesTask.h"
#include "report/CKeyFactory.h"
#include "utilities/utility.h"
#include "report/CCopasiRootContainer.h"

#define COL_SPECIES  0
#define COL_AMOUNT   1
#define COL_BTN      2
#define COL_EQUATION 3

static const unsigned char ToolBtn_data[] =
{
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
  0x8f, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x52, 0x49, 0x12, 0xc0,
  0x20, 0x08, 0x8b, 0x4e, 0x1f, 0xc6, 0xd3, 0x7c, 0x1a, 0x3f, 0xb3, 0x07,
  0x6d, 0x59, 0x9a, 0xee, 0x78, 0x10, 0x42, 0x58, 0x26, 0x5a, 0x00, 0x85,
  0x99, 0xe0, 0x3a, 0xce, 0x26, 0x28, 0x80, 0xa2, 0x25, 0x52, 0x9b, 0x27,
  0x62, 0x42, 0x79, 0x35, 0x12, 0xb6, 0x22, 0x75, 0x8d, 0x84, 0x34, 0x32,
  0xac, 0x62, 0x0f, 0x3c, 0x91, 0xf9, 0xfe, 0xb6, 0xfc, 0x32, 0xa6, 0x69,
  0x5a, 0xf9, 0x29, 0xe6, 0xd6, 0xfd, 0x7a, 0x9f, 0x88, 0xc8, 0x04, 0xe3,
  0x22, 0x46, 0xc7, 0xf9, 0x47, 0x4c, 0x29, 0xaf, 0xc6, 0x95, 0xd8, 0x9a,
  0x71, 0x6a, 0xc6, 0x16, 0xeb, 0xe8, 0x89, 0x32, 0x67, 0xe4, 0xe2, 0xcc,
  0xd3, 0xa1, 0x41, 0x2c, 0x7c, 0x17, 0x17, 0x00, 0x87, 0xa7, 0xe1, 0x3f,
  0x91, 0x63, 0x70, 0xe2, 0x74, 0x00, 0x3d, 0x09, 0x76, 0x83, 0xc1, 0xbe,
  0xf2, 0x57, 0x73, 0x22, 0xb6, 0x92, 0x93, 0x4f, 0xb1, 0x5f, 0xb6, 0x02,
  0x6f, 0x3b, 0x53, 0x57, 0x71, 0xe6, 0x68, 0xdf, 0x00, 0x00, 0x00, 0x00,
  0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMoietiesTaskResult::languageChange()
{
  retranslateUi(this);
}

void CQMoietiesTaskResult::init()
{
  mpMoietiesTask = NULL;

  QImage ToolBtn;
  ToolBtn.loadFromData(ToolBtn_data, sizeof(ToolBtn_data), "PNG");
  mToolBtn = ToolBtn;
  mpToolBtnMap = NULL;

  // Initialize the moieties tab
  mpMoieties->setNumCols(4);

  Q3Header * pHeader = mpMoieties->horizontalHeader();
  pHeader->setLabel(COL_SPECIES, "Dependent Species");
  pHeader->setLabel(COL_AMOUNT, "Total Amount");
  pHeader->setLabel(COL_BTN, "");
  pHeader->setLabel(COL_EQUATION, "Expression");

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
  mpMoieties->setNumRows(0);

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

  // TODO
  // Fill the moieties table

  // We need to rebuild the tool buton signal mapper
  pdelete(mpToolBtnMap);
  mpToolBtnMap = new QSignalMapper(this);
  connect(mpToolBtnMap, SIGNAL(mapped(int)), this, SLOT(slotCreateGlobalQuantity(int)));
  QToolButton* pBtn;

  int i = 0;
  CCopasiVector< CMoiety >::const_iterator it = pModel->getMoieties().begin();
  CCopasiVector< CMoiety >::const_iterator end = pModel->getMoieties().end();

  mpMoieties->setNumRows(end - it);

  for (; it != end; ++it, i++)
    {
      mpMoieties->setText(i, COL_SPECIES, FROM_UTF8((*it)->getObjectName()));
      mpMoieties->setText(i, COL_AMOUNT, QString::number((*it)->getNumber()));

      pBtn = new QToolButton(mpMoieties);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pBtn->sizePolicy().hasHeightForWidth()));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIconSet(QIcon(mToolBtn));
      pBtn->setTextLabel(("Create global quantity for total amount."));
      mpToolBtnMap->setMapping(pBtn, i);
      connect(pBtn, SIGNAL(clicked()), mpToolBtnMap, SLOT(map()));
      mpMoieties->setCellWidget(i, COL_BTN, pBtn);

      mpMoieties->setText(i, COL_EQUATION, FROM_UTF8((*it)->getDescription(pModel)));
    }

  mpTabWidget->setTabLabel(mpMoieties, "Moieties (" + QString::number(i) + ")");

  mpMoieties->adjustColumn(COL_SPECIES);
  mpMoieties->adjustColumn(COL_AMOUNT);
  mpMoieties->adjustColumn(COL_BTN);
  mpMoieties->adjustColumn(COL_EQUATION);

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

  std::ofstream file(utf8ToLocale(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  if (mpMoietiesTask != NULL)
    file << mpMoietiesTask->getResult();

  return;
}

void CQMoietiesTaskResult::slotCreateGlobalQuantity(int row)
{
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
