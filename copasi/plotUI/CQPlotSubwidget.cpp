// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQPlotSubwidget.h"

#include "curve2dwidget.h"
#include "HistoWidget.h"
#ifdef COPASI_BANDED_GRAPH
#include "BandedGraphWidget.h"
#endif // COPASI_BANDED_GRAPH
#include "plotwindow.h"
#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CKeyFactory.h"
#include "utilities/CAnnotatedMatrix.h"
#include "UI/CCopasiPlotSelectionDialog.h"
#include "model/CMetabNameInterface.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "UI/DataModelGUI.h"
#include "copasi/UI/qtUtilities.h"
#include "report/CCopasiRootContainer.h"

//temporary
#include "UI/CCopasiSelectionDialog.h"
#include <QListWidgetItem>
#include <QList>
#include <QMap>
//-----------------------------------------------------------------------------

/*
 *  Constructs a PlotWidget1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQPlotSubwidget::CQPlotSubwidget(QWidget* parent, const char* name, Qt::WFlags fl)
  : CopasiWidget(parent, name, fl)
  , mpCurveWidget(NULL)
  , mpHistoWidget(NULL)
#ifdef COPASI_BANDED_GRAPH
  , mpBandedGraphWidget(NULL)
#endif
{
  setupUi(this);

  mpCurveWidget = new Curve2DWidget(this);
  mpStack->addWidget(mpCurveWidget);

  mpHistoWidget = new HistoWidget(this);
  mpStack->addWidget(mpHistoWidget);

#ifdef COPASI_BANDED_GRAPH
  // this should be implemented in the CQPlotSubwidget.ui file
  // as the button will be appended behind the 'delete' button:
  QToolButton * buttonBandedGraph = new QToolButton(this);
  buttonBandedGraph->setText("New Banded Graph");
  layoutCurves->addWidget(buttonBandedGraph);
  connect(buttonBandedGraph, SIGNAL(clicked()), this, SLOT(addBandedGraphSlot()));

  mpBandedGraphWidget = new BandedGraphWidget(this)
  mpStack->addWidget(mpBandedGraphWidget);

#endif // COPASI_BANDED_GRAPH
}

CPlotItem* CQPlotSubwidget::updateItem(CPlotItem* item)
{

  if (item == NULL) return NULL;

  QWidget *current = mpStack->currentWidget();

  Curve2DWidget *curve = dynamic_cast<Curve2DWidget*>(current);

  if (curve != NULL)
    {
      curve->SaveToCurveSpec(item);
    }

  HistoWidget *hist = dynamic_cast<HistoWidget *>(current);

  if (hist != NULL)
    {
      hist->SaveToCurveSpec(item);
    }

#ifdef COPASI_BANDED_GRAPH
  BandedGraphWidget *band = dynamic_cast<BandedGraphWidget *>(current);

  if (band != NULL)
    {
      band->SaveToCurveSpec(item);
    }

#endif
  return item;
}

void CQPlotSubwidget::storeChanges()
{
  if (mLastSelection.size() == 0)
    return;

  if (mLastSelection.size() == 1)
    {
      QString oldName = mLastSelection[0]->text();
      CPlotItem* item = mList[oldName];

      if (item == NULL) return;

      QString newName = FROM_UTF8(item->getTitle());

      if (oldName != newName)
        {
          mList.remove(oldName);
          mLastSelection[0]->setText(newName);
          mList.insert(newName, item);
        }

      // assign current
    }
  else
    {
      CPlotItem *common = new CPlotItem("nope");
      updateItem(common);

      QList<QListWidgetItem*>::const_iterator it;

      for (it = mLastSelection.begin(); it != mLastSelection.end(); ++it)
        {
          CPlotItem* current = mList[(*it)->text()];

          if (current == NULL)
            continue;

          std::vector<CPlotDataChannelSpec> channels = current->getChannels();

          CPlotItem* newItem = new CPlotItem(*common);
          newItem->setTitle(current->getTitle());
          newItem->getChannels() = channels;

          mList[(*it)->text()] = newItem;

          delete current;
        }

      // assign multiple
    }
}

QWidget* CQPlotSubwidget::getWidgetForIndex(int index)
{
  return mpCurveWidget;
}

//-----------------------------------------------------------------------------
/*
 *  Destroys the object and frees any allocated resources
 */
