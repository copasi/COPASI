// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>

#define USE_LAYOUT 1

#include <sbml/packages/layout/sbml/ReactionGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>

#include "copasi.h"

#include "CLReactionGlyph.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"


CLGlyphWithCurve::CLGlyphWithCurve(const std::string & name,
                                             const CCopasiContainer * pParent)
: CLGraphicalObject(name, pParent),
mCurve()
{}

CLGlyphWithCurve::CLGlyphWithCurve(const CLGlyphWithCurve & src,
                                             const CCopasiContainer * pParent)
: CLGraphicalObject(src, pParent),
mCurve(src.mCurve)
{}

CLGlyphWithCurve::CLGlyphWithCurve(const GraphicalObject & sbml,
                                             const std::map<std::string, std::string> & modelmap,
                                             std::map<std::string, std::string> & layoutmap,
                                             const CCopasiContainer * pParent)
: CLGraphicalObject(sbml, layoutmap, pParent),
mCurve() //initialized in the body below
{
    //curve

    //TODO : check if it is one of the sbml glyphs with a curve and handle correspondingly
    //if (sbml.getCurve())
    //    mCurve = CLCurve(*sbml.getCurve());
}

CLGlyphWithCurve & CLGlyphWithCurve::operator= (const CLGlyphWithCurve & rhs)
{
    if (this == &rhs) return * this; //do nothing if lhs and rhs are the same
    
    CLGraphicalObject::operator=(rhs);
    
    //handle the specific glyph stuff:
    mCurve = rhs.mCurve;
    
    return *this;
}

void CLGlyphWithCurve::moveBy(const CLPoint &p)
{
  CLGraphicalObject::moveBy(p);
  mCurve.moveBy(p);
}

std::ostream & operator<<(std::ostream &os, const CLGlyphWithCurve & g)
{
    //TODO: bounding box?
    os << g.mCurve;
    
    return os;
}

void CLGlyphWithCurve::print(std::ostream * ostream) const
{*ostream << *this;}


//***************************


CLReferenceGlyph::CLReferenceGlyph(const std::string & name,
                                             const CCopasiContainer * pParent)
: CLGlyphWithCurve(name, pParent),
mGlyphKey()
{}

CLReferenceGlyph::CLReferenceGlyph(const CLReferenceGlyph & src,
                                             const CCopasiContainer * pParent)
: CLGlyphWithCurve(src, pParent),
mGlyphKey(src.mGlyphKey)
{}

CLReferenceGlyph::CLReferenceGlyph(const SpeciesReferenceGlyph & sbml,
                                             const std::map<std::string, std::string> & modelmap,
                                             std::map<std::string, std::string> & layoutmap,
                                             const CCopasiContainer * pParent)
: CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
mGlyphKey() //initialized in the body below
{
    //get the copasi key corresponding to the sbml id for the species reference
    if (sbml.getSpeciesReferenceId() != "")
      {
        std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getSpeciesReferenceId());
        
        if (it != modelmap.end())
            setModelObjectKey(it->second);
      }
    
    
    //get the copasi key corresponding to the sbml id for the species glyph
    if (sbml.getSpeciesGlyphId() != "")
      {
        std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());
        
        if (it != layoutmap.end())
            mGlyphKey = it->second;
      }
    
    //curve  (TODO: perhaps move to GlyphWithCurve?)
    if (sbml.getCurve())
        mCurve = CLCurve(*sbml.getCurve());
}

CLReferenceGlyph & CLReferenceGlyph::operator= (const CLReferenceGlyph & rhs)
{
    if (this == &rhs) return * this; //do nothing if lhs and rhs are the same
    
    CLGlyphWithCurve::operator=(rhs);
    
    //handle the specific glyph stuff:
    mGlyphKey = rhs.mGlyphKey;
    
    return *this;
}

CLGraphicalObject* CLReferenceGlyph::getTargetGlyph() const
{
    CCopasiObject* tmp = CCopasiRootContainer::getKeyFactory()->get(mGlyphKey);
    return dynamic_cast<CLMetabGlyph*>(tmp);
}

