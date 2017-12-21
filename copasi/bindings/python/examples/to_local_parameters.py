import COPASI
import sys

try:
    dataModel = COPASI.CCopasiRootContainer.addDatamodel()
except:
    dataModel = COPASI.CRootContainer.addDatamodel()

def create_local_parameters(input_file, output_file):
    """

    This function reads a file, and converts local to global parameters.

    :param input_file: input copasi file
    :param output_file:  output copasi file
    :return: status
    """

    if not dataModel.loadModel(input_file):
        if not dataModel.importSBML(input_file):
            print("Couldn't open input file")
            return 1

    model = dataModel.getModel()

    for i in range(model.getNumReactions()):
        reaction = model.getReaction(i)
        convert_reaction_parameters(model, reaction)

    dataModel.saveModel(output_file, True)

    return 0


def convert_reaction_parameters(model, reaction):
    """

    Convert all local parameters of the reaction and create them
    as local parameters in the model

    :param model: the model in which to create the model values
    :param reaction: the reaction whose parameters to replace
    :return: None
    """
    reaction_name = reaction.getObjectName()
    params = reaction.getParameters()
    for j in range(params.size()):
        current = params.getParameter(j)
        mv = model.createModelValue('{0}_{1}'.format(reaction_name, current.getObjectName()),
                                    reaction.getParameterValue(current.getObjectName()))
        reaction.setParameterMapping(current.getObjectName(), mv.getKey())


if __name__ == "__main__":

    if len(sys.argv) < 3:
        print ("Usage: to_local_parameters <input_copasi_file> <output_copasi_file>")
        sys.exit(0)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    create_local_parameters(input_file, output_file)
