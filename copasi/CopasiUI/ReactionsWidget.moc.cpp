/****************************************************************************
 ** ReactionsWidget meta object code from reading C++ file 'ReactionsWidget.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "ReactionsWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ReactionsWidget::className() const
{
  return "ReactionsWidget";
}

QMetaObject *ReactionsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ReactionsWidget;

#ifndef QT_NO_TRANSLATION
QString ReactionsWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("ReactionsWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ReactionsWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("ReactionsWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ReactionsWidget::staticMetaObject()
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
  static const QUMethod slot_2 = {"slotBtnOKClicked", 0, 0};
  static const QUMethod slot_3 = {"slotBtnCancelClicked", 0, 0};
  static const QMetaData slot_tbl[] = {
                                        {"slotTableCurrentChanged(int,int,int,const QPoint&)", &slot_0, QMetaData::Public},
                                        {"slotTableSelectionChanged()", &slot_1, QMetaData::Protected},
                                        {"slotBtnOKClicked()", &slot_2, QMetaData::Protected},
                                        {"slotBtnCancelClicked()", &slot_3, QMetaData::Protected}
                                      };
  static const QUParameter param_signal_0[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod signal_0 = {"name", 1, param_signal_0};
  static const QMetaData signal_tbl[] = {
                                          {"name(QString&)", &signal_0, QMetaData::Public}
                                        };
  metaObj = QMetaObject::new_metaobject(
              "ReactionsWidget", parentObject,
              slot_tbl, 4,
              signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_ReactionsWidget.setMetaObject(metaObj);
  return metaObj;
}

void* ReactionsWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "ReactionsWidget")) return (ReactionsWidget*)this;
  return QWidget::qt_cast(clname);
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL name
void ReactionsWidget::name(QString& t0)
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

bool ReactionsWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: slotTableCurrentChanged(static_QUType_int.get(_o + 1), static_QUType_int.get(_o + 2), static_QUType_int.get(_o + 3), *((QPoint*)static_QUType_ptr.get(_o + 4))); break;
    case 1: slotTableSelectionChanged(); break;
    case 2: slotBtnOKClicked(); break;
    case 3: slotBtnCancelClicked(); break;
    default:
      return QWidget::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool ReactionsWidget::qt_emit(int _id, QUObject* _o)
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

bool ReactionsWidget::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
