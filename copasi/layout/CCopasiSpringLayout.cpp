// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <iostream>
#include <map>

#include <copasi/layout/CCopasiSpringLayout.h>
#include <copasi/layout/CLGlyphs.h>
#include <copasi/layout/CLReactionGlyph.h>
#include <copasi/layout/CLayout.h>

#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CMetab.h>

#include <copasi/randomGenerator/CRandom.h>

/*

void CCopasiSpringLayout::ReactionNode::updateFromState(const std::vector<double> & vars, CCopasiSpringLayout * li)
{
  if (a != -1) //the node has to get its state itself
  {
    x = vars[a];
    y = vars[b];
  }

  //here we could add other updates that need to be done when the state was changed

  //the angle is for now calculated. It may be a state variable in the future
  //first the substrates
  double sx=0; double sy=0; unsigned int count=0;
  unsigned int i, imax=mEdges.size();
  for (i=0; i<imax; ++i)
    if (mEdges[i].role==Edge::SUBSTRATE)
    {
      sx+=li->mSpeciesNodes[mEdges[i].sindex].x;
      sy+=li->mSpeciesNodes[mEdges[i].sindex].y;
      ++count;
    }
  if (count) sx /= count; else sx=x;
  if (count) sy /= count; else sy=y;

  double px=0; double py=0; count=0;
  for (i=0; i<imax; ++i)
    if (mEdges[i].role==Edge::PRODUCT)
    {
      px+=li->mSpeciesNodes[mEdges[i].sindex].x;
      py+=li->mSpeciesNodes[mEdges[i].sindex].y;
      ++count;
    }
  if (count) px /= count; else px=x;
  if (count) py /= count; else py=y;

  double l = sqrt((px-sx)*(px-sx)+(py-sy)*(py-sy));
  if (l==0)
    {dx=1; dy=0;}
  else
  {
    dx = (px-sx)/l;
    dy = (py-sy)/l;
  }

  //angle
}
 */

//*******************************************

CCopasiSpringLayout::CCopasiSpringLayout(CLayout* layout, Parameters* ppp)
  : mpLayout(NULL)
{
  if (ppp == NULL)
    {
      // backward compatible
      ppp = new Parameters();
    }

  initFromLayout(layout, ppp);
}

bool CCopasiSpringLayout::initFromLayout(CLayout* layout, Parameters* ppp)
{
  mpLayout = layout;
  mpPar = ppp;

  if (!mpLayout) return false;

  if (!ppp) return false;

  mCompartmentMap.clear();

  //store the compartment glyph for each species glyph (if it exists)
  unsigned int i;

  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size() ; ++i)
    {
      CMetab* metab = dynamic_cast<CMetab*>(mpLayout->getListOfMetaboliteGlyphs()[i].getModelObject());
      CLCompartmentGlyph*  tmp = NULL;

      if (metab)
        {
          unsigned int j;

          for (j = 0; j < mpLayout->getListOfCompartmentGlyphs().size(); ++j)
            if (mpLayout->getListOfCompartmentGlyphs()[j].getModelObjectKey() == metab->getCompartment()->getKey())
              {
                tmp = &mpLayout->getListOfCompartmentGlyphs()[j];
                break;
              }
        }

      mCompartmentMap[&mpLayout->getListOfMetaboliteGlyphs()[i]] = tmp;
    }

  //store the compartment glyph for each reaction glyph (if it exists)
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      mCompartmentMap[&mpLayout->getListOfReactionGlyphs()[i]] = findCompartmentForReactionNode(mpLayout->getListOfReactionGlyphs()[i]);
    }

  //create the list of constant positional relations
  //we assume that text glyphs are always moved with the glyph they refer to.
  //(i.e. the are not layed out independently)
  mFixedRelations.clear();

  for (i = 0; i < mpLayout->getListOfTextGlyphs().size(); ++i)
    {
      CoordinateRelation tmp;
      tmp.target = &mpLayout->getListOfTextGlyphs()[i];
      tmp.source = mpLayout->getListOfTextGlyphs()[i].getGraphicalObject();

      if (tmp.source)
        {
          tmp.diff = tmp.target->getPosition() - tmp.source->getPosition();
          mFixedRelations.push_back(tmp);
        }
    }

  return true;
}

CLCompartmentGlyph* CCopasiSpringLayout::findCompartmentForReactionNode(CLReactionGlyph & r)
{
  CLCompartmentGlyph*  pCG = NULL;

  //r.compartmentIndex = mSpeciesNodes[r.getEdges()[0].sindex].compartmentIndex;
  unsigned int i;

  for (i = 0; i < r.getListOfMetabReferenceGlyphs().size(); ++i)
    {
      std::map<CLBase*, CLCompartmentGlyph*>::const_iterator mapIt = mCompartmentMap.find(r.getListOfMetabReferenceGlyphs()[i].getMetabGlyph());

      if (mapIt == mCompartmentMap.end())
        {
          //there is no information in the map. Should not happen.
#ifdef COPASI_DEBUG
          std::cout << "No compartment info for a species glyph!!!" << std::endl;
#endif
          continue;
        }

      if (! mapIt->second)
        continue; //the species glyph is not linked to a compartment

      if (!pCG) //this is the first compartment
        {
          pCG = mapIt->second;
          continue;
        }

      if (pCG != mapIt->second) //there are at least two different compartments
        {
          pCG = NULL;
          break;
        }
    }

  return pCG;
}

bool CCopasiSpringLayout::createVariables()
{
  //delete current variables
  mInitialState.clear();
  mVarDescription.clear();
  mMassVector.clear();

  unsigned int i;

  // add variables for the coordinates of all metabs
  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size() ; ++i)
    {
      addPositionVariables(&mpLayout->getListOfMetaboliteGlyphs()[i]);
    }

  // add variables for the coordinates of all reaction glyphs
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      addReactionVariables(&mpLayout->getListOfReactionGlyphs()[i]);
    }

  // add variables for the coordinates of all general glyphs
  for (i = 0; i < mpLayout->getListOfGeneralGlyphs().size() ; ++i)
    {
      addPositionVariables(&mpLayout->getListOfGeneralGlyphs()[i]);
    }

  // add variables for text glyphs that are not fixed to anything.
  //TODO

  return true;
}

