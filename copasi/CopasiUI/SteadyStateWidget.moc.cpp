/****************************************************************************
 ** SteadyStateWidget meta object code from reading C++ file 'SteadyStateWidget.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "SteadyStateWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SteadyStateWidget::className() const
  {
    return "SteadyStateWidget";
  }

QMetaObject *SteadyStateWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SteadyStateWidget;

#ifndef QT_NO_TRANSLATION
QString SteadyStateWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("SteadyStateWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SteadyStateWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("SteadyStateWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SteadyStateWidget::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QWidget::staticMetaObject();
  static const QUMethod slot_0 = {"taskNameChanged", 0, 0};
  static const QUMethod slot_1 = {"methodJacob", 0, 0};
  static const QUMethod slot_2 = {"methodStability", 0, 0};
  static const QUMethod slot_3 = {"parameterValueChanged", 0, 0};
  static const QUMethod slot_4 = {"CommitChange", 0, 0};
  static const QUMethod slot_5 = {"CancelChange", 0, 0};
  static const QMetaData slot_tbl[] =
    {
      {"taskNameChanged()", &slot_0, QMetaData::Public},
      {"methodJacob()", &slot_1, QMetaData::Public},
      {"methodStability()", &slot_2, QMetaData::Public},
      {"parameterValueChanged()", &slot_3, QMetaData::Public},
      {"CommitChange()", &slot_4, QMetaData::Public},
      {"CancelChange()", &slot_5, QMetaData::Public}
    };
  metaObj = QMetaObject::new_metaobject(
              "SteadyStateWidget", parentObject,
              slot_tbl, 6,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_SteadyStateWidget.setMetaObject(metaObj);
  return metaObj;
}

void* SteadyStateWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "SteadyStateWidget")) return (SteadyStateWidget*)this;
  return QWidget::qt_cast(clname);
}

bool SteadyStateWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: taskNameChanged(); break;
    case 1: methodJacob(); break;
    case 2: methodStability(); break;
    case 3: parameterValueChanged(); break;
    case 4: CommitChange(); break;
    case 5: CancelChange(); break;
    default:
      return QWidget::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool SteadyStateWidget::qt_emit(int _id, QUObject* _o)
{
  return QWidget::qt_emit(_id, _o);
}
#ifndef QT_NO_PROPERTIES

bool SteadyStateWidget::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