CQPlotSubwidget::~CQPlotSubwidget()
{}

//-----------------------------------------------------------------------------

//the slot...
void CQPlotSubwidget::addCurveSlot()
{
  if (mType == CPlotItem::plot2d)
    addCurve2D();
}

#ifdef COPASI_BANDED_GRAPH
void CQPlotSubwidget::addBandedGraphSlot()
{
  if (mType == CPlotItem::plot2d)
    addBandedGraph();
}
#endif // COPASI_BANDED_GRAPH

void CQPlotSubwidget::addHistoSlot()
{
  if (mType == CPlotItem::plot2d)
    addHisto1D();
}

int CQPlotSubwidget::getCurrentIndex()
{
  return mpListPlotItems->currentRow();
  //return tabs->count()
}

void CQPlotSubwidget::deleteCurves()
{
  for (int i = mpListPlotItems->count(); i >= 0; --i)
    {
      deleteCurve(i);
    }

  mList.clear();
  mpListPlotItems->clear();
  //while (tabs->currentWidget()) delete tabs->currentWidget();
}
void CQPlotSubwidget::deleteCurve(int index)
{
  QListWidgetItem *item = mpListPlotItems->item(index);

  if (item == NULL)
    return;

  delete mList[item->text()];
  mList.remove(item->text());
  mpListPlotItems->removeItemWidget(item);
  //delete tabs->currentWidget();
}

void CQPlotSubwidget::setCurrentIndex(int index)
{
  if (index < 0 && mpListPlotItems->count() > 0)
    index = 0;

  if (index >= mpListPlotItems->count())
    index = mpListPlotItems->count() - 1;

  //tabs->setCurrentIndex(storeTab);
  mpListPlotItems->setCurrentRow(index);
}

void CQPlotSubwidget::addPlotItem(CPlotItem* item)
{
  mpListPlotItems->addItem(FROM_UTF8(item->getTitle()));
  mList.insert(FROM_UTF8(item->getTitle()), new CPlotItem(*item), true);
  selectPlotItem(item);
}

void CQPlotSubwidget::selectPlotItem(CPlotItem* item)
{
  switch (item->getType())
    {
#ifdef COPASI_BANDED_GRAPH

      case CPlotItem::bandedGraph:
      {
        assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
        mpBandedGraphWidget->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
        mpBandedGraphWidget->LoadFromCurveSpec(item);
        mpStack->setCurrentIndex(2);
      }
      break;
#endif

      case CPlotItem::histoItem1d:
      {
        assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
        mpHistoWidget->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
        mpHistoWidget->LoadFromCurveSpec(item);
        mpStack->setCurrentIndex(1);
      }
      break;

      case CPlotItem::curve2d:
      {
        assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
        mpCurveWidget->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
        mpCurveWidget->LoadFromCurveSpec(item);
        mpStack->setCurrentIndex(0);
      }
      break;

      default:
        break;
    }
}

void CQPlotSubwidget::addCurveTab(const std::string & title,
                                  const CPlotDataChannelSpec & x,
                                  const CPlotDataChannelSpec & y)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::curve2d);
  item->addChannel(x);
  item->addChannel(y);

  addPlotItem(item);
}

