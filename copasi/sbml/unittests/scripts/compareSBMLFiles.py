# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/scripts/compareSBMLFiles.py,v $ 
#   $Revision: 1.6 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/02/15 13:11:24 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

#!/usr/bin/env python

import sys
import pdb
from xml.dom.ext.reader import Sax2
from xml.dom.ext import Print


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
       for parameter in listOfParameters.getElementsByTagName("parameter"):
            id=parameter.getAttribute("id")
            if(id==""):
                print "Error. parameter found without id."
                sys.exit(1)
            parameters[id]=parameter
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
    listOfRules=dom.getElementsByTagName("listOfRules")
    if(len(listOfRules)>1):
        print "Error. More than one listOfRules elements in model."
        sys.exit(1)
    if(len(listOfRules)==1):
        listOfRules=listOfRules[0]
        tagNames=["rateRule","assignmentRule","algebraicRule"]
        for child in listOfRules.childNodes: 
          if(child.nodeName in tagNames):
             result.append(child)
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
   name1=unitDefinition1.getAttribute("name") 
   name2=unitDefinition2.getAttribute("name")
   if(name1!=name2):
     print "the names of "+unitDefinition1.getAttribute("id")+" and "+unitdefinition2.getAttribute("id")+" differ."
   compareChildren(unitDefinition1,unitDefinition2)

def compareChildren(node1,node2):
    result=1
    children1=node1.childNodes
    children2=node2.childNodes
    if(len(children1)!=len(children2)):
        result=0
    else:
      for i in range(0,len(children1)):
        child1=children1[i]
        child2=children2[i]
        if(child1.nodeType != child2.nodeType or child1.nodeName!=child2.nodeName):
            result=0
        else:
            if(child1.nodeType==child1.ELEMENT_NODE):
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
                  if(child1.nodeName=="cn" or child1.nodeName=="ci"):
                    # check the text element
                    if(compareTextElements(child1,child2)==0):
                        return 0
                else:
                  return 0
    return result


def compareTextElements(node1,node2):
    # concatenate all text elements of both nodes and check if the resulting
    # strings are the same
    # this is not always correct, but for the cases we
    # have here (cn and ci) it should be OK
    text1=""
    for child in node1.childNodes:
        if(child.nodeType==child.TEXT_NODE):
            text1=text1+child.nodeValue
    text2=""
    for child in node2.childNodes:
        if(child.nodeType==child.TEXT_NODE):
            text2=text2+child.nodeValue
    return text1==text2



def compareFunctionDefinitions(functions1,functions2,filename1,filename2):
  # for each function definition try to find one with the same id in the
  # other file and check if the y are equal.
  # if there is none with the same id, try to find one that has a different
  # id, but has the same tree
  # if there is one, double check if it does not correspond to one with the
  # same id from the first file
  #pdb.set_trace()
  maps=[{},{}]
  for key1 in functions1.keys():
    function1=functions1[key1]
    if(key1 not in functions2.keys()):
        for key2 in functions2.keys():
            function2=functions2[key2]
            # check if function1 and function2 have the same tree
            if(compareChildren(function1,function2)==1):
                # check if function2 has a corresponding function in functions1
                if(key2 not in functions1.keys()):
                    maps[0][key1]=key2
                    maps[1][key2]=key1
                    del functions2[key2]
                    break
                else:
                    functionTemp=functions1[key2]
                    if(compareChildren(function2,functionTemp)==0):
                        maps[0][key1]=key2
                        maps[1][key2]=key1
                        del functions2[key2]
                        break

        if(key1 in maps[0].keys()):
            del functions1[key1]
            continue
    else:
        function2=functions2[key1]
        key2=key1
        if(compareChildren(function1,function2)==1):
            maps[0][key1]=key2
            maps[1][key2]=key1
            del functions1[key1]
            del functions2[key2]
        else:
            # continue the search
            for key2 in functions2.keys():
                function2=functions2[key2]
                # check if function1 and function2 have the same tree
                if(compareChildren(function1,function2)==1):
                    # check if function2 has a corresponding function in functions1
                    if(key2 not in functions1.keys()):
                        maps[0][key1]=key2
                        maps[1][key2]=key1
                        del functions2[key2]
                        break
                    else:
                        functionTemp=functions1[key2]
                        if(compareChildren(function2,functionTemp)==0):
                            maps[0][key1]=key2
                            maps[1][key2]=key1
                            del functions2[key2]
                            break
            if(key1 in maps[0].keys()):
                del functions1[key1]
                continue
  #pdb.set_trace()
  for key in maps[0].keys():
    # print "Function definition "+key+" in file "+filename1+" maps to function definition "+maps[0][key]+" in file "+filename2
    pass
  for key in functions1.keys():
    print "No corresponding function to function with id "+key+" found in "+filename2+"."
  for key in functions2.keys():
    print "No corresponding function to function with id "+key+" found in "+filename1+"."
  return maps

