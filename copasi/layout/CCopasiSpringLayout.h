// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CCopasiSpringLayout.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/11/26 16:37:18 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCopasiSpringLayout_H
#define CCopasiSpringLayout_H

#include <map>

#include "CAbstractLayoutInterface.h"
#include "math.h"



class CLBase;
class CLayout;
class CLCompartmentGlyph;
class CLMetabGlyph;

/**
 * This class defines how a layout optimization algorithm will see a COPASI
 * layout, using a spring approach.
 * No copy of the layout will be generated, meaning that setState() will
 * change the layout.
 */
class CCopasiSpringLayout : public CAbstractLayoutInterface
{
public:

  /**
   * generate a spring layout view of a COPASI layout.
   */
  CCopasiSpringLayout(CLayout* layout);

  /**
   * generates the list of variables from the layout. This method will generate
   * variables for the coordinates of all the nodes in the layout.
   * TODO: make it possible to only auto-layout a subset of the graph
   */
  bool createVariables();

  /**
   * updates the COPASI layout from the state vector. Only the updates
   * that are needed for the calculation of the potential (or for a rough
   * on the fly drawing) are done.
   */
  virtual bool setState(const std::vector<double> & vars);

  /**
   * complete the update of the layout. This updates the things
   * that are not needed for the calculation of the potential.
   * After calling this method the layout should be ready for drawing
   * or storing
   */
  void finalizeState();


//  virtual bool getState(std::vector<double> & vars);

  virtual double getPotential();
  virtual std::vector<double> getInitialValues();


  /**
   * if the reaction in single compartment, set compartment index,
   * otherwise set it to -1
   */
  //void updateCompartmentInReactionNode(ReactionNode & r);

protected:

  /// performs all initializations that are later needed to calculate the potential
  bool initFromLayout(CLayout* layout);


  ///create variables for size and position of a compartment glyph
  void addCompartmentVariables(CLCompartmentGlyph* cg);

  ///create variables for the position of a species glyph
  void addSpeciesVariables(CLMetabGlyph* mg);

  static inline double distance(const double & x1, const double & y1,
                                const double & x2, const double & y2)
  {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    //return fabs(x1-x2)<fabs(y1-y2)?fabs(y1-y2):fabs(x1-x2);
  }

  static inline double bound_distance(const double & x1, const double & y1,
                                      const double & x2, const double & y2, const double & max)
  {
    //return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //return fabs(x1-x2)<fabs(y1-y2)?fabs(y1-y2):fabs(x1-x2);

    if (fabs(x1 - x2) > max) return max;

    if (fabs(y1 - y2) > max) return max;

    double tmp = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return tmp > max ? max : tmp;
  }

  double potSpeciesSpecies(const CLMetabGlyph & a, const CLMetabGlyph & b) const;
  //double potSpeciesReaction(const SpeciesNode & a, const ReactionNode & b) const;
  //double potReactionReaction(const ReactionNode & a, const ReactionNode & b) const;
  //double potEdge(const Edge & e, const ReactionNode & r) const;
  //double potReaction(const ReactionNode & r) const;
  double potSpeciesCompartment(const CLMetabGlyph & s, const CLCompartmentGlyph & c) const;
  //double potReactionCompartment(const ReactionNode & r, const CompartmentNode & c) const;
  //double potCompartmentCompartment(const CompartmentNode & c1, const CompartmentNode & c2) const;


  CLayout* mpLayout;

  std::vector<double> mInitialState;

  ///this describes one update action that has to be performed during setState()
  struct UpdateAction
  {
    enum Update_Enum
    {
      COMPARTMENT_4V,
      SPECIES_2V
    };

    UpdateAction(Update_Enum action, CLBase* target, int index1 = -1, int index2 = -1, int index3 = -1, int index4 = -1)
        : mAction(action),
        mpTarget(target),
        mIndex1(index1),
        mIndex2(index2),
        mIndex3(index3),
        mIndex4(index4)
    {};

    Update_Enum mAction;
    CLBase* mpTarget;
    int mIndex1;
    int mIndex2;
    int mIndex3;
    int mIndex4;
  };

  ///this is the list of all update actions that have to be performed during setState();
  std::vector<UpdateAction> mUpdateActions;

  std::map<CLBase*, CLCompartmentGlyph*> mCompartmentMap;
};

#endif // CCopasiSpringLayout_H
