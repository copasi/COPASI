// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CModelVersion.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#include <QItemDelegate>
#include <QDir>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLErrorLog.h>

#include "CModelVersion.h"

CModelVersion::CModelVersion(QWidget *parent)
{
  mNCol = 8;
  mNRow = 0;

  mpModelVersionHierarchy = new QStandardItemModel(100, mNCol, parent);

  for (int col = 0; col < mNCol; ++col)
    {
      switch (col)
        {
          case 0:
            mpModelVersionHierarchy->setHeaderData(0, Qt::Horizontal, QString("Version"));
            break;

          case 1:
            mpModelVersionHierarchy->setHeaderData(1, Qt::Horizontal, QString("Derived from"));
            break;

          case 2:
            mpModelVersionHierarchy->setHeaderData(2, Qt::Horizontal, QString("Given Name"));
            break;

          case 3:
            mpModelVersionHierarchy->setHeaderData(3, Qt::Horizontal, QString("Family Name"));
            break;

          case 4:
            mpModelVersionHierarchy->setHeaderData(4, Qt::Horizontal, QString("Organization"));
            break;

          case 5:
            mpModelVersionHierarchy->setHeaderData(5, Qt::Horizontal, QString("Email"));
            break;

          case 6:
            mpModelVersionHierarchy->setHeaderData(6, Qt::Horizontal, QString("Time"));
            break;

          case 7:
            mpModelVersionHierarchy->setHeaderData(7, Qt::Horizontal, QString("Comments"));
            break;
        }
    }

  mParentOfCurrentModel = QString("");
  mPathFile = QString("");
}

CModelVersion::~CModelVersion()
{
  delete mpModelVersionHierarchy;
}

void CModelVersion::clear()
{
  mParentOfCurrentModel = QString("");
  mPathFile = QString("");
  mNRow = 0;
}

int CModelVersion::getNumberOfVersions() const
{
  return(mNRow);
}

QString CModelVersion::getParentOfCurrentModel() const
{
  return mParentOfCurrentModel;
}

QStandardItemModel *  CModelVersion::getModelVersionHierarchy() const
{
  return mpModelVersionHierarchy;
}

QString CModelVersion::getPathFile()
{
  return(mPathFile);
}

bool CModelVersion::setPathFile(QString PathFile)
{
  QDir dir(PathFile);

  if (dir.exists())
    {
      mPathFile = PathFile;
      return(true);
    }
  else
    {
      return(false);
    }
}