#def compare2FunctionDefinitions(function1,function2,filename1,filename2):
#  pass

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
   
  if(compareEntities(compartment1,compartment2,[("id","string"),("name","string"),("spatialDimensions","int"),("size","double"),("units","string"),("outside","string"),("constant","bool")])==0):
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


def compareParameters(parameters1,parameters2,filename1,filename2,parent):
    for key in parameters1.keys():
        parameter1=parameters1[key]
        parameter2=parameters2[key]
        if(not parameter2):
            print "No parameter with id "+key+" in "+parent+" in "+filename2+"."
        else:
            compare2Parameters(parameter1,parameter2,filename1,filename2,parent)
    for key in parameters2.keys():
        if(not parameters1[key]):
            print "No parameter with id "+key+" in "+parent+" in "+filename1+"."


def compare2Parameters(parameter1,parameter2,filename1,filename2,parent):
  id1=parameter1.getAttribute("id")
  id2=parameter2.getAttribute("id")
  if(id1==""):
    print "Error. parameter without id in "+parent+" in file "+filename1
  if(id2==""):
    print "Error. parameter without id in "+parent+" in file "+filename2
   
  if(compareEntities(parameter1,parameter2,[("id","string"),("name","string"),("value","double"),("units","string"),("constant","bool")])==0):
      print "parameters with id " + id1 +" in "+parent+" differ."


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
  # compare all attributes
  id1=reaction1.getAttribute("id")
  if(id1==""):
    print "Error. Found reaction without id in file "+filename1+"."
    sys.exit(1)
  id2=reaction2.getAttribute("id")
  if(id2==""):
    print "Error. Found reaction without id in file "+filename2+"."
    sys.exit(1)
  if(compareEntities(reaction1,reaction2,[("id","string"),("name","string"),("reversible","bool"),("fast","bool")])==0):
      print "reactions "+id1+" and "+id2+" differ."
  # compare the list of reactants, list of products, list of  modifiers
  list1=reaction1.getElementsByTagName("listOfReactants")
  if(len(list1)>1):
    print "Error. To many listOfReactants elements in reaction "+id1+"."
    sys.exit(1)
  list2=reaction2.getElementsByTagName("listOfReactants")
  if(len(list2)>1):
    print "Error. To many listOfReactants elements in reaction "+id2+"."
    sys.exit(1)
  if(len(list1)==len(list2) and len(list2)!=0):
    compare2SpeciesReferenceLists(list1[0],list2[0],id1,filename1,filename2)
  list1=reaction1.getElementsByTagName("listOfProducts")
  if(len(list1)>1):
    print "Error. To many listOfProducts elements in reaction "+id1+"."
    sys.exit(1)
  list2=reaction2.getElementsByTagName("listOfProducts")
  if(len(list2)>1):
    print "Error. To many listOfProducts elements in reaction "+id2+"."
    sys.exit(1)
  if(len(list1)==len(list2) and len(list2)!=0):
    compare2SpeciesReferenceLists(list1[0],list2[0],id1,filename1,filename2)
  list1=reaction1.getElementsByTagName("listOfModifiers")
  if(len(list1)>1):
    print "Error. To many listOfModifiers elements in reaction "+id1+"."
    sys.exit(1)
  list2=reaction2.getElementsByTagName("listOfModifiers")
  if(len(list2)>1):
    print "Error. To many listOfModifiers elements in reaction "+id2+"."
    sys.exit(1)
  if(len(list1)==len(list2) and len(list2)!=0):
    compare2SpeciesReferenceLists(list1[0],list2[0],id1,filename1,filename2)
  # compare the kinetic laws
  kLaw1=reaction1.getElementsByTagName("kineticLaw")
  kLaw2=reaction2.getElementsByTagName("kineticLaw")
  if(len(kLaw1)==1 and len(kLaw2)==1):
    compare2KineticLaws(kLaw1[0],kLaw2[0],id1,filename1,filename2)


