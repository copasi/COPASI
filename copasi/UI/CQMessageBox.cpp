// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QStyle>
#include <QApplication>
#include <QPushButton>

#include "copasiui3window.h"
#include "CQMessageBox.h"
#include "listviews.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/resourcesUI/CQIconResource.h"

CQMessageBox::CQMessageBox(QMessageBox::Icon icon, const QString & title, const QString & text,
                           QMessageBox::StandardButtons buttons, QWidget *parent,
                           Qt::WindowFlags f)
  : QDialog(parent, f)
  , mButton(QMessageBox::NoButton)
  , mpClickedButton(NULL)
    //QMessageBox(icon, title, QString(), buttons, parent, f),
{
  if (CopasiUI3Window::getMainWindow() != NULL)
    {
      CopasiUI3Window::getMainWindow()->setMessageShown(true);
    }

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  setupUi(this);

  setWindowTitle(title);
  mpMessage->setPlainText(text);
  mpButtonBox->setStandardButtons((QDialogButtonBox::StandardButtons)((int)buttons));
  int filteredIndex = mpTabWidget->indexOf(mpTabFiltered);

  if (filteredIndex != -1)
    mpTabWidget->removeTab(filteredIndex);

#define COPASI_PIXMAP_SIZE 64

  switch (icon)
    {
      case QMessageBox::Question:
        mpLblIcon->setPixmap(CQIconResource::icon(CQIconResource::dialog_question).pixmap(COPASI_PIXMAP_SIZE, COPASI_PIXMAP_SIZE));
        break;

      case QMessageBox::Information:
        mpLblIcon->setPixmap(CQIconResource::icon(CQIconResource::dialog_information).pixmap(COPASI_PIXMAP_SIZE, COPASI_PIXMAP_SIZE));
        break;

      case QMessageBox::Warning:
        mpLblIcon->setPixmap(CQIconResource::icon(CQIconResource::dialog_warning).pixmap(COPASI_PIXMAP_SIZE, COPASI_PIXMAP_SIZE));
        break;

      case QMessageBox::Critical:
        mpLblIcon->setPixmap(CQIconResource::icon(CQIconResource::dialog_error).pixmap(COPASI_PIXMAP_SIZE, COPASI_PIXMAP_SIZE));
        break;

      default:
        break;
    }
}

CQMessageBox::~CQMessageBox()
{
  if (CopasiUI3Window::getMainWindow() != NULL)
    {
      CopasiUI3Window::getMainWindow()->setMessageShown(false);
    }
}

