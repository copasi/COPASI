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

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import string

class Test_CCopasiMessage(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiMessage(COPASI.CCopasiMessage.ERROR,COPASI.MCSBML + 2)
    COPASI.CCopasiMessage(COPASI.CCopasiMessage.TRACE,COPASI.MCSBML + 4)
    COPASI.CCopasiMessage(COPASI.CCopasiMessage.WARNING,COPASI.MCSBML + 12,"test_function")
    COPASI.CCopasiMessage(COPASI.CCopasiMessage.WARNING,COPASI.MCOptimization + 5)
    COPASI.CCopasiMessage(COPASI.CCopasiMessage.TRACE,COPASI.MCOptimization + 7)

  def test_getText(self):
    self.assert_(COPASI.CCopasiMessage.peekLastMessage().getText().endswith("Optimization (7): No Task Type specified."),"ERROR. Message text is incorrect.")
    COPASI.CCopasiMessage.clearDeque()

  def test_getType(self):
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getType()==COPASI.CCopasiMessage.TRACE,"ERROR: Message type not correct.")
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getType()==COPASI.CCopasiMessage.WARNING,"ERROR: Message type not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_getNumber(self):
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getNumber()==COPASI.MCOptimization + 7,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getNumber()==COPASI.MCOptimization + 5,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getFirstMessage().getNumber()==COPASI.MCSBML + 2,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_clearDeque(self):
    self.assert_(COPASI.CCopasiMessage.peekFirstMessage().getNumber()!=COPASI.MCCopasiMessage + 1,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque();
    self.assert_(COPASI.CCopasiMessage.peekFirstMessage().getNumber()==COPASI.MCCopasiMessage + 1,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()


  def test_peekFirstMessage(self):
    self.assert_(COPASI.CCopasiMessage.peekFirstMessage().getNumber()==COPASI.MCSBML + 2,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.peekFirstMessage().getNumber()==COPASI.MCSBML + 2,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_peekLastMessage(self):
    self.assert_(COPASI.CCopasiMessage.peekLastMessage().getNumber()==COPASI.MCOptimization + 7,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.peekLastMessage().getNumber()==COPASI.MCOptimization + 7,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_getFirstMessage(self):
    self.assert_(COPASI.CCopasiMessage.getFirstMessage().getNumber()==COPASI.MCSBML + 2,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getFirstMessage().getNumber()==COPASI.MCSBML + 4,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getFirstMessage().getNumber()==COPASI.MCSBML + 12,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_getLastMessage(self):
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getNumber()==COPASI.MCOptimization + 7,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getNumber()==COPASI.MCOptimization + 5,"ERROR: Message number not correct.")
    self.assert_(COPASI.CCopasiMessage.getLastMessage().getNumber()==COPASI.MCSBML + 12,"ERROR: Message number not correct.")
    COPASI.CCopasiMessage.clearDeque()

  def test_getAllMessageText(self):
    text=COPASI.CCopasiMessage.getAllMessageText(True)
    self.assert_(text!="");
    COPASI.CCopasiMessage.clearDeque()
    text=COPASI.CCopasiMessage.getAllMessageText()
    self.assert_(text=="")
    self.setUp()
    text=COPASI.CCopasiMessage.getAllMessageText(False)
    self.assert_(text!="");
    COPASI.CCopasiMessage.clearDeque()

  def test_getHighestSeverity(self):
    self.assert_(COPASI.CCopasiMessage.getHighestSeverity()==COPASI.CCopasiMessage.ERROR)
    COPASI.CCopasiMessage.clearDeque()

  def test_checkForMessage(self):
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCSBML + 4)==1)
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCOptimization + 5)==1)
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCSBML + 12)==1)
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCSBML + 30)==0)
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCMathML + 2)==0)
    self.assert_(COPASI.CCopasiMessage.checkForMessage(COPASI.MCDirEntry + 2)==0)
    COPASI.CCopasiMessage.clearDeque()

def suite():
  tests=[
          'test_clearDeque'
         ,'test_getHighestSeverity'
         ,'test_getFirstMessage' 
         ,'test_getLastMessage' 
         ,'test_peekFirstMessage' 
         ,'test_peekLastMessage' 
         ,'test_getAllMessageText'
         ,'test_getText'
         ,'test_getType'
         ,'test_getNumber'
        ]
  return unittest.TestSuite(map(Test_CCopasiMessage,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