def compare2SpeciesReferenceLists(list1,list2,reactionId,filename1,filename2):
    tagName="modifierSpeciesReference"
    attributes=[("species","string"),("id","string")]
    if(list1.tagName!="listOfModifiers"):
        tagName="speciesReference"
        attributes.append(("stoichiometrie","double"))
    sRefs1=list1.getElementsByTagName(tagName)
    sRefs2=list2.getElementsByTagName(tagName)
    for x in range(len(sRefs1)-1,-1,-1):
        sRef1=sRefs1[x]
        species1=sRef1.getAttribute("species")
        if(species1==""):
            print "Error. Species reference found in "+list1.tagName+" in reaction "+reactionId+" in file "+filename1+" that does not have a species attribute."
            sys.exit(1)
        for y in range(len(sRefs2)-1,-1,-1):
            sRef2=sRefs2[y]
            species2=sRef2.getAttribute("species")
            if(species2==""):
                print "Error. Species reference found in "+list2.tagName+" in reaction "+reactionId+" in file "+filename2+" that does not have a species attribute."
                sys.exit(1)
            if(species1==species2):
                del sRefs1[x]
                del sRefs2[y]
                if(compareEntities(sRef1,sRef2,attributes)==0):
                    print "speciesReference declaration for species "+species1+" in "+list1.tagName+" for reaction "+reactionId+" differ."
                else:
                    # compare the stoichiometry math
                    math1=sRef1.getElementsByTagName("stoichiometryMath")
                    math2=sRef2.getElementsByTagName("stoichiometryMath")
                    if(len(math1)==len(math2) and len(math1)!=0):
                        if(compareChildren(math1[0],math2[0])==0):
                            print "the stoichiometryMath elements in the speciesReference declaration for species "+species1+" in "+list1.tagName+" for reaction "+reactionId+" differ."
                    elif(len(math1)!=0 or len(math2)!=0):
                        print "the stoichiometryMath elements in the speciesReference declaration for species "+species1+" in "+list1.tagName+" for reaction "+reactionId+" differ."

    for sRef in sRefs1:
        print "No corresponding speciesReference for species "+sRef.getAttribute("species")+" found in "+list2.tagName+" for reaction "+reactionId+" in file "+filename2+"."
    for sRef in sRefs2:
        print "No corresponding speciesReference for species "+sRef.getAttribute("species")+" found in "+list1.tagName+" for reaction "+reactionId+" in file "+filename1+"."



def compare2KineticLaws(kLaw1,kLaw2,reactionId,filename1,filename2):
    # compare the attributes
    if(compareEntities(kLaw1,kLaw2,[("timeUnits","string"),("substanceUnits","string")])==0):
        print "The attributes of the kineticLaws for reaction "+reactionId+" differ."
    # compare the parameters
    parameters1=findParameters(kLaw1)
    parameters2=findParameters(kLaw2)
    if(len(parameters1)==len(parameters2)):
        # compare the individual number of parameters
        compareParameters(parameters1,parameters2,filename1,filename1,"kinetic law for reaction "+reactionId)
    # compare the expressions
    math1=kLaw1.getElementsByTagName("math")
    if(len(math1)!=1):
        print "Error. Wrong number of math elements in kineticlaw for reaction "+reactionId+" in file "+filename1+"."
        sys.exit(1)
    math2=kLaw2.getElementsByTagName("math")
    if(len(math2)!=1):
        print "Error. Wrong number of math elements in kineticlaw for reaction "+reactionId+" in file "+filename2+"."
        sys.exit(1)
    if(compareChildren(math1[0],math2[0])==0):
        pass
        #print "The mathematical expression for the kineticLaws of reaction "+reactionId+" differ."


