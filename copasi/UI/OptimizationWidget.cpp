/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/OptimizationWidget.cpp,v $
   $Revision: 1.42 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/05/31 18:45:03 $
   End CVS Header */

#include <qfiledialog.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qtable.h>

#include "copasi.h"

#include "OptimizationWidget.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptMethod.h"
#include "model/CModel.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "OptimizationItemWidget.h"
#include "ObjectBrowserDialog.h"
#include "ObjectBrowserItem.h"
#include "CCopasiSelectionDialog.h"
#include "report/CKeyFactory.h"

//#include "CReportDefinitionSelect.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "utilities/CCopasiException.h"
#include "CScanContainerWidget.h"
#include "utilities/CopasiTime.h"
#include "COptWidgetTask.h"

OptimizationWidget::OptimizationWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
    //    pParent(parent)
{
  if (!name)
    setName("OptimizationWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));

  buttonsSeparator = new QFrame(this, "buttonsSeparator");
  buttonsSeparator->setGeometry(QRect(11, 281, 558, 16));
  buttonsSeparator->setFrameShape(QFrame::HLine);
  buttonsSeparator->setFrameShadow(QFrame::Sunken);
  buttonsSeparator->setFrameShape(QFrame::HLine);

  paramsGroupBox = new QGroupBox(this, "paramsGroupBox");
  paramsGroupBox->setGeometry(QRect(11, 290 - 30, 558, 98 + 120));

  typeGroupBox = new QGroupBox(this, "typeGroupBox");
  typeGroupBox->setGeometry(QRect(327, 131, 242, 108 - 30));

  timeCheck = new QCheckBox(typeGroupBox, "timeCheck");
  timeCheck->setGeometry(QRect(11, 45, 84, 19));

  steadystateCheck = new QCheckBox(typeGroupBox, "steadystateCheck");
  steadystateCheck->setGeometry(QRect(11, 20, 84, 19));

  AddTaskButton = new QPushButton(this, "AddTaskButton");
  AddTaskButton->setGeometry(QRect(327, 245 - 30, 242, 24));
  AddTaskButton->setAutoMask(TRUE);
  AddTaskButton->setOn(FALSE);

  methodGroupBox = new QGroupBox(this, "methodGroupBox");
  methodGroupBox->setGeometry(QRect(11, 131, 310, 138 - 30));

  expressionNameLabel_2 = new QLabel(methodGroupBox, "expressionNameLabel_2");
  expressionNameLabel_2->setGeometry(QRect(12, 21, 89, 20));

  methodCombo = new QComboBox(FALSE, methodGroupBox, "methodCombo");
  methodCombo->setGeometry(QRect(60, 20, 220, 20));

  param1Edit = new QLineEdit(methodGroupBox, "param1Edit");
  param1Edit->setGeometry(QRect(10, 50, 50, 20));

  param3Edit = new QLineEdit(methodGroupBox, "param3Edit");
  param3Edit->setGeometry(QRect(130, 50, 50, 20));

  param2Edit = new QLineEdit(methodGroupBox, "param2Edit");
  param2Edit->setGeometry(QRect(70, 50, 50, 20));

  param4Edit = new QLineEdit(methodGroupBox, "param4Edit");
  param4Edit->setGeometry(QRect(190, 50, 50, 20));

  param5Edit = new QLineEdit(methodGroupBox, "param5Edit");
  param5Edit->setGeometry(QRect(250, 50, 50, 20));

  confirmButton = new QPushButton(this, "confirmButton");
  confirmButton->setGeometry(QRect(12, 404 + 100, 181, 24));

  runButton = new QPushButton(this, "runButton");
  runButton->setGeometry(QRect(199, 404 + 100, 182, 24));

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setGeometry(QRect(387, 404 + 100, 181, 24));

  selectParameterButton = new QPushButton(this, "selectParameterButton");
  selectParameterButton->setGeometry(QRect(489, 71, 80, 24));

  expressionNameLabel = new QLabel(this, "expressionNameLabel");
  expressionNameLabel->setGeometry(QRect(11, 33, 51, 20));

  expressionName = new QLineEdit(this, "expressionName");
  expressionName->setGeometry(QRect(68, 33, 415, 20));
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  expressionEditlabel = new QLabel(this, "expressionEditlabel");
  expressionEditlabel->setGeometry(QRect(11, 71, 51, 24));

  expressionText = new QLineEdit(this, "expressionText");
  expressionText->setGeometry(QRect(68, 73, 415, 20));
  expressionText->setFrameShape(QLineEdit::LineEditPanel);
  expressionText->setFrameShadow(QLineEdit::Sunken);
  languageChange();
  resize(QSize(581, 447).expandedTo(minimumSizeHint()));
  //   clearWState(WState_Polished);

  // signals and slots connections

  // tab order
  setTabOrder(expressionName, expressionText);
  setTabOrder(expressionText, steadystateCheck);
  setTabOrder(steadystateCheck, timeCheck);
  setTabOrder(timeCheck, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  //scrollview

  Layoutparams = new QHBoxLayout(paramsGroupBox, 0, 6, "Layout24");
  scrollview = new CScanContainerWidget(paramsGroupBox);
  Layoutparams->addWidget(scrollview);

  mObject = NULL;

  methodCombo->insertItem("Genetic Algorithm");
  methodCombo->insertItem("Simulated Annealing");
  methodCombo->insertItem("EP2");
  methodCombo->insertItem("Hybrid GA/SA");

  //connect the runButton with the respective slot
  connect(runButton, SIGNAL(clicked()), this, SLOT(runOptimizationTask()));
  // connect the combo box with the respective slot
  connect(methodCombo, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));

  connect(timeCheck, SIGNAL(clicked()), this, SLOT(slotTimechecked()));
  connect(steadystateCheck, SIGNAL(clicked()), this, SLOT(slotSteadystatechecked()));

  connect(AddTaskButton , SIGNAL(clicked()), this, SLOT(slotAddItem()));
  connect(selectParameterButton , SIGNAL(clicked()), this, SLOT(slotChooseObject()));

  //reportDefinitionButton->setEnabled(false);

  // for the default GA option
  param1Edit->hide();
  param2Edit->hide();
  param3Edit->hide();
  param4Edit->show();
  param5Edit->show();
}

OptimizationWidget::~OptimizationWidget()
{}

void OptimizationWidget::CancelChangeButton()
{
  loadOptimization();
}

void OptimizationWidget::CheckBoxClicked()
{
}

void OptimizationWidget::runOptimizationTask()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));

  if (!optimizationTask) return;

  // save the state of the widget
  saveOptimization();

  optimizationTask->initialize(NULL);

  setCursor(Qt::WaitCursor);
  CProgressBar* tmpBar = new CProgressBar();

  optimizationTask->setProgressHandler(tmpBar);

  CCopasiTimeVariable time = CCopasiTimeVariable::getCurrentWallTime();

  try
    {
      optimizationTask->process();
    }
  catch (CCopasiException Exception)
    {
      std::cout << std::endl << "exception in optimization task" << std::endl;
      //TODO: message box
    }

  std::cout << "*************** The optimization took "
  << (CCopasiTimeVariable::getCurrentWallTime() - time).isoFormat()
  << " ***************" << std::endl;

  //should be renamed?

  optimizationTask->restore();

  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();

  return;

  std::ofstream output;

  if (optimizationTask->getReport().getTarget() != "")
    {
      if (optimizationTask->getReport().append())
        output.open(FROM_UTF8(optimizationTask->getReport().getTarget()),
                    std::ios_base::out | std::ios_base::app);
      else
        output.open(FROM_UTF8(optimizationTask->getReport().getTarget()),
                    std::ios_base::out);
    }

  if (output.is_open())
    optimizationTask->initialize(&output);

  else //ask if user insists on proceeding
    {
      if (QMessageBox::information (NULL, "No output specified,",
                                    "No report output target defined, Copasi cannot creat output for you.\n Do you want to continue running optimization task with no output?",
                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;
    }

  optimizationTask->process();

  //  ((ListViews*)pParent)->notify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());
  unsetCursor();
}

bool OptimizationWidget::loadOptimization()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));

  if (!optimizationTask) return false;

  COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
  if (!optimizationProblem) return false;

  mModel = optimizationProblem->getModel();

  scrollview->clearWidgetList();

  //scrollview->updateFromWidgetList();

  return true;
}

