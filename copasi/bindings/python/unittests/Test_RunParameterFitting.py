# -*- coding: utf-8 -*-
# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import Test_CreateSimpleModel
import math


TIME_COURSE_DATA="""New Model[Time]	A[ParticleNumber]	B[ParticleNumber]
0	100	0
0.25	94	6
0.5	88	12
0.75	81	19
1	68	32
1.25	62	38
1.5	52	48
1.75	47	53
2	36	64
2.25	31	69
2.5	28	72
2.75	26	74
3	21	79
3.25	19	81
3.5	16	84
3.75	14	86
4	10	90
4.25	9	91
4.5	8	92
4.75	8	92
5	7	93

0	100	0
0.25	86	14
0.5	81	19
0.75	74	26
1	64	36
1.25	59	41
1.5	52	48
1.75	45	55
2	36	64
2.25	31	69
2.5	28	72
2.75	27	73
3	22	78
3.25	20	80
3.5	18	82
3.75	18	82
4	17	83
4.25	17	83
4.5	15	85
4.75	12	88
5	9	91

0	100	0
0.25	90	10
0.5	83	17
0.75	71	29
1	62	38
1.25	55	45
1.5	48	52
1.75	45	55
2	45	55
2.25	36	64
2.5	30	70
2.75	28	72
3	21	79
3.25	15	85
3.5	11	89
3.75	10	90
4	9	91
4.25	8	92
4.5	7	93
4.75	5	95
5	5	95

0	100	0
0.25	89	11
0.5	79	21
0.75	70	30
1	64	36
1.25	58	42
1.5	51	49
1.75	45	55
2	40	60
2.25	34	66
2.5	28	72
2.75	22	78
3	21	79
3.25	21	79
3.5	19	81
3.75	19	81
4	15	85
4.25	11	89
4.5	11	89
4.75	9	91
5	8	92

0	100	0
0.25	90	10
0.5	77	23
0.75	65	35
1	59	41
1.25	54	46
1.5	49	51
1.75	43	57
2	38	62
2.25	37	63
2.5	32	68
2.75	28	72
3	20	80
3.25	18	82
3.5	16	84
3.75	16	84
4	15	85
4.25	15	85
4.5	13	87
4.75	12	88
5	9	91

0	100	0
0.25	86	14
0.5	72	28
0.75	67	33
1	61	39
1.25	53	47
1.5	49	51
1.75	41	59
2	36	64
2.25	28	72
2.5	25	75
2.75	21	79
3	19	81
3.25	16	84
3.5	15	85
3.75	12	88
4	8	92
4.25	7	93
4.5	6	94
4.75	5	95
5	5	95

0	100	0
0.25	89	11
0.5	81	19
0.75	71	29
1	59	41
1.25	51	49
1.5	44	56
1.75	38	62
2	35	65
2.25	31	69
2.5	29	71
2.75	25	75
3	21	79
3.25	20	80
3.5	19	81
3.75	17	83
4	15	85
4.25	14	86
4.5	12	88
4.75	10	90
5	9	91

0	100	0
0.25	87	13
0.5	74	26
0.75	64	36
1	58	42
1.25	49	51
1.5	42	58
1.75	40	60
2	35	65
2.25	32	68
2.5	28	72
2.75	26	74
3	21	79
3.25	18	82
3.5	16	84
3.75	15	85
4	14	86
4.25	10	90
4.5	9	91
4.75	7	93
5	6	94

0	100	0
0.25	87	13
0.5	75	25
0.75	72	28
1	65	35
1.25	54	46
1.5	51	49
1.75	48	52
2	41	59
2.25	39	61
2.5	35	65
2.75	32	68
3	28	72
3.25	25	75
3.5	22	78
3.75	20	80
4	20	80
4.25	19	81
4.5	18	82
4.75	16	84
5	14	86

0	100	0
0.25	92	8
0.5	82	18
0.75	73	27
1	67	33
1.25	61	39
1.5	54	46
1.75	47	53
2	40	60
2.25	36	64
2.5	29	71
2.75	26	74
3	24	76
3.25	22	78
3.5	19	81
3.75	18	82
4	17	83
4.25	16	84
4.5	15	85
4.75	13	87
5	11	89
"""