def compareRules(rules1,rules2,filename1,filename2):
    #pdb.set_trace()
    ruleMappings=[[],[]]
    for X in range(0,len(rules1)):
        ruleMappings[0].append(-1)
    for X in range(0,len(rules2)):
        ruleMappings[1].append(-1)
    mappedRules=[]
    for x in range(len(rules1)-1,-1,-1):
        rule1=rules1[x]
        variable1=""
        if(rule1.tagName=="assignmentRule" or rule1.tagName=="rateRule"):
            variable1=rule1.getAttribute("variable")
            if(variable1==""):
                print "Error. variable attribute not set on "+rule1.tagName+" in file "+filename1+"."
                sys.exit(1)
        elif (rule1.tagName!="algebraicRule"):
            print "Error. Unknown rule type "+rule1.tagName+" in file "+filename1+"."
            sys.exit(1)
        for y in range(len(rules2)-1,-1,-1):
            rule2=rules2[y]
            if(rules2 in mappedRules):
                continue
            variable2=""
            if(rule2.tagName=="assignmentRule" or rule2.tagName=="rateRule"):
                variable2=rule2.getAttribute("variable")
                if(variable2==""):
                    print "Error. variable attribute not set on "+rule2.tagName+" in file "+filename2+"."
                    sys.exit(1)
            elif (rule2.tagName!="algebraicRule"):
                print "Error. Unknown rule type "+rule2.tagName+" in file "+filename2+"."
                sys.exit(1)
            if(variable1!="" and variable1==variable2):
                del rules1[x]
                mappedRules.append(rule2)
                ruleMappings[0][x]=y
                ruleMappings[1][y]=x
                if(rule1.tagName != rule2.tagName):
                    print "Rules for variable "+variable1+" are of diffferent types."
                else:
                    if(compareChildren(rule1,rule2)==0):
                        print "Rules for variable "+variable1+" differ."
                break
            elif(variable1=="" and variable2==""):
                # check if the two algebraic rules are the same
                if(compareChildren(rule1,rule2)==1):
                    del rules1[x]
                    mappedRules.append(rule2)
                    ruleMappings[0][x]=y
                    ruleMappings[1][y]=x
                    break
    algebraicCounter=0
    for rule in rules1:
        if(rule.tagName=="algebraicRule"):
            algebraicCounter+=1
        else:
            variable=rule.getAttribute("variable")
            print "No corresponding rule for variable " + variable + " found in file "+filename2 +"."
    if(algebraicCounter!=0):
        print str(algebraicCounter)+" algebraic rules found in file "+filename1+" with no corresponding rule in file "+filename2+"."
    # now delete the rules that have already ben mapped from rules2
    for rule in mappedRules:
        del rules2[rules2.index(rule)]
    for rule in rules2:
        if(rule.tagName=="algebraicRule"):
            algebraicCounter+=1
        else:
            variable=rule.getAttribute("variable")
            print "No corresponding rule for variable " + variable + " found in file "+filename1 +"."
    if(algebraicCounter!=0):
        print str(algebraicCounter)+" algebraic rules found in file "+filename2+" with no corresponding rule in file "+filename1+"."
    #pdb.set_trace()
    return ruleMappings



