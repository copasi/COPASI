/****************************************************************************
 ** MoietyWidget1 meta object code from reading C++ file 'MoietyWidget1.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "MoietyWidget1.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MoietyWidget1::className() const
  {
    return "MoietyWidget1";
  }

QMetaObject *MoietyWidget1::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MoietyWidget1;

#ifndef QT_NO_TRANSLATION
QString MoietyWidget1::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MoietyWidget1", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}

#ifndef QT_NO_TRANSLATION_UTF8
QString MoietyWidget1::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MoietyWidget1", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}

#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MoietyWidget1::staticMetaObject()
{
  if (metaObj)
    return metaObj;

  QMetaObject* parentObject = QWidget::staticMetaObject();
  static const QUMethod slot_0 = {"slotBtnCancelClicked", 0, 0 };
  static const QUMethod slot_1 = {"slotBtnOKClicked", 0, 0 };

  static const QMetaData slot_tbl[] =
    {
      { "slotBtnCancelClicked()", &slot_0, QMetaData::Protected },
      { "slotBtnOKClicked()", &slot_1, QMetaData::Protected }
    };

  static const QUParameter param_signal_0[] =
    {
      { 0, &static_QUType_QString, 0, QUParameter::InOut }
    };
  static const QUMethod signal_0 = {"signal_emitted", 1, param_signal_0 };

  static const QMetaData signal_tbl[] =
    {
      { "signal_emitted(QString&)", &signal_0, QMetaData::Protected }
    };

  metaObj = QMetaObject::new_metaobject(
              "MoietyWidget1", parentObject,
              slot_tbl, 2,
              signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);

  cleanUp_MoietyWidget1.setMetaObject(metaObj);

  return metaObj;
}

void* MoietyWidget1::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "MoietyWidget1"))
    return (MoietyWidget1*)this;

  return QWidget::qt_cast(clname);
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL signal_emitted
void MoietyWidget1::signal_emitted(QString& t0)
{
  if (signalsBlocked())
    return ;

  QConnectionList *clist = receivers(staticMetaObject()->signalOffset() + 0);

  if (!clist)
    return ;

  QUObject o[2];

  static_QUType_QString.set(o + 1, t0);

  activate_signal(clist, o);

  t0 = static_QUType_QString.get(o + 1);
}

bool MoietyWidget1::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0:
      slotBtnCancelClicked();
      break;

    case 1:
      slotBtnOKClicked();
      break;

    default:
      return QWidget::qt_invoke(_id, _o);
    }

  return TRUE;
}

bool MoietyWidget1::qt_emit(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->signalOffset())
    {
    case 0:
      signal_emitted(static_QUType_QString.get(_o + 1));
      break;

    default:
      return QWidget::qt_emit(_id, _o);
    }

  return TRUE;
}

#ifndef QT_NO_PROPERTIES

bool MoietyWidget1::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}

#endif // QT_NO_PROPERTIES