bool CModelVersion::isVersionRepeated(QString Version)
{
  int i;

  for (i = 0; i < mNRow; i++)
    {
      if ((QString::compare(mpModelVersionHierarchy->item(i, 0)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          return(true);
        }
    }

  return(false);
}

int CModelVersion::addNewVersion(QString Version, QString AuthorGivenName, QString AuthorFamilyName, QString AuthorOrganization, QString AuthorEmail, QString Comments)
{
  if (Version.isEmpty())
    {
      return(2);
    }

  if (isVersionRepeated(Version))
    {
      return(1);
    }

  QString DerivedFrom;

  if (mNRow == 0)
    {
      DerivedFrom = QString("");
    }
  else
    {
      DerivedFrom = mParentOfCurrentModel;
    }

  QString Time = QDateTime::currentDateTime().toString();

  versionToTable(Version, DerivedFrom, AuthorGivenName, AuthorFamilyName, AuthorOrganization, AuthorEmail, Comments, Time);

  if (updateVersionXML())
    {
      return(0);
    }
  else
    {
      return(3);  //If Versioning Hierarchy xml file was not updated properly
    }
}

void CModelVersion::versionToTable(QString Version, QString DerivedFrom, QString AuthorGivenName, QString AuthorFamilyName, QString AuthorOrganization, QString AuthorEmail, QString Comments, QString Time)
{

  if (((mNRow + 1) % 100) == 0)
    {
      reallocateModelVersionHierarchyTable((mNRow + 101));
    }

  for (int col = 0; col < mNCol; ++col)
    {
      QModelIndex index = mpModelVersionHierarchy->index(mNRow, col, QModelIndex());

      switch (col)
        {
          case 0:
            mpModelVersionHierarchy->setData(index, QVariant(Version));
            break;

          case 1:
            mpModelVersionHierarchy->setData(index, QVariant(DerivedFrom));
            break;

          case 2:
            mpModelVersionHierarchy->setData(index, QVariant(AuthorGivenName));
            break;

          case 3:
            mpModelVersionHierarchy->setData(index, QVariant(AuthorFamilyName));
            break;

          case 4:
            mpModelVersionHierarchy->setData(index, QVariant(AuthorOrganization));
            break;

          case 5:
            mpModelVersionHierarchy->setData(index, QVariant(AuthorEmail));
            break;

          case 6:
            mpModelVersionHierarchy->setData(index, QVariant(Time));
            break;

          case 7:
            mpModelVersionHierarchy->setData(index, QVariant(Comments));
            break;
        }
    }

  mParentOfCurrentModel = Version;
  mNRow++;
}

int CModelVersion::deleteVersion(QString Version)
{

  if (Version.isEmpty())
    {
      return(1);
    }

  if (isVersionRepeated(Version) == false)
    {
      return(2);
    }

  QString parentVersion;
  int deletedRow = 0;

  for (deletedRow = 0; deletedRow < mNRow; deletedRow++)
    {
      if ((QString::compare(mpModelVersionHierarchy->item(deletedRow, 0)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          parentVersion = mpModelVersionHierarchy->item(deletedRow, 1)->text();
          break;
        }
    }

  if ((deletedRow == 0) && (mNRow > 1))
    {
      return(3);
    }

  if ((QString::compare(mParentOfCurrentModel, Version, Qt::CaseInsensitive)) == 0)
    {
      mParentOfCurrentModel = parentVersion;
    }

  // To delete a row - shift up every row under the deleted one / Retune the parent of deleted version in the second column
  // First shift up the rows
  int i;
  int j;

  for (i = deletedRow; (i + 1) < mNRow; i++)
    {
      for (j = 0; j < mNCol; ++j)
        {
          //mpModelVersionHierarchy->item(i,j)->text() = mpModelVersionHierarchy->item(i+1,j)->text();
          QModelIndex index = mpModelVersionHierarchy->index(i, j, QModelIndex());

          mpModelVersionHierarchy->setData(index, QVariant(mpModelVersionHierarchy->item(i + 1, j)->text()));
        }
    }

  mNRow--;

  // Now reset the second columns
  for (i = 0; i < mNRow; i++)
    {
      if ((QString::compare(mpModelVersionHierarchy->item(i, 1)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          QModelIndex index = mpModelVersionHierarchy->index(i, 1, QModelIndex());
          mpModelVersionHierarchy->setData(index, QVariant(parentVersion));
        }
    }

  if (updateVersionXML())
    {
      return(0);
    }
  else
    {
      return(4);  //If Versioning Hierarchy xml file was not updated properly
    }
}

int CModelVersion::restoreVersion(QString Version)
{
  if (Version.isEmpty())
    {
      return(1);
    }

  if (isVersionRepeated(Version) == false)
    {
      return(2);
    }

  mParentOfCurrentModel = Version;

  if (updateVersionXML())
    {
      return(0);
    }
  else
    {
      return(3);  //If Versioning Hierarchy xml file was not updated properly
    }
}

int CModelVersion::updateSelectedCell(const QModelIndex &index, QString text)
{
  if ((index.row() < 0) || (index.row() > mNRow - 1) || (index.column() < 0) || (index.column() > mNCol - 1))
    {
      return(1);
    }

  if (text.isEmpty())
    {
      return(2);
    }

  mpModelVersionHierarchy->setData(index, QVariant(text));

  if (updateVersionXML())
    {
      return(0);
    }
  else
    {
      return(3);  //If Versioning Hierarchy xml file was not updated properly
    }
}

void CModelVersion::reallocateModelVersionHierarchyTable(int Nrow)
{
  QStandardItemModel ModelVersionHierarchy(Nrow, mNCol);

  // Now copy mpModelVersionHierarcy in ModelVersionHierarchy
  int row, col;

  for (row = 0; row < mNRow; row++)
    {
      for (col = 0; col < mNCol; ++col)
        {
          QStandardItem *item = new QStandardItem(QString(mpModelVersionHierarchy->item(row, col)->text()));
          ModelVersionHierarchy.setItem(row, col, item);
        }
    }

  // Now realocate mpModelVersionHierarchy and refill it
  //mpModelVersionHierarchy = ModelVersionHierarchy;
  //~ModelVersionHierarchy();
  mpModelVersionHierarchy = new QStandardItemModel(Nrow, mNCol);

  for (col = 0; col < mNCol; ++col)
    {
      switch (col)
        {
          case 0:
            mpModelVersionHierarchy->setHeaderData(0, Qt::Horizontal, QString("Version"));
            break;

          case 1:
            mpModelVersionHierarchy->setHeaderData(1, Qt::Horizontal, QString("Derived from"));
            break;

          case 2:
            mpModelVersionHierarchy->setHeaderData(2, Qt::Horizontal, QString("Given Name"));
            break;

          case 3:
            mpModelVersionHierarchy->setHeaderData(3, Qt::Horizontal, QString("Family Name"));
            break;

          case 4:
            mpModelVersionHierarchy->setHeaderData(4, Qt::Horizontal, QString("Organization"));
            break;

          case 5:
            mpModelVersionHierarchy->setHeaderData(5, Qt::Horizontal, QString("Email"));
            break;

          case 6:
            mpModelVersionHierarchy->setHeaderData(6, Qt::Horizontal, QString("Time"));
            break;

          case 7:
            mpModelVersionHierarchy->setHeaderData(7, Qt::Horizontal, QString("Comments"));
            break;
        }
    }

  for (row = 0; row < mNRow; row++)
    {
      for (col = 0; col < mNCol; col++)
        {
          QStandardItem *item = new QStandardItem(QString(ModelVersionHierarchy.item(row, col)->text()));
          mpModelVersionHierarchy->setItem(row, col, item);
        }
    }

  //remove ModelVersionHierarchy
}

bool CModelVersion::updateVersionXML()
{
  bool success = false;
  //XMLErrorLog log;
  QString dataFile;

  if (mPathFile == "")
    {
      dataFile = "VersionHierarchy.xml";
    }
  else
    {
      dataFile = mPathFile + "/VersionHierarchy.xml";
    }

  XMLOutputStream_t * stream = XMLOutputStream_createFile(dataFile.toUtf8(), "UTF-8", 1);

  if (stream != NULL)
    {
      int i;
      XMLOutputStream_startElement(stream, "VersioningHierarchy");

      for (i = 0 ; i < mNRow; i ++)
        {
          XMLOutputStream_startElement(stream, "Version");
          XMLOutputStream_writeAttributeChars(stream, "Version", mpModelVersionHierarchy->item(i, 0)->text().toUtf8());
          XMLOutputStream_startElement(stream, "Derived_from");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 1)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Derived_from");
          XMLOutputStream_startElement(stream, "Author_Name");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 2)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Author_Name");
          XMLOutputStream_startElement(stream, "Author_Family");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 3)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Author_Family");
          XMLOutputStream_startElement(stream, "Author_Organization");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 4)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Author_Organization");
          XMLOutputStream_startElement(stream, "Author_Email");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 5)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Author_Email");
          XMLOutputStream_startElement(stream, "Time");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 6)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Time");
          XMLOutputStream_startElement(stream, "Comments");
          XMLOutputStream_writeChars(stream, mpModelVersionHierarchy->item(i, 7)->text().toUtf8());
          XMLOutputStream_endElement(stream, "Comments");
          XMLOutputStream_endElement(stream, "Version");
        }

      XMLOutputStream_startElement(stream, "ParentOfCurrentModel");
      XMLOutputStream_writeChars(stream, mParentOfCurrentModel.toUtf8());
      XMLOutputStream_endElement(stream, "ParentOfCurrentModel");
      XMLOutputStream_endElement(stream, "VersioningHierarchy");
      XMLOutputStream_free(stream);
      success = true;
    }

  return(success);
}