void CQPlotSubwidget::addCurve2D()
{
  CCopasiPlotSelectionDialog* pBrowser = new CCopasiPlotSelectionDialog();
  std::vector< const CCopasiObject * > vector1;
  std::vector< const CCopasiObject * > vector2;
  pBrowser->setOutputVectors(&vector1, &vector2);
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  pBrowser->setModel(pDataModel->getModel(), CQSimpleSelectionTree::NumericValues);

  if (pBrowser->exec() == QDialog::Rejected)
    {
      return;
    }

  //this assumes that the vector is empty if nothing was chosen
  if (vector1.size() == 0 || vector2.size() == 0)
    {
      return;
    }

  std::vector<CCopasiObjectName> objects1, objects2;
  size_t i;
  std::vector<CCopasiObjectName>::const_iterator sit;
  const CArrayAnnotation *pArray;

  // 1. enable user to choose either a cell, an entire row/column, or even the objects themselves, if they are arrays.
  // 2. translate to CNs and remove duplicates

  // x-axis is set for single cell selection
  std::string cn;

  for (i = 0; i < vector1.size(); i++)
    {
      if (vector1[i])  // the object is not empty
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector1[i])))
            {
              // second argument is true as only single cell here is allowed. In this case we
              //can assume that the size of the return vector is 1.
              const CCopasiObject * pObject = CCopasiSelectionDialog::chooseCellMatrix(pArray, true, true, "X axis: ")[0];

              if (!pObject) continue;

              cn = pObject->getCN();
            }
          else
            cn = vector1[i]->getCN();

          // check whether cn is already on objects1
          for (sit = objects1.begin(); sit != objects1.end(); ++sit)
            {
              if (*sit == cn) break;
            }

          // if not exist, input cn into objects1
          if (sit == objects1.end())
            {
              objects1.push_back(cn);
            }
        }
    }

  for (i = 0; i < vector2.size(); i++)
    {
      if (vector2[i])
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector2[i])))
            {
              // second argument is set false for multi selection
              std::vector<const CCopasiObject*> vvv = CCopasiSelectionDialog::chooseCellMatrix(pArray, false, true, "Y axis: ");
              std::vector<const CCopasiObject*>::const_iterator it;

              for (it = vvv.begin(); it != vvv.end(); ++it)
                {
                  if (!*it) continue;

                  cn = (*it)->getCN();

                  //check if the CN already is in the list, if not add it.
                  for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                    if (*sit == cn) break;

                  if (sit == objects2.end())
                    objects2.push_back(cn);
                }
            }
          else
            {
              cn = vector2[i]->getCN();

              //check if the CN already is in the list, if not add it.
              for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                if (*sit == cn) break;

              if (sit == objects2.end())
                objects2.push_back(cn);
            }
        }
    }

  C_INT32 storeTab = getCurrentIndex();

  if (objects1.size() == 1)
    {
      for (i = 0; i < objects2.size(); ++i)
        {
          addCurveTab(pDataModel->getDataObject(objects2[i])->getObjectDisplayName()
                      + "|"
                      + pDataModel->getDataObject(objects1[0])->getObjectDisplayName(),
                      objects1[0], objects2[i]);
        }
    }
  else if (objects2.size() == 1)
    {
      for (i = 0; i < objects1.size(); ++i)
        {
          addCurveTab(pDataModel->getDataObject(objects2[0])->getObjectDisplayName()
                      + "|"
                      + pDataModel->getDataObject(objects1[i])->getObjectDisplayName(),
                      objects1[i], objects2[0]);
        }
    }
  else
    {
      size_t imax;

      if (objects1.size() > objects2.size())
        imax = objects2.size();
      else
        imax = objects1.size();

      for (i = 0; i < imax; ++i)
        {
          addCurveTab(pDataModel->getDataObject(objects2[i])->getObjectDisplayName()
                      + "|"
                      + pDataModel->getDataObject(objects1[i])->getObjectDisplayName() ,
                      objects1[i], objects2[i]);
        }
    }

  setCurrentIndex(storeTab);
}

#ifdef COPASI_BANDED_GRAPH
void CQPlotSubwidget::addBandedGraphTab(const std::string & title,
                                        const CPlotDataChannelSpec & x,
                                        const CPlotDataChannelSpec & yone,
                                        const CPlotDataChannelSpec & ytwo)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::bandedGraph);
  item->addChannel(x);
  item->addChannel(yone);
  item->addChannel(ytwo);

  addPlotItem(item);
}

