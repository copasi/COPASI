/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ReactionsWidget.cpp,v $
   $Revision: 1.78 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/11/04 19:53:07 $
   End CVS Header */

#include "ReactionsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qfontmetrics.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "model/CReaction.h"
#include "CReactionInterface.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

std::vector<const CCopasiObject*> ReactionsWidget::getObjects() const
  {
    CCopasiVectorN<CReaction>& tmp = dataModel->getModel()->getReactions();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void ReactionsWidget::init()
{
  mOT = ListViews::REACTION;
  numCols = 5;
  table->setNumCols(numCols);
  std::vector<const CCopasiObject*> objectstemp;
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Equation");
  tableHeader->setLabel(3, "Kinetics");
  tableHeader->setLabel(4, "Flux");
  colWidth.reserve(5); // reserve only for the number of columns needed
  resetColWidth(); // resets the width of columns in the table

  //this restricts users from editing function names
  table->setColumnReadOnly (3, true);
  table->setColumnReadOnly (4, true);
}

void ReactionsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CReaction* pRea = (const CReaction*)obj;

  table->setText(row, 1, FROM_UTF8(pRea->getObjectName()));

  table->setText(row, 2, FROM_UTF8(CChemEqInterface::getChemEqString(dataModel->getModel(), *pRea, false)));
  table->setColumnWidth(2, colWidth[1]);

  if (&(pRea->getFunction()))
    {
      table->setText(row, 3, FROM_UTF8(pRea->getFunction().getObjectName()));
      table->setColumnWidth(3, colWidth[2]);
    }

  table->setText(row, 4, QString::number(pRea->getFlux()));
  table->setColumnWidth(4, colWidth[3]);
}

void ReactionsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to ri;
  CReactionInterface ri;
  ri.initFromReaction(*(dataModel->getModel()), obj->getKey());

  QString equation(table->text(row, 2));
  if ((const char *)equation.utf8() != ri.getChemEqString())
    {
      //first check if the string is a valid equation
      if (!CChemEqInterface::isValidEq((const char *)equation.utf8()))
        {
          std::cout << "Not a valid equation!\n\n";
          return;
        }
      else
        {
          //tell the reaction interface
          ri.setChemEqString((const char *)equation.utf8());
        }
    }

  //first check if new metabolites need to be created
  bool createdMetabs = ri.createMetabolites(*(dataModel->getModel()));
  //this writes all changes to the reaction
  ri.writeBackToReaction(*(dataModel->getModel()));
  //dataModel->getModel()->compile();
  //this tells the gui what it needs to know.
  if (createdMetabs) ListViews::notify(ListViews::METABOLITE, ListViews::ADD, "");
}

void ReactionsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, "");
  if (exc != 3)
    table->setText(row, 3, "");
  table->setText(row, 4, "");
}

QString ReactionsWidget::defaultObjectName() const
  {
    return "reaction";
  }

CCopasiObject* ReactionsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CReaction* pRea;
  while (!(pRea = dataModel->getModel()->createReaction(nname)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Reaction: " << nname << " : " << pRea->getKey() << std::endl;
  return pRea;
}

void ReactionsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  resetColWidth();

  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      dataModel->getModel()->removeReaction(keys[i]);
      ListViews::notify(ListViews::REACTION, ListViews::DELETE, keys[i]);
    }
}

void ReactionsWidget::checkColumnWidth (const CCopasiObject* obj)
{
  //sets the colWidth variable...all the rules for changing the column width
  // are specified here.

  if (!obj) return;

  const CReaction* pRea = (const CReaction*)obj;
  // cast the object

  QString eqString = FROM_UTF8(CChemEqInterface::getChemEqString(dataModel->getModel(), *pRea, false));
  // read the object

  if (colWidth[1] < fontMetrics().width(eqString, eqString.length()))
    {
      colWidth[1] = fontMetrics().width(eqString, eqString.length()) + 20;
    }

  // set the ColWidth if it is greater than it previous value.

  if (&(pRea->getFunction()))
    {
      QString funcString = FROM_UTF8(pRea->getFunction().getObjectName());

      if (colWidth[2] < fontMetrics().width(funcString, funcString.length()))
        {
          colWidth[2] = fontMetrics().width(funcString, funcString.length()) + 20;
        }
    }
}

void ReactionsWidget::resetColWidth()
{
  colWidth[0] = 80;
  colWidth[1] = 80;
  colWidth[2] = 80;
  colWidth[3] = 80;
  colWidth[4] = 80;
}
