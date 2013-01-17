// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <iostream>
#include "CCopasiSpringLayout.h"
#include "CLGlyphs.h"
#include "CLReactionGlyph.h"
#include "CLayout.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"

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

CCopasiSpringLayout::CCopasiSpringLayout(CLayout* layout)
  : mpLayout(NULL)
{
  initFromLayout(layout);
}

bool CCopasiSpringLayout::initFromLayout(CLayout* layout)
{
  mpLayout = layout;

  if (!mpLayout) return false;

  mCompartmentMap.clear();

  //store the compartment glyph for each species glyph (if it exists)
  unsigned int i;

  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size() ; ++i)
    {
      CMetab* metab = dynamic_cast<CMetab*>(mpLayout->getListOfMetaboliteGlyphs()[i]->getModelObject());
      CLCompartmentGlyph*  tmp = NULL;

      if (metab)
        {
          unsigned int j;

          for (j = 0; j < mpLayout->getListOfCompartmentGlyphs().size(); ++j)
            if (mpLayout->getListOfCompartmentGlyphs()[j]->getModelObjectKey() == metab->getCompartment()->getKey())
              {
                tmp = mpLayout->getListOfCompartmentGlyphs()[j];
                break;
              }
        }

      mCompartmentMap[mpLayout->getListOfMetaboliteGlyphs()[i]] = tmp;
    }

  //store the compartment glyph for each reaction glyph (if it exists)
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      mCompartmentMap[mpLayout->getListOfReactionGlyphs()[i]] = findCompartmentForReactionNode(*mpLayout->getListOfReactionGlyphs()[i]);
    }

  //create the list of constant positional relations
  //we assume that text glyphs are always moved with the glyph they refer to.
  //(i.e. the are not layed out independently)
  mFixedRelations.clear();

  for (i = 0; i < mpLayout->getListOfTextGlyphs().size(); ++i)
    {
      CoordinateRelation tmp;
      tmp.target = mpLayout->getListOfTextGlyphs()[i];
      tmp.source = mpLayout->getListOfTextGlyphs()[i]->getGraphicalObject();

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
      std::map<CLBase*, CLCompartmentGlyph*>::const_iterator mapIt = mCompartmentMap.find(r.getListOfMetabReferenceGlyphs()[i]->getMetabGlyph());

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
      addSpeciesVariables(mpLayout->getListOfMetaboliteGlyphs()[i]);
    }

  // add variables for the coordinates of all reaction glyphs
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      addReactionVariables(mpLayout->getListOfReactionGlyphs()[i]);
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

void CCopasiSpringLayout::addSpeciesVariables(CLMetabGlyph* mg)
{
  if (!mg)
    return;

  bool side = false; //TODO: find out if it is a side reactant

  VariableDescription desc;
  desc.isAngle = false;

  int first_index = mInitialState.size();

  //x position
  mInitialState.push_back(mg->getX());
  mVarDescription.push_back(desc);
  mMassVector.push_back(side ? 0.1 : 1.0);

  //y position
  mInitialState.push_back(mg->getY());
  mVarDescription.push_back(desc);
  mMassVector.push_back(side ? 0.1 : 1.0);

  mUpdateActions.push_back(UpdateAction(UpdateAction::SPECIES_2V, mg, first_index, first_index + 1));
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

          case UpdateAction::SPECIES_2V:
            ((CLMetabGlyph*)(it->mpTarget))->setX(vars[it->mIndex1]);
            ((CLMetabGlyph*)(it->mpTarget))->setY(vars[it->mIndex2]);
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
  std::vector<CoordinateRelation>::const_iterator it, itEnd = mFixedRelations.end();

  for (it = mFixedRelations.begin(); it != itEnd; ++it)
    it->target->setPosition(it->source->getPosition() + it->diff);

  //for now, only create curves for the reaction glyphs
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() ; ++i)
    {
      CLReactionGlyph* pRG = mpLayout->getListOfReactionGlyphs()[i];

      //Determine the average position of substrates and products, giving less weight to side reactants
      CLPoint s, p;
      double s_c = 0; double p_c = 0;
      unsigned int j, jmax = pRG->getListOfMetabReferenceGlyphs().size();

      for (j = 0; j < jmax; ++j)
        {
          if (pRG->getListOfMetabReferenceGlyphs()[j]->getRole() == CLMetabReferenceGlyph::SUBSTRATE)
            {
              s_c += 1.0;
              s = s + pRG->getListOfMetabReferenceGlyphs()[j]->getMetabGlyph()->getBoundingBox().getCenter();
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j]->getRole() == CLMetabReferenceGlyph::SIDESUBSTRATE)
            {
              s_c += 0.1;
              s = s + pRG->getListOfMetabReferenceGlyphs()[j]->getMetabGlyph()->getBoundingBox().getCenter() * 0.1;
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j]->getRole() == CLMetabReferenceGlyph::PRODUCT)
            {
              p_c += 1.0;
              p = p + pRG->getListOfMetabReferenceGlyphs()[j]->getMetabGlyph()->getBoundingBox().getCenter();
            }

          if (pRG->getListOfMetabReferenceGlyphs()[j]->getRole() == CLMetabReferenceGlyph::SIDEPRODUCT)
            {
              p_c += 0.1;
              p = p + pRG->getListOfMetabReferenceGlyphs()[j]->getMetabGlyph()->getBoundingBox().getCenter() * 0.1;
            }
        }

      if (s_c > 0)
        s = s * (1 / s_c);
      else
        s = pRG->getPosition();

      if (p_c > 0)
        p = p * (1 / p_c);
      else
        p = pRG->getPosition();

      CLPoint dir = p - s; //overall direction of reaction

      if (dir.getX() == 0 && dir.getY() == 0)
        dir = CLPoint(1, 0);

      CLPoint reaction_s = pRG->getPosition() - (dir * 0.05);
      CLPoint reaction_p = pRG->getPosition() + (dir * 0.05);

      pRG->getCurve().clear();
      pRG->getCurve().addCurveSegment(CLLineSegment(reaction_s, reaction_p));

      for (j = 0; j < jmax; ++j)
        {
          //here we need to generate the curves for the MetabReferenceGlyphs.
          //we will need to consider the size of the glyphs, role of the metab in the reaction, etc.
          //For now, only a primitive implementation: TODO: improve
          CLMetabReferenceGlyph* pMRG = pRG->getListOfMetabReferenceGlyphs()[j];
          CLPoint reactionPoint;
          double direction;
          double modifierLength = -0.2;

          switch (pMRG->getRole())
            {
              case CLMetabReferenceGlyph::SUBSTRATE :
              case CLMetabReferenceGlyph::SIDESUBSTRATE :
                reactionPoint = reaction_s;
                direction = -0.1;
                break;

              case CLMetabReferenceGlyph::PRODUCT :
              case CLMetabReferenceGlyph::SIDEPRODUCT :
                reactionPoint = reaction_p;
                direction = 0.1;
                break;

              default:
                direction = 0.0;
                reactionPoint = pRG->getPosition();
            }

          CLPoint metabPoint = borderProjection(pMRG->getMetabGlyph(), reactionPoint + dir * direction /*(modifierLength * 1.5)*/, 5);

          pMRG->getCurve().clear();
          pMRG->getCurve().addCurveSegment(CLLineSegment(reactionPoint,
                                           metabPoint,
                                           reactionPoint + dir * direction,
                                           (reactionPoint + dir * (direction * 1.5) + metabPoint) * 0.5));
        }
    }

  //rearrange the text boxes
  //TODO

  //calculate bounding box for the layout, or recenter the layout
  //for (i = 0; i < mpLayout->getListOfSpeciesGlyphs().size() ; ++i)
}

