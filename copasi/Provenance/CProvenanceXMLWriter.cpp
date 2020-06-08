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

#include "CProvenanceXMLWriter.h"

#include <QUndoStack>
#include <QFile>
#include <QItemDelegate>
#include <QDir>
#include <QSet>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLErrorLog.h>
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"
#include <copasi/UI/qtUtilities.h>
#include "copasi/undo/CUndoStack.h"

CProvenanceXMLWriter::CProvenanceXMLWriter(QWidget* parent, CUndoStack *undoStack, QString PathFile, QString ProvenanceOrigionFiletype, QString ProvenanceOrigionTime, QList<QString> VersionsPathToCurrentModel):
  mProvenanceTotalEntityNumber(0)
  , mProvenanceTotalActionNumber(0)
  , mProvenanceTotalAgentNumber(0)
  , mProvenanceOrigionFileType(ProvenanceOrigionFiletype)
  , mProvenanceOrigionTime(ProvenanceOrigionTime)
  , mProvenanceAuthorNameMap()
  //, mProvenanceParentOfCurrentModel(ProvenanceParentOfCurrentModel)
  //, mVersioningParentOfCurrentModel(VersioningParentOfCurrentModel)
  , mpUndoStack(undoStack)
  , mVersionsPathToCurrentModel(VersionsPathToCurrentModel)
{
  mPathFile = PathFile;
}

CProvenanceXMLWriter::~CProvenanceXMLWriter()
{
}

QHash<QString, QString> CProvenanceXMLWriter::reconstructProvenanceEntityNameMap()
{
  mProvenanceTotalEntityNumber = 0;
  mProvenanceTotalActionNumber = 0;
  mProvenanceTotalAgentNumber = 0;
  mProvenanceAuthorNameMap.clear();
  QHash<QString, QString> ProvenanceEntityNameMap;
  XMLErrorLog log;
  QMap<QString, QString> UpdatingNamesActivityNameMap;

// First complete the maps for versioning
  int VersionCounter;

  for (VersionCounter = 0; VersionCounter < mVersionsPathToCurrentModel.size(); ++VersionCounter)
    {
      QString dataFile = mPathFile + "/" + mVersionsPathToCurrentModel.at(VersionCounter) + "/" + mVersionsPathToCurrentModel.at(VersionCounter) + "Provenance.xml";
      QFile Fout(dataFile);

      if (Fout.exists())
        {
          XMLInputStream stream(dataFile.toUtf8(), true, "", &log);

          if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
            {
              XMLToken ProvenanceInformation = stream.next();

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

                      // if new entity ID add to MAP
                      if (!ProvenanceEntityNameMap.contains(EntityID))
                        {
                          QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                          ProvenanceEntityNameMap.insert(EntityID, EntityName);
                          mProvenanceTotalEntityNumber++;
                        }
                    }

                  else if (next.getName() == "activity")
                    {
                      XMLToken xmlEntity = stream.next();
                      QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                      QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                      QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                      if ((ActivityAction == "Update") && (ActivityProperty == "Name"))
                        {
                          UpdatingNamesActivityNameMap.insert(ActivityID, ActivityNewValue);
                        }

                      mProvenanceTotalActionNumber++;
                    }
                  else if (next.getName() == "agent")
                    {
                      XMLToken xmlEntity = stream.next();
                      //If it is a new Agent add to map
                      QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id

                      if (!mProvenanceAuthorNameMap.contains(AgentID))
                        {
                          QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                          QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
                          mProvenanceAuthorNameMap.insert(AgentID, (AgentName + AgentFamilyName));
                          mProvenanceTotalAgentNumber++;
                        }
                    }
                  else if (next.getName() == "used")
                    {
                      XMLToken xmlEntity = stream.next();
                      bool ChangedName = false;
                      QString ActivityID, EntityID;

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              break;
                            }

                          if (child.getName() == "activity")
                            {

                              ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                              if (UpdatingNamesActivityNameMap.contains(ActivityID))
                                {
                                  ChangedName = true;
                                }
                            }

                          if (child.getName() == "entity")
                            {
                              EntityID = QString::fromStdString(child.getAttrValue(0));
                            }
                        }

                      if (ChangedName)
                        {
                          ProvenanceEntityNameMap[EntityID] =  UpdatingNamesActivityNameMap.value(ActivityID);
                        }
                    }
                  else
                    {
                      XMLToken xmlEntity = stream.next();

                      while (stream.isGood())
                        {
                          XMLToken child  = stream.next();

                          if (child.isEndFor(xmlEntity))
                            {
                              break;
                            }
                        }
                    }
                }
            }
        }
    }