void CCopasiSpringLayout::addCompartmentVariables(CLCompartmentGlyph* cg)
{
  if (!cg)
    return;

  VariableDescription desc;
  desc.isAngle = false;

  int first_index = mInitialState.size();

  //x position
  mInitialState.push_back(cg->getX());
  mVarDescription.push_back(desc);
  mMassVector.push_back(0.01);

  //y position
  mInitialState.push_back(cg->getY());
  mVarDescription.push_back(desc);
  mMassVector.push_back(0.01);

  //width
  mInitialState.push_back(cg->getWidth());
  mVarDescription.push_back(desc);
  mMassVector.push_back(0.01);

  //height
  mInitialState.push_back(cg->getHeight());
  mVarDescription.push_back(desc);
  mMassVector.push_back(0.01);

  mUpdateActions.push_back(UpdateAction(UpdateAction::COMPARTMENT_4V, cg, first_index, first_index + 1, first_index + 2, first_index + 3));
}

void CCopasiSpringLayout::addPositionVariables(CLGraphicalObject* pGO)
{
  if (!pGO)
    return;

  bool side = false; //TODO: find out if it is a side reactant

  VariableDescription desc;
  desc.isAngle = false;

  int first_index = mInitialState.size();

  //x position
  mInitialState.push_back(pGO->getX());
  mVarDescription.push_back(desc);
  mMassVector.push_back(side ? 0.1 : 1.0);

  //y position
  mInitialState.push_back(pGO->getY());
  mVarDescription.push_back(desc);
  mMassVector.push_back(side ? 0.1 : 1.0);

  mUpdateActions.push_back(UpdateAction(UpdateAction::POSITION_2V, pGO, first_index, first_index + 1));
}

void CCopasiSpringLayout::addReactionVariables(CLReactionGlyph* rg)
{
  if (!rg)
    return;

  VariableDescription desc;
  desc.isAngle = false;

  int first_index = mInitialState.size();

  C_FLOAT64 xxx, yyy;

  //first look if the glyph is described by a curve
  if (rg->getCurve().getNumCurveSegments())
    {
      unsigned int numsegs = rg->getCurve().getNumCurveSegments();
      xxx = 0.5 * (rg->getCurve().getCurveSegments()[0].getStart().getX()
                   + rg->getCurve().getCurveSegments()[numsegs - 1].getEnd().getX());
      yyy = 0.5 * (rg->getCurve().getCurveSegments()[0].getStart().getY()
                   + rg->getCurve().getCurveSegments()[numsegs - 1].getEnd().getY());
    }
  else
    {
      xxx = rg->getX() + 0.5 * rg->getWidth();
      yyy = rg->getY() + 0.5 * rg->getHeight();
    }

  //x position
  mInitialState.push_back(xxx);
  mVarDescription.push_back(desc);
  mMassVector.push_back(1.0);

  //y position
  mInitialState.push_back(yyy);
  mVarDescription.push_back(desc);
  mMassVector.push_back(1.0);

  mUpdateActions.push_back(UpdateAction(UpdateAction::REACTION_2V, rg, first_index, first_index + 1));
}

bool CCopasiSpringLayout::setState(const std::vector<double> & vars)
{
  if (vars.size() < mVarDescription.size())
    return false;

  std::vector<UpdateAction>::const_iterator it, itEnd = mUpdateActions.end();

  for (it = mUpdateActions.begin(); it != itEnd; ++it)
    {
      switch (it->mAction)
        {
          case UpdateAction::COMPARTMENT_4V:
            ((CLCompartmentGlyph*)(it->mpTarget))->setX(vars[it->mIndex1]);
            ((CLCompartmentGlyph*)(it->mpTarget))->setY(vars[it->mIndex2]);
            ((CLCompartmentGlyph*)(it->mpTarget))->setWidth(vars[it->mIndex3]);
            ((CLCompartmentGlyph*)(it->mpTarget))->setHeight(vars[it->mIndex4]);
            break;

          case UpdateAction::POSITION_2V:
            ((CLGraphicalObject*)(it->mpTarget))->setX(vars[it->mIndex1]);
            ((CLGraphicalObject*)(it->mpTarget))->setY(vars[it->mIndex2]);
            break;

          case UpdateAction::REACTION_2V:
            ((CLReactionGlyph*)(it->mpTarget))->setX(vars[it->mIndex1]);
            ((CLReactionGlyph*)(it->mpTarget))->setY(vars[it->mIndex2]);
            break;

          default:
#ifdef COPASI_DEBUG
            std::cout << "Unknown Action!!!" << std::endl;
#endif
            break;
        };
    }

  //If we assume that the position of the dependent (text) glyphs can have an influence
  //on the layout we need to update them here.
  //Currently we assume that is not the case and the update will be done in finalizeState();

  return true;
}