void CLReferenceGlyph::exportToSBML(SpeciesReferenceGlyph * g, //TODO
                                         const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                                         std::map<std::string, const SBase*>& sbmlIDs,
                                         const std::map<const CLBase*, const SBase*> & layoutmap) const
{
    if (!g) return;
    
    //call the coresponding method of the base class
    CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);
    
    //reference to species glyph
    CLGraphicalObject* tmp = getTargetGlyph();
    
    if (tmp)
      {
        std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);
        
        if (it != layoutmap.end())
          {
            if (it->second)
              {
                //we need to cast here since layout objects in libsbml don´t inherit the getId() method
                //from SBase
                const GraphicalObject* pGO = dynamic_cast<const GraphicalObject*>(it->second);
                
                if (pGO)
                    g->setSpeciesGlyphId(pGO->getId());
              }
          }
      }
    
    //curve
    mCurve.exportToSBML(g->getCurve(), copasimodelmap);
}

std::ostream & operator<<(std::ostream &os, const CLReferenceGlyph & g)
{
    os << "    ReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
    
    const CLGraphicalObject* tmp = g.getTargetGlyph();
    
    if (tmp)
        os << "      refers to a Glyph that refers to "
        << tmp->getModelObjectDisplayName() << std::endl;
    
    os << g.mCurve; //TODO refer to base class?
    
    return os;
}

void CLReferenceGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//*********************************************************************


const std::string CLMetabReferenceGlyph::RoleName[] =
{
  "undefined role",
  "substrate",
  "product",
  "side substrate",
  "side product",
  "modifier",
  "activator",
  "inhibitor"
  ""
};

const std::string CLMetabReferenceGlyph::XMLRole[] =
{
  "undefinedRole",
  "substrate",
  "product",
  "sideSubstrate",
  "sideProduct",
  "modifier",
  "activator",
  "inhibitor",
  ""
};



CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CCopasiContainer * pParent)
    : CLGlyphWithCurve(name, pParent),
    mMetabGlyphKey(),
    mRole(UNDEFINED)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CCopasiContainer * pParent)
    : CLGlyphWithCurve(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey),
    mRole(src.mRole)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
    const std::map<std::string, std::string> & modelmap,
    std::map<std::string, std::string> & layoutmap,
    const CCopasiContainer * pParent)
    : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
    mMetabGlyphKey(), //initialized in the body below
    mRole((Role)sbml.getRole())
{
  //get the copasi key corresponding to the sbml id for the species reference
  if (sbml.getSpeciesReferenceId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getSpeciesReferenceId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.getSpeciesGlyphId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());

      if (it != layoutmap.end())
        mMetabGlyphKey = it->second;
    }

  //curve
  if (sbml.getCurve())
    mCurve = CLCurve(*sbml.getCurve());
}

CLMetabReferenceGlyph & CLMetabReferenceGlyph::operator= (const CLMetabReferenceGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:
  mMetabGlyphKey = rhs.mMetabGlyphKey;
  mRole = rhs.mRole;

  return *this;
}

CLMetabGlyph* CLMetabReferenceGlyph::getMetabGlyph() const
{
  CCopasiObject* tmp = CCopasiRootContainer::getKeyFactory()->get(mMetabGlyphKey);
  return dynamic_cast<CLMetabGlyph*>(tmp);
}

void CLMetabReferenceGlyph::exportToSBML(SpeciesReferenceGlyph * g,
    const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
    std::map<std::string, const SBase*>& sbmlIDs,
    const std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  //reference to species glyph
  CLMetabGlyph* tmp = getMetabGlyph();

  if (tmp)
    {
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end())
        {
          if (it->second)
            {
              //we need to cast here since layout objects in libsbml don´t inherit the getId() method
              //from SBase
              const GraphicalObject* pGO = dynamic_cast<const GraphicalObject*>(it->second);

              if (pGO)
                g->setSpeciesGlyphId(pGO->getId());
            }
        }
    }

  //curve
  mCurve.exportToSBML(g->getCurve(), copasimodelmap);

  //Role
  g->setRole((SpeciesReferenceRole_t)mRole);
  //this depends on the copasi role enum being synchronous to the sbml one
}

std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g)
{
  os << "    MetabReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  os << "      Role: " << CLMetabReferenceGlyph::RoleName[g.getRole()] << "\n";

  const CLMetabGlyph* tmp = g.getMetabGlyph();

  if (tmp)
    os << "      refers to a MetabGlyph that refers to "
       << tmp->getModelObjectDisplayName() << std::endl;

  os << g.mCurve;

  return os;
}

void CLMetabReferenceGlyph::print(std::ostream * ostream) const
{*ostream << *this;}


//*********** CLGeneralGlyph ****************************************

CLGeneralGlyph::CLGeneralGlyph(const std::string & name,
                                 const CCopasiContainer * pParent)
