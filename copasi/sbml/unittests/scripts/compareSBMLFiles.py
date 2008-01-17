# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/scripts/compareSBMLFiles.py,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/01/17 20:06:23 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

#!/usr/bin/env python

import sys
import pdb
from xml.dom.ext.reader import Sax2


def createDOMTree(file):
    reader=Sax2.Reader()
    return reader.fromStream(file)


def findUnitDefinitions(dom):
    elements=dom.getElementsByTagName("unitDefinition")
    result={}
    for element in elements:
      id=element.getAttributeNode("id")
      if(not id):
        print "Error could not find id for unit definiton node."
        sys.exit(1)
      result[id.nodeValue]=element
    return result

def findFunctionDefinitions(dom):
    elements=dom.getElementsByTagName("functionDefinition")
    result={}
    for element in elements:
      id=element.getAttributeNode("id")
      if(not id):
        print "Error could not find id for function definiton node."
        sys.exit(1)
      result[id.nodeValue]=element
    return result


def findCompartments(dom):
    elements=dom.getElementsByTagName("compartment")
    result={}
    for element in elements:
      id=element.getAttributeNode("id")
      if(not id):
        print "Error could not find id for compartment node."
        sys.exit(1)
      result[id.nodeValue]=element
      return result


def findSpecies(dom):
    elements=dom.getElementsByTagName("species")
    result={}
    for element in elements:
      id=element.getAttributeNode("id")
      if(not id):
        print "Error could not find id for species node."
        sys.exit(1)
      result[id.nodeValue]=element
    return result


def findParameters(model):
    listOfParameters=[]
    for child in model.childNodes:
      if(child.nodeName=="listOfParameters"):
        listOfParameters=child
        break;
    parameters={}
    if(listOfParameters):
       parameters=listOfParameters.getElementsByTagName("parameter")
    return parameters

def findReactions(dom):
    elements=dom.getElementsByTagName("reaction")
    result={}
    for element in elements:
      id=element.getAttributeNode("id")
      if(not id):
        print "Error could not find id for reaction node."
        sys.exit(1)
      result[id.nodeValue]=element
    return result


def findRules(dom):
    result=[]
    for name in ["rateRule","assignmentRule","algebraicRule"]: 
      elements=dom.getElementsByTagName(name)
      for element in elements:
        result.append(element)
    return result

def compareEntities(e1,e2,attributes):
    result=1
    for attribute in attributes:
        a1=e1.getAttribute(attribute[0]);
        a2=e2.getAttribute(attribute[0]);
        if(a1!=a2):
            result=0
            break
    return result;


def compareUnitDefinitions(unitdefinitions1,unitdefinitions2,filename1,filename2):
  if(len(unitdefinitions1)!=len(unitdefinitions2)):
    print "The two files have a different number of unit definitions."
  for key in unitdefinitions1.keys():
    unitdefinition1=unitdefinitions1[key]
    unitdefinition2=unitdefinitions2[key]
    if(not unitdefinition2):
        print "No unit with id "+key+" in file "+filename2+"."
        continue
    compare2UnitDefinitions(unitdefinition1,unitdefinition2,filename1,filename2);
  for key in unitdefinitions2.keys():
    if(key not in unitdefinitions1.keys()):
        print "No unit with id "+key+" in file "+filename1+"."


def compare2UnitDefinitions(unitDefinition1,unitDefinition2,filename1,filename2):
   name1=unitdefinition1.getAttribute("name") 
   name2=unitdefinition2.getAttribute("name")
   if(name1!=name2):
     print "the names of "+unitDefinition1.getAttribute("id")+" and "+unitdefinition2.getAttribute("id")+" differ."
   compareChildren(unitdefinition1,unitdefinition2)

def compareChildren(node1,node2):
    result=1
    children1=node1.getChildNodes
    children2=node2.getChildNodes
    if(len(children1)!=len(children2)):
        result=0
    else:
      for i in range(0,len(children1)):
        child1=children1[i]
        child2=children2[i]
        if(child1.nodeName!=child1.nodeName):
            result=0
        else:
            attributes1=child1.attributes
            attributes2=child2.attributes
            if((attributes1 and attributes2)):
               if(len(attributes1)==len(attributes2)):
                 attributeMap1={}
                 attributeMap2={}
                 for attribute in attributes1:
                    attributeMap1[attribute.name]=attribute
                 for attribute in attributes2:
                    attributeMap2[attribute.name]=attribute
                 for key in attributeMap1.keys():
                    attribute=attributeMap2[key]
                    if(not attribute):
                        return 0
                 result=compareChildren(child1,child2)
               else:
                 return 0
            elif ((not attributes1) and (not attributes2)):
               result=compareChildren(child1,child2)
            else:
               return 0


    return result