// Then add map of Main body provenance
  QString dataFile = mPathFile + "/ProvenanceMainBody.xml";

  QFile Fout(dataFile);

  // If the main body provenance does not exist, rename current session provenance as main body provenance
  if (Fout.exists())
    {
      XMLInputStream stream(dataFile.toUtf8(), true, "", &log);

      if ((stream.peek().isStart()) && (stream.peek().getName() == "document"))
        {
          XMLToken ProvenanceInformation = stream.next();

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

                  // if new entity ID add to MAP
                  if (!ProvenanceEntityNameMap.contains(EntityID))
                    {

                      QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                      ProvenanceEntityNameMap.insert(EntityID, EntityName);
                      mProvenanceTotalEntityNumber++;
                    }
                }

              else if (next.getName() == "activity")
                {
                  XMLToken xmlEntity = stream.next();
                  QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                  QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                  QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                  QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                  if ((ActivityAction == "Update") && (ActivityProperty == "Name"))
                    {
                      UpdatingNamesActivityNameMap.insert(ActivityID, ActivityNewValue);
                    }

                  mProvenanceTotalActionNumber++;
                }
              else if (next.getName() == "agent")
                {
                  XMLToken xmlEntity = stream.next();
                  QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id

                  //If it is a new Agent add to map
                  if (!mProvenanceAuthorNameMap.contains(AgentID))
                    {

                      QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                      QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
                      mProvenanceAuthorNameMap.insert(AgentID, (AgentName + AgentFamilyName));
                      mProvenanceTotalAgentNumber++;
                    }
                }
              else if (next.getName() == "used")
                {
                  XMLToken xmlEntity = stream.next();
                  bool ChangedName = false;
                  QString ActivityID, EntityID;

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      // if we reached the end element of the 'Version' element : add this data as a new version
                      if (child.isEndFor(xmlEntity))
                        {
                          //add here
                          break;
                        }

                      if (child.getName() == "activity")
                        {

                          ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID

                          if (UpdatingNamesActivityNameMap.contains(ActivityID))
                            {
                              ChangedName = true;
                            }
                        }

                      if (child.getName() == "entity")
                        {
                          EntityID = QString::fromStdString(child.getAttrValue(0));
                        }
                    }

                  if (ChangedName)
                    {
                      ProvenanceEntityNameMap[EntityID] =  UpdatingNamesActivityNameMap.value(ActivityID);
                    }
                }
              else
                {
                  XMLToken xmlEntity = stream.next();

                  while (stream.isGood())
                    {
                      XMLToken child  = stream.next();

                      if (child.isEndFor(xmlEntity))
                        {
                          break;
                        }
                    }
                }
            }
        }
    }

  return (ProvenanceEntityNameMap);
}