: CLGlyphWithCurve(name, pParent),
mvReferences("ListOfReferenceGlyphs", this)
{}

CLGeneralGlyph::CLGeneralGlyph(const CLGeneralGlyph & src,
                                 const CCopasiContainer * pParent)
: CLGlyphWithCurve(src, pParent),
mvReferences(src.mvReferences, this)
{
    //TODO?
}

//TODO this is a placeholder for the upcoming sbml generalGlyph handling
CLGeneralGlyph::CLGeneralGlyph(const GraphicalObject & sbml,
                               const std::map<std::string, std::string> & modelmap,
                               std::map<std::string, std::string> & layoutmap,
                               const CCopasiContainer * pParent)
: CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
mvReferences("ListOfReferenceGlyphs", this)
{
/*
    //get the copasi key corresponding to the sbml id for the reaction
    if (sbml.getReactionId() != "")
      {
        std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReactionId());
        
        if (it != modelmap.end())
            setModelObjectKey(it->second);
      }
    
    //species reference glyphs
    C_INT32 i, imax = sbml.getListOfSpeciesReferenceGlyphs()->size();
    
    for (i = 0; i < imax; ++i)
      {
        const SpeciesReferenceGlyph* tmp
        = dynamic_cast<const SpeciesReferenceGlyph*>(sbml.getListOfSpeciesReferenceGlyphs()->get(i));
        
        if (tmp)
            addReferenceGlyph(new CLReferenceGlyph(*tmp, modelmap, layoutmap));
      }
    
    //curve
    if (sbml.getCurve())
        mCurve = CLCurve(*sbml.getCurve());

*/
}


CLGeneralGlyph & CLGeneralGlyph::operator= (const CLGeneralGlyph & rhs)
{
    if (this == &rhs) return * this; //do nothing if lhs and rhs are the same
    
    CLGlyphWithCurve::operator=(rhs);
    
    //handle the specific glyph stuff:
    
    size_t i, imax = rhs.mvReferences.size();
    
    for (i = 0; i < imax; ++i)
        addReferenceGlyph(new CLReferenceGlyph(*rhs.mvReferences[i]));
    
    return *this;
}

void CLGeneralGlyph::addReferenceGlyph(CLReferenceGlyph * glyph)
{
    if (glyph)
        mvReferences.add(glyph, true); //true means vector takes ownership
}

void CLGeneralGlyph::moveBy(const CLPoint &p)
{
  CLGlyphWithCurve::moveBy(p);

  size_t i, imax = mvReferences.size();

  for (i = 0; i < imax; ++i)
    mvReferences[i]->moveBy(p);
}

/*void CLGeneralGlyph::exportToSBML(ReactionGlyph * g,
                                   const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                                   std::map<std::string, const SBase*>& sbmlIDs,
                                   std::map<const CLBase*, const SBase*> & layoutmap) const
{
    if (!g) return;
    
    //call the coresponding method of the base class
    CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);
    
    //reference to model objects
    CCopasiObject* tmp = getModelObject();
    
    if (tmp)
      {
        std::map<const CCopasiObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);
        
        if (it != copasimodelmap.end())
          {
            if (it->second)
                g->setReactionId(it->second->getId());
          }
      }
    
    //curve
    mCurve.exportToSBML(g->getCurve(), copasimodelmap);
    
    //Metab reference  glyphs
    size_t i, imax = mvReferences.size();
    
    for (i = 0; i < imax; ++i)
      {
        CLReferenceGlyph * tmp = mvReferences[i];
        
        //check if the glyph exists in the libsbml data
        std::map<const CCopasiObject*, SBase*>::const_iterator it;
        it = copasimodelmap.find(tmp);
        
        SpeciesReferenceGlyph * pG;
        
        if (it == copasimodelmap.end()) //not found
          {
            pG = new SpeciesReferenceGlyph;
            g->getListOfSpeciesReferenceGlyphs()->appendAndOwn(pG);
          }
        else
          {
            pG = dynamic_cast<SpeciesReferenceGlyph*>(it->second);
          }
        
        layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
        tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
      }
}*/

void CLGeneralGlyph::exportToSBML(GraphicalObject * g, //TODO
                                  const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                                  std::map<std::string, const SBase*>& sbmlIDs,
                                  std::map<const CLBase*, const SBase*> & layoutmap) const
{
    if (!g) return;
    
    //TODO insert the code from above once we have the libsbml generalGlyph class
    
    //call the coresponding method of the base class
    CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);
}

