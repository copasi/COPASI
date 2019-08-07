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

#include "CEntityProvenanceDialog.h"
#include "ui_CEntityProvenanceDialog.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/undo/CUndoStack.h"

CEntityProvenanceDialog::CEntityProvenanceDialog(QWidget *parent,
    CUndoStack *undoStack,
    QString PathFile,
    QList<QString> VersionsPathToCurrentModeconst,
    const char* name):
  CopasiWidget(parent, name)
{
  setupUi(this);
  //setUpdatesEnabled(true);
  //mProvenanceParentOfCurrentModel = ProvenanceParentOfCurrentModel;
  //mVersioningParentOfCurrentModel = VersioningParentOfCurrentModel;
  mVersionsPathToCurrentModel = VersionsPathToCurrentModeconst;
  mPathFile = PathFile;
  mpUndoStack = undoStack;
  mEntityName = "";
  mNCol = 5; //total number of UNDO History column
  mSelectedIndex = 0;
  mpProvenanceTable = new QStandardItemModel(100, mNCol, parent);
  mNRow = 0;
  int col;

  for (col = 0; col < mNCol; col++)
    {
      switch (col)
        {

          case 0:
            mpProvenanceTable->setHeaderData(0, Qt::Horizontal, QString("Action"));
            break;

          case 1:
            mpProvenanceTable->setHeaderData(1, Qt::Horizontal, QString("Property"));
            break;

          case 2:
            mpProvenanceTable->setHeaderData(2, Qt::Horizontal, QString("New Value"));
            break;

          case 3:
            mpProvenanceTable->setHeaderData(3, Qt::Horizontal, QString("Time"));
            break;

          case 4:
            mpProvenanceTable->setHeaderData(4, Qt::Horizontal, QString("Author"));
            break;
        }
    }

  ProvXMLFiles2ProvenanceTable();

  if (mpUndoStack != NULL)
    {
      CurrentSessionEdits2ProvenanceTable();
    }

  mpEntityProvenanceView->setModel(mpProvenanceTable);
  mpEntityProvenanceView->setSelectionBehavior(QAbstractItemView::SelectRows);
  mpEntityProvenanceView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  int i;

  for (i = mNRow ; i < mpProvenanceTable->rowCount(); i++)
    {
      mpEntityProvenanceView->setRowHidden(i, true);
    }
}

CEntityProvenanceDialog::~CEntityProvenanceDialog()
{}

