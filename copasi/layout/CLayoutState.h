// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef C_LAYOUT_STATE_H
#define C_LAYOUT_STATE_H

#include <map>
#include <string>

class CLayout;
class CLBoundingBox;
class CLCurve;

class CLayoutState
{
public:
  CLayoutState(const CLayout* layout);
  virtual ~CLayoutState();

  void applyTo(CLayout *layout) const;

  static void tagLayout(CLayout* layout);

protected:
  typedef std::map<const std::string, CLBoundingBox*> StringBoundMap;
  typedef std::map<const std::string, CLCurve*> StringCurveMap;
  std::map<const std::string, CLBoundingBox*> mAdditionalState;
  std::map<const std::string, CLBoundingBox*> mCompartmentState;
  std::map<const std::string, CLBoundingBox*> mReactionState;
  std::map<const std::string, CLBoundingBox*> mSpeciesState;
  std::map<const std::string, CLBoundingBox*> mTextState;
  std::map<const std::string, CLCurve*> mCurves;
};

#endif //C_LAYOUT_STATE_H