def compareFunctionDefinitions(functions1,functions2,filename1,filename2):
  pass

def compare2FunctionDefinitions(function1,function2,filename1,filename2):
  pass

def compareCompartments(compartments1,compartments2,filename1,filename2):
    for key in compartments1.keys():
        compartment1=compartments1[key]
        compartment2=compartments2[key]
        if(not compartment2):
            print "No compartment with id "+key+" in "+filename2+"."
        else:
            compare2Compartments(compartment1,compartment2,filename1,filename2)
    for key in compartments2.keys():
        if(not compartments1[key]):
            print "No compartment with id "+key+" in "+filename1+"."


def compare2Compartments(compartment1,compartment2,filename1,filename2):
  id1=compartment1.getAttribute("id")
  id2=compartment2.getAttribute("id")
  if(id1==""):
    print "Error. Compartment without id in "+filename1
  if(id2==""):
    print "Error. Compartment without id in "+filename2
   
  if(compareEntities(compartment1,compartement2,[("id","string"),("name","string"),("spatialDimensions","int"),("size","double"),("units","string"),("outside","string"),("constant","bool")])==0):
      print "compartments "+id1+" and "+id2+" differ."


def compareSpecies(species1,species2,filename1,filename2):
    for key in species1.keys():
        s1=species1[key]
        s2=species2[key]
        if(not s2):
            print "No species with id "+key+" in "+filename2+"."
        else:
            compare2Species(s1,s2,filename1,filename2)
    for key in species2.keys():
        if(not species1[key]):
            print "No species with id "+key+" in "+filename1+"."


def compare2Species(species1,species2,filename1,filename2):
  id1=species1.getAttribute("id")
  id2=species2.getAttribute("id")
  if(id1==""):
    print "Error. Species without id in "+filename1
  if(id2==""):
    print "Error. Species without id in "+filename2
   
  if(compareEntities(species1,species2,[("id","string"),("name","string"),("compartment","string"),("initialAmount","double"),("initialConcentration","double"),("substanceUnits","string"),("spatialSizeUnits","string"),("hasOnlySubstanceUnits","bool"),("boundaryCondition","bool"),("charge","int"),("constant","bool")])==0):
      print "species "+id1+" and "+id2+" differ."


def compareParameters(parameters1,parameters2,filename1,filename2):
    for key in parameters1.keys():
        parameter1=parameters1[key]
        parameter2=parameters2[key]
        if(not parameter2):
            print "No parameter with id "+key+" in "+filename2+"."
        else:
            compare2Parameters(parameter1,parameter2,filename1,filename2)
    for key in parameters2.keys():
        if(not parameters1[key]):
            print "No parameter with id "+key+" in "+filename1+"."


def compare2Parameters(parameter1,parameter2,filename1,filename2):
  id1=parameter1.getAttribute("id")
  id2=parameter2.getAttribute("id")
  if(id1==""):
    print "Error. parameter without id in "+filename1
  if(id2==""):
    print "Error. parameter without id in "+filename2
   
  if(compareEntities(parameter1,parameter2,[("id","string"),("name","string"),("value","double"),("units","string"),("constant","bool")])==0):
      print "parameter "+id1+" and "+id2+" differ."


def compareReactions(reactions1,reactions2,filename1,filename2):
    for key in reactions1.keys():
        reaction1=reactions1[key]
        reaction2=reactions2[key]
        if(not reaction2):
            print "No reaction with id "+key+" in "+filename2+"."
        else:
            compare2Reactions(reaction1,reaction2,filename1,filename2)
    for key in reactions2.keys():
        if(not reactions1[key]):
            print "No reaction with id "+key+" in "+filename1+"."

def compare2Reactions(reaction1,reaction2,filename1,filename2):
  pass


def compareRules(rules1,rules2,filename1,filename2):
    for key in rules1.keys():
        rule1=rules1[key]
        rule2=rules2[key]
        if(not rule2):
            print "No rule for entity with id "+key+" in "+filename2+"."
        else:
            compare2Rules(rule1,rule2,filename1,filename2)
    for key in rules2.keys():
        if(not rules1[key]):
            print "No rule for entity with id "+key+" in "+filename1+"."


def compare2Rules(rule1,rule2,filename1,filename2):
  pass


