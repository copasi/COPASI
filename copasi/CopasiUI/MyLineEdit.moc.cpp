/****************************************************************************
 ** MyLineEdit meta object code from reading C++ file 'MyLineEdit.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "MyLineEdit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyLineEdit::className() const
{
  return "MyLineEdit";
}

QMetaObject *MyLineEdit::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyLineEdit;

#ifndef QT_NO_TRANSLATION
QString MyLineEdit::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MyLineEdit", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyLineEdit::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MyLineEdit", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyLineEdit::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QLineEdit::staticMetaObject();
  static const QUMethod slot_0 = {"slotLineEditChanged", 0, 0};
  static const QMetaData slot_tbl[] = {
                                        {"slotLineEditChanged()", &slot_0, QMetaData::Protected}
                                      };
  static const QUMethod signal_0 = {"sideySignal", 0, 0};
  static const QMetaData signal_tbl[] = {
                                          {"sideySignal()", &signal_0, QMetaData::Protected}
                                        };
  metaObj = QMetaObject::new_metaobject(
              "MyLineEdit", parentObject,
              slot_tbl, 1,
              signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_MyLineEdit.setMetaObject(metaObj);
  return metaObj;
}

void* MyLineEdit::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "MyLineEdit")) return (MyLineEdit*)this;
  return QLineEdit::qt_cast(clname);
}

// SIGNAL sideySignal
void MyLineEdit::sideySignal()
{
  activate_signal(staticMetaObject()->signalOffset() + 0);
}

bool MyLineEdit::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: slotLineEditChanged(); break;
    default:
      return QLineEdit::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool MyLineEdit::qt_emit(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->signalOffset())
    {
    case 0: sideySignal(); break;
    default:
      return QLineEdit::qt_emit(_id, _o);
    }
  return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MyLineEdit::qt_property(int _id, int _f, QVariant* _v)
{
  return QLineEdit::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