// static
QMessageBox::StandardButton CQMessageBox::information(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Information, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  QMessageBox::StandardButton choice = (QMessageBox::StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

QMessageBox::StandardButton CQMessageBox::question(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Question, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  QMessageBox::StandardButton choice = (QMessageBox::StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::warning(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Warning, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  QMessageBox::StandardButton choice = (QMessageBox::StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::critical(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Critical, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  QMessageBox::StandardButton choice = (QMessageBox::StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::confirmDelete(QWidget *parent,
    const QString &objectType, const QString &objects,
    const CDataContainer * pContainer)
{
  if (pContainer == NULL)
    return QMessageBox::Ok;

  CDataObject::ObjectSet DeletedObjects;
  DeletedObjects.insert(pContainer);

  // Determine the affected data model
  const CDataModel * pDataModel = pContainer->getObjectDataModel();

  // Determine the affected function DB
  CFunctionDB * pFunctionDB =
    dynamic_cast< CFunctionDB * >(pContainer->getObjectAncestor("FunctionDB"));

  if (pDataModel == NULL &&
      pFunctionDB == NULL)
    return QMessageBox::Ok;

  if (pFunctionDB != NULL)
    {
      // TODO In case a function is deleted we need to loop through all data models
      pDataModel = ListViews::dataModel(parent);

      assert(pDataModel != NULL);
    }
  else
    {
      pFunctionDB = CRootContainer::getFunctionList();
    }

  bool isUsed = false;
  QString msg = buildDeleteConfirmationMessage(objectType, objects,
                pFunctionDB, DeletedObjects, pDataModel, isUsed);

  QMessageBox::StandardButton choice = QMessageBox::Ok;

  if (isUsed)
    {
      choice = CQMessageBox::question(parent, "CONFIRM DELETE", msg,
                                      QMessageBox::Ok | QMessageBox::Cancel,
                                      QMessageBox::Cancel);
    }

  return choice;
}

QString CQMessageBox::buildDeleteConfirmationMessage(
  const QString & objectType,
  const QString & objects,
  CFunctionDB * pFunctionDB,
  std::set< const CObjectInterface * > & DeletedObjects,
  const CDataModel * pDataModel,
  bool &isUsed)
{
  QString msg =
    QString("Do you want to delete the listed %1?\n  %2\n").arg(objectType, objects);

  CDataObject::DataObjectSet Functions;
  CDataObject::DataObjectSet Reactions;
  CDataObject::DataObjectSet Metabolites;
  CDataObject::DataObjectSet Values;
  CDataObject::DataObjectSet Compartments;
  CDataObject::DataObjectSet Events;
  CDataObject::DataObjectSet EventAssignments;
  CDataObject::DataObjectSet Tasks;

  isUsed = false;

  if (pFunctionDB != NULL)
    {
      isUsed |= pFunctionDB->appendDependentFunctions(DeletedObjects, Functions);

      if (Functions.size() > 0)
        {
          msg.append("Following functions(s) reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Functions.begin();
          CDataObject::DataObjectSet::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              DeletedObjects.insert(*it);
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  const CModel * pModel = NULL;

  if (pDataModel != NULL)
    {
      pModel = pDataModel->getModel();

      // We need to check the tasks
      isUsed |= pDataModel->appendDependentTasks(DeletedObjects, Tasks);

      if (Tasks.size() > 0)
        {
          msg.append("Following task(s) reference above and will be modified:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Tasks.begin();
          CDataObject::DataObjectSet::const_iterator end = Tasks.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  if (pModel != NULL)
    {
      isUsed |= pModel->appendAllDependents(DeletedObjects, Reactions, Metabolites,
                                            Compartments, Values, Events, EventAssignments);

      if (Reactions.size() > 0)
        {
          msg.append("Following reactions(s) reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Reactions.begin();
          CDataObject::DataObjectSet::const_iterator end = Reactions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Metabolites.size() > 0)
        {
          msg.append("Following species reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Metabolites.begin();
          CDataObject::DataObjectSet::const_iterator end = Metabolites.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Values.size() > 0)
        {
          msg.append("Following global quantities reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Values.begin();
          CDataObject::DataObjectSet::const_iterator end = Values.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Compartments.size() > 0)
        {
          msg.append("Following compartment(s) reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Compartments.begin();
          CDataObject::DataObjectSet::const_iterator end = Compartments.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Events.size() > 0)
        {
          msg.append("Following event(s) reference above and will be deleted:\n  ");

          CDataObject::DataObjectSet::const_iterator it = Events.begin();
          CDataObject::DataObjectSet::const_iterator end = Events.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (EventAssignments.size() > 0)
        {
          bool first = true;

          CDataObject::DataObjectSet::const_iterator it = EventAssignments.begin();
          CDataObject::DataObjectSet::const_iterator end = EventAssignments.end();

          for (; it != end; ++it)
            {
              const CDataObject * pEvent = (*it)->getObjectAncestor("Event");

              if (Events.find(pEvent) == Events.end())
                {
                  if (first)
                    {
                      msg.append("Following event assignment(s) reference above and will be deleted:\n  ");
                      first = false;
                    }

                  const CDataObject * pObject = CRootContainer::getKeyFactory()->get((*it)->getObjectName());
                  std::string ObjectName = (pObject != NULL) ? pObject->getObjectName() : (*it)->getObjectName();
                  msg.append(FROM_UTF8(pEvent->getObjectName() + ": " + ObjectName));
                  msg.append("\n  ");
                }
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  return msg;
}

void CQMessageBox::setText(const QString & text)
{
  mpMessage->setPlainText(text);
}

void CQMessageBox::setFilteredText(const QString & text)
{
  int filteredIndex = mpTabWidget->indexOf(mpTabFiltered);

  if (filteredIndex == -1 && !text.isEmpty())
    mpTabWidget->addTab(mpTabFiltered, "Filtered Messages");

  mpFilteredMessage->setPlainText(text);
}

void CQMessageBox::setDefaultButton(QMessageBox::StandardButton defaultButton)
{
  auto *button = mpButtonBox->button((QDialogButtonBox::StandardButton) defaultButton);
  setDefaultButton(button);
}

void CQMessageBox::setDefaultButton(QPushButton* button)
{
  if (button != NULL)
    {
      button->setDefault(true);
      button->setFocus();
    }
}

void CQMessageBox::slotButtonPressed(QAbstractButton * pButton)
{
  mButton = (QMessageBox::StandardButton)((int) mpButtonBox->standardButton(pButton));
  mpClickedButton = pButton;
  close();
}

QAbstractButton* CQMessageBox::clickedButton()
{
  return mpClickedButton;
}

int CQMessageBox::exec()
{
  int result = QDialog::exec();
  return (int)mButton;
}

QAbstractButton*
CQMessageBox::button(QMessageBox::StandardButton button)
{
  return mpButtonBox->button((QDialogButtonBox::StandardButton)((int) button));
}

QPushButton*
CQMessageBox::addButton(QMessageBox::StandardButton button)
{
  return mpButtonBox->addButton((QDialogButtonBox::StandardButton)((int) button));
}