void CProvenanceXMLWriter::updateCurrentSessionProvenance()
{

// If the parent of current model was changes, remove the main body of Provenance
// The file management will be done by COMBINE Archive
  /*
    if (mProvenanceParentOfCurrentModel != mVersioningParentOfCurrentModel)
      {
        mProvenanceParentOfCurrentModel = mVersioningParentOfCurrentModel;
        QString dataFile = mPathFile + "/ProvenanceMainBody.xml";
        QFile Fout(dataFile);
        Fout.remove();
      }
  */
// Update Current Session Provenance
  QHash<QString, QString> ProvenanceEntityNameMap = reconstructProvenanceEntityNameMap();
  QString dataFile = mPathFile + "/ProvenanceCurrentSession.xml";
  XMLOutputStream_t * stream = XMLOutputStream_createFile(dataFile.toUtf8(), "UTF-8", 1);
  CCopasiParameter * pParameter;
  QString AuthorID;

  if (stream != NULL)
    {
      int i, j;
      XMLOutputStream_startElement(stream, "prov:document");
      XMLOutputStream_writeAttributeChars(stream, "xmlns:prov",  "http://www.w3.org/ns/prov#");
      XMLOutputStream_writeAttributeChars(stream, "xmlns:xsi",  "http://www.w3.org/2001/XMLSchema-instance");
      XMLOutputStream_writeAttributeChars(stream, "xmlns:xsd",  "http://www.w3.org/2001/XMLSchema");

      CConfigurationFile * configFile = CRootContainer::getConfiguration();
      QString Action;
      int EditNumber = mpUndoStack->size();
      //QString EntityInfo[ EditNumber + 1][5];  // Information of each Entity in the model
      //QString EntityNameMap[ EditNumber + 1][2]; //Map name to Entity ID
      //QString ENtityActionMap[ EditNumber + 1][4];
      QString **EntityInfo = new QString * [EditNumber + 1];

      // 0: Id, 1: Model, 2: Type, 3: Name (CN?), 4: Time
      for (i = 0; i < EditNumber + 1; i++)
        {
          EntityInfo[i] = new QString [5];
        }

      // 0: Id, 1: Name (CN?)
      QString **EntityNameMap = new QString * [EditNumber + 1];

      for (i = 0; i < EditNumber + 1; i++)
        {
          EntityNameMap[i] = new QString [2];
        }

      QString **ENtityActionMap = new QString * [EditNumber + 1];

      for (i = 0; i < EditNumber + 1; i++)
        {
          ENtityActionMap[i] = new QString [4];
        }

      int EntityCount = 0;
      int EntityIndexCount = 0;
      int EntityNamesCount = 0;
      int UndoTableSize = 0;

      for (i = 0 ; i <  EditNumber; i ++)
        {
          const QUndoCommand *cmd = mpUndoStack->command(i);
          const CCopasiUndoCommand *cCommand = dynamic_cast<const CCopasiUndoCommand*>(cmd);
          Action = QString(FROM_UTF8(cCommand->getAction()));

          if ((Action == "Add to list") || (Action == "Delete set") || (Action == "Change"))
            {
              UndoTableSize++;

              if (Action == "Add to list") // Add Entity to Entity information and ID name mapping
                {
                  EntityInfo[EntityCount][0] = QString("Entity_") + QString::number(EntityIndexCount + 1 + mProvenanceTotalEntityNumber);
                  EntityInfo[EntityCount][1] = QString("Model");
                  EntityInfo[EntityCount][2] = QString(FROM_UTF8(cCommand->getEntityType()));
                  EntityInfo[EntityCount][3] = QString(FROM_UTF8(cCommand->getName()));
                  EntityInfo[EntityCount][4] = QString(FROM_UTF8(cCommand->getTime()));
                  EntityCount++;
                  EntityIndexCount++;
                  EntityNameMap[EntityNamesCount][0] = EntityInfo[EntityCount - 1][3];
                  EntityNameMap[EntityNamesCount][1] = EntityInfo[EntityCount - 1][0];
                  EntityNamesCount++;
                  ENtityActionMap[i][0] = EntityInfo[EntityCount - 1][0];
                }
              else  // if the name is not in the list - Add to list
                {
                  bool Flag = true;

                  for (j = 0; j < EntityNamesCount; j ++)
                    {
                      if (EntityNameMap[j][0] == QString(FROM_UTF8(cCommand->getName())))
                        {
                          Flag = false;
                          ENtityActionMap[i][0] = EntityNameMap[j][1];
                          break;
                        }
                    }

                  if (Flag)
                    {
                      // First check the Entity has been reported in previous Version or MainBody provenance file
                      QHashIterator<QString, QString> EntityMapIterator(ProvenanceEntityNameMap);
                      bool EntityHasWrittenBefore = false;

                      while (EntityMapIterator.hasNext())
                        {
                          EntityMapIterator.next();

                          if (EntityMapIterator.value() == QString::fromUtf8(cCommand->getName().c_str()))
                            {
                              EntityHasWrittenBefore = true;
                              EntityInfo[EntityCount][0] = EntityMapIterator.key();
                            }
                        }

                      // If reported bofore:
                      if (EntityHasWrittenBefore)
                        {
                          EntityInfo[EntityCount][1] = QString("Model");
                          EntityInfo[EntityCount][2] = QString(FROM_UTF8(cCommand->getEntityType()));
                          EntityInfo[EntityCount][3] = QString(FROM_UTF8(cCommand->getName()));
                          EntityInfo[EntityCount][4] = QString("Unknown");
                          EntityCount++;
                          EntityNameMap[EntityNamesCount][0] = EntityInfo[EntityCount - 1][3];
                          EntityNameMap[EntityNamesCount][1] = EntityInfo[EntityCount - 1][0];
                          EntityNamesCount++;
                          ENtityActionMap[i][0] = EntityInfo[EntityCount - 1][0];
                        }
                      // If not reported before:
                      else
                        {
                          EntityInfo[EntityCount][0] = QString("Entity_") + QString::number(EntityIndexCount + 1 + mProvenanceTotalEntityNumber);
                          EntityInfo[EntityCount][1] = QString("Model");
                          EntityInfo[EntityCount][2] = QString(FROM_UTF8(cCommand->getEntityType()));
                          EntityInfo[EntityCount][3] = QString(FROM_UTF8(cCommand->getName()));
                          EntityInfo[EntityCount][4] = QString("Unknown");
                          EntityCount++;
                          EntityIndexCount++;
                          EntityNameMap[EntityNamesCount][0] = EntityInfo[EntityCount - 1][3];
                          EntityNameMap[EntityNamesCount][1] = EntityInfo[EntityCount - 1][0];
                          EntityNamesCount++;
                          ENtityActionMap[i][0] = EntityInfo[EntityCount - 1][0];
                        }
                    }
                }

              if ((Action == "Change") && (cCommand->getProperty() == "Name")) // In Entity name change occasion add to ID name mapping
                {
                  for (j = 0; j < EntityNamesCount; j ++)
                    {
                      if (EntityNameMap[j][0] == QString(FROM_UTF8(cCommand->getName())))
                        break;
                    }

                  EntityNameMap[EntityNamesCount][0] = QString(FROM_UTF8(cCommand->getNewValue()));
                  EntityNameMap[EntityNamesCount][1] = EntityNameMap[j][1];
                  EntityNamesCount++;
                }
            }
          else
            {
              break;
            }
        }

      for (i = 0; i < EntityCount; i++)
        {
          XMLOutputStream_startElement(stream, "prov:entity");
          XMLOutputStream_writeAttributeChars(stream, "prov:id",  EntityInfo[i][0].toUtf8());
          XMLOutputStream_writeAttributeChars(stream, "Main_Type",  EntityInfo[i][1].toUtf8());
          XMLOutputStream_writeAttributeChars(stream, "Entity_Type",  EntityInfo[i][2].toUtf8());
          XMLOutputStream_writeAttributeChars(stream, "Initial_name",  EntityInfo[i][3].toUtf8());
          XMLOutputStream_endElement(stream, "prov:entity");
        }

      for (i = 0 ; i <  UndoTableSize; i ++)
        {
          const QUndoCommand *cmd = mpUndoStack->command(i);
          const CCopasiUndoCommand *cCommand = dynamic_cast<const CCopasiUndoCommand*>(cmd);
          Action = QString(FROM_UTF8(cCommand->getAction()));

          if (Action == "Add to list")
            {
              Action = QString("Insertion");
              ENtityActionMap[i][2] = QString("prov:wasGeneratedBy");
            }
          else if (Action == "Delete set")
            {
              Action = QString("Deletion");
              ENtityActionMap[i][2] = QString("prov:used");
            }
          else if (Action == "Change") //&&((cCommand->getProperty() != "Name")))
            {
              Action = QString("Update");
              ENtityActionMap[i][2] = QString("prov:used");
            }
          else
            {
              break;
            }

          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:id", (QString("Activity_") + QString::number(i + 1 + mProvenanceTotalActionNumber)).toUtf8());
          XMLOutputStream_writeAttributeChars(stream, "Action",  Action.toUtf8());
          // Loop through all changed properties
          // Properties which describe contained entities need to be handled recursively
          // We also need to look at pre and post process data.
          XMLOutputStream_writeAttributeChars(stream, "Property",  cCommand->getProperty().c_str());
          XMLOutputStream_writeAttributeChars(stream, "New_value",  cCommand->getNewValue().c_str());
          XMLOutputStream_endElement(stream, "prov:activity");
          ENtityActionMap[i][1] = QString("Activity_") + QString::number(i + 1 + mProvenanceTotalActionNumber);
          ENtityActionMap[i][3] = QString(FROM_UTF8(cCommand->getTime()));
        }

      for (i = 0 ; i < UndoTableSize; i ++)
        {
          if (ENtityActionMap[i][2] == QString("prov:used"))
            {
              XMLOutputStream_startElement(stream, "prov:used");
              XMLOutputStream_startElement(stream, "prov:activity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][1].toUtf8());
              XMLOutputStream_endElement(stream, "prov:activity");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][0].toUtf8());
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_endElement(stream, "prov:used");
            }
          else if (ENtityActionMap[i][2] == QString("prov:wasGeneratedBy"))
            {
              XMLOutputStream_startElement(stream, "prov:wasGeneratedBy");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][0].toUtf8());
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_startElement(stream, "prov:activity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][1].toUtf8());
              XMLOutputStream_endElement(stream, "prov:activity");
              XMLOutputStream_endElement(stream, "prov:wasGeneratedBy");
            }
        }

      //Prov Agent
      //First check whether the agent of current session has been reported before
      QMapIterator<QString, QString> ProvenanceAuthorMapIterator(mProvenanceAuthorNameMap);
      bool AuthorHasWrittenBefore = false;

      while (ProvenanceAuthorMapIterator.hasNext())
        {
          ProvenanceAuthorMapIterator.next();

          if (ProvenanceAuthorMapIterator.value() == (QString::fromUtf8(configFile->getParameter("Given Name")->getValue< std::string >().c_str()) + QString::fromUtf8(configFile->getParameter("Family Name")->getValue< std::string >().c_str())))
            {
              AuthorHasWrittenBefore  = true;
              AuthorID = ProvenanceAuthorMapIterator.key();
            }
        }

      // If reported before:

      //If it is a new agent:
      if (!AuthorHasWrittenBefore)
        {
          AuthorID = QString("Agent_") + QString::number(mProvenanceTotalAgentNumber + 1);
        }

      XMLOutputStream_startElement(stream, "prov:agent");

      /*
       * We should consider using the standard below for
       * <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
       *    xmlns:vcard="http://www.w3.org/2006/vcard/ns#">
       *   <vcard:Individual rdf:about="#agentId">
       *     <vcard:hasName rdf:parseType="Resource">
       *       <vcard:given-name>%GivenName%</vcard:given-name>
       *       <vcard:family-name>%FamilyName%</vcard:family-name>
       *     </vcard:hasName>
       *     <vcard:hasEmail rdf:resource="mailto:corky@example.com%email%"/>
       *     <vcard:hasOrganizationName rdf:parseType="Resource">
       *       <vcard:organization-name>%ORG%</vcard:organization-name>
       *     </vcard:hasNamehasOrganizationName>
       *   </vcard:Individual>
       * </rdf:RDF>
       */

      XMLOutputStream_writeAttributeChars(stream, "prov:id",  AuthorID.toUtf8());
      pParameter = configFile->getParameter("Given Name");
      XMLOutputStream_writeAttributeChars(stream, "GivenName",  pParameter->getValue< std::string >().c_str());
      pParameter = configFile->getParameter("Family Name");
      XMLOutputStream_writeAttributeChars(stream, "FamilyName",  pParameter->getValue< std::string >().c_str());
      pParameter = configFile->getParameter("Organization");
      XMLOutputStream_writeAttributeChars(stream, "Organization",  pParameter->getValue< std::string >().c_str());
      pParameter = configFile->getParameter("Email");
      XMLOutputStream_writeAttributeChars(stream, "Email",  pParameter->getValue< std::string >().c_str());
      XMLOutputStream_endElement(stream, "prov:agent");

      for (i = 0 ; i < EntityCount; i++)
        {
          XMLOutputStream_startElement(stream, "prov:wasAttributedTo");
          XMLOutputStream_startElement(stream, "prov:entity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  EntityInfo[i][0].toUtf8());
          XMLOutputStream_endElement(stream, "prov:entity");
          XMLOutputStream_startElement(stream, "prov:agent");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  AuthorID.toUtf8());
          XMLOutputStream_endElement(stream, "prov:agent");
          XMLOutputStream_endElement(stream, "prov:wasAttributedTo");
        }

      for (i = 0 ; i <   UndoTableSize; i ++)
        {
          XMLOutputStream_startElement(stream, "prov:wasAssociatedWith");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][1].toUtf8());
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:agent");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  AuthorID.toUtf8());
          XMLOutputStream_endElement(stream, "prov:agent");
          XMLOutputStream_endElement(stream, "prov:wasAssociatedWith");
        }

      for (i = 0 ; i < EntityCount; i++)
        {
          if (EntityInfo[i][4] != "Unknown")
            {
              XMLOutputStream_startElement(stream, "prov:wasGeneratedBy");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  EntityInfo[i][0].toUtf8());
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_startElement(stream, "prov:time");
              XMLOutputStream_writeChars(stream, EntityInfo[i][4].toUtf8());
              XMLOutputStream_endElement(stream, "prov:time");
              XMLOutputStream_endElement(stream, "prov:wasGeneratedBy");
            }
        }

      for (i = 0 ; i <  UndoTableSize; i ++)
        {
          XMLOutputStream_startElement(stream, "prov:wasStartedBy");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][1].toUtf8());
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:time");
          XMLOutputStream_writeChars(stream, ENtityActionMap[i][3].toUtf8());
          XMLOutputStream_endElement(stream, "prov:time");
          XMLOutputStream_endElement(stream, "prov:wasStartedBy");
          XMLOutputStream_startElement(stream, "prov:wasEndedBy");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  ENtityActionMap[i][1].toUtf8());
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:time");
          XMLOutputStream_writeChars(stream, ENtityActionMap[i][3].toUtf8());
          XMLOutputStream_endElement(stream, "prov:time");
          XMLOutputStream_endElement(stream, "prov:wasEndedBy");
        }

      XMLOutputStream_endElement(stream, "prov:document");
      XMLOutputStream_free(stream);
    }
}