void CEntityProvenanceDialog::ProvXMLFiles2ProvenanceTable()
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
          QHash<QString, QString > ENtityIDInformation;
          QHash<QString, QList<QString> > ActivityIDInformation;
          QMap<QString, QString> AgentIDAuthor;
          QHash<QString,  int> ActivityIDProvTableRow;

          while (stream.isGood())
            {
              stream.skipText();
              XMLToken next = stream.peek();

              // if we reached the end table element, we stop
              if (next.isEndFor(ProvenanceInformation))
                break;

              if (next.getName() == "entity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                  ENtityIDInformation.insert(EntityID, EntityName);
                }
              else if (next.getName() == "activity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                  QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                  QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));
                  QList<QString> ActivityInformation;
                  ActivityInformation.append(ActivityAction);
                  ActivityInformation.append(ActivityProperty);
                  ActivityInformation.append(ActivityNewValue);
                  ActivityIDInformation.insert(ActivityID, ActivityInformation);
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
                  QString ActivityID, EntityID, EntityName;
                  bool ActivityExists = false;
                  bool EntityExists = false;
                  QList<QString>  ActivityInformation;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (EntityExists))
                            {
// Checks with Entity display Name and adds to table
// It should be replaced with COPASI Object Name
                              if (EntityName == mEntityName)
                                {
                                  ActivityIDProvTableRow.insert(ActivityID, mNRow);
                                  AddOneLineToTable(ActivityInformation.at(0), ActivityInformation.at(1), ActivityInformation.at(2), "", "");
                                }
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (ActivityIDInformation.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  ActivityInformation = ActivityIDInformation.value(ActivityID);
                                }
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));

                              if (ENtityIDInformation.contains(EntityID))
                                {
                                  EntityExists = true;
                                  EntityName = ENtityIDInformation.value(EntityID);
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
                              QModelIndex index = mpProvenanceTable->index(TableRow, 4, QModelIndex());
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
                              QModelIndex index = mpProvenanceTable->index(TableRow, 3, QModelIndex());
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
              QHash<QString, QString > ENtityIDInformation;
              QHash<QString,  int> ActivityIDProvTableRow;
              QMap<QString, QString> AgentIDAuthor;
              QHash<QString, QList<QString> > ActivityIDInformation;

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
                      ENtityIDInformation.insert(EntityID, EntityName);
                    }
                  else if (next.getName() == "activity")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                      QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                      QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));
                      QList<QString> ActivityInformation;
                      ActivityInformation.append(ActivityAction);
                      ActivityInformation.append(ActivityProperty);
                      ActivityInformation.append(ActivityNewValue);
                      ActivityIDInformation.insert(ActivityID, ActivityInformation);
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
                      QString ActivityID, EntityID, EntityName;
                      bool ActivityExists = false;
                      bool EntityExists = false;
                      QList<QString>  ActivityInformation;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              if ((ActivityExists)  && (EntityExists))
                                {
                                  // Checks with Entity display Name and adds to table
                                  // It should be replaced with COPASI Object Name
                                  if (EntityName == mEntityName)
                                    {
                                      ActivityIDProvTableRow.insert(ActivityID, mNRow);
                                      AddOneLineToTable(ActivityInformation.at(0), ActivityInformation.at(1), ActivityInformation.at(2), "", "");
                                    }
                                }

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "activity")
                                {

                                  ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                                  if (ActivityIDInformation.contains(ActivityID))
                                    {
                                      ActivityExists = true;
                                      ActivityInformation = ActivityIDInformation.value(ActivityID);
                                    }
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));

                                  if (ENtityIDInformation.contains(EntityID))
                                    {
                                      EntityExists = true;
                                      EntityName = ENtityIDInformation.value(EntityID);
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
                                  QModelIndex index = mpProvenanceTable->index(TableRow, 4, QModelIndex());
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
                                  QModelIndex index = mpProvenanceTable->index(TableRow, 3, QModelIndex());
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
    }

