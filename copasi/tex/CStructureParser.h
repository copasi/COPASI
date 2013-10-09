// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// written by pwilly on 09.07.08

#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <QtXml/QXmlAttributes>
#include <QtCore/QLinkedList>

class QString;

class CStructureParser : public QXmlDefaultHandler
{
public:
  CStructureParser(int);
  //  ~CStructureParser(){};

  bool startDocument();
  bool startElement(const QString&, const QString&, const QString& ,
                    const QXmlAttributes&);
  bool characters(const QString&);
  bool endElement(const QString&, const QString&, const QString&);

  bool ignorableWhitespace(const QString&);
  bool skippedEntity(const QString&);

  QString getTeX();

private:
  QString indent;

  // for writing formula in latex form
  QString texHead, tex, texTail;

  // tags
  QString tagName;

  // for column allignment
  bool needToWriteColumnAllignment;
  int sumColumns;
  int indexColumns;

  QLinkedList<QString> mListOfUncompletedTags;
};

#endif