void CCopasiSpringLayout::finalizeState()
{
  unsigned int i;

  //update the positions of the dependent glyphs
  //this can be done here since we assume that those glyphs
  //do not affect the layout.
  updateFixedRelations();

  //for now, only create curves for the reaction glyphs
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      CLReactionGlyph* pRG = &mpLayout->getListOfReactionGlyphs()[i];

      //Determine the average position of substrates and products, giving less weight to side reactants
      CLPoint s, p;
      double s_c = 0; double p_c = 0;
      unsigned int j, jmax = pRG->getListOfMetabReferenceGlyphs().size();

      for (j = 0; j < jmax; ++j)
        {
          if (pRG->getListOfMetabReferenceGlyphs()[j].getFunctionalRole() == CLMetabReferenceGlyph::SUBSTRATE)
            {
              CLMetabGlyph* metabGlyph = pRG->getListOfMetabReferenceGlyphs()[j].getMetabGlyph();

              if (metabGlyph != NULL)
                {
                  s_c += 1.0;
                  s = s + metabGlyph->getBoundingBox().getCenter();
                }
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j].getFunctionalRole() == CLMetabReferenceGlyph::SIDESUBSTRATE)
            {
              CLMetabGlyph* metabGlyph = pRG->getListOfMetabReferenceGlyphs()[j].getMetabGlyph();

              if (metabGlyph != NULL)
                {
                  s_c += 0.1;
                  s = s + metabGlyph->getBoundingBox().getCenter() * 0.1;
                }
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j].getFunctionalRole() == CLMetabReferenceGlyph::PRODUCT)
            {
              CLMetabGlyph* metabGlyph = pRG->getListOfMetabReferenceGlyphs()[j].getMetabGlyph();

              if (metabGlyph != NULL)
                {
                  p_c += 1.0;
                  p = p + metabGlyph->getBoundingBox().getCenter();
                }
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j].getFunctionalRole() == CLMetabReferenceGlyph::SIDEPRODUCT)
            {
              CLMetabGlyph* metabGlyph = pRG->getListOfMetabReferenceGlyphs()[j].getMetabGlyph();

              if (metabGlyph != NULL)
                {

                  p_c += 0.1;
                  p = p + metabGlyph->getBoundingBox().getCenter() * 0.1;
                }
            }
        }

      CLPoint position = pRG->getPosition();

      if (position.getX() == 0 && position.getY() == 0
          && pRG->getDimensions().getWidth() == 0
          && pRG->getDimensions().getHeight() == 0
          && pRG->getCurve().getNumCurveSegments() > 0)
        {
          position = pRG->getCurve().getCurveSegments()[0].getStart();
          pRG->setPosition(position);
        }

      if (s_c > 0)
        s = s * (1 / s_c);
      else
        {
          s = position;
        }

      if (p_c > 0)
        p = p * (1 / p_c);
      else
        p = position;

      CLPoint dir = p - s; //overall direction of reaction

      if (dir.getX() == 0 && dir.getY() == 0)
        dir = CLPoint(1, 0);

      CLPoint ortho_dir = CLPoint(dir.getY(), -dir.getX());
      ortho_dir.scale(1 / sqrt(pow(ortho_dir.getX(), 2) + pow(ortho_dir.getY(), 2)));

      CLPoint reaction_s = position - (dir * 0.05);
      CLPoint reaction_p = position + (dir * 0.05);
      CLPoint reaction_m1 = position + ortho_dir * 10;
      CLPoint reaction_m2 = position - ortho_dir * 10;

      pRG->getCurve().clear();
      pRG->getCurve().addCurveSegment(CLLineSegment(reaction_s, reaction_p));

      for (j = 0; j < jmax; ++j)
        {
          //here we need to generate the curves for the MetabReferenceGlyphs.
          //we will need to consider the size of the glyphs, role of the metab in the reaction, etc.
          //For now, only a primitive implementation: TODO: improve
          CLMetabReferenceGlyph* pMRG = &pRG->getListOfMetabReferenceGlyphs()[j];
          double direction;
          //double modifierLength = -0.2;

          switch (pMRG->getFunctionalRole())
            {
              case CLMetabReferenceGlyph::SUBSTRATE :
              case CLMetabReferenceGlyph::SIDESUBSTRATE :
              {
                direction = -0.1;
                CLPoint metabPoint = borderProjection(pMRG->getMetabGlyph(), reaction_s + dir * direction /*(modifierLength * 1.5)*/, 5);
                pMRG->getCurve().clear();
                pMRG->getCurve().addCurveSegment(CLLineSegment(reaction_s,
                                                 metabPoint,
                                                 reaction_s + dir * direction,
                                                 (reaction_s + dir * (direction * 1.5) + metabPoint) * 0.5));
              }
              break;

              case CLMetabReferenceGlyph::PRODUCT :
              case CLMetabReferenceGlyph::SIDEPRODUCT :
              {
                direction = 0.1;
                CLPoint metabPoint = borderProjection(pMRG->getMetabGlyph(), reaction_p + dir * direction /*(modifierLength * 1.5)*/, 5);
                pMRG->getCurve().clear();
                pMRG->getCurve().addCurveSegment(CLLineSegment(reaction_p,
                                                 metabPoint,
                                                 reaction_p + dir * direction,
                                                 (reaction_p + dir * (direction * 1.5) + metabPoint) * 0.5));
              }
              break;

              default:
              {
                CLPoint reactionPoint;

                if (pMRG->getMetabGlyph() && ortho_dir.dot(pRG->getPosition() - pMRG->getMetabGlyph()->getPosition()) < 0)
                  {
                    direction = +10.0;
                    reactionPoint = reaction_m1;
                  }
                else
                  {
                    direction = -10.0;
                    reactionPoint = reaction_m2;
                  }

                CLPoint metabPoint = borderProjection(pMRG->getMetabGlyph(), reactionPoint + dir * 0 * direction /*(modifierLength * 1.5)*/, 5);
                pMRG->getCurve().clear();
                pMRG->getCurve().addCurveSegment(CLLineSegment(metabPoint,
                                                 reactionPoint,
                                                 (reactionPoint + dir * (0 * direction * 1.5) + metabPoint) * 0.5,
                                                 reactionPoint + ortho_dir * direction));
              }
            }
        }
    }

  //update the curves in the general glyph
  for (i = 0; i < mpLayout->getListOfGeneralGlyphs().size() ; ++i)
    {
      CLGeneralGlyph* pGG = &mpLayout->getListOfGeneralGlyphs()[i];

      size_t j;

      for (j = 0; j < pGG->getListOfReferenceGlyphs().size(); ++j)
        {
          CLReferenceGlyph* pRG = &pGG->getListOfReferenceGlyphs()[j];

          if (pRG->getCurve().getNumCurveSegments() == 0) continue;

          CLPoint refPoint = borderProjection(pRG->getTargetGlyph(), pRG->getBoundingBox().getCenter(), 5);
          pRG->getCurve().clear();
          pRG->getCurve().addCurveSegment(CLLineSegment(refPoint, pRG->getBoundingBox().getCenter()));
        }
    }

  //calculate bounding box for the layout, or recenter the layout
  mpLayout->calculateAndAssignBounds();
}

void CCopasiSpringLayout::updateFixedRelations()
{
  std::vector<CoordinateRelation>::const_iterator it, itEnd = mFixedRelations.end();

  for (it = mFixedRelations.begin(); it != itEnd; ++it)
    it->target->setPosition(it->source->getPosition() + it->diff);
}

CLPoint CCopasiSpringLayout::borderProjection(CLGraphicalObject* go, const CLPoint & p, double d)
{
  if (go == NULL)
    return p;

  CLPoint center = go->getBoundingBox().getCenter();
  CLPoint diff = p - center;

  CLPoint ret;

  if (fabs(diff.getX()) * (fabs(go->getHeight()) * 0.5 + d) > fabs(diff.getY()) * (fabs(go->getWidth()) * 0.5 + d))
    {
      double f = (fabs(go->getWidth()) * 0.5 + d) / fabs(diff.getX());
      ret = center + diff * f;
    }
  else
    {
      double f = (fabs(go->getHeight()) * 0.5 + d) / fabs(diff.getY());
      ret = center + diff * f;
    }

  return ret;
}