int CModelVersion::readVersionXML()
{

  // error log for logging errors while reading
  XMLErrorLog log;
  // initializing xml input stream
  QString dataFile;

  if (mPathFile == "")
    {
      dataFile = "VersionHierarchy.xml";
    }
  else
    {
      dataFile = mPathFile + "/VersionHierarchy.xml";
    }

  QFile Fout(dataFile);

  if (!Fout.exists())
    {
      return(1);
    }

  XMLInputStream stream(dataFile.toUtf8(), true, "", &log);

  if ((stream.peek().isStart()) && (stream.peek().getName() == "VersioningHierarchy"))
    {
      //qDebug() << "stream is start and peek name is version heirarchy " <<endl;
    }
  else
    {
      //qDebug() << "stream is niether start nor peek name is version heirarchy " <<endl;
      return(3);
    }

  XMLToken VersioningHierarchy = stream.next();

  // now read as long as we have something
  while (stream.isGood())
    {

      stream.skipText();
      // grab the next element
      XMLToken next = stream.peek();

      // if we reached the end table element, we stop
      if (next.isEndFor(VersioningHierarchy))
        break;

      // otherwise we read a new version from the stream
      if (!((next.getName() == "Version") || (next.getName() == "ParentOfCurrentModel")))
        {
          // if we are not at the version element, we are wrong here and bail
          log.add(XMLError(MissingXMLElements, "expected 'Version' element"));
        }
      else if (next.getName() == "Version")
        {
          XMLToken xmlVersion = stream.next();
          QString VersionName = QString::fromStdString(xmlVersion.getAttrValue("Version"));
          QString DerivedFrom, AuthorName, AuthorFamily, AuthorOrganization, AuthorEmail, Time, Comments = ("");

          // since unfortunately the other elements are text-elements
          // we need to sort them here
          while (stream.isGood())
            {
              XMLToken child  = stream.next();

              // if we reached the end element of the 'Version' element : add this data as a new version
              if (child.isEndFor(xmlVersion))
                {
                  //add here
                  versionToTable(VersionName, DerivedFrom, AuthorName, AuthorFamily, AuthorOrganization, AuthorEmail, Comments, Time);
                  break;
                }

              if (child.isStart())
                {

                  if (child.getName() == "Derived_from")
                    {
                      DerivedFrom = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Author_Name")
                    {
                      AuthorName = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Author_Family")
                    {
                      AuthorFamily = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Author_Organization")
                    {
                      AuthorOrganization = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Author_Email")
                    {
                      AuthorEmail = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Time")
                    {
                      Time = QString::fromStdString(stream.next().getCharacters());
                    }
                  else if (child.getName() == "Comments")
                    {
                      Comments = QString::fromStdString(stream.next().getCharacters());
                    }
                  else
                    {
                      log.add(XMLError(MissingXMLElements, "unexpected  attribute in 'Version' element"));
                    }
                }
            }
        }
      else
        {
          while (stream.isGood())
            {
              XMLToken xmlParent = stream.next();

              if (xmlParent.isStart())
                {
                  if (xmlParent.getName() == "ParentOfCurrentModel")
                    {
                      mParentOfCurrentModel = QString::fromStdString(stream.next().getCharacters());
                      break;
                    }
                }
            }
        }
    }

  if (log.getNumErrors() > 0)
    {
      log.printErrors();
      return(2);
    }

  return(0);
}

#ifdef COPASI_Provenance
QList<QString>  CModelVersion::getChildrenOfVersionForProvenanceXML(QString Version)
{
  int i;
  QList<QString>  ChildrenVersions;

  //Check if the Version has any child - add them to list
  for (i = 0; i < mNRow; i++)
    {
      if ((QString::compare(mpModelVersionHierarchy->item(i, 1)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          ChildrenVersions.append(mpModelVersionHierarchy->item(i, 0)->text());
        }
    }

  return(ChildrenVersions);
}
QList<QString>  CModelVersion::getVersionsPathToCurrentModel()
{
  QList<QString> ReversePath, DirectPath;

// Fill the Version path to a QList from the current version to the root verison
  ReversePath.append(mParentOfCurrentModel);
  bool HasParent = true;
  QString Version = mParentOfCurrentModel;
  QString parentVersion;

  while (HasParent)
    {
      int i = 0;
      HasParent = false;

      for (i = 0; i < mNRow; i++)
        {
          if ((QString::compare(mpModelVersionHierarchy->item(i, 0)->text(), Version, Qt::CaseInsensitive)) == 0)
            {
              parentVersion = mpModelVersionHierarchy->item(i, 1)->text();
              HasParent = true;
              break;
            }
        }

      if (HasParent)
        {
          ReversePath.append(parentVersion);
          Version = parentVersion;
        }
    }

// Reverse the QList to have the Version path from root version to the current version
  if (!ReversePath.isEmpty())
    {
      int j;

      for (j = 0; j < ReversePath.size(); ++j)
        {
          DirectPath.append(ReversePath.at(ReversePath.size() - (j + 1)));
        }
    }

  return(DirectPath);
}

#endif

void CModelVersion::restoreLastSavedVersioningHierarchy(QString Version)
{
  mParentOfCurrentModel = Version;
  updateVersionXML();
}

QString CModelVersion::getParentVersion(QString Version)
{
  int i;
  QString ParentVersion = QString("");

  for (i = 0; i < mNRow; i++)
    {
      if ((QString::compare(mpModelVersionHierarchy->item(i, 0)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          ParentVersion = mpModelVersionHierarchy->item(i, 1)->text();
          break;
        }
    }

  return(ParentVersion);
}