// Provenance Current Model provenance to table
  //if (mProvenanceParentOfCurrentModel == mVersioningParentOfCurrentModel)
  //  {

  dataFile = mPathFile + "/ProvenanceMainBody.xml";

  QFile Fout2(dataFile);

  if (Fout2.exists())
    {

      XMLErrorLog log1;
      XMLInputStream stream(dataFile.toUtf8(), true, "", &log1);

      if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
        {
          XMLToken ProvenanceInformation = stream.next();
          QHash<QString, QString > ENtityIDInformation;
          QMap<QString, QString> AgentIDAuthor;
          QHash<QString, QList<QString> > ActivityIDInformation;
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
                  ENtityIDInformation.insert(EntityID, EntityName);
                }
              else if (next.getName() == "activity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                  QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                  QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));
                  QList<QString> ActivityInformation;
                  ActivityInformation.append(ActivityAction);
                  ActivityInformation.append(ActivityProperty);
                  ActivityInformation.append(ActivityNewValue);
                  ActivityIDInformation.insert(ActivityID, ActivityInformation);
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
                  QString ActivityID, EntityID, EntityName;
                  bool ActivityExists = false;
                  bool EntityExists = false;
                  QList<QString>  ActivityInformation;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          if ((ActivityExists)  && (EntityExists))
                            {
// Checks with Entity display Name and adds to table
// It should be replaced with COPASI Object Name
                              if (EntityName == mEntityName)
                                {
                                  ActivityIDProvTableRow.insert(ActivityID, mNRow);
                                  AddOneLineToTable(ActivityInformation.at(0), ActivityInformation.at(1), ActivityInformation.at(2), "", "");
                                }
                            }

                          break;
                        }

                      if (child.isStart())
                        {

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (ActivityIDInformation.contains(ActivityID))
                                {
                                  ActivityExists = true;
                                  ActivityInformation = ActivityIDInformation.value(ActivityID);
                                }
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));

                              if (ENtityIDInformation.contains(EntityID))
                                {
                                  EntityExists = true;
                                  EntityName = ENtityIDInformation.value(EntityID);
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
                              QModelIndex index = mpProvenanceTable->index(TableRow, 4, QModelIndex());
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
                              QModelIndex index = mpProvenanceTable->index(TableRow, 3, QModelIndex());
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

void CEntityProvenanceDialog::CurrentSessionEdits2ProvenanceTable()
{
  // set the table header data
  int row;

  // Retrieve Author's information from Configuration
  CConfigurationFile * configFile = CRootContainer::getConfiguration();
  CCopasiParameter * pParameter;
  QString Name, Action, Property, NewValue, Time, Author, GivenName, FamilyName;
  pParameter = configFile->getParameter("Given Name");
  GivenName = FROM_UTF8(pParameter->getValue< std::string >());
  pParameter = configFile->getParameter("Family Name");
  FamilyName = FROM_UTF8(pParameter->getValue< std::string >());

  if (pParameter != NULL)
    {

      Author = (GivenName + QString(" ") + FamilyName);
    }

  CUndoStack::const_iterator it = mpUndoStack->begin();
  CUndoStack::const_iterator end = mpUndoStack->end();

  for (; it != end; ++it)
    {
      Name = QString(FROM_UTF8((*it)->getObjectCN(true)));

      // This part should be replaced by COPASI Object Name
      // Currently Displayed Name is used to fill the Entity Dialog table
      if (Name == mEntityName)
        {
          switch ((*it)->getType())
            {
              case CUndoData::Type::CHANGE:
                Action = QString("Update");
                break;

              case CUndoData::Type::INSERT:
                Action = QString("Insert");
                break;

              case CUndoData::Type::REMOVE:
                Action = QString("Delete");
                break;
            }

          Property = QString(FROM_UTF8(cCommand->getProperty()));
          NewValue = QString(FROM_UTF8(cCommand->getNewValue()));
          Time = QString(FROM_UTF8(cCommand->getTime()));
          AddOneLineToTable(Action, Property, NewValue, Time, Author);
        }
    }
}

void CEntityProvenanceDialog::reallocateProvenanceTable(int Nrow)
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
            mpProvenanceTable->setHeaderData(0, Qt::Horizontal, QString("Action"));
            break;

          case 1:
            mpProvenanceTable->setHeaderData(1, Qt::Horizontal, QString("Property"));
            break;

          case 2:
            mpProvenanceTable->setHeaderData(2, Qt::Horizontal, QString("New Value"));
            break;

          case 3:
            mpProvenanceTable->setHeaderData(3, Qt::Horizontal, QString("Time"));
            break;

          case 4:
            mpProvenanceTable->setHeaderData(4, Qt::Horizontal, QString("Author"));
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

void  CEntityProvenanceDialog::AddOneLineToTable(QString Action, QString Property, QString NewValue, QString Time, QString Author)
{
  if (((mNRow + 1) % 100) == 0)
    {
      reallocateProvenanceTable((mNRow + 101));
    }

  for (int col = 0; col < mNCol; ++col)
    {
      QModelIndex index = mpProvenanceTable->index(mNRow, col, QModelIndex());

      switch (col)
        {
          case 0:
            mpProvenanceTable->setData(index, QVariant(Action));
            break;

          case 1:
            mpProvenanceTable->setData(index, QVariant(Property));
            break;

          case 2:
            mpProvenanceTable->setData(index, QVariant(NewValue));
            break;

          case 3:
            mpProvenanceTable->setData(index, QVariant(Time));
            break;

          case 4:
            mpProvenanceTable->setData(index, QVariant(Author));
            break;
        }
    }

  mpEntityProvenanceView->setRowHidden(mNRow, false);

  mNRow++;
}

void CEntityProvenanceDialog::load(QUndoStack * UndoStack, QString EntityNameQString, QString PathFile,  QList<QString> VersionsPathToCurrentModel)
{

  //mProvenanceParentOfCurrentModel = ProvenanceParentOfCurrentModel;
  //mVersioningParentOfCurrentModel = VersioningParentOfCurrentModel;
  mVersionsPathToCurrentModel = VersionsPathToCurrentModel;
  mPathFile = PathFile;
  mpUndoStack = UndoStack;
  mEntityName = EntityNameQString;
  mSelectedIndex = 0;
  //mpProvenanceTable = new QStandardItemModel(100, mNCol, parent);
  mNRow = 0;

  ProvXMLFiles2ProvenanceTable();

  if (mpUndoStack != NULL)
    {
      CurrentSessionEdits2ProvenanceTable();
    }

  int i;

  for (i = mNRow ; i < mpProvenanceTable->rowCount(); i++)
    {
      mpEntityProvenanceView->setRowHidden(i, true);
    }
}
