/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MoietyWidget.cpp,v $
   $Revision: 1.64 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 16:26:50 $
   End CVS Header */

#include "MoietyWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "model/CMoiety.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "qmessagebox.h"
#include "qapplication.h"
#include "copasiui3window.h"

std::vector<const CCopasiObject*> MoietyWidget::getObjects() const
  {
    const CCopasiVectorN<CMoiety>& tmp = CCopasiDataModel::Global->getModel()->getMoieties();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void MoietyWidget::init()
{
  mExtraLayout->addStretch();
  btnRun = new QPushButton("&Recalculate", this);
  mExtraLayout->addWidget(btnRun);
  connect(btnRun, SIGNAL(clicked ()), this,
          SLOT(slotBtnRunClicked()));

  numCols = 4;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  table->hideColumn(0);
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Equation");
  tableHeader->setLabel(3, "Number");
}

void MoietyWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMoiety* pMoi = (const CMoiety*)obj;
  table->setText(row, 1, FROM_UTF8(pMoi->getObjectName()));
  table->setText(row, 2, FROM_UTF8(pMoi->getDescription(CCopasiDataModel::Global->getModel())));
  table->setText(row, 3, QString::number(pMoi->getNumber()));
}

void MoietyWidget::tableLineToObject(unsigned C_INT32 C_UNUSED(row), CCopasiObject* C_UNUSED(obj))
{}

void MoietyWidget::defaultTableLineContent(unsigned C_INT32 C_UNUSED(row), unsigned C_INT32 C_UNUSED(exc))
{}

QString MoietyWidget::defaultObjectName() const
  {return "";}

CCopasiObject* MoietyWidget::createNewObject(const std::string & C_UNUSED(name))
{return NULL;}

void MoietyWidget::deleteObjects(const std::vector<std::string> & C_UNUSED(keys))
{}

void MoietyWidget::slotBtnRunClicked()
{
  if (CCopasiDataModel::Global->isChanged())
    {
      const QApplication* qApp = dataModel->getQApp();
      if (qApp)
        {
          CopasiUI3Window* mainWidget = dynamic_cast<CopasiUI3Window*>(qApp->mainWidget());
          if (mainWidget)
            {
              CCopasiDataModel::Global->autoSave();
              /*if (QMessageBox::question(mainWidget, "Model Changed", "Your model contains unsaved changes.\nDo you want to save those changes?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::Yes)
                {
                  mainWidget->saveFile();
                }
              */
            }
        }
    }
  CCopasiDataModel::Global->getModel()->compileIfNecessary();
  fillTable();

  mIgnoreUpdates = true; //to avoid recursive calls
  ListViews::notify(ListViews::MODEL, ListViews::CHANGE);
  mIgnoreUpdates = false; //to avoid recursive calls
}
