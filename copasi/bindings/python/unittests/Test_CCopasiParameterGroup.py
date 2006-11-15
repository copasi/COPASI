import COPASI
import unittests
from types import *


class Test_CCopasiParameterGroup(unittests.TestCase):
  def setUp(self):
    self.paramgroup=COPASI.CCopasiParameterGroup("ParameterGroup")
    self.paramgroup.addParameter("param1",CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("param2",CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("param3",CCopasiParameter.DOUBLE)


   
  def test_addParameter(self):
    self.paramgroup.clear()
    self.paramgroup.addParameter("testparam1",CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("testparam2",CCopasiParameter.UDOUBLE)
    self.paramgroup.addParameter("testparam3",CCopasiParameter.INT)
    self.paramgroup.addParameter("testparam4",CCopasiParameter.UINT)
    self.paramgroup.addParameter("testparam5",CCopasiParameter.BOOL)
    self.paramgroup.addParameter("testparam6",CCopasiParameter.GROUP)
    self.paramgroup.addParameter("testparam7",CCopasiParameter.CN)
    self.paramgroup.addParameter("testparam8",CCopasiParameter.STRING)
    self.paramgroup.addParameter("testparam9",CCopasiParameter.KEY)
    self.paramgroup.addParameter("testparam10",CCopasiParameter.FILE)
    self._assert(self.paramgroup.size()==10)


  def test_addGroup(self):
    self.paramgroup.addGroup("testgroup")
    self._assert(self.paramgroup.size()==4)

  def test_removeParameter(self):
    self.removeParameter("param1")
    self._assert(self.paramgroup.size()==2)
    self.removeParameter(0)
    self._assert(self.paramgroup.size()==1)

  def test_getParameter(self):
    param=self.paramgroup.getParameter("param2")
    self._assert(param.__class__==COPASI.CCopasiParameter)
    self._assert(param.getObjectName()=="param2")
    param=self.paramgroup.getParameter(0)
    self._assert(param.__class__==COPASI.CCopasiParameter)
    self._assert(param.getObjectName()=="param1")

  def test_getGroup(self):
    self.paramgroup.addGroup("testgroup")
    self.paramgroup.addGroup("testgroup_2")
    group=self.paramgroup.getGroup("testgroup")
    self._assert(group.__class__==COPASI.CCopasiParameterGroup)
    self._assert(group.getObjectName()=="testgroup")
    group=self.paramgroup.getGroup(5)
    self._assert(group.__class__==COPASI.CCopasiParameterGroup)
    self._assert(group.getObjectName()=="testgroup_2")



  def test_getType(self):
    t=self.paramgroup.getType(0)
    self._assert(type(t)==IntType)
    self._assert(t==CCopasiParameter.DOUBLE)
    t2=self.paramgroup.getType("param2")
    self._assert(type(t2)==IntType)
    self._assert(t2==CCopasiParameter.DOUBLE)

  def test_getKey(self):
    key=self.paramgroup.getKey("param1")
    self._assert(type(key)==StringType)
    key=self.paramgroup.getKey(2)
    self._assert(type(key)==StringType)

  def test_getName(self):
    name=self.paramgroup.getName(1)
    self._assert(type(name)==StringType)
    self._assert(name=="param2")

  def test_size(self):
    size=self.paramgroup.size()
    self._assert(type(size)==IntType)
    self._assert(size==3)

  def test_clear(self):
    self.paramgroup.clear()
    self._assert(self.paramgroup.size()==0)

  def test_getIndex(self):
    index=self.paramgroup.getIndex("param3")
    self._assert(type(index)=IntType)
    self._assert(index==2)

def suite():
  tests=[
         ,'test_size'
         ,'test_clear'
          'test_addParameter'
         ,'test_getParameter'
         ,'test_addGroup'
         ,'test_removeParameter'
         ,'test_getGroup'
         ,'test_getType'
         ,'test_getKey'
         ,'test_getName'
         ,'test_getIndex'
        ]
  return unittests.TestSuite(map(Test_CCopasiParameterGroup,tests))