void CQPlotSubwidget::addBandedGraph()
{
  CCopasiPlotSelectionDialog* pBrowser = new CCopasiPlotSelectionDialog();
  std::vector< const CCopasiObject * > vector1;
  std::vector< const CCopasiObject * > vector2;
  pBrowser->setOutputVectors(&vector1, &vector2);
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  pBrowser->setModel(pDataModel->getModel(), CQSimpleSelectionTree::NumericValues);

  if (pBrowser->exec() == QDialog::Rejected)
    {
      return;
    }

  //this assumes that the vector is empty if nothing was chosen
  if (vector1.size() == 0 || vector2.size() == 0)
    {
      return;
    }

  std::vector<CCopasiObjectName> objects1, objects2;
  size_t i;
  std::vector<CCopasiObjectName>::const_iterator sit;
  const CArrayAnnotation *pArray;

  // 1. enable user to choose either a cell, an entire row/column, or even the objects themselves, if they are arrays.
  // 2. translate to CNs and remove duplicates

  // x-axis is set for single cell selection
  std::string cn;

  for (i = 0; i < vector1.size(); i++)
    {
      if (vector1[i])  // the object is not empty
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector1[i])))
            {
              // second argument is true as only single cell here is allowed. In this case we
              //can assume that the size of the return vector is 1.
              const CCopasiObject * pObject = CCopasiSelectionDialog::chooseCellMatrix(pArray, true, true, "X axis: ")[0];

              if (!pObject) continue;

              cn = pObject->getCN();
            }
          else
            cn = vector1[i]->getCN();

          // check whether cn is already on objects1
          for (sit = objects1.begin(); sit != objects1.end(); ++sit)
            {
              if (*sit == cn) break;
            }

          // if not exist, input cn into objects1
          if (sit == objects1.end())
            {
              objects1.push_back(cn);
            }
        }
    }

  for (i = 0; i < vector2.size(); i++)
    {
      if (vector2[i])
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector2[i])))
            {
              // second argument is set false for multi selection
              std::vector<const CCopasiObject*> vvv = CCopasiSelectionDialog::chooseCellMatrix(pArray, false, true, "Y axis: ");
              std::vector<const CCopasiObject*>::const_iterator it;

              for (it = vvv.begin(); it != vvv.end(); ++it)
                {
                  if (!*it) continue;

                  cn = (*it)->getCN();

                  //check if the CN already is in the list, if not add it.
                  for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                    if (*sit == cn) break;

                  if (sit == objects2.end())
                    objects2.push_back(cn);
                }
            }
          else
            {
              cn = vector2[i]->getCN();

              //check if the CN already is in the list, if not add it.
              for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                if (*sit == cn) break;

              if (sit == objects2.end())
                objects2.push_back(cn);
            }
        }
    }

  C_INT32 storeTab = tabs->count();

  if (objects1.size() == 1)
    {
      for (i = 0; i < objects2.size(); ++i)
        {
          addBandedGraphTab(pDataModel->getDataObject(objects2[i])->getObjectDisplayName()
                            + "|"
                            + pDataModel->getDataObject(objects1[0])->getObjectDisplayName(),
                            objects1[0], objects2[i]);
        }
    }
  else if (objects2.size() == 1)
    {
      for (i = 0; i < objects1.size(); ++i)
        {
          addBandedGraphTab(pDataModel->getDataObject(objects2[0])->getObjectDisplayName()
                            + "|"
                            + pDataModel->getDataObject(objects1[i])->getObjectDisplayName(),
                            objects1[i], objects2[0]);
        }
    }
  else
    {
      size_t imax;

      if (objects1.size() > objects2.size())
        imax = objects2.size();
      else
        imax = objects1.size();

      for (i = 0; i < imax; ++i)
        {
          addBandedGraphTab(pDataModel->getDataObject(objects2[i])->getObjectDisplayName()
                            + "|"
                            + pDataModel->getDataObject(objects1[i])->getObjectDisplayName() ,
                            objects1[i], objects2[i]);
        }
    }

  tabs->setCurrentIndex(storeTab);
}
#endif // COPASI_BANDED_GRAPH