void CProvenanceXMLWriter::updateOrigionOfProvenance(QString OrigionalFile)
{
  QString dataFile = mPathFile + "/ProvenanceOrigion.xml";
  QFile Fout(dataFile);

  // If the Origion of provenance does not exist, Save the origional file description in a prov xml file
  if (!Fout.exists())
    {
      XMLOutputStream_t * stream = XMLOutputStream_createFile(dataFile.toUtf8(), "UTF-8", 1);
      CCopasiParameter * pParameter;
      CConfigurationFile * configFile = CRootContainer::getConfiguration();

      if (stream != NULL)
        {
          XMLOutputStream_startElement(stream, "prov:document");
          XMLOutputStream_writeAttributeChars(stream, "xmlns:prov",  "http://www.w3.org/ns/prov#");
          XMLOutputStream_writeAttributeChars(stream, "xmlns:xsi",  "http://www.w3.org/2001/XMLSchema-instance");
          XMLOutputStream_writeAttributeChars(stream, "xmlns:xsd",  "http://www.w3.org/2001/XMLSchema");
          XMLOutputStream_startElement(stream, "prov:entity");
          XMLOutputStream_writeAttributeChars(stream, "prov:id",  "Entity_0");
          XMLOutputStream_writeAttributeChars(stream, "Main_Type",  "Document");
          XMLOutputStream_writeAttributeChars(stream, "Entity_Type",  "Document");
          XMLOutputStream_writeAttributeChars(stream, "Initial_name",  OrigionalFile.toUtf8());
          XMLOutputStream_endElement(stream, "prov:entity");

          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:id",  "Activity_0");
          XMLOutputStream_writeAttributeChars(stream, "Action",  mProvenanceOrigionFileType.toUtf8());
          XMLOutputStream_endElement(stream, "prov:activity");

          if (mProvenanceOrigionFileType == "Create")
            {
              XMLOutputStream_startElement(stream, "prov:wasGeneratedBy");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Entity_0");
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_startElement(stream, "prov:activity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Activity_0");
              XMLOutputStream_endElement(stream, "prov:activity");
              XMLOutputStream_endElement(stream, "prov:wasGeneratedBy");
            }
          else
            {
              XMLOutputStream_startElement(stream, "prov:used");
              XMLOutputStream_startElement(stream, "prov:activity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Activity_0");
              XMLOutputStream_endElement(stream, "prov:activity");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Entity_0");
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_endElement(stream, "prov:used");
            }

          XMLOutputStream_startElement(stream, "prov:agent");
          XMLOutputStream_writeAttributeChars(stream, "prov:id",  "Agent_1");
          pParameter = configFile->getParameter("Given Name");
          XMLOutputStream_writeAttributeChars(stream, "GivenName",  pParameter->getValue< std::string >().c_str());
          pParameter = configFile->getParameter("Family Name");
          XMLOutputStream_writeAttributeChars(stream, "FamilyName",  pParameter->getValue< std::string >().c_str());
          pParameter = configFile->getParameter("Organization");
          XMLOutputStream_writeAttributeChars(stream, "Organization",  pParameter->getValue< std::string >().c_str());
          pParameter = configFile->getParameter("Email");
          XMLOutputStream_writeAttributeChars(stream, "Email",  pParameter->getValue< std::string >().c_str());
          XMLOutputStream_endElement(stream, "prov:agent");

          XMLOutputStream_startElement(stream, "prov:wasAttributedTo");
          XMLOutputStream_startElement(stream, "prov:entity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Entity_0");
          XMLOutputStream_endElement(stream, "prov:entity");
          XMLOutputStream_startElement(stream, "prov:agent");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Agent_1");
          XMLOutputStream_endElement(stream, "prov:agent");
          XMLOutputStream_endElement(stream, "prov:wasAttributedTo");

          XMLOutputStream_startElement(stream, "prov:wasAssociatedWith");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Activity_0");
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:agent");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Agent_1");
          XMLOutputStream_endElement(stream, "prov:agent");
          XMLOutputStream_endElement(stream, "prov:wasAssociatedWith");

          if (mProvenanceOrigionFileType == "Create")
            {
              XMLOutputStream_startElement(stream, "prov:wasGeneratedBy");
              XMLOutputStream_startElement(stream, "prov:entity");
              XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Entity_0");
              XMLOutputStream_endElement(stream, "prov:entity");
              XMLOutputStream_startElement(stream, "prov:time");
              XMLOutputStream_writeChars(stream, mProvenanceOrigionTime.toUtf8());
              XMLOutputStream_endElement(stream, "prov:time");
              XMLOutputStream_endElement(stream, "prov:wasGeneratedBy");
            }

          XMLOutputStream_startElement(stream, "prov:wasStartedBy");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Activity_0");
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:time");
          XMLOutputStream_writeChars(stream, mProvenanceOrigionTime.toUtf8());
          XMLOutputStream_endElement(stream, "prov:time");
          XMLOutputStream_endElement(stream, "prov:wasStartedBy");
          XMLOutputStream_startElement(stream, "prov:wasEndedBy");
          XMLOutputStream_startElement(stream, "prov:activity");
          XMLOutputStream_writeAttributeChars(stream, "prov:ref",  "Activity_0");
          XMLOutputStream_endElement(stream, "prov:activity");
          XMLOutputStream_startElement(stream, "prov:time");//CRootContainer::getConfiguration()->getWorkingDirectory())
          XMLOutputStream_writeChars(stream, mProvenanceOrigionTime.toUtf8());
          XMLOutputStream_endElement(stream, "prov:time");
          XMLOutputStream_endElement(stream, "prov:wasEndedBy");

          XMLOutputStream_endElement(stream, "prov:document");
          XMLOutputStream_free(stream);
        }
    }
}

