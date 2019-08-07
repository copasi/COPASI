// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QFile>
#include <QItemDelegate>
#include <QDir>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLErrorLog.h>

#include "CProvenanceDialog.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

CProvenanceDialog::CProvenanceDialog(QWidget* parent, QString PathFile ,  QList<QString> VersionsPathToCurrentModel)
  : QDialog(parent)
{
  setupUi(this);
  //mProvenanceParentOfCurrentModel = ProvenanceParentOfCurrentModel;
  //mVersioningParentOfCurrentModel = VersioningParentOfCurrentModel;
  mVersionsPathToCurrentModel = VersionsPathToCurrentModel;
  mPathFile = PathFile;
  mNCol = 8; //total number of UNDO History column
  mSelectedIndex = 0;
  mpProvenanceTable = new QStandardItemModel(10000, mNCol, parent);
  mNRow = 0;
  int col;

  for (col = 0; col < mNCol; col++)
    {
      switch (col)
        {
          case 0:
            mpProvenanceTable->setHeaderData(0, Qt::Horizontal, QString("Entity Type"));
            break;

          case 1:
            mpProvenanceTable->setHeaderData(1, Qt::Horizontal, QString("Name"));
            break;

          case 2:
            mpProvenanceTable->setHeaderData(2, Qt::Horizontal, QString("Action"));
            break;

          case 3:
            mpProvenanceTable->setHeaderData(3, Qt::Horizontal, QString("Property"));
            break;

          case 4:
            mpProvenanceTable->setHeaderData(4, Qt::Horizontal, QString("New Value"));
            break;

          case 5:
            mpProvenanceTable->setHeaderData(5, Qt::Horizontal, QString("Time"));
            break;

          case 6:
            mpProvenanceTable->setHeaderData(6, Qt::Horizontal, QString("Author"));
            break;

          case 7:
            mpProvenanceTable->setHeaderData(7, Qt::Horizontal, QString("Main Type"));
            break;
        }
    }

  //attach Browsing tree to its view
  //mpTreeView = new QTreeView(this);
  ProvXMLFiles2ProvenanceTable();
  CurrentSessionEdits2ProvenanceTable();

  mpProvenanceBrowseTree = new QStandardItemModel();
  generateProvenanceBrowsingTree();
  mpTreeView->setModel(mpProvenanceBrowseTree);
  connect(mpTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
  mpTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // attach the model to the view
  mpProvenanceView->setModel(mpProvenanceTable);
  mpProvenanceView->setSelectionBehavior(QAbstractItemView::SelectRows);
  mpProvenanceView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  mpProvenanceView->setColumnHidden(7, true);
  int i;

  for (i = mNRow ; i < mpProvenanceTable->rowCount(); i++)
    {
      mpProvenanceView->setRowHidden(i, true);
    }
}
CProvenanceDialog::~CProvenanceDialog()
{
  delete ui;
}

void CProvenanceDialog::generateProvenanceBrowsingTree()
{
  // Add provenance as the root of Browising tree
  QStandardItem *item = new QStandardItem(QString("Provenance"));
  mpProvenanceBrowseTree->appendRow(item);
  QStandardItem *item1 = new QStandardItem(QString("Model"));
  item->appendRow(item1);
  item = item1;
  item1 =  new QStandardItem(QString("Compartments"));
  item->appendRow(item1);
  item1 =  new QStandardItem(QString("Species"));
  item->appendRow(item1);
  item1 =  new QStandardItem(QString("Reactions"));
  item->appendRow(item1);
  item1 =  new QStandardItem(QString("Global Quantities"));
  item->appendRow(item1);
  item1 =  new QStandardItem(QString("Events"));
  item->appendRow(item1);
}

void CProvenanceDialog::CurrentSessionEdits2ProvenanceTable()
{
  // set the table header data
  int row;

  // Retrieve Author's information from Configuration
  CConfigurationFile * configFile = CRootContainer::getConfiguration();
  CCopasiParameter * pParameter;
  QString EntityType, Name, Action, Property, NewValue, Time, Author, GivenName, FamilyName;
  pParameter = configFile->getParameter("Given Name");
  GivenName = FROM_UTF8(pParameter->getValue< std::string >());
  pParameter = configFile->getParameter("Family Name");
  FamilyName = FROM_UTF8(pParameter->getValue< std::string >());

  if (pParameter != NULL)
    {

      Author = (GivenName + QString(" ") + FamilyName);
    }

  for (row = 0; row < mpUndoStack->count(); row++)
    {
      const QUndoCommand *cmd = mpUndoStack->command(row);
      const CCopasiUndoCommand *cCommand = dynamic_cast<const CCopasiUndoCommand*>(cmd);
      EntityType = QString(FROM_UTF8(cCommand->getEntityType()));
      Name = QString(FROM_UTF8(cCommand->getName()));
      Action = QString(FROM_UTF8(cCommand->getAction()));

      if (Action == "Add to list")
        {
          Action = QString("Insert");
        }
      else if (Action == "Delete set")
        {
          Action = QString("Delete");
        }
      else if (Action == "Change")
        {
          Action = QString("Update");
        }
      else
        {
          break;
        }

      Property = QString(FROM_UTF8(cCommand->getProperty()));
      NewValue = QString(FROM_UTF8(cCommand->getNewValue()));
      Time = QString(FROM_UTF8(cCommand->getTime()));
      AddOneLineToTable(EntityType, Name, Action, Property, NewValue, Time, Author);
    }
}

void CProvenanceDialog::on_mpTreeView_doubleClicked(const QModelIndex &index)
{
  int i;

  for (i = 0 ; i < mNRow; i++)
    {
      mpProvenanceView->setRowHidden(i, false);
    }

  QString ChosenItem = mpProvenanceBrowseTree->data(index).toString();
  bool Flag = false;

  if ((ChosenItem == "Compartments") || (ChosenItem == "Reactions") || (ChosenItem == "Events"))
    {
      ChosenItem.resize(ChosenItem.size() - 1);
      Flag = true;
    }
  else if (ChosenItem == "Species")
    {
      Flag = true;
    }
  else if (ChosenItem == "Global Quantities")
    {
      ChosenItem = QString("Global Quantity");
      Flag = true;
    }

  if (Flag) // The first line should be checked
    {
      for (i = 0 ; i < mNRow; i++)
        {
          if (mpProvenanceTable->item(i, 0)->text() != ChosenItem)
            {
              mpProvenanceView->setRowHidden(i, true);
            }
        }
    }
  else // the end hidden line should be checked
    {
      if (ChosenItem == "Model")
        {
          for (i = 0 ; i < mNRow; i++)
            {
              if (mpProvenanceTable->item(i, 7)->text() != ChosenItem)
                {
                  mpProvenanceView->setRowHidden(i, true);
                }
            }
        }

// This part for Task
      else if (ChosenItem == "Tasks")
        {
          for (i = 0 ; i < mNRow; i++)
            {
              if (mpProvenanceTable->item(i, 7)->text() != ChosenItem)
                {
                  mpProvenanceView->setRowHidden(i, true);
                }
            }
        }
      else
        {
          //Something except Model Tasks etc.
        }
    }
}

void CProvenanceDialog::ProvXMLFiles2ProvenanceTable()
{

// Provenance of origin of file to table
  QString dataFile = mPathFile + "/ProvenanceOrigion.xml";

  QFile Fout(dataFile);

  if (Fout.exists())
    {

      XMLErrorLog log1;
      XMLInputStream stream(dataFile.toUtf8(), true, "", &log1);

      if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
        {
          XMLToken ProvenanceInformation = stream.next();
          QHash<QString, QList<QString> > ENtityIDInformation;
          QMap<QString, QString> AgentIDAuthor;
          QHash<QString,  int> ActivityIDProvTableRow;

          while (stream.isGood())
            {
              stream.skipText();
              //grab the next element
              XMLToken next = stream.peek();

              // if we reached the end table element, we stop
              if (next.isEndFor(ProvenanceInformation))
                break;

              if (next.getName() == "entity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                  QString MainType = QString::fromStdString(xmlEntity.getAttrValue("Main_Type"));
                  QString EntityType = QString::fromStdString(xmlEntity.getAttrValue("Entity_Type"));
                  QList<QString> EntityInformation;
                  EntityInformation.append(EntityName);
                  EntityInformation.append(MainType);
                  EntityInformation.append(EntityType);
                  ENtityIDInformation.insert(EntityID, EntityInformation);
                }
              else if (next.getName() == "activity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                  QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                  QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                  ActivityIDProvTableRow.insert(ActivityID, mNRow);
                  AddOneLineToTable("", "", ActivityAction, ActivityProperty, ActivityNewValue, "", "");
                }
              else if (next.getName() == "agent")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                  QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
                  AgentIDAuthor.insert(AgentID, (AgentName + " " + AgentFamilyName));
                }

              else if (next.getName() == "used")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, EntityID;
                  bool ActivityExists = false;
                  bool EntityExists = false;
                  int TableRow;
                  QList<QString> EntityInformation;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (EntityExists))
                            {
                              // Add entity name
                              QModelIndex index = mpProvenanceTable->index(TableRow, 1, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(0)));
                              // add Main Type: Model, Task, Document
                              index = mpProvenanceTable->index(TableRow, 7, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(1)));
                              // add Entity Type
                              index = mpProvenanceTable->index(TableRow, 0, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(2)));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));

                              if (ENtityIDInformation.contains(EntityID))
                                {
                                  EntityExists = true;
                                  EntityInformation = ENtityIDInformation.value(EntityID);
                                }
                            }
                        }
                    }
                }

              else if (next.getName() == "wasAttributedTo")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID, EntityID;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "agent")
                            {

                              AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }

              else if (next.getName() == "wasAssociatedWith")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID, ActivityID, Author;
                  bool ActivityExists = false;
                  bool AgentExists = false;
                  int TableRow;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (AgentExists))
                            {
                              QModelIndex index = mpProvenanceTable->index(TableRow, 6, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(Author));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "agent")
                            {

                              AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (AgentIDAuthor.contains(AgentID))
                                {
                                  AgentExists = true;
                                  Author =  AgentIDAuthor.value(AgentID);
                                }
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }
                        }
                    }
                }
              else if (next.getName() == "wasGeneratedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, EntityID, Time;
                  bool timeExists = false;
                  bool activityExists = false;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          if (activityExists)
                            {
                            }

                          if (timeExists)
                            {
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0));
                              activityExists = true;
                            }

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                              timeExists = true;
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }
              else if (next.getName() == "wasStartedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, Time;
                  bool ActivityExists = false;
                  bool TimeExists = false;
                  int TableRow;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (TimeExists))
                            {
                              QModelIndex index = mpProvenanceTable->index(TableRow, 5, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(Time));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                              TimeExists = true;
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }
                        }
                    }
                }
              else if (next.getName() == "wasEndedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, Time;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }

              else
                {
                  break;
                }
            }
        }
    }