void CQPlotSubwidget::addHisto1DTab(const std::string & title,
                                    const CPlotDataChannelSpec & x, const C_FLOAT64 & incr)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::histoItem1d);
  item->addChannel(x);
  item->setValue("increment", incr);

  addPlotItem(item);
}

void CQPlotSubwidget::addHisto1D()
{
  C_INT32 storeTab = getCurrentIndex();
  addHisto1DTab("Histogram", CPlotDataChannelSpec(CCopasiObjectName("")), 1.0);
  setCurrentIndex(storeTab);
}

void CQPlotSubwidget::createHistograms(std::vector<const CCopasiObject* >objects, const C_FLOAT64 & incr)
{
  C_INT32 storeTab = getCurrentIndex();

  size_t i;

  for (i = 1; i < objects.size(); ++i)
    {
      if (objects[i])
        addHisto1DTab("Histogram: " + objects[i]->getObjectDisplayName(),
                      CPlotDataChannelSpec(objects[i]->getCN()), incr);

      //         lineEditTitle->setText("Histogram: " + FROM_UTF8(mpObjectX->getObjectDisplayName()));
    }

  setCurrentIndex(storeTab);
}

//-----------------------------------------------------------------------------

void CQPlotSubwidget::removeCurve()
{
  deleteCurve(getCurrentIndex());
}

//-----------------------------------------------------------------------------

void CQPlotSubwidget::commitPlot()
{
  saveToPlotSpec();

  loadFromPlotSpec(dynamic_cast<CPlotSpecification*>(CCopasiRootContainer::getKeyFactory()->get(mKey)));
}

//-----------------------------------------------------------------------------

void CQPlotSubwidget::deletePlot()
{
  size_t Index, Size;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (!pDataModel->getModel())
    return;

  CPlotSpecification * pspec = dynamic_cast< CPlotSpecification * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!pspec) return;

  Index =
    pDataModel->getPlotDefinitionList()->CCopasiVector<CPlotSpecification>::getIndex(pspec);
  pDataModel->getPlotDefinitionList()->removePlotSpec(mKey);
  std::string deletedKey = mKey;

  Size = pDataModel->getPlotDefinitionList()->size();

  if (Size > 0)
    enter((*pDataModel->getPlotDefinitionList())[std::min(Index, Size - 1)]->CCopasiParameter::getKey());
  else
    enter("");

  //ListViews::
  protectedNotify(ListViews::PLOT, ListViews::DELETE, deletedKey);
}

//-----------------------------------------------------------------------------