void CProvenanceXMLWriter::mergeProvenanceFiles(QString SourceFile1, QString SourceFile2, QString TargetFile)
{
  QString dataFile, dataFile2, dataFile3;
  dataFile = mPathFile + "/" + SourceFile1;
  QFile Fout(dataFile);
  dataFile2 = mPathFile + "/" + SourceFile2;
  QFile Fout2(dataFile2);
  dataFile3 = mPathFile + "/" + TargetFile;

  // If only one provenance file exists
  if ((!Fout.exists()) && (Fout2.exists()))
    {
      Fout2.copy(dataFile3);
    }
  else if ((Fout.exists()) && (!Fout2.exists()))
    {
      Fout.copy(dataFile3);
    }
  // If no provenance file exists
  else if ((!Fout.exists()) && (!Fout2.exists()))
    {
      //both files do not exist
    }
  //Otherwise merge two provenance files
  else
    {

      XMLErrorLog log1, log2;
      XMLInputStream in1(dataFile.toUtf8(), true, "", &log1);
      XMLInputStream in2(dataFile2.toUtf8(), true, "", &log2);

      if ((in1.peek().isStart()) &&
          (in1.peek().getName() == "document") &&
          (in2.peek().isStart()) &&
          (in2.peek().getName() == "document"))
        {
          XMLToken ProvenanceInformation = in1.next();
          XMLToken ProvenanceInformation2 = in2.next();
          XMLOutputStream_t * out = XMLOutputStream_createFile(dataFile3.toUtf8(), "UTF-8", 1);
          QSet<QString> ProvenanceEntityList;
          QSet<QString> ProvenanceAuthorList;

          if (out != NULL)
            {
              XMLOutputStream_startElement(out, "prov:document");
              XMLOutputStream_writeAttributeChars(out, "xmlns:prov",  "http://www.w3.org/ns/prov#");
              XMLOutputStream_writeAttributeChars(out, "xmlns:xsi",  "http://www.w3.org/2001/XMLSchema-instance");
              XMLOutputStream_writeAttributeChars(out, "xmlns:xsd",  "http://www.w3.org/2001/XMLSchema");

              while (in1.isGood())//&&(!FirstXMLFinished)&&(!StateChanged))
                {
                  in1.skipText();
                  //grab the next element
                  XMLToken next = in1.peek();

                  // if we reached the end table element, we stop
                  if (next.isEndFor(ProvenanceInformation))
                    {
                      //FirstXMLFinished = true;
                      break;
                    }

                  if (next.getName() == "entity")
                    {
                      XMLToken xmlEntity = in1.next();
                      QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                      QString MainType = QString::fromStdString(xmlEntity.getAttrValue("Main_Type"));
                      QString EntityType = QString::fromStdString(xmlEntity.getAttrValue("Entity_Type"));

                      ProvenanceEntityList << EntityID;

                      XMLOutputStream_startElement(out, "prov:entity");
                      XMLOutputStream_writeAttributeChars(out, "prov:id",  EntityID.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Main_Type",  MainType.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Entity_Type",  EntityType.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Initial_name",  EntityName.toUtf8());
                      XMLOutputStream_endElement(out, "prov:entity");
                    }
                  else if (next.getName() == "activity")
                    {
                      XMLToken xmlEntity = in1.next();
                      QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                      QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                      QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                      XMLOutputStream_startElement(out, "prov:activity");
                      XMLOutputStream_writeAttributeChars(out, "prov:id",  ActivityID.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Action",  ActivityAction.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Property",  ActivityProperty.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "New_value",  ActivityNewValue.toUtf8());
                      XMLOutputStream_endElement(out, "prov:activity");
                    }
                  else if (next.getName() == "agent")
                    {
                      //  state="agent";
                      XMLToken xmlEntity = in1.next();
                      QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                      QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
                      QString AgentOrganization = QString::fromStdString(xmlEntity.getAttrValue("Organization"));
                      QString AgentEmail = QString::fromStdString(xmlEntity.getAttrValue("Email"));
                      ProvenanceAuthorList.insert(AgentID);
                      XMLOutputStream_startElement(out, "prov:agent");
                      XMLOutputStream_writeAttributeChars(out, "prov:id",  AgentID.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "GivenName",  AgentName.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "FamilyName",  AgentFamilyName.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Organization",  AgentOrganization.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Email",  AgentEmail.toUtf8());
                      XMLOutputStream_endElement(out, "prov:agent");
                    }

                  else if (next.getName() == "used")
                    {

                      XMLToken xmlEntity = in1.next();
                      QString ActivityID, EntityID;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:used");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");
                              XMLOutputStream_endElement(out, "prov:used");
                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "activity")
                                {

                                  ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attribute is reference to activity ID
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }

                  else if (next.getName() == "wasAttributedTo")
                    {
                      XMLToken xmlEntity = in1.next();
                      QString AgentID, EntityID;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasAttributedTo");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");
                              XMLOutputStream_startElement(out, "prov:agent");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  AgentID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:agent");
                              XMLOutputStream_endElement(out, "prov:wasAttributedTo");

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
                      XMLToken xmlEntity = in1.next();
                      QString AgentID, ActivityID;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasAssociatedWith");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:agent");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  AgentID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:agent");
                              XMLOutputStream_endElement(out, "prov:wasAssociatedWith");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "agent")
                                {

                                  AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasGeneratedBy")
                    {
                      XMLToken xmlEntity = in1.next();

                      QString ActivityID, EntityID, Time;
                      bool timeExists = false;
                      bool activityExists = false;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasGeneratedBy");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");

                              if (activityExists)
                                {
                                  XMLOutputStream_startElement(out, "prov:activity");
                                  XMLOutputStream_writeChars(out, ActivityID.toUtf8());
                                  XMLOutputStream_endElement(out, "prov:activity");
                                }

                              if (timeExists)
                                {
                                  XMLOutputStream_startElement(out, "prov:time");
                                  XMLOutputStream_writeChars(out, Time.toUtf8());
                                  XMLOutputStream_endElement(out, "prov:time");
                                }

                              XMLOutputStream_endElement(out, "prov:wasGeneratedBy");

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

                                  Time = QString::fromStdString(in1.next().getCharacters());
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
                      XMLToken xmlEntity = in1.next();
                      QString ActivityID, Time;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasStartedBy");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",   ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:time");
                              XMLOutputStream_writeChars(out, Time.toUtf8());
                              XMLOutputStream_endElement(out, "prov:time");
                              XMLOutputStream_endElement(out, "prov:wasStartedBy");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(in1.next().getCharacters());
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasEndedBy")
                    {

                      XMLToken xmlEntity = in1.next();
                      QString ActivityID, Time;

                      while (in1.isGood())
                        {
                          XMLToken child  = in1.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(stream3, "prov:wasEndedBy");
                              XMLOutputStream_startElement(stream3, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",   ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(stream3, "prov:time");
                              XMLOutputStream_writeChars(stream3, Time.toUtf8());
                              XMLOutputStream_endElement(out, "prov:time");
                              XMLOutputStream_endElement(stream3, "prov:wasEndedBy");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(in1.next().getCharacters());
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

//    Analyzing the second Stream
              while (in2.isGood())//&&(!SecondXMLFinished)&&(!StateChanged))
                {
                  stream2.skipText();
                  //grab the next element
                  XMLToken next = stream2.peek();

                  // if we reached the end table element, we stop
                  if (next.isEndFor(ProvenanceInformation2))
                    {
                      // SecondXMLFinished = true;
                      break;
                    }

                  if (next.getName() == "entity")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString EntityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString EntityName = QString::fromStdString(xmlEntity.getAttrValue("Initial_name"));
                      QString MianType = QString::fromStdString(xmlEntity.getAttrValue("Main_Type"));
                      QString EntityType = QString::fromStdString(xmlEntity.getAttrValue("Entity_Type"));

                      //ProvenanceEntityList<<EntityID;
                      if (!ProvenanceEntityList.contains(EntityID))
                        {
                          XMLOutputStream_startElement(out, "prov:entity");
                          XMLOutputStream_writeAttributeChars(out, "prov:id",  EntityID.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "Main_Type",  MianType.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "Entity_Type",  EntityType.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "Initial_name",  EntityName.toUtf8());
                          XMLOutputStream_endElement(out, "prov:entity");
                        }
                    }
                  else if (next.getName() == "activity")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString ActivityID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString ActivityAction = QString::fromStdString(xmlEntity.getAttrValue("Action"));
                      QString ActivityProperty = QString::fromStdString(xmlEntity.getAttrValue("Property"));
                      QString ActivityNewValue = QString::fromStdString(xmlEntity.getAttrValue("New_value"));

                      XMLOutputStream_startElement(out, "prov:activity");
                      XMLOutputStream_writeAttributeChars(out, "prov:id",  ActivityID.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Action",  ActivityAction.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "Property",  ActivityProperty.toUtf8());
                      XMLOutputStream_writeAttributeChars(out, "New_value",  ActivityNewValue.toUtf8());
                      XMLOutputStream_endElement(out, "prov:activity");
                    }
                  else if (next.getName() == "agent")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString AgentID = QString::fromStdString(xmlEntity.getAttrValue(0)); // The first attribute is prov:id
                      QString AgentName = QString::fromStdString(xmlEntity.getAttrValue("GivenName"));
                      QString AgentFamilyName = QString::fromStdString(xmlEntity.getAttrValue("FamilyName"));
                      QString AgentOrganization = QString::fromStdString(xmlEntity.getAttrValue("Organization"));
                      QString AgentEmail = QString::fromStdString(xmlEntity.getAttrValue("Email"));

                      //mProvenanceAuthorNameMap.insert(AgentID, (AgentName + AgentFamilyName));
                      if (!ProvenanceAuthorList.contains(AgentID))
                        {
                          XMLOutputStream_startElement(out, "prov:agent");
                          XMLOutputStream_writeAttributeChars(out, "prov:id",  AgentID.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "GivenName",  AgentName.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "FamilyName",  AgentFamilyName.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "Organization",  AgentOrganization.toUtf8());
                          XMLOutputStream_writeAttributeChars(out, "Email",  AgentEmail.toUtf8());
                          XMLOutputStream_endElement(out, "prov:agent");
                        }
                    }

                  else if (next.getName() == "used")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString ActivityID, EntityID;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:used");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");
                              XMLOutputStream_endElement(out, "prov:used");
                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "activity")
                                {

                                  ActivityID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                                }

                              if (child.getName() == "entity")
                                {
                                  EntityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }

                  else if (next.getName() == "wasAttributedTo")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString AgentID, EntityID;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasAttributedTo");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");
                              XMLOutputStream_startElement(out, "prov:agent");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  AgentID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:agent");
                              XMLOutputStream_endElement(out, "prov:wasAttributedTo");

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

                      XMLToken xmlEntity = in2.next();
                      QString AgentID, ActivityID;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasAssociatedWith");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:agent");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  AgentID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:agent");
                              XMLOutputStream_endElement(out, "prov:wasAssociatedWith");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "agent")
                                {

                                  AgentID = QString::fromStdString(child.getAttrValue(0)); // The first attrube is reference to activity ID
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasGeneratedBy")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString ActivityID, EntityID, Time;
                      bool timeExists = false;
                      bool activityExists = false;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasGeneratedBy");
                              XMLOutputStream_startElement(out, "prov:entity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",  EntityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:entity");

                              if (activityExists)
                                {
                                  XMLOutputStream_startElement(out, "prov:activity");
                                  XMLOutputStream_writeChars(out, ActivityID.toUtf8());
                                  XMLOutputStream_endElement(out, "prov:activity");
                                }

                              if (timeExists)
                                {
                                  XMLOutputStream_startElement(out, "prov:time");
                                  XMLOutputStream_writeChars(out, Time.toUtf8());
                                  XMLOutputStream_endElement(out, "prov:time");
                                }

                              XMLOutputStream_endElement(out, "prov:wasGeneratedBy");

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

                                  Time = QString::fromStdString(in2.next().getCharacters());
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
                      XMLToken xmlEntity = in2.next();
                      QString ActivityID, Time;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasStartedBy");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(out, "prov:ref",   ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:time");
                              XMLOutputStream_writeChars(stream3, Time.toUtf8());
                              XMLOutputStream_endElement(stream3, "prov:time");
                              XMLOutputStream_endElement(out, "prov:wasStartedBy");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(in2.next().getCharacters());
                                }

                              if (child.getName() == "activity")
                                {
                                  ActivityID = QString::fromStdString(child.getAttrValue(0));
                                }
                            }
                        }
                    }
                  else if (next.getName() == "wasEndedBy")
                    {
                      XMLToken xmlEntity = in2.next();
                      QString ActivityID, Time;

                      while (in2.isGood())
                        {
                          XMLToken child  = in2.next();

                          // if we reached the end element of the 'Version' element : add this data as a new version
                          if (child.isEndFor(xmlEntity))
                            {
                              //add here
                              XMLOutputStream_startElement(out, "prov:wasEndedBy");
                              XMLOutputStream_startElement(out, "prov:activity");
                              XMLOutputStream_writeAttributeChars(stream3, "prov:ref",   ActivityID.toUtf8());
                              XMLOutputStream_endElement(out, "prov:activity");
                              XMLOutputStream_startElement(out, "prov:time");
                              XMLOutputStream_writeChars(out, Time.toUtf8());
                              XMLOutputStream_endElement(out, "prov:time");
                              XMLOutputStream_endElement(out, "prov:wasEndedBy");

                              break;
                            }

                          if (child.isStart())
                            {

                              if (child.getName() == "time")
                                {

                                  Time = QString::fromStdString(in2.next().getCharacters());
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

              XMLOutputStream_endElement(out, "prov:document");
              XMLOutputStream_free(out);
            }
        }
    }
}