// Provenance of Versions to table
  int VersionCounter;

  for (VersionCounter = 0; VersionCounter < mVersionsPathToCurrentModel.size(); ++VersionCounter)
    {
      QString dataFile = mPathFile + "/" + mVersionsPathToCurrentModel.at(VersionCounter) + "/" + mVersionsPathToCurrentModel.at(VersionCounter) + "Provenance.xml";
      QFile Fout(dataFile);

      if (Fout.exists())
        {

          XMLErrorLog log1;
          XMLInputStream stream(dataFile.toUtf8(), true, "", &log1);

          if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
            {
              XMLToken ProvenanceInformation = stream.next();
              QHash<QString, QList<QString> > ENtityIDInformation;
              QHash<QString,  int> ActivityIDProvTableRow;
              QMap<QString, QString> AgentIDAuthor;

              while (stream.isGood())
                {
                  stream.skipText();
                  //grab the next element
                  XMLToken next = stream.peek();

                  // if we reached the end table element, we stop
                  if (next.isEndFor(ProvenanceInformation))
                    break;

                  if (next.getName() == "entity")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                      QString MainType = QString::fromStdString(xmlEntity.getAttrValue("Main_Type"));
                      QString EntityType = QString::fromStdString(xmlEntity.getAttrValue("Entity_Type"));

                      QList<QString> EntityInformation;
                      EntityInformation.append(EntityName);
                      EntityInformation.append(MainType);
                      EntityInformation.append(EntityType);
                      ENtityIDInformation.insert(EntityID, EntityInformation);
                    }
                  else if (next.getName() == "activity")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                      QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                      QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                      ActivityIDProvTableRow.insert(ActivityID, mNRow);
                      AddOneLineToTable("", "", ActivityAction, ActivityProperty, ActivityNewValue, "", "");
                    }
                  else if (next.getName() == "agent")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                      QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
// We don't show Organizzation and Email in this Table
                      //QString AgentOrganization = QString::fromStdString(xmlEntity.getAttrValue("Organization"));
                      //QString AgentEmail = QString::fromStdString(xmlEntity.getAttrValue("Email"));
                      AgentIDAuthor.insert(AgentID, (AgentName + " " + AgentFamilyName));
                    }

                  else if (next.getName() == "used")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID, EntityID;
                      bool ActivityExists = false;
                      bool EntityExists = false;
                      int TableRow;
                      QList<QString> EntityInformation;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              if ((ActivityExists)  && (EntityExists))
                                {
                                  // Add entity name
                                  QModelIndex index = mpProvenanceTable->index(TableRow, 1, QModelIndex());
                                  mpProvenanceTable->setData(index, QVariant(EntityInformation.at(0)));
                                  // add Main Type: Model, Task, Document
                                  index = mpProvenanceTable->index(TableRow, 7, QModelIndex());
                                  mpProvenanceTable->setData(index, QVariant(EntityInformation.at(1)));
                                  // add Entity Type
                                  index = mpProvenanceTable->index(TableRow, 0, QModelIndex());
                                  mpProvenanceTable->setData(index, QVariant(EntityInformation.at(2)));
                                }

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "activity")
                                {

                                  ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                                  if (ActivityIDProvTableRow.contains(ActivityID))
                                    {
                                      ActivityExists = true;
                                      TableRow = ActivityIDProvTableRow.value(ActivityID);
                                    }
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));

                                  if (ENtityIDInformation.contains(EntityID))
                                    {
                                      EntityExists = true;
                                      EntityInformation = ENtityIDInformation.value(EntityID);
                                    }
                                }
                            }
                        }
                    }

                  else if (next.getName() == "wasAttributedTo")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString AgentID, EntityID;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "agent")
                                {

                                  AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }

                  else if (next.getName() == "wasAssociatedWith")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString AgentID, ActivityID, Author;
                      bool ActivityExists = false;
                      bool AgentExists = false;
                      int TableRow;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              //add here
                              if ((ActivityExists)  && (AgentExists))
                                {
                                  QModelIndex index = mpProvenanceTable->index(TableRow, 6, QModelIndex());
                                  mpProvenanceTable->setData(index, QVariant(Author));
                                }

                              break;

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "agent")
                                {

                                  AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                                  if (AgentIDAuthor.contains(AgentID))
                                    {
                                      AgentExists = true;
                                      Author =  AgentIDAuthor.value(AgentID);
                                    }
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));

                                  if (ActivityIDProvTableRow.contains(ActivityID))
                                    {
                                      ActivityExists = true;
                                      TableRow = ActivityIDProvTableRow.value(ActivityID);
                                    }
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasGeneratedBy")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID, EntityID, Time;
                      bool timeExists = false;
                      bool activityExists = false;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here

                              if (activityExists)
                                {
                                }

                              if (timeExists)
                                {
                                }

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "activity")
                                {

                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                  activityExists = true;
                                }

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(stream.next().getCharacters());
                                  timeExists = true;
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasStartedBy")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID, Time;
                      bool ActivityExists = false;
                      bool TimeExists = false;
                      int TableRow;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              if ((ActivityExists)  && (TimeExists))
                                {
                                  QModelIndex index = mpProvenanceTable->index(TableRow, 5, QModelIndex());
                                  mpProvenanceTable->setData(index, QVariant(Time));
                                }

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(stream.next().getCharacters());
                                  TimeExists = true;
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));

                                  if (ActivityIDProvTableRow.contains(ActivityID))
                                    {
                                      ActivityExists = true;
                                      TableRow = ActivityIDProvTableRow.value(ActivityID);
                                    }
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasEndedBy")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID, Time;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(stream.next().getCharacters());
                                  //qDebug() << "It reaches time" <<endl;
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }

                  else
                    {
                      break;
                    }
                }
            }
        }
    }