//*************************************

double CCopasiSpringLayout::potSpeciesSpecies(const CLMetabGlyph & a, const CLMetabGlyph & b) const
{
  double tmp;
  tmp = bound_distance(a.getX() + a.getWidth() / 2, a.getY() + a.getHeight() / 2,
                       b.getX() + b.getWidth() / 2, b.getY() + b.getHeight() / 2, 200);

  if (tmp < 1) tmp = 1;

  return /*a.charge*b.charge*/ 1 / tmp; //TODO: reintroduce the charge
}

double CCopasiSpringLayout::potSpeciesReaction(const CLMetabGlyph & a, const CLReactionGlyph & b) const
{
  double tmp = bound_distance(a.getX() + a.getWidth() / 2, a.getY() + a.getHeight() / 2,
                              b.getX() + b.getWidth() / 2, b.getY() + b.getHeight() / 2, 200);

  if (tmp < 1) tmp = 1;

  return /*a.charge*b.charge*/ 1 / tmp; //TODO: reintroduce the charge
}

double CCopasiSpringLayout::potReactionReaction(const CLReactionGlyph & a, const CLReactionGlyph & b) const
{
  double tmp = bound_distance(a.getX() + a.getWidth() / 2, a.getY() + a.getHeight() / 2,
                              b.getX() + b.getWidth() / 2, b.getY() + b.getHeight() / 2, 200);

  if (tmp < 1) tmp = 1;

  return /*a.charge*b.charge*/ 1 / tmp; //TODO: reintroduce the charge
}

double CCopasiSpringLayout::potEdge(const CLMetabReferenceGlyph & e, const CLReactionGlyph & r) const
{
  double dist = mpPar->values[1];

  if (e.getRole() == CLMetabReferenceGlyph::SIDESUBSTRATE || e.getRole() == CLMetabReferenceGlyph::SIDEPRODUCT)
    dist = mpPar->values[3];

  const CLMetabGlyph * pMG = e.getMetabGlyph();

  if (pMG == NULL)
    return 0;

  double tmp = distance(pMG->getX() + pMG->getWidth() / 2, pMG->getY() + pMG->getHeight() / 2,
                        r.getX() + r.getWidth() / 2, r.getY() + r.getHeight() / 2);

  if (e.getRole() == CLMetabReferenceGlyph::MODIFIER)
    return mpPar->values[4] * pow(tmp - dist, 2);
  else
    return mpPar->values[2] * pow(tmp - dist, 2);
}

double CCopasiSpringLayout::potSecondOrderEdge(const CLMetabReferenceGlyph & e1, const CLMetabReferenceGlyph & e2, double & dist) const
{
  const CLMetabGlyph * pMG1 = e1.getMetabGlyph();
  const CLMetabGlyph * pMG2 = e2.getMetabGlyph();

  if (pMG1 == NULL || pMG2 == NULL)
    return 0;

  double tmp = distance(pMG1->getX() + pMG1->getWidth() / 2, pMG1->getY() + pMG1->getHeight() / 2,
                        pMG2->getX() + pMG2->getWidth() / 2, pMG2->getY() + pMG2->getHeight() / 2);

  return pow(tmp - dist, 2);
}

double CCopasiSpringLayout::potGeneralEdge(const CLReferenceGlyph & e, const CLGeneralGlyph & r) const
{
  double dist = 30;

  const CLGraphicalObject * pMG = e.getTargetGlyph();

  if (pMG == NULL)
    return 0.0;

  double tmp = distance(pMG->getX() + pMG->getWidth() / 2, pMG->getY() + pMG->getHeight() / 2,
                        r.getX() + r.getWidth() / 2, r.getY() + r.getHeight() / 2);

  return pow(tmp - dist, 2);
}

/*

double CCopasiSpringLayout::potReaction(const ReactionNode & r) const
{
  double ret=0;

  double r_angle=r.dy>0?acos(r.dx):-acos(r.dx);

  unsigned int i, imax=r.getEdges().size();
  for (i=0; i<imax; ++i)
  {
    double s_angle = (mSpeciesNodes[r.getEdges()[i].sindex].x-r.x)>0
                       ? atan((mSpeciesNodes[r.getEdges()[i].sindex].y-r.y)/(mSpeciesNodes[r.getEdges()[i].sindex].x-r.x))
                       : 3.1415+atan((mSpeciesNodes[r.getEdges()[i].sindex].y-r.y)/(mSpeciesNodes[r.getEdges()[i].sindex].x-r.x))
                     ;

    if (r.getEdges()[i].role==Edge::SUBSTRATE)
    {
      ret+=cos(s_angle-r_angle);
    }
    if (r.getEdges()[i].role==Edge::PRODUCT)
    {
      ret-=cos(s_angle-r_angle);
    }
    if (r.getEdges()[i].role==Edge::MODIFIER)
    {
      ret+=cos(2*(s_angle-r_angle));
    }
  }
 */
/*  for (i=0; i<imax; ++i)
  {
    if (r.getEdges()[i].role==Edge::SUBSTRATE)
    {
      ret+=(mSpeciesNodes[r.getEdges()[i].sindex].x-r.x)*r.dx
           +(mSpeciesNodes[r.getEdges()[i].sindex].y-r.y)*r.dy;
    }
    if (r.getEdges()[i].role==Edge::PRODUCT)
    {
      ret+=-(mSpeciesNodes[r.getEdges()[i].sindex].x-r.x)*r.dx
           -(mSpeciesNodes[r.getEdges()[i].sindex].y-r.y)*r.dy;
    }
  }*/

/*
  return ret;
}

 */
double CCopasiSpringLayout::potSpeciesCompartment(const CLMetabGlyph & s, const CLCompartmentGlyph & c) const
{
  double tmp = 0;
  double dist = fabs((s.getX() + 0.5 * s.getWidth()) - (c.getX() + 0.5 * c.getWidth()));

  if (dist > (0.5 * c.getWidth() - 50))
    tmp += pow(dist - 0.5 * c.getWidth() + 50, 2);

  dist = fabs((s.getY() + 0.5 * s.getHeight()) - (c.getY() + 0.5 * c.getHeight()));

  if (dist > (0.5 * c.getHeight() - 50))
    tmp += pow(dist - 0.5 * c.getHeight() + 50, 2);

  return tmp /**s.charge*/; //TODO reintroduce charge
}

