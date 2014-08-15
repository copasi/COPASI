// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%ignore CRDFTriplet::operator bool;
%ignore CRDFTriplet::operator <;

%{

#include "MIRIAM/CMIRIAMResource.h"
#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFPredicate.h"
#include "MIRIAM/CRDFSubject.h"
#include "MIRIAM/CRDFTriplet.h"
#include "MIRIAM/CModelMIRIAMInfo.h"

%}

%ignore CMIRIAMResources::updateMIRIAMResources(CProcessReport * pProcessReport);
%ignore CMIRIAMResourceObject::CMIRIAMResourceObject(CRDFNode * pNode);
%ignore CMIRIAMResourceObject::setNode;
%ignore CRDFGraph::getAboutNode;
%ignore CRDFGraph::getNameSpaceMap;
%ignore CRDFGraph::getBlankNodeMap;
%ignore CRDFGraph::getLocalResourceNodeMap;
%ignore CRDFGraph::getRemoteResourceNodes;
%ignore CRDFGraph::addTriplet;
%ignore CRDFGraph::removeTriplet;
%ignore CRDFGraph::destroyUnreferencedNode;
%ignore CRDFGraph::moveTriplet;
%ignore CRDFGraph::getTriplets;
%ignore CRDFGraph::getIncomingTriplets;
%ignore CRDFGraph::getParentSubjects;
%ignore CRDFGraph::getPredicatePath;
%ignore CRDFGraph::createAboutNode;

%ignore CRDFTriplet::CRDFTriplet;
%ignore CRDFTriplet::pSubject;
%ignore CRDFTriplet::Predicate;
%ignore CRDFTriplet::pObject;

%include "MIRIAM/CMIRIAMResource.h"
%include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFPredicate.h"
#include "MIRIAM/CRDFSubject.h"
%include "MIRIAM/CRDFTriplet.h"
%include "MIRIAM/CModelMIRIAMInfo.h"



