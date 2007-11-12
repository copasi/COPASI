// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/moc_qwt3dPlot.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/12 17:01:06 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Plot3d meta object code from reading C++ file 'qwt3dPlot.h'
 **
 ** Created: Fri Nov 9 16:46:16 2007
 **      by: The Qt MOC ($Id: moc_qwt3dPlot.cpp,v 1.1 2007/11/12 17:01:06 akoenig Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "qwt3dPlot.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Plot3d::className() const
  {
    return "Plot3d";
  }

QMetaObject *Plot3d::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Plot3d("Plot3d", &Plot3d::staticMetaObject);

#ifndef QT_NO_TRANSLATION
QString Plot3d::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("Plot3d", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Plot3d::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("Plot3d", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Plot3d::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = BaseWidget::staticMetaObject();
  metaObj = QMetaObject::new_metaobject(
              "Plot3d", parentObject,
              0, 0,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_Plot3d.setMetaObject(metaObj);
  return metaObj;
}

void* Plot3d::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "Plot3d"))
    return this;
  return BaseWidget::qt_cast(clname);
}

bool Plot3d::qt_invoke(int _id, QUObject* _o)
{
  return BaseWidget::qt_invoke(_id, _o);
}

bool Plot3d::qt_emit(int _id, QUObject* _o)
{
  return BaseWidget::qt_emit(_id, _o);
}
#ifndef QT_NO_PROPERTIES

bool Plot3d::qt_property(int id, int f, QVariant* v)
{
  return BaseWidget::qt_property(id, f, v);
}

bool Plot3d::qt_static_property(QObject* , int , int , QVariant*){return FALSE;}
#endif // QT_NO_PROPERTIES
