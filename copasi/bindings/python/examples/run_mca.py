#!/usr/bin/env python

# This example loads an SBML file and runs the MCA task on it,
# finally the result is plotted.
#


from __future__ import print_function
import sys
from COPASI import *
from types import *

dataModel = None


def print_annotated_matrix(title, annotated_matrix):
    # type: (str, CArrayAnnotation) -> None
    """ Utility function printing an annotated matrix"""

    print(title)
    print('==========')

    size = annotated_matrix.size()
    if len(size) != 2:
        print ("  This simple function only deals with two dimensional matrices")
        return

    rows = size[0]
    columns = size[1]
    print ("Size of the matrix is: {0} rows x {1} columns".format(rows, columns))

    row_headers = annotated_matrix.getAnnotationsString(0)
    col_headers = annotated_matrix.getAnnotationsString(1)

    #print column headers
    print ("\t\t", end='')
    for i in range(columns):
        print("{0}\t".format(col_headers[i]), end='')
    print()

    for j in range(rows):
        for i in range(columns):
            if i == 0:
                print("{0}\t".format(row_headers[j]), end='')

            current_object = annotated_matrix.getObject(CCopasiObjectName("[{0}][{1}]".format(j, i)))
            assert (isinstance(current_object, CCopasiObject))
            current = current_object.printToString()
            print("{0}\t".format(current), end='')
        print()
    print()
    pass


def run_mca(fileName):
    """ This function runs the MCA task on the given SBML file"""

    global dataModel
    if dataModel is None:
        dataModel = CCopasiRootContainer.addDatamodel()
        assert (isinstance(dataModel, CCopasiDataModel))

    # load sbml file
    if not dataModel.importSBML(fileName):
        print("Could not load SBML file due to:")
        print(CCopasiMessage.getAllMessageText())
        sys.exit(1)

    # setup mca task
    task = dataModel.getTask("Metabolic Control Analysis")
    assert (isinstance(task, CMCATask))
    # mark task as executable
    task.setScheduled(True)
    problem = task.getProblem()
    assert (isinstance(problem, CMCAProblem))
    # specify that we want to perform steady state analysis
    problem.setSteadyStateRequested(True)

    # run mca task
    if not task.initialize(CCopasiTask.OUTPUT_UI):
        print ("could not initialize mca task")
        print(CCopasiMessage.getAllMessageText())
        sys.exit(2)

    if not task.processWithOutputFlags(True, CCopasiTask.OUTPUT_UI):
        print ("could not run mca task")
        print (task.getProcessError())
        sys.exit(3)

    # print results
    method = task.getMethod()
    assert (isinstance(method, CMCAMethod))
    print_annotated_matrix("Scaled Concentration Control Coefficients", method.getScaledConcentrationCCAnn())
    print_annotated_matrix("Scaled Flux Control Coefficients", method.getScaledFluxCCAnn())
    print_annotated_matrix("Scaled Elasticities", method.getScaledElasticitiesAnn())

    pass


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: run_mca <sbml file>")
        sys.exit(1)
    else:
        run_mca(sys.argv[1])
