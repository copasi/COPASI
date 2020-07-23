// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QEFFECT_DESCRIPTION_H
#define QEFFECT_DESCRIPTION_H

#include <QColor>
#include <string>

#include <copasi/qlayout/CQLayoutScene.h>

/**
 * This class describes a graphic effect to be added on top of a glyph.
 *
 * They represent post processing that is done without having to change the
 * actual structure of the rendering.
 */
class CQEffectDescription
{
public:
  enum Mode
  {
    DropShadow,
    Colorize,
    Scale
  };

  /**
   * Creates a new effect description in scale mode with the specified
   * scale and cn
   *
   * @param cn the cn to a model element (species, reaction ...), this
   *        is not the cn to a value reference!
   *
   * @param startScale start scaling factor to be applied. For example
   *        0.5 would mean that the size would be scaled to twice
   *        what it was minimally
   *
   * @param endScale end scaling factor to be applied. For example
   *        2.0 would mean that the size would be scaled to 200% of
   *        what it was maximally
   *
   * @param dataCN used in case the model element is not the same element
   *        as the one to get the data from. If not specified it will default
   *        to the model element cn.
   */
  CQEffectDescription(const std::string & cn, qreal startScale, qreal endScale, const std::string & dataCN = "");

  /**
   * Creates a new effect description with the given parameters
   *
   * @param cn the cn to a model element (species, reaction ...), this
   *        is not the cn to a value reference!
   *
   * @param mode the mode to be used, defaults to colorize
   *
   * @param startColor the start color to use for the minimal value (defaults to white)
   *
   * @param endColor the end color to be used for the maximal value (defaults to red)
   *
   * @param dataCN used in case the model element is not the same element
   *        as the one to get the data from. If not specified it will default
   *        to the model element cn.
   */
  CQEffectDescription(const std::string & cn, Mode mode = Colorize, const QColor & startColor = Qt::white, const QColor & endColor = Qt::red, const std::string & dataCN = "");

  /**
   * Constructs a new effect with the given model and data cn and mode
   *
   * @param cn the cn to a model element (species, reaction ...), this
   *        is not the cn to a value reference!
   *
   * @param dataCN used in case the model element is not the same element
   *        as the one to get the data from. If not specified it will default
   *        to the model element cn.
   *
   * @param mode the mode to be used, defaults to colorize
   */
  CQEffectDescription(const std::string & cn, const std::string & dataCn, Mode mode = Colorize);

  virtual ~CQEffectDescription();

  /**
   * @return the cn to the model element (species, reaction ...)
   */
  const std::string& getCN()const;

  /**
   * sets the cn to the model element (species, reaction ...)
   *
   * @param cn the cn to set
   */
  void setCN(const std::string& cn);

  /**
   * @return the display name of the element (resolved by CN lookup of the
   * model element cn)
   */
  std::string getDisplayName() const;

  /**
   * @return the cn to the reference element to be mapped (this is where the data comes from)
   */
  const std::string & getDataCN() const;

  /**
   * Set the cn to the element where the data comes from
   * @param a CN that will deliver data to the animation
   */
  void setDataCN(const std::string& cn);

  /**
   * @return the start color
   */
  const QColor& getStartColor() const;

  /**
   * Set the start color
   *
   * @param color the color to be set
   */
  void setStartColor(const QColor& color);

  /**
   * @return the end color
   */
  const QColor& getEndColor() const;

  /**
   * set the end color
   *
   * @param color the color to be set
   */
  void setEndColor(const QColor& color);

  /**
   * @return the start scale, this is what the minimal value will be assigned to. (i.e 0.5 to scale a glyph down to 50%)
   */
  qreal getScaleStart() const;

  /**
   * Sets the start scale
   *
   * @param scale the start scale to be used
   */
  void setScaleStart(qreal scale);

  /**
   * @return the end scale, this is what the maximal element will be assigned to
   */
  qreal getScaleEnd() const;

  /**
   * sets the end scale
   *
   * @param scale the end scale to be used
   */
  void setScaleEnd(qreal scale);

  /**
   * @return the model that this effect uses.
   */
  Mode getMode() const;

  /**
   * Sets the mode for this effect
   *
   * @param mode the mode to be used.
   */
  void setMode(Mode mode);

  /**
   * removes the effect from the scene
   */
  virtual void removeFromScene(CQLayoutScene& scene);

  /**
   * applies the effect to the scene with the given scale
   */
  void applyToScene(CQLayoutScene& scene, qreal t);

protected:
  std::string mElementCN;
  std::string mDataCN;
  QColor mStartColor;
  QColor mEndColor;
  qreal  mScaleStart;
  qreal mScaleEnd;
  Mode mMode;
};

#endif // QEFFECT_DESCRIPTION_H