bool OptimizationWidget::slotAddItem()
{
  if (expressionText->text().length() > 0)
    {
      parseExpression(); // populates CKinFunction

      OptimizationItemWidget * tmp;
      //create item to get the default values
      COptProblem* tmpProblem = new COptProblem();

      tmp = new OptimizationItemWidget(scrollview);
      //tmp1->initFromOptimizationItem(tmpItem, CCopasiDataModel::Global->getModel());
      scrollview->addWidget(tmp);
      if (tmpProblem) delete tmpProblem;
      return true;
    }
  else
    return false;
}

bool OptimizationWidget::saveOptimization() const
  {
    COptTask* optimizationTask =
      dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
    if (!optimizationTask) return false;

    COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
    if (!optimizationProblem) return false;

    // optimizationProblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

    return true;
  }

void OptimizationWidget::ReportDefinitionClicked()
{
  /*  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
    COptTask* optimizationTask = (COptTask*)(CCopasiContainer*)GlobalKeys.get(optimizationTaskKey);
    pSelectDlg->setReport(&(optimizationTask->getReport()));
    pSelectDlg->loadReportDefinitionVector();
    if (pSelectDlg->exec () == QDialog::Rejected)
      {
        return;
      }*/
}

//************* CCopasiWidget interface *******************************