class Test_RunParameterFitting(unittest.TestCase):
   def setUp(self):
    self.datamodel=Test_CreateSimpleModel.createModel()

   def test_runParameterFittingOnSimpleModel(self):
        fitTask=self.datamodel.addTask(COPASI.CTaskEnum.Task_parameterFitting)
        self.assert_(fitTask!=None)
        self.assert_(fitTask.__class__==COPASI.CFitTask)
        fitMethod=fitTask.getMethod()
        self.assert_(fitMethod!=None)
        # the object must be an instance of COptMethod or a subclass thereof
        # (CFitMethod)
        self.assert_(isinstance(fitMethod,COPASI.COptMethod))
        fitProblem=fitTask.getProblem()
        self.assert_(fitProblem!=None)
        self.assert_(fitProblem.__class__==COPASI.CFitProblem)
        experimentSet=fitProblem.getParameter("Experiment Set")
        self.assert_(experimentSet!=None)
        self.assert_(experimentSet.__class__ == COPASI.CExperimentSet)
        self.assert_(experimentSet.getExperimentCount() == 0)
        # first experiment
        experiment=COPASI.CExperiment(experimentSet)
        self.assert_(experiment!=None)
        self.assert_(experiment.__class__==COPASI.CExperiment)
        with open("parameter_fitting_data_simple.txt", 'w') as data_file:
          data_file.write(TIME_COURSE_DATA)
        experiment.setFileName("parameter_fitting_data_simple.txt")
        experiment.setFirstRow(1)
        self.assert_(experiment.getFirstRow()==1)
        experiment.setLastRow(22)
        self.assert_(experiment.getLastRow()==22)
        experiment.setHeaderRow(1)
        self.assert_(experiment.getHeaderRow()==1)
        experiment.setExperimentType(COPASI.CTaskEnum.Task_timeCourse)
        self.assert_(experiment.getExperimentType()==COPASI.CTaskEnum.Task_timeCourse)
        experiment.setNumColumns(3)
        self.assert_(experiment.getNumColumns()==3)
        objectMap=experiment.getObjectMap()
        self.assert_(objectMap!=None)
        self.assert_(objectMap.__class__==COPASI.CExperimentObjectMap)
        result=objectMap.setNumCols(3)
        self.assert_(result==True)
        result=objectMap.setRole(0,COPASI.CExperiment.time)
        self.assert_(result==True)
        self.assert_(objectMap.getRole(0)==COPASI.CExperiment.time)
        model=self.datamodel.getModel()
        self.assert_(model!=None)
        self.assert_(model.__class__==COPASI.CModel)
        timeReference=model.getObject(COPASI.CCommonName("Reference=Time"))
        self.assert_(timeReference!=None)
        self.assert_(timeReference.__class__==COPASI.CDataObject)
        objectMap.setObjectCN(0,timeReference.getCN())
        # getObjectCN returns a string whereas getCN returns a
        # CCommonName
        self.assert_(objectMap.getObjectCN(0)==timeReference.getCN().getString())
        metabA=model.getMetabolite(0)
        self.assert_(metabA!=None)
        self.assert_(metabA.__class__==COPASI.CMetab)
        metabB=None
        if(metabA.getObjectName()!="A"):
            metabB=metabA
            metabA=model.getMetabolite(1)
            self.assert_(metabA!=None)
            self.assert_(metabA.__class__==COPASI.CMetab)
        else:
            metabB=model.getMetabolite(1)
            self.assert_(metabB!=None)
            self.assert_(metabB.__class__==COPASI.CMetab)
        objectMap.setRole(1,COPASI.CExperiment.dependent)
        particleReference=metabA.getObject(COPASI.CCommonName("Reference=ParticleNumber"))
        self.assert_(particleReference!=None)
        self.assert_(particleReference.__class__==COPASI.CDataObject)
        objectMap.setObjectCN(1,particleReference.getCN())
        # getObjectCN returns a string whereas getCN returns a
        # CCommonName
        self.assert_(objectMap.getObjectCN(1)==particleReference.getCN().getString())
        objectMap.setRole(2,COPASI.CExperiment.dependent)
        particleReference=metabB.getObject(COPASI.CCommonName("Reference=ParticleNumber"))
        self.assert_(particleReference!=None)
        self.assert_(particleReference.__class__==COPASI.CDataObject)
        objectMap.setObjectCN(2,particleReference.getCN())
        # getObjectCN returns a string whereas getCN returns a
        # CCommonName
        self.assert_(objectMap.getObjectCN(2)==particleReference.getCN().getString())
        # reading from string is not possible with the current C++ API
        #result=experiment.read(TIME_COURSE_DATA,False)
        #self.assert_(result==True)
        experimentSet.addExperiment(experiment)
        self.assert_(experimentSet.getExperimentCount()==1)
        # addExperiment makes a copy, so we need to get the added experiment
        # again
        experimentSet.compile(model.getMathContainer())
        experiment=experimentSet.getExperiment(0)
        self.assert_(experiment!=None)
        self.assert_(experiment.__class__==COPASI.CExperiment)

        reaction=model.getReaction(0)
        self.assert_(reaction!=None)
        self.assert_(reaction.__class__==COPASI.CReaction)
        self.assert_(reaction.isLocalParameter(0)==True)
        parameter=reaction.getParameters().getParameter(0)
        self.assert_(parameter!=None)
        self.assert_(parameter.__class__==COPASI.CCopasiParameter)
        
        # define CFitItems
        self.assert_(fitProblem.getOptItemSize()==0)
        parameterReference=parameter.getObject(COPASI.CCommonName("Reference=Value"))
        self.assert_(parameterReference!=None)
        self.assert_(parameterReference.__class__==COPASI.CDataObject)
        fitItem=fitProblem.addFitItem(parameterReference.getCN())
        self.assert_(fitItem!=None)
        self.assert_(fitItem.__class__==COPASI.CFitItem)
        fitItem.setStartValue(4.0)
        fitItem.setLowerBound(COPASI.CCommonName("0.0001"))
        fitItem.setUpperBound(COPASI.CCommonName("10"))
        self.assert_(fitItem.getStartValue()==4.0)
        # add the fit item to the correct parameter group
        optimizationItemGroup=fitProblem.getParameter("OptimizationItemList")
        self.assert_(optimizationItemGroup!=None)
        self.assert_(optimizationItemGroup.__class__==COPASI.CCopasiParameterGroup)
        # addParameter makes a copy of the fit item, so we have to get it back
        fitItem=optimizationItemGroup.getParameter(0)
        self.assert_(fitItem!=None)
        self.assert_(fitItem.__class__==COPASI.CFitItem)
        self.datamodel.saveModel('test3.cps',True)
        result=True
        try:
          result=fitTask.process(True)
        except:
          result=False
        self.assertEqual(COPASI.CCopasiMessage.getAllMessageText(), '')
        self.assert_(result==True)
        # just check if the result is in the correct range. The actual value is
        # probably off since we use only one experiment to fit
        self.assert_((fitItem.getLocalValue()-0.5)/0.5 < 1.0)

   def test_runParameterFittingOnExtendedModel(self):
        Test_CreateSimpleModel.extendModel(self.datamodel)


def suite():
  tests=[
          'test_runParameterFittingOnSimpleModel'
         ,'test_runParameterFittingOnExtendedModel'
        ]
  return unittest.TestSuite(map(Test_RunParameterFitting,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