double CCopasiSpringLayout::potReactionCompartment(const CLReactionGlyph & r, const CLCompartmentGlyph & c) const
{
  double tmp = 0;
  double dist = fabs((r.getX() + 0.5 * r.getWidth()) - (c.getX() + 0.5 * c.getWidth()));

  if (dist > (0.5 * c.getWidth() - 50))
    tmp += pow(dist - 0.5 * c.getWidth() + 50, 2);

  dist = fabs((r.getY() + 0.5 * r.getHeight()) - (c.getY() + 0.5 * c.getHeight()));

  if (dist > (0.5 * c.getHeight() - 50))
    tmp += pow(dist - 0.5 * c.getHeight() + 50, 2);

  return tmp /**s.charge*/; //TODO reintroduce charge
}

/*

double CCopasiSpringLayout::potCompartmentCompartment(const CLCompartmentGlyph & c1, const CLCompartmentGlyph & c2) const
{
  double tmp=0;
  double distx=fabs(c1.x-c2.x) - (0.5*c1.w + 0.5*c2.w+20);
  double disty=fabs(c1.y-c2.y) - (0.5*c1.h + 0.5*c2.h+20);
  double dist = distx > disty ? distx : disty;

  if (dist < 0)
    tmp+= -dist;
  return tmp;
}
 */

double CCopasiSpringLayout::getPotential()
{
  //here we need to add the different effects that contribute to the potential

  double tmp = 0;

  //repulsion between species nodes
  unsigned int i, j;

  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size() - 1; ++i)
    for (j = i + 1; j < mpLayout->getListOfMetaboliteGlyphs().size(); ++j)
      {
        if (i != j)
          tmp += mpPar->values[0] * potSpeciesSpecies(mpLayout->getListOfMetaboliteGlyphs()[i], mpLayout->getListOfMetaboliteGlyphs()[j]);
      }

  // only if we have reactions!
  if (mpLayout->getListOfReactionGlyphs().size() > 0)
    {
      //repulsion between species nodes and reaction nodes
      for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size(); ++i)
        for (j = 0; j < mpLayout->getListOfReactionGlyphs().size(); ++j)
          {
            tmp += mpPar->values[0] * potSpeciesReaction(mpLayout->getListOfMetaboliteGlyphs()[i], mpLayout->getListOfReactionGlyphs()[j]);
          }

      //repulsion between reaction nodes
      for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() - 1; ++i)
        for (j = i + 1; j < mpLayout->getListOfReactionGlyphs().size(); ++j)
          {
            if (i != j)
              tmp += mpPar->values[0] * potReactionReaction(mpLayout->getListOfReactionGlyphs()[i], mpLayout->getListOfReactionGlyphs()[j]);
          }
    }

  //spring force for species references
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* pRG = &mpLayout->getListOfReactionGlyphs()[i];

      for (j = 0; j < pRG->getListOfMetabReferenceGlyphs().size(); ++j)
        {
          tmp += potEdge(pRG->getListOfMetabReferenceGlyphs()[j], *pRG);

          //second order
          CLMetabReferenceGlyph::Role role = pRG->getListOfMetabReferenceGlyphs()[j].getFunctionalRole();

          if (role != CLMetabReferenceGlyph::SUBSTRATE && role != CLMetabReferenceGlyph::SIDESUBSTRATE)
            continue;

          double dist = role == CLMetabReferenceGlyph::SUBSTRATE ? mpPar->values[1] : mpPar->values[3];
          size_t k;

          for (k = 0; k < pRG->getListOfMetabReferenceGlyphs().size(); ++k)
            {
              CLMetabReferenceGlyph::Role role2 = pRG->getListOfMetabReferenceGlyphs()[k].getFunctionalRole();

              if (role2 != CLMetabReferenceGlyph::PRODUCT && role2 != CLMetabReferenceGlyph::SIDEPRODUCT)
                continue;

              dist += role2 == CLMetabReferenceGlyph::PRODUCT ? mpPar->values[1] : mpPar->values[3];

              tmp += mpPar->values[5] * potSecondOrderEdge(pRG->getListOfMetabReferenceGlyphs()[j], pRG->getListOfMetabReferenceGlyphs()[k], dist);
            }
        }
    }

  for (i = 0; i < mpLayout->getListOfGeneralGlyphs().size(); ++i)
    {
      CLGeneralGlyph* pRG = &mpLayout->getListOfGeneralGlyphs()[i];

      for (j = 0; j < pRG->getListOfReferenceGlyphs().size(); ++j)
        {
          tmp += potGeneralEdge(pRG->getListOfReferenceGlyphs()[j], *pRG);
        }
    }

  /*
      //forces at reaction nodes
      for (i=0; i<mReactionNodes.size(); ++i)
        {
          tmp += 3000* potReaction(mReactionNodes[i]);
        }
  */

  //force to keep species in compartment
  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size(); ++i)
    {
      CLMetabGlyph* tmpMG = &mpLayout->getListOfMetaboliteGlyphs()[i];
      std::map<CLBase*, CLCompartmentGlyph*>::const_iterator mapIt = mCompartmentMap.find(tmpMG);

      if (mapIt == mCompartmentMap.end())
        {
          //there is no information in the map. Should not happen.
#ifdef COPASI_DEBUG
          std::cout << "No compartment info for a species glyph!!!" << std::endl;
#endif
          continue;
        }

      CLCompartmentGlyph* tmpCG = mapIt->second;

      if (tmpCG) //the species glyph is inside a compartment glyph
        tmp +=  mpPar->values[6] * potSpeciesCompartment(*tmpMG, *tmpCG);
    }

  //force to keep reaction nodes in compartment
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* tmpRG = &mpLayout->getListOfReactionGlyphs()[i];
      std::map<CLBase*, CLCompartmentGlyph*>::const_iterator mapIt = mCompartmentMap.find(tmpRG);

      if (mapIt == mCompartmentMap.end())
        {
          //there is no information in the map. Should not happen.
#ifdef COPASI_DEBUG
          std::cout << "No compartment info for a reaction glyph!!!" << std::endl;
#endif
          continue;
        }

      CLCompartmentGlyph* tmpCG = mapIt->second;

      if (tmpCG) //the reaction glyph is inside a compartment glyph
        tmp += mpPar->values[7] * potReactionCompartment(*tmpRG, *tmpCG);
    }

  /*

    //force to shrink compartments
    for (i=0; i<mCompartmentNodes.size(); ++i)
      {
        tmp += 0.2*(fabs(mCompartmentNodes[i].w-100)+fabs(mCompartmentNodes[i].h-100));
      }

    //repulsion between compartments
    for (i=0; i<mCompartmentNodes.size(); ++i)
    for (j=0; j<mCompartmentNodes.size(); ++j)
      {
        if (i!=j)
          tmp += 100*potCompartmentCompartment(mCompartmentNodes[i], mCompartmentNodes[j]);
      }

    //centering force
    for (i=0; i<mCompartmentNodes.size(); ++i)
      {
        tmp += 10*(fabs(mCompartmentNodes[i].x)+fabs(mCompartmentNodes[i].y));
      }
    */
  return tmp;
}

