/****************************************************************************
 ** FunctionWidget meta object code from reading C++ file 'FunctionWidget.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "FunctionWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FunctionWidget::className() const
{
  return "FunctionWidget";
}

QMetaObject *FunctionWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FunctionWidget;

#ifndef QT_NO_TRANSLATION
QString FunctionWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("FunctionWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FunctionWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("FunctionWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FunctionWidget::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QWidget::staticMetaObject();
  static const QUParameter param_slot_0[] = {
        {0, &static_QUType_int, 0, QUParameter::In},
        {0, &static_QUType_int, 0, QUParameter::In},
        {0, &static_QUType_int, 0, QUParameter::In},
        {0, &static_QUType_ptr, "const QPoint&", QUParameter::In}
      };
  static const QUMethod slot_0 = {"slotTableCurrentChanged", 4, param_slot_0};
  static const QUMethod slot_1 = {"slotTableSelectionChanged", 0, 0};
  static const QMetaData slot_tbl[] = {
                                        {"slotTableCurrentChanged(int,int,int,const QPoint&)", &slot_0, QMetaData::Public},
                                        {"slotTableSelectionChanged()", &slot_1, QMetaData::Protected}
                                      };
  static const QUParameter param_signal_0[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod signal_0 = {"name", 1, param_signal_0};
  static const QMetaData signal_tbl[] = {
                                          {"name(QString&)", &signal_0, QMetaData::Protected}
                                        };
  metaObj = QMetaObject::new_metaobject(
              "FunctionWidget", parentObject,
              slot_tbl, 2,
              signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_FunctionWidget.setMetaObject(metaObj);
  return metaObj;
}

void* FunctionWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "FunctionWidget")) return (FunctionWidget*)this;
  return QWidget::qt_cast(clname);
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL name
void FunctionWidget::name(QString& t0)
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

bool FunctionWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: slotTableCurrentChanged(static_QUType_int.get(_o + 1), static_QUType_int.get(_o + 2), static_QUType_int.get(_o + 3), *((QPoint*)static_QUType_ptr.get(_o + 4))); break;
    case 1: slotTableSelectionChanged(); break;
    default:
      return QWidget::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool FunctionWidget::qt_emit(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->signalOffset())
    {
    case 0: name(static_QUType_QString.get(_o + 1)); break;
    default:
      return QWidget::qt_emit(_id, _o);
    }
  return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool FunctionWidget::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
