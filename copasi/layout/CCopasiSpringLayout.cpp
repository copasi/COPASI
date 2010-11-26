// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CCopasiSpringLayout.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/11/26 16:37:18 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <iostream>
#include "CCopasiSpringLayout.h"
#include "CLGlyphs.h"
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

  for (i = 0; i < mpLayout->getListOfMetaboliteGlyphs().size() - 1; ++i)
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

/*

void CCopasiSpringLayout::addReactionNodeWithVariables(const double & xpos, const double & ypos)
{
  ReactionNode tmpnode(this);

  VariableDescription desc;
  desc.isAngle=false;

  tmpnode.x=xpos;
  tmpnode.a = mInitialState.size();
  mInitialState.push_back(tmpnode.x);
  mVarDescription.push_back(desc);
  mMassVector.push_back(1.0);

  tmpnode.y=ypos;
  tmpnode.b = mInitialState.size();
  mInitialState.push_back(tmpnode.y);
  mVarDescription.push_back(desc);
  mMassVector.push_back(1.0);

  tmpnode.compartmentIndex=-1;

  mReactionNodes.push_back(tmpnode);
}

void CCopasiSpringLayout::updateCompartmentInReactionNode(ReactionNode & r)
{
  if (r.getEdges().size()==0)
    r.compartmentIndex = -1;
  else
  {
    r.compartmentIndex = mSpeciesNodes[r.getEdges()[0].sindex].compartmentIndex;
    int i;
    for (i=1; i<r.getEdges().size(); ++i)
      if (mSpeciesNodes[r.getEdges()[i].sindex].compartmentIndex != r.compartmentIndex)
      {
        r.compartmentIndex = -1;
        break;
      }
  }
}
*/

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

          default:
            std::cout << "Unknown Action!!!" << std::endl;
            break;
        };
    }

  return true;
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

/*
double CCopasiSpringLayout::potSpeciesReaction(const SpeciesNode & a, const ReactionNode & b) const
{
  double tmp = bound_distance(a.x, a.y, b.x, b.y, 200);
  if (tmp<1) tmp=1;
  return a.charge*b.charge/tmp;
}

double CCopasiSpringLayout::potReactionReaction(const ReactionNode & a, const ReactionNode & b) const
{
  double tmp = bound_distance(a.x, a.y, b.x, b.y, 200);
  if (tmp<1) tmp=1;
  return a.charge*b.charge/tmp;
}

double CCopasiSpringLayout::potEdge(const Edge & e, const ReactionNode & r) const
{
  double dist=70;
  if (e.role==Edge::SIDESUBSTRATE || e.role==Edge::SIDEPRODUCT)
    dist=40;

  const SpeciesNode & sn = mSpeciesNodes[e.sindex];
  double tmp = distance(sn.x, sn.y, r.x, r.y);

  if (e.role==Edge::MODIFIER)
    return 0.3*pow(tmp-dist, 2);
  else
    return pow(tmp-dist, 2);
}

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

  if (dist > (0.5*c.getWidth() - 50))
    tmp += pow(dist - 0.5 * c.getWidth() + 50, 2);

  dist = fabs((s.getY() + 0.5 * s.getHeight()) - (c.getY() + 0.5 * c.getHeight()));

  if (dist > (0.5*c.getHeight() - 50))
    tmp += pow(dist - 0.5 * c.getHeight() + 50, 2);

  return tmp /**s.charge*/; //TODO reintroduce charge
}

/*
double CCopasiSpringLayout::potReactionCompartment(const ReactionNode & r, const CompartmentNode & c) const
{
  double tmp=0;
  double dist=fabs(r.x-c.x);
  if (dist > (0.5*c.w-50))
    tmp+=pow(dist-0.5*c.w+50,2);

  dist=fabs(r.y-c.y);
  if (dist > (0.5*c.h-50))
    tmp+=pow(dist-0.5*c.h+50,2);

  return tmp*r.charge;
}

double CCopasiSpringLayout::potCompartmentCompartment(const CompartmentNode & c1, const CompartmentNode & c2) const
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

  /*
    //repulsion between species nodes and reaction nodes
    for (i=0; i<mSpeciesNodes.size(); ++i)
    for (j=0; j<mReactionNodes.size(); ++j)
      {
        tmp += 100000*potSpeciesReaction(mSpeciesNodes[i], mReactionNodes[j]);
      }

    //repulsion between reaction nodes
    for (i=0; i<mReactionNodes.size()-1; ++i)
    for (j=i+1; j<mReactionNodes.size(); ++j)
      {
        if (i!=j)
          tmp += 100000*potReactionReaction(mReactionNodes[i], mReactionNodes[j]);
      }

    //spring force for species references
    for (i=0; i<mReactionNodes.size(); ++i)
      for (j=0; j<mReactionNodes[i].getEdges().size(); ++j)
      {
        tmp += 0.5* potEdge(mReactionNodes[i].getEdges()[j], mReactionNodes[i]);
      }

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
          std::cout << "No compartment info for a species glyph!!!" << std::endl;
          continue;
        }

      CLCompartmentGlyph* tmpCG = mapIt->second;

      if (tmpCG) //the species glyph is inside a compartment glyph
        tmp += 0.2 * potSpeciesCompartment(*tmpMG, *tmpCG);
    }




  /*
  //force to keep reaction nodes in compartment
  for (i=0; i<mReactionNodes.size(); ++i)
    {
      if (mReactionNodes[i].compartmentIndex >=0)
        tmp += 0.2*potReactionCompartment(mReactionNodes[i], mCompartmentNodes[mReactionNodes[i].compartmentIndex]);
    }

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

std::vector<double> CCopasiSpringLayout::getInitialValues()
{
  return mInitialState;
}