bool OptimizationWidget::enter(const std::string & key)
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(key));
  if (!optimizationTask) return false;

  optimizationTaskKey = key;

  //pSteadyStateWidget->enter(SteadyStateKey);
  //pTrajectoryWidget->enter(TrajectoryKey);

  // ((COptProblem*)(optimizationTask->getProblem()))->createDebugOptimization(dataModel->getModel());

  loadOptimization();

  return true;
}

bool OptimizationWidget::leave()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
  if (!optimizationTask) return false;

  return saveOptimization();
}

bool OptimizationWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      // check if there is a list of Report Defs
      CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = CCopasiDataModel::Global->getReportDefinitionList();
      if (pReportDefinitionVector)
        reportDefinitionButton->setEnabled(true);
      break;
    default:
      break;
    }
  return true;
}

std::string OptimizationWidget::getKey()
{
  return optimizationTaskKey;
}

bool OptimizationWidget::changeMethod(int index)
{
  switch (index)
    {
    case 0:
      // OptimizationGA
      // show only relevant boxes
      param1Edit->hide();
      param2Edit->hide();
      param3Edit->hide();
      param4Edit->show();
      param5Edit->show();
      break;

    case 1:
      param1Edit->hide();
      param2Edit->hide();
      param3Edit->hide();
      param4Edit->hide();
      param5Edit->show();
      break;
    case 2:
      param1Edit->hide();
      param2Edit->hide();
      param3Edit->hide();
      param4Edit->hide();
      param5Edit->show();
      break;

    default:
;
    }
  return true;
}

void OptimizationWidget::languageChange()
{
  setCaption(tr("Optimization"));
  typeGroupBox->setTitle(tr("Type"));
  timeCheck->setText(tr("Time Course"));
  steadystateCheck->setText(tr("Steady State"));
  AddTaskButton->setText(tr("Add"));
  methodGroupBox->setTitle(tr("Optimization Technique"));
  expressionNameLabel_2->setText(tr("Method"));
  param2Edit->setText(QString::null);
  confirmButton->setText(tr("confirm"));
  runButton->setText(tr("run"));
  cancelButton->setText(tr("cancel"));
  selectParameterButton->setText(tr("..."));
  expressionNameLabel->setText(tr("Name"));
  expressionEditlabel->setText(tr("Expression"));
  expressionText->setText(QString::null);
}

