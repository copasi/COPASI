#!/bin/env python

# This script reads a COPASI file, as well as a tab delimited file, and creates optimization items (that is
# parameters that COPASI might vary during an optimization / parameter estimation task) for the entries contained
# therein. The resulting file will be written into an output file that is provided as final argument.
#
# The tab delimited file should have the following structure:
#
#   name    min_value   max_value   start_value
#
# where 'name' is a display name as used in COPASI, 'min_value' and 'max_value' are strings representing the lower
# and upper bound of the range and 'start_value' is the start value that the next optimization should take. all double
# values are to be written in either floating point or scientific notation, using a dot as decimal separator.
#
# Examples for display names are:
#
#   (R1).k1 -> representing a local parameter 'k1' in a Reaction named 'R1'
#   [X]_0   -> for the initial concentration of a species 'X'
#   Values[scale].InitialValue -> the initial value of a global parameter 'scale'
#
#

import COPASI
import sys
import csv

dm = COPASI.CRootContainer.addDatamodel()
assert (isinstance(dm, COPASI.CDataModel))
print("using COPASI: %s" % COPASI.CVersion.VERSION.getVersion())


def parse_settings(file_name):
    # simple helper function parsing the csv file and returning a list of items found
    opt_items = []
    with open(file_name) as tab_data:
        data_reader = csv.reader(tab_data, delimiter='\t')
        for entry in data_reader:
            opt_items.append(entry)

    return opt_items


def add_optitems_from_files(input_cps_file, settings_file, output_file):
    global dm
    # read COPASI file
    if not dm.loadModel(input_cps_file):
        print("Couldn't read COPASI file")
        raise ValueError(COPASI.CCopasiMessage_getAllMessageText())

    # read settings file
    settings = parse_settings(settings_file)

    if len(settings) == 0:
        # nothing to do
        return

    # get fit task & problem
    task = dm.getTask('Parameter Estimation')  # could also be dm.getTask('Optimization') for an optimization problem
    problem = task.getProblem()

    # add items
    for entry in settings:
        p = dm.findObjectByDisplayName(entry[0])  # we locate the parameter in the currently loaded file
        if p is None:  # skip over non-existing items
            continue
        item = problem.addOptItem(p.getCN())   # if we found it, we can get its internal identifier and create the item
        item.setLowerBound(COPASI.CCommonName(entry[1]))   # set the lower
        item.setUpperBound(COPASI.CCommonName(entry[2]))   # and upper bound
        item.setStartValue(float(entry[3]))                # as well as the initial value
        print('...added optitem for %s in range(%s, %s) and start value %s' % (entry[0], entry[1], entry[2], entry[3]))

    # finally save result file
    dm.saveModel(output_file, True)


if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args < 4:
        print ("usage: add_optitems <in cps file> <tab settings file> <out cps_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    tab_settings = sys.argv[2]
    out_file = sys.argv[3]

    add_optitems_from_files(input_file, tab_settings, out_file)
