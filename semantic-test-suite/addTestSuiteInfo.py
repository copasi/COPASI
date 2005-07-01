#!/usr/bin/python


import sys
from xml.dom.minidom import parse, parseString
import xml.dom.ext

infileName=sys.argv[1]
endTime=sys.argv[2]
stepNumber=sys.argv[3]
resultFilename=sys.argv[4]
tempDirectory=sys.argv[5]
speciesNames=sys.argv[6:]

domTree=parse(infileName)

    
def getModelName(CopasiNode):
    modelName=""
    for child in CopasiNode.childNodes:
        if child.localName=="Model":
            modelName=child.getAttribute("name")
            break
    return modelName

#def getCompartmentName(CopasiNode):
#    compartmentName=""
#    for child1 in CopasiNode.childNodes:
#        if child1.localName=="Model":
#            for child2 in child1.childNodes:
#                if child2.localName=="ListOfCompartments":
#                    for child3 in child2.childNodes:
#                        if child3.localName=="Compartment":
#                            compartmentName=child3.getAttribute("name")
#                            break
#    return compartmentName


def createSpecies2CompartmentMap(CopasiNode):
    species2compartmentmap={}
    compartmentKey2CompartmentNameMap={}
    for child1 in CopasiNode.childNodes:
        if child1.localName=="Model":
            for child2 in child1.childNodes:
                if child2.localName=="ListOfCompartments":
                    for child3 in child2.childNodes:
                        if child3.localName=="Compartment":
                            compartmentName=child3.getAttribute("name")
                            compartmentKey=child3.getAttribute("key")
                            compartmentKey2CompartmentNameMap[compartmentKey]=compartmentName
                
                if child2.localName=="ListOfMetabolites":
                    for child3 in child2.childNodes:
                        if child3.localName=="Metabolite":
                            speciesId=child3.getAttribute("name")
                            compartmentKey=child3.getAttribute("compartment")
                            if(not compartmentKey2CompartmentNameMap.has_key(compartmentKey)):
                                print "ERROR: No compartment found for key \""+compartmentKey+"\"." 
                                sys.exit(1)    
                            species2compartmentmap[speciesId]=compartmentKey2CompartmentNameMap[compartmentKey]
    return species2compartmentmap;


    
for node in domTree.childNodes:
    startTime="0"
    if node.localName=="COPASI":
        modelName=getModelName(node)
        
        # delete the list of tasks and the list of reports
        for child in node.childNodes:
            if child.localName=="ListOfTasks":
                node.removeChild(child)
            if child.localName=="ListOfReports":
                node.removeChild(child)
        
        listOfTasksNode=domTree.createElement("ListOfTasks")
       
        node.appendChild(listOfTasksNode)
       
        taskNode=domTree.createElement("Task")
        listOfTasksNode.appendChild(taskNode)
        
        taskNode.setAttribute("key","Task_1")
        taskNode.setAttribute("name","Time-Course")
        taskNode.setAttribute("type","timeCourse")
        taskNode.setAttribute("scheduled","true")
        
        reportNode=domTree.createElement("Report")
        taskNode.appendChild(reportNode)

        reportNode.setAttribute("reference","CReportDefinition_0")
        reportNode.setAttribute("target",resultFilename)
        reportNode.setAttribute("append","0")

        problemNode=domTree.createElement("Problem")
        taskNode.appendChild(problemNode)
        
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","StepNumber")
        parameterNode.setAttribute("type","unsignedInteger")
        parameterNode.setAttribute("value",stepNumber)
        
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","StepSize")
        parameterNode.setAttribute("type","float")
        parameterNode.setAttribute("value",str((float(endTime)-float(startTime))/float(stepNumber)))
         
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","StartTime")
        parameterNode.setAttribute("type","float")
        parameterNode.setAttribute("value",startTime)
        
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","EndTime")
        parameterNode.setAttribute("type","float")
        parameterNode.setAttribute("value",endTime)
         
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","TimeSeriesRequested")
        parameterNode.setAttribute("type","bool")
        parameterNode.setAttribute("value","1")
        
        parameterNode=domTree.createElement("Parameter")
        problemNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","OutputStartTime")
        parameterNode.setAttribute("type","float")
        parameterNode.setAttribute("value",startTime)

        methodNode=domTree.createElement("Method")
        taskNode.appendChild(methodNode)

        methodNode.setAttribute("name","Deterministic (LSODA)")
        methodNode.setAttribute("type","Deterministic(LSODA)")

        parameterNode=domTree.createElement("Parameter")
        methodNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","LSODA.RelativeTolerance")
        parameterNode.setAttribute("type","unsignedFloat")
        parameterNode.setAttribute("value","1e-06")

        parameterNode=domTree.createElement("Parameter")
        methodNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","LSODA.AbsoluteTolerance")
        parameterNode.setAttribute("type","unsignedFloat")
        parameterNode.setAttribute("value","1e-12")

        parameterNode=domTree.createElement("Parameter")
        methodNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","LSODA.AdamsMaxOrder")
        parameterNode.setAttribute("type","unsignedInteger")
        parameterNode.setAttribute("value","12")

        parameterNode=domTree.createElement("Parameter")
        methodNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","LSODA.BDFMaxOrder")
        parameterNode.setAttribute("type","unsignedInteger")
        parameterNode.setAttribute("value","5")

        parameterNode=domTree.createElement("Parameter")
        methodNode.appendChild(parameterNode)

        parameterNode.setAttribute("name","LSODA.MaxStepsInternal")
        parameterNode.setAttribute("type","unsignedInteger")
        parameterNode.setAttribute("value","10000")

        listOfReportsNode=domTree.createElement("ListOfReports")
        node.appendChild(listOfReportsNode)

        reportNode=domTree.createElement("Report")
        listOfReportsNode.appendChild(reportNode)

        reportNode.setAttribute("key","CReportDefinition_0")
        reportNode.setAttribute("name","ReportDefinition_0")
        reportNode.setAttribute("taskType","timeCourse")

        commentNode=domTree.createElement("Comment")
        reportNode.appendChild(commentNode)

        bodyNode=domTree.createElement("body")
        commentNode.appendChild(bodyNode)

        bodyNode.setAttribute("xmlns","http://www.w3.org/1999/xhtml")

        tableNode=domTree.createElement("Table")
        reportNode.appendChild(tableNode)

        objectNode=domTree.createElement("Object")
        tableNode.appendChild(objectNode)

        objectNode.setAttribute("cn","CN=Root,Model="+modelName+",Reference=Time")

        species2compartmentmap=createSpecies2CompartmentMap(node)
        for speciesName in speciesNames:
            objectNode=domTree.createElement("Object")
            tableNode.appendChild(objectNode)
            compartmentName="";
            if(species2compartmentmap.has_key(speciesName)):
               compartmentName=species2compartmentmap[speciesName]
            else:
               print "ERROR: Unknown species \""+speciesName+"\"."
               sys.exit(1)  
            objectNode.setAttribute("cn","CN=Root,Model="+modelName+",Vector=Compartments["+compartmentName+"],Vector=Metabolites["+speciesName+"],Reference=Concentration")
        

xml.dom.ext.PrettyPrint(domTree,file(infileName,"w"))

domTree.unlink()


