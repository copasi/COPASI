import COPASI
import unittest
from types import *


class Test_CReportDefinition(unittest.TestCase):
  def setUp(self):
    self.repdef=COPASI.CReportDefinition("reportDefinition")
    self.repdef.setComment("This is a test")

  def test_getComment(self):
    comment=self.repdef.getComment()
    self.assert_(type(comment)==StringType)

  def test_setComment(self):
    comment="comment"
    self.repdef.setComment(comment)
    self.assert_(self.repdef.getComment()==comment)
    

  def test_setTaskType(self):
    tt=CCopasiTask.mca
    self.repdef.setTaskType(tt)
    self.assert_(self.repdef.getTaskType()==tt)

  def test_getTaskType(self):
    tt=self.repdef.getTaskType()
    self.assert_(type(tt)==IntType)


  def test_setSeparator(self):
    text="zzz"
    sep=COPASI.CCopasiReportSeparator(text)
    self.repdef.setSeparator(sep)
    self.assert_(self.repdef.getSeparator().getStaticString()==text)

  def test_getSeparator(self):
    sep=self.repdef.getSeparator()
    self.assert_(sep.__class__==COPASI.CCopasiReportSeparator)

  def test_getTitle(self):
    v=self.repdef.getTitle()
    self.assert_(type(v)==BooleanType)

  def test_setTitle(self):
    v=1
    self.repdef.setTitle(v)
    self.assert_(self.repdef.getTitle()==v)
    v=0
    self.repdef.setTitle(v)
    self.assert_(self.repdef.getTitle()==v)

  def test_isTable(self):
    v=self.repdef.isTable()
    self.assert_(type(v)==BooleanType)
    

  def test_setIsTable(self):
    v=1
    self.repdef.setIsTable(v)
    self.assert_(self.repdef.isTable()==v)
    v=0
    self.repdef.setIsTable(v)
    self.assert_(self.repdef.isTable()==v)

  def test_getPrecision(self):
    p=self.repdef.getPrecision()
    self.assert_(type(p)==IntType)


  def test_setPrecision(self):
    p=13
    self.repdef.setPrecision(p)
    self.assert_(self.repdef.getPrecision()==p)

  def test_getKey(self):
    key=self.repdef.getKey()
    self.assert_(type(key)==StringType) 

  def test_getTableAddr(self):
    self.assert_(0)

  def test_getFooterAddr(self):
    self.assert_(0)
  
  def test_getHeaderAddr(self):
    self.assert_(0)
  
  def test_getBodyAddr(self):
    self.assert_(0)


def suite():
  tests=[
          'test_getComment'
         ,'test_setComment'
         ,'test_getTaskType'
         ,'test_setTaskType'
         ,'test_getSeparator'
         ,'test_setSeparator'
         ,'test_getTitle'
         ,'test_setTitle'
         ,'test_isTable'
         ,'test_setIsTable'
         ,'test_getPrecision'
         ,'test_setPrecision'
         ,'test_getKey'
         ,'test_getTableAddr'
         ,'test_getFooterAddr'
         ,'test_getHeaderAddr'
         ,'test_getBodyAddr'
        ]
  return unittest.TestSuite(map(Test_CReportDefinition,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


