# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CEvent.py,v $ 
#   $Revision: 1.1.2.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2010/05/04 19:53:02 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import math

class Test_CEvent(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.model=self.datamodel.getModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.model.createMetabolite("metab1","Comp1")
    self.event1=self.model.createEvent("Event_1")

  def test_Base(self):
    self.assert_(self.event1 != None)
    self.assert_(self.event1.__class__ == COPASI.CEvent)

  def test_Order(self):
    self.event1.setOrder(25);
    self.assert_(self.event1.getOrder()==25)

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
    assignment.setTargetKey(self.metab.getKey())
    self.assert_(assignment.getTargetKey() == self.metab.getKey())
    expression = "5.0+12.3"
    assignment.setExpression(expression)
    expression2 = assignment.getExpression()
    self.assert_(expression2 == expression)

 
def suite():
  tests=[
          'test_Base'
         ,'test_Order'
         ,'test_DelayAssignment'
         ,'test_TriggerExpression'
         ,'test_DelayExpression'
         ,'test_Assignments'
        ]
  return unittest.TestSuite(map(Test_CEvent,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


