#ifndef QEFFECT_DESCRIPTION_EDIT_H
#define QEFFECT_DESCRIPTION_EDIT_H

#include <qlayout/ui_qeffectdescriptionedit.h>

class QEffectDescription;
class QEffectDescriptionEdit : public QWidget, public Ui::QEffectDescriptionEdit
{
  Q_OBJECT
public: 
  QEffectDescriptionEdit(QWidget* parent = 0, Qt::WindowFlags f = 0);
  ~QEffectDescriptionEdit();
  void initFrom(const QEffectDescription* other, bool multiple=false);
  void saveTo(QEffectDescription* other, bool multiple=false);
  QEffectDescription* toDescription() const;

  public slots:
    void slotModeChanged();
    void slotScaleEndChanged(QString);
    void slotScaleStartChanged(QString);
    void slotSelectObject();
    void slotSelectColorEnd();
    void slotSelectColorStart();
protected: 
  QEffectDescription* mpCurrent; 
};

#endif //QEFFECT_DESCRIPTION_EDIT_H