// Provenance Current Model provenance to table
//  if (mProvenanceParentOfCurrentModel == mVersioningParentOfCurrentModel)
//    {
  dataFile = mPathFile + "/ProvenanceMainBody.xml";

  QFile Fout2(dataFile);

  if (Fout2.exists())
    {
      XMLErrorLog log1;
      XMLInputStream stream(dataFile.toUtf8(), true, "", &log1);

      if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
        {
          XMLToken ProvenanceInformation = stream.next();
          QHash<QString, QList<QString> > ENtityIDInformation;
          QMap<QString, QString> AgentIDAuthor;
          QHash<QString,  int> ActivityIDProvTableRow;

          while (stream.isGood())
            {
              stream.skipText();
              //grab the next element
              XMLToken next = stream.peek();

              // if we reached the end table element, we stop
              if (next.isEndFor(ProvenanceInformation))
                break;

              if (next.getName() == "entity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                  QString MainType = QString::fromStdString(xmlEntity.getAttrValue("Main_Type"));
                  QString EntityType = QString::fromStdString(xmlEntity.getAttrValue("Entity_Type"));
                  QList<QString> EntityInformation;
                  EntityInformation.append(EntityName);
                  EntityInformation.append(MainType);
                  EntityInformation.append(EntityType);
                  ENtityIDInformation.insert(EntityID, EntityInformation);
                }
              else if (next.getName() == "activity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                  QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                  QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                  ActivityIDProvTableRow.insert(ActivityID, mNRow);
                  AddOneLineToTable("", "", ActivityAction, ActivityProperty, ActivityNewValue, "", "");
                }
              else if (next.getName() == "agent")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                  QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));

// We don't show Organizzation and Email in this Table
                  //QString AgentOrganization = QString::fromStdString(xmlEntity.getAttrValue("Organization"));
                  //QString AgentEmail = QString::fromStdString(xmlEntity.getAttrValue("Email"));

                  AgentIDAuthor.insert(AgentID, (AgentName + " " + AgentFamilyName));
                }

              else if (next.getName() == "used")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, EntityID;
                  bool ActivityExists = false;
                  bool EntityExists = false;
                  int TableRow;
                  QList<QString> EntityInformation;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (EntityExists))
                            {
                              // Add entity name
                              QModelIndex index = mpProvenanceTable->index(TableRow, 1, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(0)));
                              // add Main Type: Model, Task, Document
                              index = mpProvenanceTable->index(TableRow, 7, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(1)));
                              // add Entity Type
                              index = mpProvenanceTable->index(TableRow, 0, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(EntityInformation.at(2)));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));

                              if (ENtityIDInformation.contains(EntityID))
                                {
                                  EntityExists = true;
                                  EntityInformation = ENtityIDInformation.value(EntityID);
                                }
                            }
                        }
                    }
                }

              else if (next.getName() == "wasAttributedTo")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID, EntityID;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "agent")
                            {

                              AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }

              else if (next.getName() == "wasAssociatedWith")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID, ActivityID, Author;
                  bool ActivityExists = false;
                  bool AgentExists = false;
                  int TableRow;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (AgentExists))
                            {
                              QModelIndex index = mpProvenanceTable->index(TableRow, 6, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(Author));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "agent")
                            {

                              AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (AgentIDAuthor.contains(AgentID))
                                {
                                  AgentExists = true;
                                  Author =  AgentIDAuthor.value(AgentID);
                                }
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }
                        }
                    }
                }
              else if (next.getName() == "wasGeneratedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, EntityID, Time;
                  bool timeExists = false;
                  bool activityExists = false;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          if (activityExists)
                            {
                            }

                          if (timeExists)
                            {
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0));
                              activityExists = true;
                            }

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                              timeExists = true;
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }
              else if (next.getName() == "wasStartedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, Time;
                  bool ActivityExists = false;
                  bool TimeExists = false;
                  int TableRow;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (TimeExists))
                            {
                              QModelIndex index = mpProvenanceTable->index(TableRow, 5, QModelIndex());
                              mpProvenanceTable->setData(index, QVariant(Time));
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                              TimeExists = true;
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));

                              if (ActivityIDProvTableRow.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  TableRow = ActivityIDProvTableRow.value(ActivityID);
                                }
                            }
                        }
                    }
                }
              else if (next.getName() == "wasEndedBy")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID, Time;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "time")
                            {

                              Time = QString::fromStdString(stream.next().getCharacters());
                            }

                          if (child.getName() == "activity")
                            {
                              ActivityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }
                    }
                }

              else
                {
                  break;
                }
            }
        }
    }