const std::vector<double> & CCopasiSpringLayout::getInitialValues() const
{
  return mInitialState;
}

const std::vector<CCopasiSpringLayout::UpdateAction>& CCopasiSpringLayout::getUpdateActions() const
{
  return mUpdateActions;
}

void randomlyPlaceGlyphInCompartmentGlyph(CLGraphicalObject* pGl, const CLGraphicalObject* pContainer, CRandom *pRandom)
{
  double x = pContainer->getPosition().getX()
             + pRandom->getRandomCC() * (pContainer->getDimensions().getWidth() - pGl->getDimensions().getWidth());
  double y = pContainer->getPosition().getY()
             + pRandom->getRandomCC() * (pContainer->getDimensions().getHeight() - pGl->getDimensions().getHeight());
  pGl->setPosition(CLPoint(x, y));
}

void randomlyPlaceGlyphInDimensions(CLGraphicalObject* pGl, const CLDimensions* pContainer, CRandom *pRandom)
{
  double x = pRandom->getRandomCC() * (pContainer->getWidth() - pGl->getDimensions().getWidth());
  double y = pRandom->getRandomCC() * (pContainer->getHeight() - pGl->getDimensions().getHeight());
  pGl->setPosition(CLPoint(x, y));
}

void placeTextGlyphs(CLayout* pLayout)
{
  size_t i;

  for (i = 0; i < pLayout->getListOfTextGlyphs().size(); ++i)
    {
      CLTextGlyph* pTG = &pLayout->getListOfTextGlyphs()[i];
      CLGraphicalObject* pGO = pTG->getGraphicalObject();

      if (!pGO)
        continue;

      pTG->setPosition(CLPoint(pGO->getX() + 2, pGO->getY() + 2));
    }
}

/**
 * This function produces a random layout. It first shufles around
 * metab glyphs and reaction centers, and finally corrects all ars
 */
void CCopasiSpringLayout::randomize()
{
  CRandom* pRandom = CRandom::createGenerator(CRandom::mt19937, CRandom::getSystemSeed());

  size_t i;

  //compartment glyphs

  //metab glyphs
  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size(); ++i)
    {
      CLMetabGlyph* pMetabGlyph = &mpLayout->getListOfMetaboliteGlyphs()[i];
      const CMetab* pMetab = dynamic_cast<const CMetab*>(pMetabGlyph->getModelObject());

      if (!pMetab)
        continue;

      //find the compartment glyph
      const CCompartment* pComp = pMetab->getCompartment();

      if (!pComp)
        continue;

      const CLCompartmentGlyph* pCompGlyph = NULL;
      size_t j;

      for (j = 0; j < mpLayout->getListOfCompartmentGlyphs().size(); ++j)
        if (mpLayout->getListOfCompartmentGlyphs()[j].getModelObjectKey()
            == pComp->getKey())
          {
            pCompGlyph = &mpLayout->getListOfCompartmentGlyphs()[j];
            break;
          }

      if (pCompGlyph)
        randomlyPlaceGlyphInCompartmentGlyph(pMetabGlyph, pCompGlyph, pRandom);
      else
        randomlyPlaceGlyphInDimensions(pMetabGlyph, &mpLayout->getDimensions(), pRandom);
    }

  //reaction glyphs
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* pReactionGlyph = &mpLayout->getListOfReactionGlyphs()[i];
      CLPoint center(0, 0);
      size_t count;

      for (count = 0; count < pReactionGlyph->getListOfMetabReferenceGlyphs().size(); ++count)
        {
          CLMetabGlyph* metabGlyph = pReactionGlyph->getListOfMetabReferenceGlyphs()[count].getMetabGlyph();

          if (metabGlyph == NULL) continue;

          center = center + metabGlyph->getBoundingBox().getCenter();
        }

      center = center * (1.0 / pReactionGlyph->getListOfMetabReferenceGlyphs().size());
      center = center + CLPoint(pRandom->getRandomCC() * 20 - 10,  pRandom->getRandomCC() * 20 - 10);

      pReactionGlyph->setPosition(center);

      /*if (pCompGlyph)
        randomlyPlaceGlyphInCompartmentGlyph(pMetabGlyph, pCompGlyph);
      else
        randomlyPlaceGlyphInDimensions(pMetabGlyph, &mpCurrentLayout->getDimensions());*/
    }

  placeTextGlyphs(mpLayout);
  delete pRandom;

  finalizeState();
}

class CompartmentInfo
{
public:
  unsigned int mNumItems;
  double mAreaSum;

  CompartmentInfo()
    : mNumItems(0),
      mAreaSum(0.0)
  {}

  void add(double area)
  {
    ++mNumItems;
    mAreaSum += area;
  }
};

