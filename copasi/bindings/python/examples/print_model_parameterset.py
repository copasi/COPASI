import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()
assert (isinstance(dm, COPASI.CDataModel))


def print_group(label, group):
    # type: (str, COPASI.CModelParameterGroup) -> None
    """ This function takes a parameter group and prints it"""
    print (label)
    for i in range(group.size()):
        current = group.getChild(i)

        if isinstance(current, COPASI.CModelParameterGroup):  # reaction parameters have a subgroup for each rection
            print ("  Reaction: %s" % current.getName())

            for j in range(current.size()):  # followed by the kinetic parameters
                param = current.getChild(j)
                print ("    {0} = {1}".format(param.getName(), param.getValue(COPASI.CCore.Framework_Concentration)))
        else:  # otherwise we just have name value pairs
            print ("    {0} = {1}".format(current.getName(), current.getValue(COPASI.CCore.Framework_Concentration)))


def print_set(parameter_set):
    #  type: (COPASI.CModelParameterSet) -> None
    """This function takes a model parameter set and prints all of its content"""

    print ("Parameter set: %s" % parameter_set.getObjectName())
    parameter_set.compile()  # need to compile otherwise we might not get concentrations
    # time ... here we just take out the value of the first group / first child that will be the time
    group = parameter_set.getModelParameter(0)
    child = group.getChild(0)
    print ("  Initial time: %d" % child.getValue(COPASI.CCore.Framework_Concentration))
    # compartment sizes
    print_group("  Compartment Sizes", parameter_set.getModelParameter(1))
    # species concentrations
    print_group("  Species Concentrations", parameter_set.getModelParameter(2))
    # global quantities
    print_group("  Global Quantities", parameter_set.getModelParameter(3))
    # kinetic parameters
    print_group("  Kinetic Parameters", parameter_set.getModelParameter(4))


def print_model_parameter_set(input_file, parameter_set):
    # type: (str, str) -> None
    """This function reads a COPASI file, and prints either all parameter sets, or the one with the given name"""
    if not dm.loadModel(input_file):
        print ("Model could not be loaded.")
        print (COPASI.CCopasiMessage.getAllMessageText())
        return

    model = dm.getModel()
    assert (isinstance(model, COPASI.CModel))

    # get parameter sets
    sets = model.getModelParameterSets()

    for current in sets:  # iterate over all of them
        assert (isinstance(current, COPASI.CModelParameterSet))

        if (parameter_set is not None) and (current.getObjectName() != parameter_set):
            continue  # parameter set was specified and current name is different so continue to another one

        print_set(current)


if __name__ == "__main__":
    num_args = len(sys.argv)
    file_name = None
    parameter_set = None
    if num_args < 2:
        print ("usage: print_model_parameterset <model file> [parameter set name]")
        sys.exit(1)
    file_name = sys.argv[1]

    if num_args > 2:
        parameter_set = sys.argv[2]

    print_model_parameter_set(file_name, parameter_set)

