// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CStructureParser.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/25 07:51:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// written by pwilly on 09.07.08

#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <qxml.h>
#include <qvaluelist.h>

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

    bool ignorableWhitespace (const QString&);
    bool skippedEntity (const QString&);

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

    QValueList<QString> mListOfUncompletedTags;
  };

#endif
