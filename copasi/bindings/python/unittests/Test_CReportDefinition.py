import COPASI
import unittests
from types import *


class Test_CReportDefinition(unittests.TestCase):
  def setUp(self):
    self.repdef=COPASI.CReportDefinition("reportDefinition")
    self.setComment("This is a test")

  def test_getComment(self):
    comment=self.repdef.getComment()
    self._assert(type(comment)==StringType)

  def test_setComment(self):
    comment="comment"
    self.repdef.setComment(comment)
    self._assert(self.repdef.getComment()==comment)
    

  def test_setTaskType(self):
    tt=CCopasiTask.mca
    self.repdef.setTaskType(tt)
    self._assert(self.repdef.getTaskType()==tt)

  def test_getTaskType(self):
    tt=self.repdef.getTaskType()
    self._assert(type(tt)==IntType)


  def test_setSeparator(self):
    text="zzz"
    sep=COPASI.CCopasiReportSeparator(text)
    self.repdef.setSeparator(sep)
    self._assert(self.repdef.getSeparator().getStaticString()==text)

  def test_getSeparator(self):
    sep=self.repdef.getSeparator()
    self._assert(sep.__class__==COPASI.CCopasiReportSeparator)

  def test_getTitle(self):
    v=self.repdef.getTitle()
    self._assert(type(v)==BooleanType)

  def test_setTitle(self):
    v=true
    self.repdef.setTitle(v)
    self._assert(self.repdef.getTitle()==v)
    v=false
    self.repdef.setTitle(v)
    self._assert(self.repdef.getTitle()==v)

  def test_isTable(self):
    v=self.repdef.isTable()
    self._assert(type(v)==BooleanType)
    

  def test_setIsTable(self):
    v=true
    self.repdef.setIsTable(v)
    self._assert(self.repdef.isTable()==v)
    v=false
    self.repdef.setIsTable(v)
    self._assert(self.repdef.isTable()==v)

  def test_getPrecision(self):
    p=self.repdef.getPrecision()
    self._assert(type(p)==IntType)


  def test_setPrecision(self):
    p=13
    self.repdef.setPrecision(p)
    self._assert(self.repdef.getPrecision()==p)

  def test_getKey(self):
    key=self.repdef.getKey()
    self._assert(type(key)==StringType) 

  def test_getTableAddr(self):
    self._assert(false)

  def test_getFooterAddr(self):
    self._assert(false)
  
  def test_getHeaderAddr(self):
    self._assert(false)
  
  def test_getBodyAddr(self):
    self._assert(false)