void CQPlotSubwidget::addPlot()
{
  leave();

  std::string name = "plot_";
  int i = 0;
  CPlotSpecification* pPl = NULL;
  name += TO_UTF8(QString::number(i));
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  while (!(pPl = pDataModel->getPlotDefinitionList()->createPlotSpec(name, CPlotItem::plot2d)))
    {
      i++;
      name = "plot_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = pPl->CCopasiParameter::getKey();
  protectedNotify(ListViews::PLOT, ListViews::ADD, key);
  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

//-----------------------------------------------------------------------------

void CQPlotSubwidget::resetPlot()
{
  loadFromPlotSpec(dynamic_cast<CPlotSpecification*>(CCopasiRootContainer::getKeyFactory()->get(mKey)));
}

//-----------------------------------------------------------------------------

bool CQPlotSubwidget::loadFromPlotSpec(const CPlotSpecification *pspec)
{
  if (!pspec) return false;

  mLastSelection.clear();

  //title
  titleLineEdit->setText(pspec->getTitle().c_str());

  //active?
  activeCheckBox->setChecked(pspec->isActive());

  //type
  mType = pspec->getType();

  switch (mType)
    {
#ifdef COPASI_BANDED_GRAPH

      case CPlotItem::bandedGraph:
#endif // COPASI_BANDED_GRAPH
      case CPlotItem::plot2d:
        checkLogX->setChecked(pspec->isLogX());
        checkLogY->setChecked(pspec->isLogY());
        break;

      default:
        fatalError();
        break;
    }

  C_INT32 oldIndex = getCurrentIndex();

  //clear tabWidget
  deleteCurves();

  //reconstruct tabWidget from curve specs
  const CCopasiVector<CPlotItem> & curves = pspec->getItems();
  size_t i, imax = curves.size();

  for (i = 0; i < imax; ++i)
    {
      addPlotItem(curves[i]);
    }

  setCurrentIndex(oldIndex);

  return true; //TODO really check
}

bool CQPlotSubwidget::saveToPlotSpec()
{
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(mpObject);

  if (!pspec) return true;

  pspec->cleanup();

  //title
  if (pspec->getTitle() != TO_UTF8(titleLineEdit->text()))
    {
      pspec->setTitle(TO_UTF8(titleLineEdit->text()));
      protectedNotify(ListViews::PLOT, ListViews::RENAME, mKey);
    }

  //active?
  pspec->setActive(activeCheckBox->isChecked());

  //scales
  pspec->setLogX(checkLogX->isChecked());
  pspec->setLogY(checkLogY->isChecked());

  //curves
  CPlotItem* item;

  storeChanges();

  QMap<QString, CPlotItem*>::iterator it;

  for (it = mList.begin(); it != mList.end(); ++it)
    {
      CPlotItem* currentItem = (*it);

      if (currentItem == NULL) continue;

      item = new CPlotItem(*currentItem);

      if (item != NULL)
        if (!pspec->getItems().add(item , true))
          delete item;
    }

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  // However we do not check whether the scan item are changed we delete all
  // and create them new.
  if (true)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      // mChanged = false;
    }

  return true;
}

//-----------------------------------------------------------------------------

//TODO:  save a copy!

bool CQPlotSubwidget::enterProtected()
{
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(mpObject);

  if (!pspec)
    {
      mpListView->switchToOtherWidget(42, "");
      return false;
    }

  return loadFromPlotSpec(pspec);
}
bool CQPlotSubwidget::areOfSameType(QList<QListWidgetItem*>& items)
{
  if (items.size() <= 1) return true;

  QList<CPlotItem::Type> temp;

  QList<QListWidgetItem*>::iterator it;

  for (it = items.begin(); it != items.end(); ++it)
    {
      CPlotItem *item = mList[(*it)->text()];

      if (!temp.contains(item->getType()))
        temp.append(item->getType());
    }

  return temp.size() == 1;
}
void CQPlotSubwidget::itemSelectionChanged()
{
  storeChanges();
  QList<QListWidgetItem*> current = mpListPlotItems->selectedItems();

  if (current.size() == 0)
    {
      mpStack->setEnabled(false);
    }
  else if (current.size() == 1)
    {
      mpStack->setEnabled(true);
      selectPlotItem(mList[current[0]->text()]);
    }
  else
    {
      if (!areOfSameType(current))
        {
          mpStack->setEnabled(false);
        }
      else
        {
          mpStack->setEnabled(true);
          selectPlotItem(mList[current[0]->text()]);
        }
    }

  mLastSelection = current;
}

//-----------------------------------------------------------------------------

bool CQPlotSubwidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (mIgnoreUpdates || isHidden()) return true;

  switch (objectType)
    {
        //TODO: check list:
      case ListViews::MODEL:

        switch (action)
          {
            case ListViews::DELETE:
              mpObject = NULL;
              mKey = "";
              return enterProtected();
              break;

            default:
              break;
          }

        break;

      case ListViews::PLOT:

        if (key == mKey)
          {
            switch (action)
              {
                case ListViews::DELETE:
                  mpObject = NULL;
                  mKey = "";
                  return enterProtected();
                  break;

                case ListViews::CHANGE:
                  return enterProtected();
                  break;

                default:
                  break;
              }
          }

        break;

      default:
        break;
    }

  return true;
}

//-----------------------------------------------------------------------------

bool CQPlotSubwidget::leave()
{
  return saveToPlotSpec();
}