void CProvenanceXMLWriter::updateMainBodyProvenace()
{
  //First merge Main body and current session provenance in a temporary file
  mergeProvenanceFiles("ProvenanceMainBody.xml", "ProvenanceCurrentSession.xml", "Temp.xml");

  // Delete Main body and Current session Provenance and rename Temp to Current Session
  QDir destination;
  QString dataFile = mPathFile + "/ProvenanceMainBody.xml";
  destination.remove(dataFile);
  dataFile = mPathFile + "/ProvenanceCurrentSession.xml";
  destination.remove(dataFile);
  dataFile = mPathFile + "/Temp.xml";
  QString dataFile2 = mPathFile + "/ProvenanceMainBody.xml";
  destination.rename(dataFile, dataFile2);
}

void CProvenanceXMLWriter::updateVersionProvenanceXMLFile(QString VersionName)
{
  updateCurrentSessionProvenance();
  updateMainBodyProvenace();
  QDir destination;
  QString dataFile = mPathFile + "/ProvenanceMainBody.xml";
  QString dataFile2 = mPathFile + "/" + VersionName + "/" + VersionName + "Provenance.xml";
  destination.rename(dataFile, dataFile2);
}

void CProvenanceXMLWriter::deleteVersionProvenance(QString VersionName)
{
  QDir destination;
  QString dataFile = mPathFile + "/" + VersionName +  "/" + VersionName + "Provenance.xml";
  destination.remove(dataFile);
}