def compareDocuments(doc1,doc2,filename1,filename2):
   # check if they have the same level and version
   level1=doc1.getAttribute("level");
   level2=doc2.getAttribute("level");
   if(level1==""):
     print "Error. Document in file "+filename1+" does not have a level attribute."
     sys.exit(1)
   if(level2==""):
     print "Error. Document in file "+filename2+" does not have a level attribute."
     sys.exit(1)
   if(level1 != level2):
     print "Documents have differing level attributes."

   version1=doc1.getAttribute("version");
   version2=doc2.getAttribute("version");
   if(version1==""):
     print "Error. Document in file "+filename1+" does not have a version."
     sys.exit(1)
   if(version2==""):
     print "Error. Document in file "+filename2+" does not have a version."
     sys.exit(1)
   if(version1 != version2):
     print "Documents have differing version attributes."
   model1=doc1.getElementsByTagName("model")
   if(not model1):
     print "Error. No model element found in document for "+filename1+"."
     sys.exit(1)
   model2=doc2.getElementsByTagName("model")
   if(not model2):
     print "Error. No model element found in document for "+filename2+"."
     sys.exit(1)
   if(len(model1)!=1):
     print "Error. More than one model element in the document: "+filename1
     sys.exit(1)
   if(len(model2)!=1):
     print "Error. More than one model element in the document: "+filename2
     sys.exit(1)
   compareModels(model1[0],model2[0],filename1,filename2)

def compareModels(model1,model2,filename1,filename2):
  # check if the id and the name are the same
  # check if the comments and the annotations are the same
   id1=model1.getAttribute("id");
   id2=model2.getAttribute("id");
   if((id1=="" and id2!="") or (id2=="" and id1!="") or (id1!="" and id2!="" and id1 != id2)):
     print "mode elements have differing id attributes."

   name1=model1.getAttribute("name");
   name2=model2.getAttribute("name");
   if((name1=="" and  name2!="") or (name2=="" and name1!="") or (name1!="" and name2!="" and name1 != name2)):
     print "model elements have differing name attributes."


   unitDefinitions1=findUnitDefinitions(model1)
   functionDefinitions1=findFunctionDefinitions(model1)
   compartments1=findCompartments(model1)
   metabolites1=findSpecies(model1)
   parameters1=findParameters(model1)
   reactions1=findReactions(model1)
   rules1=findRules(model1)
   unitDefinitions2=findUnitDefinitions(model2)
   functionDefinitions2=findFunctionDefinitions(model2)
   compartments2=findCompartments(model2)
   metabolites2=findSpecies(model2)
   parameters2=findParameters(model2)
   reactions2=findReactions(model2)
   rules2=findRules(model2)
   compareUnitDefinitions(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareFunctionDefinitions(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareCompartments(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareSpecies(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareParameters(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareReactions(unitDefinitions1,unitDefinitions2,filename1,filename2)
   compareRules(unitDefinitions1,unitDefinitions2,filename1,filename2)




if __name__ == "__main__":
  if(len(sys.argv)!=3):
     print "Usage: compareSBMLFiles SBMLFILE1 SBMLFILE2"
     sys.exit(1)
  FILENAME1=sys.argv[1]
  FILENAME2=sys.argv[2]
  FILE1=open(FILENAME1,"r")
  if(not FILE1):
     print "Error. Could not open "+FILENAME1+"."
     sys.exit(1)
  FILE2=open(FILENAME2,"r")
  if(not FILE2):
     print "Error. Could not open "+FILENAME2+"."
     sys.exit(1)
  dom1=createDOMTree(FILE1)
  if(not dom1):
     print "Error. Could not create DOM Tree for file "+FILENAME1+"."
     sys.exit(1)
  dom2=createDOMTree(FILE2)
  if(not dom2):
     print "Error. Could not create DOM Tree for file "+FILENAME2+"."
     sys.exit(1)

  sbmlNode1=dom1.getElementsByTagName("sbml")
  if(not sbmlNode1):
    print "Error. Could not find sbml elements in document for file "+FILENAME1+"."
    sys.exit(1)
  sbmlNode2=dom2.getElementsByTagName("sbml")
  if(not sbmlNode2):
    print "Error. Could not find sbml elements in document for file "+FILENAME2+"."
    sys.exit(1)
  if(len(sbmlNode1)!=1):
    print "Error. To many sbml elements in file "+FILENAME1+"."
    sys.exit(1)
  if(len(sbmlNode2)!=1):
    print "Error. To many sbml elements in file "+FILENAME2+"."
    sys.exit(1)
  #pdb.set_trace()
  compareDocuments(sbmlNode1[0],sbmlNode2[0],FILENAME1,FILENAME2)



