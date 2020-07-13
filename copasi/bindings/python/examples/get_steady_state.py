#!/usr/bin/env python

# example script running a model to steady state and printing the state
# before and after

import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()
assert(isinstance(dm, COPASI.CDataModel))


def load_model(filename):
    """
    Loads a COPASI model if 'cps' is in the filename, otherwise tries
    to import the model as sbml file.
    :param filename: the filename to load
    """
    global dm
    if 'cps' in filename:
        if not dm.loadModel(filename):
            print("couldn't load %s " % filename)
            sys.exit(1)
    else:
        if not dm.importSBML(filename):
            print("couldn't load %s " % filename)
            sys.exit(1)

    # ensure that transient values are applied (for printing later, otherwise
    # printing the first state would result in nan values)
    dm.getModel().applyInitialValues()


def print_state():
    """
    prints species concentration and concentration rates, as well as
    fluxes.
    """
    model = dm.getModel()
    print("Species: ")
    for metab in model.getMetabolites():
        print(' {0} conc: {1}, rate: {2}'.format(metab.getObjectName(),
                                                 metab.getConcentration(),
                                                 metab.getConcentrationRate()))
    print('')

    print("Reactions: ")
    for reaction in model.getReactions():
        print(' {0} flux: {1}'.format(reaction.getObjectName(),
                                      reaction.getFlux()))
    print('')


def run_steady_state():
    """
    Runs the model to steady state with the parameters as defined in the COPASI
    file (or default in case of SBML)
    """
    task = dm.getTask('Steady-State')
    # setup parameters as needed here ...
    task.initialize(COPASI.CCopasiTask.NO_OUTPUT)
    task.process(True)
    task.restore()


if __name__ == "__main__":
    filename = 'brusselator.cps'
    num_args = len(sys.argv)
    if num_args > 1:
        filename = sys.argv[1]

    load_model(filename)

    print('Before running steady state')
    print('===========================')
    print_state()

    run_steady_state()

    print('After running steady state')
    print('==========================')
    print_state()
