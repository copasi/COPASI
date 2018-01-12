import COPASI
import sys

try:
    dataModel = COPASI.CCopasiRootContainer.addDatamodel()
except:
    dataModel = COPASI.CRootContainer.addDatamodel()

def write_ids_to_names(input_file, output_file):
    """

    This function writes all sbml ids occurring in the input_file into the
    objects name fields. The previous name will be stored in an annotation
    object, so that the file can be renamed again later


    :param input_file: input copasi file
    :param output_file:  output copasi file
    :return: status
    """

    if not dataModel.loadModel(input_file):
        print("Couldn't open input file")
        return 1

    model = dataModel.getModel()

    write_ids_to_all_in(model.getCompartments())
    write_ids_to_all_in(model.getMetabolitesX())
    write_ids_to_all_in(model.getModelValues())
    write_ids_to_all_in(model.getReactions())
    write_ids_to_all_in(model.getEvents())

    dataModel.saveModel(output_file, True)

    return 0


def write_ids_to_all_in(vector):
    for i in range(vector.size()):
        entity = vector.get(i)
        write_id_to_object(entity)


def write_id_to_object(entity):
    id = entity.getSBMLId()
    if id == '':
        return
    name = entity.getObjectName()
    entity.setObjectName(id)
    annotation = COPASI.CAnnotation_castObject(entity)
    annotation.addUnsupportedAnnotation('oldName',
                                        '<oldName xmlns="http://copasi.org/annotations" name="{0}"/>'.format(name))


if __name__ == "__main__":

    if len(sys.argv) < 3:
        print ("Usage: write_ids_to_name <input_copasi_file> <output_copasi_file>")
        sys.exit(0)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    write_ids_to_names(input_file, output_file)
