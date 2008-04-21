# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CMatrix.py,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/21 10:27:07 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CMatrix(unittest.TestCase):
  def setUp(self):
    self.numRows=5
    self.numCols=11
    self.matrix=COPASI.FloatMatrix(self.numRows,self.numCols)

  def test_numRows(self):
    n=self.matrix.numRows()
    self.assert_(type(n)==IntType)
    self.assert_(n==self.numRows)

  def test_numCols(self):
    n=self.matrix.numCols()
    self.assert_(type(n)==IntType)
    self.assert_(n==self.numCols)


  def test_size(self):
    n=self.matrix.size()
    self.assert_(type(n)==IntType)
    self.assert_(n==(self.numCols*self.numRows))

  def test_resize(self):
    nr=13
    nc=2
    self.matrix.resize(nr,nc)
    self.assert_(self.matrix.numRows()==nr)
    self.assert_(self.matrix.numCols()==nc)
    self.assert_(self.matrix.size()==nr*nc)

def suite():
  tests=[
          'test_numRows'
         ,'test_numCols'
         ,'test_size'
         ,'test_resize'
        ]
  return unittest.TestSuite(map(Test_CMatrix,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