//}
}

void CProvenanceDialog::reallocateProvenanceTable(int Nrow)
{
  QStandardItemModel ProvenanceTable(Nrow, mNCol);

  // Now copy mpProvenanceTable in ProvenanceTable
  int row, col;

  for (row = 0; row < mNRow; row++)
    {
      for (col = 0; col < mNCol; ++col)
        {
          QStandardItem *item = new QStandardItem(QString(mpProvenanceTable->item(row, col)->text()));
          ProvenanceTable.setItem(row, col, item);
        }
    }

  // Now realocate mpProvenanceTable and refill it
  mpProvenanceTable = new QStandardItemModel(Nrow, mNCol);

  for (col = 0; col < mNCol; ++col)
    {
      switch (col)
        {
          case 0:
            mpProvenanceTable->setHeaderData(0, Qt::Horizontal, QString("Entity Type"));
            break;

          case 1:
            mpProvenanceTable->setHeaderData(1, Qt::Horizontal, QString("Name"));
            break;

          case 2:
            mpProvenanceTable->setHeaderData(2, Qt::Horizontal, QString("Action"));
            break;

          case 3:
            mpProvenanceTable->setHeaderData(3, Qt::Horizontal, QString("Property"));
            break;

          case 4:
            mpProvenanceTable->setHeaderData(4, Qt::Horizontal, QString("New Value"));
            break;

          case 5:
            mpProvenanceTable->setHeaderData(5, Qt::Horizontal, QString("Time"));
            break;

          case 6:
            mpProvenanceTable->setHeaderData(6, Qt::Horizontal, QString("Author"));
            break;

          case 7:
            mpProvenanceTable->setHeaderData(7, Qt::Horizontal, QString("Main Type"));
            break;
        }
    }

  for (row = 0; row < mNRow; row++)
    {
      for (col = 0; col < mNCol; col++)
        {
          QStandardItem *item = new QStandardItem(QString(ProvenanceTable.item(row, col)->text()));
          mpProvenanceTable->setItem(row, col, item);
        }
    }
}

