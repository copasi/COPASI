#!/bin/env python
import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()
assert (isinstance(dm, COPASI.CDataModel))


def setup_sensitivities(report_name):

    # activate sensitivity task
    task = dm.getTask('Sensitivities')
    task.setScheduled(True)

    problem = task.getProblem()
    assert (isinstance(problem, COPASI.CSensProblem))
    # set subtask type
    problem.setSubTaskType(COPASI.CSensProblem.TimeSeries)
    # set effect (either using the object lists, or a specific CN of an object)
    item = COPASI.CSensItem()
    item.setListType(COPASI.CObjectLists.NON_CONST_METAB_CONCENTRATIONS)
    # or use item.setSingleObjectCN(...)
    problem.setTargetFunctions(item)
    # set cause by just removing all, and then adding the primary (and secondary cause)
    problem.removeVariables()
    item = COPASI.CSensItem()
    item.setListType(COPASI.CObjectLists.ALL_PARAMETER_VALUES)
    problem.addVariables(item)
    # add a secondary cause just like that

    # set the report filename
    report = task.getReport()
    assert (isinstance(report, COPASI.CReport))
    report.setTarget(report_name)


if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args < 3:
        print("usage: run_sensitivities <sbml file | copasi file> <report name>")
        sys.exit(1)

    file_name = sys.argv[1]
    # try and read the file
    if not dm.loadModel(file_name) and not dm.importSBML(file_name):
        print ("Model could not be loaded.")
        print (COPASI.CCopasiMessage.getAllMessageText())
        sys.exit(2)

    # sets up the sensitivities task
    setup_sensitivities(sys.argv[2])

    # next save the model for use with CopasiSE
    # dm.saveModel('out_sens.cps', True)
    # or run the task ...