std::ostream & operator<<(std::ostream &os, const CLGeneralGlyph & g)
{
    os << "GeneralGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
    os << g.mCurve;
    
    size_t i, imax = g.mvReferences.size();
    
    if (imax)
      {
        os << "  List of reference glyphs: \n";
        
        for (i = 0; i < imax; ++i)
            os << *g.mvReferences[i];
      }
    
    return os;
}

void CLGeneralGlyph::print(std::ostream * ostream) const
{*ostream << *this;}


//*********** CLReactionGlyph ****************************************

CLReactionGlyph::CLReactionGlyph(const std::string & name,
                                 const CCopasiContainer * pParent)
    : CLGlyphWithCurve(name, pParent),
    mvMetabReferences("ListOfMetabReferenceGlyphs", this)
{}

CLReactionGlyph::CLReactionGlyph(const CLReactionGlyph & src,
                                 const CCopasiContainer * pParent)
    : CLGlyphWithCurve(src, pParent),
    mvMetabReferences(src.mvMetabReferences, this)
{
  //TODO
}

CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & sbml,
                                 const std::map<std::string, std::string> & modelmap,
                                 std::map<std::string, std::string> & layoutmap,
                                 const CCopasiContainer * pParent)
    : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
    mvMetabReferences("ListOfMetabReferenceGlyphs", this)
{
  //get the copasi key corresponding to the sbml id for the reaction
  if (sbml.getReactionId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReactionId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //species reference glyphs
  C_INT32 i, imax = sbml.getListOfSpeciesReferenceGlyphs()->size();

  for (i = 0; i < imax; ++i)
    {
      const SpeciesReferenceGlyph* tmp
        = dynamic_cast<const SpeciesReferenceGlyph*>(sbml.getListOfSpeciesReferenceGlyphs()->get(i));

      if (tmp)
        addMetabReferenceGlyph(new CLMetabReferenceGlyph(*tmp, modelmap, layoutmap));
    }

  //curve
  if (sbml.getCurve())
    mCurve = CLCurve(*sbml.getCurve());
}

CLReactionGlyph & CLReactionGlyph::operator= (const CLReactionGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:
  size_t i, imax = rhs.mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    addMetabReferenceGlyph(new CLMetabReferenceGlyph(*rhs.mvMetabReferences[i]));

  return *this;
}

/*const std::vector<CLMetabReferenceGlyph*> CLReactionGlyph::getListOfMetabReferenceGlyphs() const
{
    std::vector<CLMetabReferenceGlyph*> ret;
    size_t i, imax = mvReferences.size();
    
    for (i = 0; i < imax; ++i)
      {
        CLMetabReferenceGlyph * tmp = dynamic_cast<CLMetabReferenceGlyph*>(mvReferences[i]);
        if(tmp)
            ret.push_back(tmp);
      }
    return ret;
}*/


void CLReactionGlyph::addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph)
{
  if (glyph)
    mvMetabReferences.add(glyph, true); //true means vector takes ownership
}

void CLReactionGlyph::moveBy(const CLPoint &p)
{
  CLGlyphWithCurve::moveBy(p);

  size_t i, imax = mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    mvMetabReferences[i]->moveBy(p);
}

void CLReactionGlyph::exportToSBML(ReactionGlyph * g,
                                   const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                                   std::map<std::string, const SBase*>& sbmlIDs,
                                   std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  //reference to model objects
  CCopasiObject* tmp = getModelObject();

  if (tmp)
    {
      std::map<const CCopasiObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);

      if (it != copasimodelmap.end())
        {
          if (it->second)
            g->setReactionId(it->second->getId());
        }
    }

  //curve
  mCurve.exportToSBML(g->getCurve(), copasimodelmap);

  //Metab reference  glyphs
  size_t i, imax = mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    {
      CLMetabReferenceGlyph * tmp = mvMetabReferences[i];

      //check if the glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      SpeciesReferenceGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new SpeciesReferenceGlyph;
          g->getListOfSpeciesReferenceGlyphs()->appendAndOwn(pG);
        }
      else
        {
          pG = dynamic_cast<SpeciesReferenceGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
    }
}

std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g)
{
  os << "ReactionGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  os << g.mCurve;

  size_t i, imax = g.mvMetabReferences.size();

  if (imax)
    {
      os << "  List of metab reference glyphs: \n";

      for (i = 0; i < imax; ++i)
        os << *g.mvMetabReferences[i];
    }

  return os;
}

void CLReactionGlyph::print(std::ostream * ostream) const
{*ostream << *this;}