void  CProvenanceDialog::AddOneLineToTable(QString EntityType, QString Name, QString Action, QString Property, QString NewValue, QString Time, QString Author)
{
  if (((mNRow + 1) % 10000) == 0)
    {
      reallocateProvenanceTable((mNRow + 10001));
    }

  for (int col = 0; col < mNCol; ++col)
    {
      QModelIndex index = mpProvenanceTable->index(mNRow, col, QModelIndex());

      switch (col)
        {
          case 0:
            mpProvenanceTable->setData(index, QVariant(EntityType));
            break;

          case 1:
            mpProvenanceTable->setData(index, QVariant(Name));
            break;

          case 2:
            mpProvenanceTable->setData(index, QVariant(Action));
            break;

          case 3:
            mpProvenanceTable->setData(index, QVariant(Property));
            break;

          case 4:
            mpProvenanceTable->setData(index, QVariant(NewValue));
            break;

          case 5:
            mpProvenanceTable->setData(index, QVariant(Time));
            break;

          case 6:
            mpProvenanceTable->setData(index, QVariant(Author));
            break;

// Currently just Model information is passed from UNdo to the Dialog - Task will add in future
          case 7:
            mpProvenanceTable->setData(index, QVariant(QString("Model")));
            break;
        }
    }

  mNRow++;
}