CLPoint CCopasiSpringLayout::borderProjection(CLGraphicalObject* go, const CLPoint & p, double d)
{
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

  //if (tmp<30)
  //  return 0.001*(30-tmp)*a.charge*b.charge;
  //else
  //  return 0;
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
  double dist = 70;

  if (e.getRole() == CLMetabReferenceGlyph::SIDESUBSTRATE || e.getRole() == CLMetabReferenceGlyph::SIDEPRODUCT)
    dist = 40;

  const CLMetabGlyph * pMG = e.getMetabGlyph();
  double tmp = distance(pMG->getX() + pMG->getWidth() / 2, pMG->getY() + pMG->getHeight() / 2,
                        r.getX() + r.getWidth() / 2, r.getY() + r.getHeight() / 2);

  if (e.getRole() == CLMetabReferenceGlyph::MODIFIER)
    return 0.3 * pow(tmp - dist, 2);
  else
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
          tmp += 100000 * potSpeciesSpecies(*mpLayout->getListOfMetaboliteGlyphs()[i], *mpLayout->getListOfMetaboliteGlyphs()[j]);
      }

  // only if we have reactions!
  if (mpLayout->getListOfReactionGlyphs().size() > 0)
    {
      //repulsion between species nodes and reaction nodes
      for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size(); ++i)
        for (j = 0; j < mpLayout->getListOfReactionGlyphs().size(); ++j)
          {
            tmp += 100000 * potSpeciesReaction(*mpLayout->getListOfMetaboliteGlyphs()[i], *mpLayout->getListOfReactionGlyphs()[j]);
          }

      //repulsion between reaction nodes
      for (i = 0; i < mpLayout->getListOfReactionGlyphs().size() - 1; ++i)
        for (j = i + 1; j < mpLayout->getListOfReactionGlyphs().size(); ++j)
          {
            if (i != j)
              tmp += 100000 * potReactionReaction(*mpLayout->getListOfReactionGlyphs()[i], *mpLayout->getListOfReactionGlyphs()[j]);
          }
    }

  //spring force for species references
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* pRG = mpLayout->getListOfReactionGlyphs()[i];

      for (j = 0; j < pRG->getListOfMetabReferenceGlyphs().size(); ++j)
        {
          tmp += 0.5 * potEdge(*pRG->getListOfMetabReferenceGlyphs()[j], *pRG);
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
      CLMetabGlyph* tmpMG = mpLayout->getListOfMetaboliteGlyphs()[i];
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
        tmp += 0.2 * potSpeciesCompartment(*tmpMG, *tmpCG);
    }

  //force to keep reaction nodes in compartment
  for (i = 0; i < mpLayout->getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* tmpRG = mpLayout->getListOfReactionGlyphs()[i];
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
        tmp += 0.2 * potReactionCompartment(*tmpRG, *tmpCG);
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
