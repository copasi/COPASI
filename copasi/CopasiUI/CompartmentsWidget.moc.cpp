/****************************************************************************
 ** CompartmentsWidget meta object code from reading C++ file 'CompartmentsWidget.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "CompartmentsWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CompartmentsWidget::className() const
  {
    return "CompartmentsWidget";
  }

QMetaObject *CompartmentsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CompartmentsWidget;

#ifndef QT_NO_TRANSLATION
QString CompartmentsWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CompartmentsWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CompartmentsWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CompartmentsWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CompartmentsWidget::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QWidget::staticMetaObject();
  static const QUParameter param_slot_0[] =
    {
      {0, &static_QUType_int, 0, QUParameter::In },
      {0, &static_QUType_int, 0, QUParameter::In },
      {0, &static_QUType_int, 0, QUParameter::In },
      {0, &static_QUType_ptr, "const QPoint&", QUParameter::In }
    };
  static const QUMethod slot_0 = {"slotTableCurrentChanged", 4, param_slot_0 };
  static const QUMethod slot_1 = {"slotTableSelectionChanged", 0, 0 };
  static const QUMethod slot_2 = {"slotBtnOKClicked", 0, 0 };
  static const QUMethod slot_3 = {"slotBtnCancelClicked", 0, 0 };
  static const QUParameter param_slot_4[] =
    {
      {0, &static_QUType_int, 0, QUParameter::In },
      {0, &static_QUType_int, 0, QUParameter::In }
    };
  static const QUMethod slot_4 = {"tableValueChanged", 2, param_slot_4 };
  static const QMetaData slot_tbl[] =
    {
      {"slotTableCurrentChanged(int,int,int,const QPoint&)", &slot_0, QMetaData::Public },
      {"slotTableSelectionChanged()", &slot_1, QMetaData::Protected },
      {"slotBtnOKClicked()", &slot_2, QMetaData::Protected },
      {"slotBtnCancelClicked()", &slot_3, QMetaData::Protected },
      {"tableValueChanged(int,int)", &slot_4, QMetaData::Protected }
    };
  static const QUParameter param_signal_0[] =
    {
      {0, &static_QUType_QString, 0, QUParameter::InOut }
    };
  static const QUMethod signal_0 = {"name", 1, param_signal_0 };
  static const QUParameter param_signal_1[] =
    {
      {0, &static_QUType_QString, 0, QUParameter::InOut }
    };
  static const QUMethod signal_1 = {"signal_emitted", 1, param_signal_1 };
  static const QMetaData signal_tbl[] =
    {
      {"name(QString&)", &signal_0, QMetaData::Public },
      {"signal_emitted(QString&)", &signal_1, QMetaData::Private }
    };
  metaObj = QMetaObject::new_metaobject(
              "CompartmentsWidget", parentObject,
              slot_tbl, 5,
              signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_CompartmentsWidget.setMetaObject(metaObj);
  return metaObj;
}

void* CompartmentsWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "CompartmentsWidget"))
    return (CompartmentsWidget*)this;
  return QWidget::qt_cast(clname);
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL name
void CompartmentsWidget::name(QString& t0)
{
  if (signalsBlocked())
    return;
  QConnectionList *clist = receivers(staticMetaObject()->signalOffset() + 0);
  if (!clist)
    return;
  QUObject o[2];
  static_QUType_QString.set(o + 1, t0);
  activate_signal(clist, o);
  t0 = static_QUType_QString.get(o + 1);
}

// SIGNAL signal_emitted
void CompartmentsWidget::signal_emitted(QString& t0)
{
  if (signalsBlocked())
    return;
  QConnectionList *clist = receivers(staticMetaObject()->signalOffset() + 1);
  if (!clist)
    return;
  QUObject o[2];
  static_QUType_QString.set(o + 1, t0);
  activate_signal(clist, o);
  t0 = static_QUType_QString.get(o + 1);
}

bool CompartmentsWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0:
      slotTableCurrentChanged(static_QUType_int.get(_o + 1), static_QUType_int.get(_o + 2), static_QUType_int.get(_o + 3), *((QPoint*)static_QUType_ptr.get(_o + 4)));
      break;
    case 1:
      slotTableSelectionChanged();
      break;
    case 2:
      slotBtnOKClicked();
      break;
    case 3:
      slotBtnCancelClicked();
      break;
    case 4:
      tableValueChanged(static_QUType_int.get(_o + 1), static_QUType_int.get(_o + 2));
      break;
    default:
      return QWidget::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool CompartmentsWidget::qt_emit(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->signalOffset())
    {
    case 0:
      name(static_QUType_QString.get(_o + 1));
      break;
    case 1:
      signal_emitted(static_QUType_QString.get(_o + 1));
      break;
    default:
      return QWidget::qt_emit(_id, _o);
    }
  return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CompartmentsWidget::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
