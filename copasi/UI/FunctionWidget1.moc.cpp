/****************************************************************************
 ** FunctionWidget1 meta object code from reading C++ file 'FunctionWidget1.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "FunctionWidget1.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FunctionWidget1::className() const
  {
    return "FunctionWidget1";
  }

QMetaObject *FunctionWidget1::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FunctionWidget1;

#ifndef QT_NO_TRANSLATION
QString FunctionWidget1::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("FunctionWidget1", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}

#ifndef QT_NO_TRANSLATION_UTF8
QString FunctionWidget1::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("FunctionWidget1", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}

#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FunctionWidget1::staticMetaObject()
{
  if (metaObj)
    return metaObj;

  QMetaObject* parentObject = QWidget::staticMetaObject();

  static const QUParameter param_slot_0[] =
    {
      { "setValue", &static_QUType_QString, 0, QUParameter::In }
    };
  static const QUMethod slot_0 = {"slotCancelButtonPressed", 1, param_slot_0 };

  static const QMetaData slot_tbl[] =
    {
      { "slotCancelButtonPressed(QString)", &slot_0, QMetaData::Protected }
    };

  metaObj = QMetaObject::new_metaobject(
              "FunctionWidget1", parentObject,
              slot_tbl, 1,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);

  cleanUp_FunctionWidget1.setMetaObject(metaObj);

  return metaObj;
}

void* FunctionWidget1::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "FunctionWidget1"))
    return (FunctionWidget1*)this;

  return QWidget::qt_cast(clname);
}

bool FunctionWidget1::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0:
      slotCancelButtonPressed(static_QUType_QString.get(_o + 1));
      break;

    default:
      return QWidget::qt_invoke(_id, _o);
    }

  return TRUE;
}

bool FunctionWidget1::qt_emit(int _id, QUObject* _o)
{
  return QWidget::qt_emit(_id, _o);
}

#ifndef QT_NO_PROPERTIES

bool FunctionWidget1::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}

#endif // QT_NO_PROPERTIES
