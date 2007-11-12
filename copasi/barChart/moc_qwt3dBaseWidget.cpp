// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/moc_qwt3dBaseWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/12 17:01:06 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** BaseWidget meta object code from reading C++ file 'qwt3dBaseWidget.h'
 **
 ** Created: Fri Nov 9 16:46:17 2007
 **      by: The Qt MOC ($Id: moc_qwt3dBaseWidget.cpp,v 1.1 2007/11/12 17:01:06 akoenig Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "qwt3dBaseWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *BaseWidget::className() const
  {
    return "BaseWidget";
  }

QMetaObject *BaseWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_BaseWidget("BaseWidget", &BaseWidget::staticMetaObject);

#ifndef QT_NO_TRANSLATION
QString BaseWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("BaseWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString BaseWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("BaseWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* BaseWidget::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QWidget::staticMetaObject();
  static const QUMethod slot_0 = {"languageChange", 0, 0 };
  static const QUMethod slot_1 = {"setSlider", 0, 0 };
  static const QMetaData slot_tbl[] =
    {
      {"languageChange()", &slot_0, QMetaData::Protected },
      {"setSlider()", &slot_1, QMetaData::Protected}
    };
  metaObj = QMetaObject::new_metaobject(
              "BaseWidget", parentObject,
              slot_tbl, 2,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_BaseWidget.setMetaObject(metaObj);
  return metaObj;
}

void* BaseWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "BaseWidget"))
    return this;
  return QWidget::qt_cast(clname);
}

bool BaseWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: languageChange(); break;
    case 1: setSlider(); break;
    default:
      return QWidget::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool BaseWidget::qt_emit(int _id, QUObject* _o)
{
  return QWidget::qt_emit(_id, _o);
}
#ifndef QT_NO_PROPERTIES

bool BaseWidget::qt_property(int id, int f, QVariant* v)
{
  return QWidget::qt_property(id, f, v);
}

bool BaseWidget::qt_static_property(QObject* , int , int , QVariant*){return FALSE;}
#endif // QT_NO_PROPERTIES
