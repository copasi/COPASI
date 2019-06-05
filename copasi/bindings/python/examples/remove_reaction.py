import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()
assert (isinstance(dm, COPASI.CDataModel))


def remove_reaction_by_name(model, reaction_name):
    # type: (COPASI.CModel, str) -> None
    key = None
    for reaction in model.getReactions():
        if reaction.getObjectName() == reaction_name:
            key = reaction.getKey()
            break

    if key:
        model.removeReaction(key)
    else:
        print('No reaction with name "{0}" found'.format(reaction_name))


if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args < 2:
        print("usage: remove_reaction <input file> <reaction to remove> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    reaction = sys.argv[2]
    output_file = sys.argv[3]

    if not dm.loadModel(input_file):
        print("Loading the model failed.")
        print(COPASI.CCopasimessage.getAllMessageText())
        sys.exit(1)

    model = dm.getModel()

    remove_reaction_by_name(model, reaction)

    dm.saveModel(output_file, True)