CLayout* CCopasiSpringLayout::createLayout(
  CDataContainer *parent,
  const std::set<const CCompartment*>& compartments,
  const std::set<const CReaction*>& reactions,
  const std::set<const CMetab*>& metabs,
  const std::set<const CMetab*>& sideMetabs,
  Parameters* mParams
)
{
  CLayout *pResult = new CLayout("Layout", parent);

  double fontSize = 16.0;
  double fontHeight = fontSize * 1.5;

  // create a species glyph for each species in metabs

  std::map<const CCompartment*, CompartmentInfo> compInfo;
  std::map<const CMetab*, CLMetabGlyph*> metabMap;

  std::set<const CMetab*>::const_iterator metabIt;

  for (metabIt = metabs.begin(); metabIt != metabs.end(); ++metabIt)
    {
      if (sideMetabs.find(*metabIt) != sideMetabs.end())
        continue;

      //estimate the size of the glyph
      double width = (double)((*metabIt)->getObjectName().length() * fontSize);
      double height = (double)fontHeight;

      if (width < height)
        {
          width = height;
        }

      //create the glyph
      CLMetabGlyph* pMetabGlyph = new CLMetabGlyph;
      pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
      pMetabGlyph->setModelObjectKey((*metabIt)->getKey());

      pResult->addMetaboliteGlyph(pMetabGlyph);
      metabMap[*metabIt] = pMetabGlyph;

      //create the text glyph for the label
      CLTextGlyph* pTextGlyph = new CLTextGlyph;
      pTextGlyph->setDimensions(CLDimensions(width, height));
      pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
      pTextGlyph->setModelObjectKey((*metabIt)->getKey());

      pResult->addTextGlyph(pTextGlyph);

      //add up the sizes for the compartment
      const CCompartment* pComp = NULL;

      if (compartments.find((*metabIt)->getCompartment()) != compartments.end())
        pComp = (*metabIt)->getCompartment();

      compInfo[pComp].add((width + 4) * (height + 4));
    }

  //now the reaction glyphs
  std::set<const CReaction*>::const_iterator reactIt;

  for (reactIt = reactions.begin(); reactIt != reactions.end(); ++reactIt)
    {
      CLReactionGlyph* pReactionGlyph = new CLReactionGlyph;
      //pResult->setDimensions(CLDimensions(width, height));
      pReactionGlyph->setModelObjectKey((*reactIt)->getKey());
      //pReactionGlyph->getCurve().addCurveSegment(CLLineSegment(CLPoint(x, y),
      //                                             CLPoint(x + length, y)));
      bool isReversible = (*reactIt)->isReversible();
      pResult->addReactionGlyph(pReactionGlyph);

      //now add the species reference glyphs.

      //substrates
      const CDataVector < CChemEqElement >& substrates = (*reactIt)->getChemEq().getSubstrates();
      bool substrateExists = false;
      CDataVector<CChemEqElement>::const_iterator elIt;

      for (elIt = substrates.begin(); elIt != substrates.end(); ++elIt)
        {
          const CMetab* pMetab = elIt->getMetabolite();

          if (!pMetab)
            continue;

          CLMetabGlyph* pMetabGlyph = NULL;
          CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;
          CLMetabReferenceGlyph::Role functionalRole;

          //is it a side reactant? If yes, create a new metab glyph
          if (sideMetabs.find(pMetab) != sideMetabs.end())
            {
              //estimate the size of the glyph
              double width = (double)((pMetab)->getObjectName().length() * fontSize);
              double height = (double)fontHeight;

              if (width < height)
                {
                  width = height;
                }

              //create the glyph
              pMetabGlyph = new CLMetabGlyph;
              pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
              pMetabGlyph->setModelObjectKey(pMetab->getKey());
              //TODO: mark as duplicate
              pResult->addMetaboliteGlyph(pMetabGlyph);

              //create the text glyph for the label
              CLTextGlyph* pTextGlyph = new CLTextGlyph;
              pTextGlyph->setDimensions(CLDimensions(width, height));
              pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
              pTextGlyph->setModelObjectKey(pMetab->getKey());

              pResult->addTextGlyph(pTextGlyph);

              //add up the sizes for the compartment
              const CCompartment* pComp = NULL;

              if (compartments.find(pMetab->getCompartment()) != compartments.end())
                pComp = pMetab->getCompartment();

              compInfo[pComp].add((width + 4) * (height + 4));

              role = isReversible
                     ? CLMetabReferenceGlyph::SIDEPRODUCT
                     : CLMetabReferenceGlyph::SIDESUBSTRATE;
              functionalRole = CLMetabReferenceGlyph::SIDESUBSTRATE;
            }
          else
            {
              //find the existing metab glyph
              std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
              mmIt = metabMap.find(pMetab);

              if (mmIt != metabMap.end())
                pMetabGlyph = mmIt->second;

              role = isReversible
                     ? CLMetabReferenceGlyph::PRODUCT
                     : CLMetabReferenceGlyph::SUBSTRATE;
              functionalRole = CLMetabReferenceGlyph::SUBSTRATE;
            }

          if (!pMetabGlyph)
            continue;

          CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
          //pResult->setModelObjectKey(modelobjectkey);
          pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole(role);
          pRefGlyph->setFunctionalRole(functionalRole);
          pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
          substrateExists = true;
        } //substrates

      // if we have no substrates, add a dummy / invisible node for now
      if (!substrateExists)
        {
          CLMetabGlyph* pMetabGlyph = new CLMetabGlyph;
          pMetabGlyph->setDimensions(CLDimensions(1, 1));
          pMetabGlyph->setObjectRole("invisible");
          pResult->addMetaboliteGlyph(pMetabGlyph);

          CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
          //pResult->setModelObjectKey(modelobjectkey);
          pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole(CLMetabReferenceGlyph::SUBSTRATE); //TODO side substr?
          pRefGlyph->setFunctionalRole(CLMetabReferenceGlyph::SUBSTRATE);
          pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
        }

      //products
      const CDataVector < CChemEqElement >& products = (*reactIt)->getChemEq().getProducts();
      bool productExists = false;

      for (elIt = products.begin(); elIt != products.end(); ++elIt)
        {
          const CMetab* pMetab = elIt->getMetabolite();

          if (!pMetab)
            continue;

          CLMetabGlyph* pMetabGlyph = NULL;
          CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;
          CLMetabReferenceGlyph::Role functionalRole;

          //is it a side reactant? If yes, create a new metab glyph
          if (sideMetabs.find(pMetab) != sideMetabs.end())
            {
              //estimate the size of the glyph
              double width = (double)((pMetab)->getObjectName().length() * fontSize);
              double height = (double)fontHeight;

              if (width < height)
                {
                  width = height;
                }

              //create the glyph
              pMetabGlyph = new CLMetabGlyph;
              pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
              pMetabGlyph->setModelObjectKey(pMetab->getKey());
              //TODO: mark as duplicate
              pResult->addMetaboliteGlyph(pMetabGlyph);

              //create the text glyph for the label
              CLTextGlyph* pTextGlyph = new CLTextGlyph;
              pTextGlyph->setDimensions(CLDimensions(width, height));
              pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
              pTextGlyph->setModelObjectKey(pMetab->getKey());

              pResult->addTextGlyph(pTextGlyph);

              //add up the sizes for the compartment
              const CCompartment* pComp = NULL;

              if (compartments.find(pMetab->getCompartment()) != compartments.end())
                pComp = pMetab->getCompartment();

              compInfo[pComp].add((width + 4) * (height + 4));

              role = CLMetabReferenceGlyph::SIDEPRODUCT;
              functionalRole = CLMetabReferenceGlyph::SIDEPRODUCT;
            }
          else
            {
              //find the existing metab glyph
              std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
              mmIt = metabMap.find(pMetab);

              if (mmIt != metabMap.end())
                pMetabGlyph = mmIt->second;

              role = CLMetabReferenceGlyph::PRODUCT;
              functionalRole = CLMetabReferenceGlyph::PRODUCT;
            }

          if (!pMetabGlyph)
            continue;

          CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
          //pResult->setModelObjectKey(modelobjectkey);
          pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole(role);
          pRefGlyph->setFunctionalRole(functionalRole);
          pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
          productExists = true;
        } //products

      // if we have no substrates, add a dummy / invisible node for now
      if (!productExists)
        {
          CLMetabGlyph* pMetabGlyph = new CLMetabGlyph;
          pMetabGlyph->setDimensions(CLDimensions(1, 1));
          pMetabGlyph->setObjectRole("invisible");
          pResult->addMetaboliteGlyph(pMetabGlyph);

          CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
          //pResult->setModelObjectKey(modelobjectkey);
          pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole(CLMetabReferenceGlyph::PRODUCT); //TODO side substr?
          pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
        }

      //modifiers
      const CDataVector < CChemEqElement >& modifiers = (*reactIt)->getChemEq().getModifiers();

      for (elIt = modifiers.begin(); elIt != modifiers.end(); ++elIt)
        {
          const CMetab* pMetab = elIt->getMetabolite();

          if (!pMetab)
            continue;

          CLMetabGlyph* pMetabGlyph = NULL;
          CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;

          //is it a side reactant? If yes, create a new metab glyph
          if (sideMetabs.find(pMetab) != sideMetabs.end())
            {
              //estimate the size of the glyph
              double width = (double)((pMetab)->getObjectName().length() * fontSize);
              double height = (double)fontHeight;

              if (width < height)
                {
                  width = height;
                }

              //create the glyph
              pMetabGlyph = new CLMetabGlyph;
              pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
              pMetabGlyph->setModelObjectKey(pMetab->getKey());
              //TODO: mark as duplicate
              pResult->addMetaboliteGlyph(pMetabGlyph);

              //create the text glyph for the label
              CLTextGlyph* pTextGlyph = new CLTextGlyph;
              pTextGlyph->setDimensions(CLDimensions(width, height));
              pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
              pTextGlyph->setModelObjectKey(pMetab->getKey());

              pResult->addTextGlyph(pTextGlyph);

              //add up the sizes for the compartment
              const CCompartment* pComp = NULL;

              if (compartments.find(pMetab->getCompartment()) != compartments.end())
                pComp = pMetab->getCompartment();

              compInfo[pComp].add((width + 4) * (height + 4));

              role = CLMetabReferenceGlyph::MODIFIER; //TODO SIDEMODIFIER???
            }
          else
            {
              //find the existing metab glyph
              std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
              mmIt = metabMap.find(pMetab);

              if (mmIt != metabMap.end())
                pMetabGlyph = mmIt->second;

              role = CLMetabReferenceGlyph::MODIFIER;
            }

          if (!pMetabGlyph)
            continue;

          CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
          //pResult->setModelObjectKey(modelobjectkey);
          pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole(role);
          pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
        } //modifiers
    } //reactions

  //rules
  size_t i;

  for (i = 0; i < pResult->getListOfMetaboliteGlyphs().size(); ++i)
    {
      const CLMetabGlyph* pMetabGlyph = &pResult->getListOfMetaboliteGlyphs()[i];
      const CMetab* pMetab = dynamic_cast<const CMetab*>(pMetabGlyph->getModelObject());

      if (!pMetab)
        continue;

      if (pMetab->getStatus() == CModelEntity::Status::ODE || pMetab->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          CLGeneralGlyph* pGG = new CLGeneralGlyph;
          pGG->setDimensions(CLDimensions(10, 10));
          pGG->setObjectRole("rule");

          pResult->addGeneralGlyph(pGG);

          CLReferenceGlyph* pRefGlyph = new CLReferenceGlyph;
          pRefGlyph->setDimensions(CLDimensions(10, 10));
          pRefGlyph->setTargetGlyphKey(pMetabGlyph->getKey());
          pRefGlyph->setRole("rule connection");
          pGG->addReferenceGlyph(pRefGlyph);
        }
    }

  //after all other glyphs are created, create the compartment glyphs
  double xxx = 0;
  std::set<const CCompartment*>::const_iterator compIt;

  for (compIt = compartments.begin(); compIt != compartments.end(); ++compIt)
    {
      double compSize = 10000;
      std::map<const CCompartment*, CompartmentInfo>::const_iterator ccIt;
      ccIt = compInfo.find(*compIt);

      if (ccIt != compInfo.end())
        {
          //some glyphs are placed inside this compartment glyph
          compSize = ccIt->second.mAreaSum * 40;
        }

      //create the glyph
      CLCompartmentGlyph* pCompGlyph = new CLCompartmentGlyph;
      pCompGlyph->setModelObjectKey((*compIt)->getKey());
      pCompGlyph->setDimensions(CLDimensions(CLDimensions(sqrt(compSize), sqrt(compSize))));
      pCompGlyph->setPosition(CLPoint(xxx, 5));
      xxx += sqrt(compSize) + 10;

      pResult->addCompartmentGlyph(pCompGlyph);
    }

  //
  // double sss = sqrt(compInfo[NULL].mAreaSum * 40);
  //
  // // determine and set the layout dimensions
  // CLBoundingBox box = pResult->calculateBoundingBox();
  // if (box.getDimensions().getWidth() < sss)
  //   box.getDimensions().setWidth(sss);
  //
  // if (box.getDimensions().getHeight() < sss)
  //   box.getDimensions().setHeight(sss);
  //
  // pResult->setDimensions(CLDimensions(box.getDimensions().getWidth() + 30.0, box.getDimensions().getHeight() + 30.0));

  // randomize
  CCopasiSpringLayout l(pResult, mParams);
  l.randomize();

  // determine and set the layout dimensions
  CLBoundingBox box = pResult->calculateBoundingBox();
  pResult->setDimensions(CLDimensions(box.getDimensions().getWidth() + 30.0, box.getDimensions().getHeight() + 30.0));

  return pResult;
}
