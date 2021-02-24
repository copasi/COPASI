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

import COPASI
import unittest
from types import *
import math

class Test_CEvent(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
    self.model=self.datamodel.getModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.model.createMetabolite("metab1","Comp1")
    self.event1=self.model.createEvent("Event_1")

  def test_Base(self):
    self.assert_(self.event1 != None)
    self.assert_(self.event1.__class__ == COPASI.CEvent)

  def test_Priority(self):
    expression = "25"
    result = self.event1.setPriorityExpression(expression)
    self.assert_(result == True)
    expression2 = self.event1.getPriorityExpression()
    self.assert_(expression == expression2);

  def test_DelayAssignment(self):
    self.event1.setDelayAssignment(True)
    self.assert_(self.event1.getDelayAssignment() == True)
    self.event1.setDelayAssignment(False)
    self.assert_(self.event1.getDelayAssignment() == False)

  def test_TriggerExpression(self):
    expression = "<CN=Root,Model=New Model,Reference=Time> gt 3.0"
    self.event1.setTriggerExpression(expression)
    expression2 = self.event1.getTriggerExpression()
    self.assert_(expression == expression2);
    
  def test_DelayExpression(self):
    expression = "7.0"
    result = self.event1.setDelayExpression(expression)
    self.assert_(result == True)
    expression2 = self.event1.getDelayExpression()
    self.assert_(expression == expression2);

  def test_Assignments(self):
    self.assert_(self.event1.getAssignments().size() == 0)
    assignment = self.event1.createAssignment()
    self.assert_(assignment.__class__ == COPASI.CEventAssignment)
    self.assert_(self.event1.getAssignments().size() == 1)
    assignment.setTargetCN(self.metab.getCN())
    self.assertEquals(assignment.getTargetCN(),self.metab.getCN().getString())
    expression = "5.0+12.3"
    assignment.setExpression(expression)
    expression2 = assignment.getExpression()
    self.assert_(expression2 == expression)

 
def suite():
  tests=[
          'test_Base'
         ,'test_Priority'
         ,'test_DelayAssignment'
         ,'test_TriggerExpression'
         ,'test_DelayExpression'
         ,'test_Assignments'
        ]
  return unittest.TestSuite(map(Test_CEvent,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


