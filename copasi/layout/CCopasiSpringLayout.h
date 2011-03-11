// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CCopasiSpringLayout.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/03/11 21:21:14 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCopasiSpringLayout_H
#define CCopasiSpringLayout_H

#include <map>

#include "CAbstractLayoutInterface.h"
#include "math.h"


#include "CLBase.h"
class CLayout;
class CLGraphicalObject;
class CLCompartmentGlyph;
class CLMetabGlyph;
class CLReactionGlyph;
class CLMetabReferenceGlyph;

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
   * if all participants of a reaction are in a single compartment return the compartment
   * glyph, otherwise return NULL
   */
  CLCompartmentGlyph* findCompartmentForReactionNode(CLReactionGlyph & r);

protected:

  /// performs all initializations that are later needed to calculate the potential
  bool initFromLayout(CLayout* layout);


  ///create variables for size and position of a compartment glyph
  void addCompartmentVariables(CLCompartmentGlyph* cg);

  ///create variables for the position of a species glyph
  void addSpeciesVariables(CLMetabGlyph* mg);

  ///create variables for the position of a reaction glyph
  void addReactionVariables(CLReactionGlyph* rg);

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
  double potSpeciesReaction(const CLMetabGlyph & a, const CLReactionGlyph & b) const;
  double potReactionReaction(const CLReactionGlyph & a, const CLReactionGlyph & b) const;
  double potEdge(const CLMetabReferenceGlyph & e, const CLReactionGlyph & r) const;
  //double potReaction(const CLReactionGlyph & r) const;
  double potSpeciesCompartment(const CLMetabGlyph & s, const CLCompartmentGlyph & c) const;
  double potReactionCompartment(const CLReactionGlyph & r, const CLCompartmentGlyph & c) const;
  //double potCompartmentCompartment(const CLCompartmentGlyph & c1, const CLCompartmentGlyph & c2) const;

  /**
   * calculate a point just outside the bounding box of a given graphical object
   * on the line between the center of the object and the point p.
   * d specifies the distance from the border of the object.
   */
  CLPoint borderProjection(CLGraphicalObject* go, const CLPoint & p, double d);

  CLayout* mpLayout;

  std::vector<double> mInitialState;

  ///this describes one update action that has to be performed during setState()
  struct UpdateAction
  {
    enum Update_Enum
    {
      COMPARTMENT_4V,
      SPECIES_2V,
      REACTION_2V
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

  ///this map contains information about the compartment glyph a given glyph is located in
  std::map<CLBase*, CLCompartmentGlyph*> mCompartmentMap;

  /**
   * this struct describes a constant relation between two graphical objects.
   * It can be used to specify that a text glyph always has a certain position relativ to another object
   */
  struct CoordinateRelation
  {
    const CLGraphicalObject * source;
    CLGraphicalObject * target;
    CLPoint diff;
  };

  /// a list of fixed positon relations between objects. Should be constructed in initFromLayout()
  std::vector<CoordinateRelation> mFixedRelations;
};

#endif // CCopasiSpringLayout_H