#def compare2Rules(rule1,rule2,filename1,filename2):
  # check if both rules have the same type
  # check if the expressions are identical
  #if(rule1.tagName!=rule2.tagName):
  #  print "Rules for 


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
   return compareModels(model1[0],model2[0],filename1,filename2)

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
   functionMappings=compareFunctionDefinitions(functionDefinitions1,functionDefinitions2,filename1,filename2)
   compareCompartments(compartments1,compartments2,filename1,filename2)
   compareSpecies(metabolites1,metabolites2,filename1,filename2)
   compareParameters(parameters1,parameters2,filename1,filename2,"the list of global parameters")
   compareReactions(reactions1,reactions2,filename1,filename2)
   ruleMappings=compareRules(rules1,rules2,filename1,filename2)
   return functionMappings,ruleMappings

def writeReorderedSecond(model2,functionMappings,ruleMappings,outfileName):
    # go through the file and replace all function ids with the corresponding
    # id from the other file
    functionDefinitions=model2.getElementsByTagName("functionDefinition")
    for functionDefinition in functionDefinitions:
        id=functionDefinition.getAttribute("id")
        if(id==""):
            print "Error. function definition without id found."
            sys.exit(1)
        if(id in functionMappings[1].keys()):
            functionDefinition.setAttribute("id",functionMappings[1][id])
        else:
            # if there is no mapping for a specific function, check if the name is
            # unique, if not, replace it by a unique name and add this to the mappings
            newId=id
            if(id in functionMappings[0].keys()):
              ext=1
              newId="function_"+str(ext)
              while((newId in functionMappings[0].keys()) or (newId in functionMappings[1].keys())):
                ext=ext+1
                newId="function_"+str(ext)
                functionDefinition.setAttribute("id",newId)
            functionMappings[1][id]=newId
    # replace all functions calls with calls to the mapped function ids
    ciNodes=model2.getElementsByTagName("ci")
    for ciNode in ciNodes:
        for node in ciNode.childNodes:
            if(node.nodeType==node.TEXT_NODE and node.nodeValue.strip() in functionMappings[1].keys()):
                node.nodeValue=" "+functionMappings[1][node.nodeValue.strip()]+" "
    # bring all rules into the same order as in the first file
    listOfRules=model2.getElementsByTagName("listOfRules")
    if(len(listOfRules)==1):
        listOfRules=listOfRules[0]
        # delete all existing rules
        ruleIndex=0
        reOrderedRules=[]
        for x in range(0,len(ruleMappings[1])):
            reOrderedRules.append(None)
        tagNames=["algebraicRule","rateRule","assignmentRule"]
        for child in listOfRules.childNodes:
            if(child.nodeType==child.ELEMENT_NODE):
                if(child.tagName in tagNames):
                    # which position will this rule get
                    newPosition=ruleMappings[1][ruleIndex]
                    if(newPosition==-1):
                        reOrderedRules.append(child)
                    else:
                        reOrderedRules[newPosition]=child
                    ruleIndex=ruleIndex+1 
        ruleIndex=0
        #pdb.set_trace()
        for X in range(0,len(listOfRules.childNodes)):
            child=listOfRules.childNodes[X]
            if(child.nodeType==child.ELEMENT_NODE):
                if(child.tagName in tagNames):
                  if(child!=reOrderedRules[ruleIndex]):
                    listOfRules.replaceChild(reOrderedRules[ruleIndex].cloneNode(1),child)
                ruleIndex=ruleIndex+1
    elif(len(listOfRules)>1):
        print "Error. More than one listOfRules elements found in model."
        sys.exit(1)
    # write the reordered model
    outfile=open(outfileName,"w")
    Print(model2,outfile)




if __name__ == "__main__":
  if(len(sys.argv)!=4):
     print "Usage: compareSBMLFiles SBMLFILE1 SBMLFILE2 OUTFILENAME"
     sys.exit(1)
  FILENAME1=sys.argv[1]
  FILENAME2=sys.argv[2]
  OUTFILENAME=sys.argv[3]
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
  functionMappings,ruleMappings=compareDocuments(sbmlNode1[0],sbmlNode2[0],FILENAME1,FILENAME2)
  writeReorderedSecond(dom2,functionMappings,ruleMappings,OUTFILENAME)