void CProvenanceXMLWriter::combineVersionProvenance(QString ParentVersionName, QString VersionName)
{
  mergeProvenanceFiles(ParentVersionName +  "/" + ParentVersionName + "Provenance.xml", VersionName +  "/" + VersionName + "Provenance.xml", "Temp.xml");

  // Delete Main body and Current session Provenance and rename Temp to Current Session
  QDir destination;
  QString dataFile = mPathFile + "/" + VersionName +  "/" + VersionName + "Provenance.xml";
  destination.remove(dataFile);
  dataFile = mPathFile + "/Temp.xml";
  QString dataFile2 = mPathFile +  "/" + VersionName +  "/" + VersionName + "Provenance.xml";
  destination.rename(dataFile, dataFile2);
}

void CProvenanceXMLWriter::deleteParentofCurrentVersionProvenance(QString VersionName)
{
  QDir destination;
  QString dataFile = mPathFile + "/ProvenanceMainBody.xml";
// The file management will be done by COMBINE Archive
  /*
    if (mProvenanceParentOfCurrentModel != mVersioningParentOfCurrentModel)
      {
        destination.remove(dataFile);
      }
  */
  mergeProvenanceFiles(VersionName +  "/" + VersionName + "Provenance.xml", "ProvenanceMainBody.xml", "Temp.xml");
  destination.remove(dataFile);
  dataFile = mPathFile + "/Temp.xml";
  QString dataFile2 = mPathFile +  "/ProvenanceMainBody.xml";
  destination.rename(dataFile, dataFile2);
}
