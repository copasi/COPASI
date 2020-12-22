#!/bin/env python3
import COPASI


dm = COPASI.CRootContainer.addDatamodel()


def create_datahandler(names):
  """initialize datahandler from display names
  """
  dh = COPASI.CDataHandler()
  for name in names:
    obj = dm.findObjectByDisplayName(name)
    
    if not obj: 
      print('no object for name {0}'.format(name))
      continue

    if isinstance(obj, COPASI.CModel): # fix for time
      obj = obj.getValueReference()

    cn = obj.getCN().getString()
    dh.addDuringName(COPASI.CRegisteredCommonName(cn))
    print('added {0}'.format(cn))
  return dh


def print_results(dh):
  """prints the data as tsv
  """
  num = dh.getNumRowsDuring()
  for i in range(num): 
    current = dh.getNthRow(i)
    for j in current:
      print('{0}\t'.format(j), end='')
    print('\n', end='')
  pass

if __name__ == "__main__":

  # the brusselator example is distributed with copasi, or grab it from: 
  # https://github.com/copasi/COPASI/blob/develop/TestSuite/distribution/brusselator.cps
  dm.loadModel('brusselator.cps')
  dh = create_datahandler(['Time', '[X]', '[Y]', '(R4).Flux'])
  tc = dm.getTask('Time-Course')
  tc.initializeRawWithOutputHandler(COPASI.CCopasiTask.OUTPUT_DURING, dh)
  tc.processRaw(True)
  print_results(dh)
