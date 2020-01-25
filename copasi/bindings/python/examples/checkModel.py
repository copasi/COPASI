import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()

def checkModel(file_name):
  if not dm.loadModel(file_name):
    dm.importSBML(file_name)

  a = COPASI.CModelAnalyzer(dm.getModel())

  res = a.getReactionResults()

  for result in res:
    if result.hasIssue(): # only output problematic reactions
      print(result.getResultString(False, True))
  
if __name__ == "__main__": 
  if len(sys.argv) < 2: 
    print("usage: python checkModel <copasi | sbml filename)")
    sys.exit(1)
    
  checkModel(sys.argv[1])
