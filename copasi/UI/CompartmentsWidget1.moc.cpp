/****************************************************************************
 ** CompartmentsWidget1 meta object code from reading C++ file 'CompartmentsWidget1.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "CompartmentsWidget1.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CompartmentsWidget1::className() const
  {
    return "CompartmentsWidget1";
  }

QMetaObject *CompartmentsWidget1::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CompartmentsWidget1;

#ifndef QT_NO_TRANSLATION
QString CompartmentsWidget1::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CompartmentsWidget1", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}

#ifndef QT_NO_TRANSLATION_UTF8
QString CompartmentsWidget1::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CompartmentsWidget1", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}

#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CompartmentsWidget1::staticMetaObject()
{
  if (metaObj)
    return metaObj;

  QMetaObject* parentObject = QWidget::staticMetaObject();

  metaObj = QMetaObject::new_metaobject(
              "CompartmentsWidget1", parentObject,
              0, 0,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);

  cleanUp_CompartmentsWidget1.setMetaObject(metaObj);

  return metaObj;
}

void* CompartmentsWidget1::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "CompartmentsWidget1"))
    return (CompartmentsWidget1*)this;

  return QWidget::qt_cast(clname);
}

bool CompartmentsWidget1::qt_invoke(int _id, QUObject* _o)
{
  return QWidget::qt_invoke(_id, _o);
}

bool CompartmentsWidget1::qt_emit(int _id, QUObject* _o)
{
  return QWidget::qt_emit(_id, _o);
}

#ifndef QT_NO_PROPERTIES

bool CompartmentsWidget1::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}

#endif // QT_NO_PROPERTIES
