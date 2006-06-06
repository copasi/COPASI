/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mml/Attic/qtmmlwidget.h,v $
   $Revision: 1.2.2.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/06 13:43:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/***************************************************************************
 **
 ** Copyright (C) 2003-2004 Trolltech AS.  All rights reserved.
 **
 ** Licensees holding valid Qt Enterprise Edition licenses may use this
 ** file in accordance with the Qt Solutions License Agreement provided
 ** with the Solution.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 ** PURPOSE.
 **
 ** Please email sales@trolltech.com for information
 ** about Qt Solutions License Agreements.
 **
 ** Contact info@trolltech.com if any conditions of this licensing are
 ** not clear to you.
 **
 */
#ifndef QTMMLWIDGET_H
#define QTMMLWIDGET_H

#include <qdom.h>
#include <qframe.h>

class MmlDocument;

class QtMmlWidget : public QFrame
  {
  public:
    enum MmlFont {NormalFont, FrakturFont, SansSerifFont, ScriptFont,
                  MonospaceFont, DoublestruckFont};

    QtMmlWidget(QWidget *parent = 0, const char *name = 0);
    ~QtMmlWidget();

    QString fontName(MmlFont type) const;
    void setFontName(MmlFont type, const QString &name);
    int baseFontPointSize() const;
    void setBaseFontPointSize(int size);

    bool setContent(const QString &text, QString *errorMsg = 0,
                    int *errorLine = 0, int *errorColumn = 0);
    void dump() const;
    virtual QSize sizeHint() const;

    void setDrawFrames(bool b);
    bool drawFrames() const;

    void clear();

  protected:
    virtual void drawContents(QPainter *p);

  private:
    MmlDocument *m_doc;
  };

#endif