/* function - slotChooseObject
 * Description -  parsing */ 
/* Author - stupe   */

void OptimizationWidget::slotChooseObject()
{
  //  int rowCount;
  std::string mPrevExpr;
  std::string mStr;
  std::string parseMe;
  CCopasiObject* mpObj;
  mModel = CCopasiDataModel::Global->getModel();
  CCopasiObjectName CN;

  CCopasiObject* tmpObject = mObject;
  // open a selection dialog with single selection mode
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);

  browseDialog->setModel(mModel);

  browseDialog->setSingleSelection(true);
  //browseDialog->enableExpertMode(false);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (mObject)
    selection->push_back(mObject);
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      mObject = selection->at(0);
      if (mObject)
        {
          parseList.push_back(mObject);
          mPrevExpr = (expressionText->text());
          parseMe = CRegisteredObjectName(mObject->getCN());
          mPrevExpr = mPrevExpr.append("<");
          mPrevExpr = mPrevExpr.append(mObject->getObjectDisplayName());
          mPrevExpr = mPrevExpr.append(">");
          //CN = CCopasiObjectName(mObject->getObjectName());
          mpObj = (CCopasiObject*)CCopasiContainer::Root->getObject(parseMe);
          //parseMe =
          //mpObj = (CCopasiObject*)CCopasiContainer::Root->getObject(CN.getRemainder());
          C_FLOAT64 value = *(C_FLOAT64*)mObject->getReference();
          //value = *(C_FLOAT64*)mpObj->getReference();
          /*/mStr = mObject->getObjectDisplayName();
          //const QString mPrevExpr(mStr.c_str());
          //expressionText->remove(expressionText->len
          //expressionText->append(mPrevExpr.truncate(mPrevExpr.lenght()-1));*/

          //mPrevExpr = mPrevExpr.append(mObject->getCN());
          expressionText->setText(FROM_UTF8(mPrevExpr));
          //rowCount = expressionText->numLines();
          //expressionText->setCursorPosition(rowCount ,1000);

          if (mObject != tmpObject)
            {
              if (mObject->isValueDbl())
                {
                  value = *(C_FLOAT64*)mObject->getReference();
                  //lineEditMin->setText(QString::number(value*0.5));
                  //lineEditMax->setText(QString::number(value*2));
                }
            }
        }

      else
        expressionName->setText("");
    }

  else
  {}
}

/* function - slotParseExpression
 * Description -  parsing */ 
/* Author - stupe   */

bool OptimizationWidget::parseExpression()
{
  std::string mName = "temp";
  std::string mDisplayName = "";
  std::string mRNDesc = "";
  std::string temp = "";
  std::string mDesc = std::string(expressionText->text());
  std::vector<CCopasiObject *>::iterator it = parseList.begin();
  //CFunction* pFunc;
  //pFunc = CCopasiDataModel::Global->getFunctionList()->createFunction(name, CFunction::UserDefined)
  for (int i = 0; i < mDesc.length(); i++)
    {
      mRNDesc += mDesc[i];
      mDisplayName = "";
      if (mDesc[i] == '<')
        {
          i++;
          it = parseList.begin();
          while (i < mDesc.length() && mDesc[i] != '>')
            {
              mDisplayName += mDesc[i];
              i++;
            }

          while (it < parseList.end())
            {
              temp = (*it)->getObjectDisplayName();
              if ((*it)->getObjectDisplayName() == mDisplayName)
                {
                  mRNDesc += (*it)->getCN();
                  break;
                }

              it++;
            }

          mRNDesc += ">";
        }
    }

  CKinFunction* pFunction = new CKinFunction(mName);
  pFunction->setDescription(mRNDesc);
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
  if (!optimizationTask) return false;

  COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
  if (!optimizationProblem) return false;
  optimizationProblem->setFunction(pFunction);
}

void OptimizationWidget::slotSteadystatechecked()
{
  timeCheck->setChecked(false);
}

void OptimizationWidget::slotTimechecked()
{
  steadystateCheck->setChecked(false);
}
//***********************************************************
