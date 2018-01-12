import COPASI
import sys
from lxml import etree

try:
    dataModel = COPASI.CCopasiRootContainer.addDatamodel()
except:
    dataModel = COPASI.CRootContainer.addDatamodel()

def restore_names(input_file, output_file):
    """

    This function restores the names of elements from an annotation
    object.

    :param input_file: input copasi file
    :param output_file:  output copasi file
    :return: status
    """

    if not dataModel.loadModel(input_file):
        print("Couldn't open input file")
        return 1

    model = dataModel.getModel()

    restore_names_in(model.getCompartments())
    restore_names_in(model.getMetabolitesX())
    restore_names_in(model.getModelValues())
    restore_names_in(model.getReactions())
    restore_names_in(model.getEvents())

    dataModel.saveModel(output_file, True)

    return 0


def restore_names_in(vector):
    for i in range(vector.size()):
        entity = vector.get(i)
        restore_name_for(entity)


def restore_name_for(entity):
    annotation = COPASI.CAnnotation_castObject(entity)
    xml = annotation.getUnsupportedAnnotation('oldName')
    if xml == '':
        return
    doc = etree.fromstring(xml)
    name = doc.attrib.get('name', '')
    if name == '':
        return
    entity.setObjectName(name)
    annotation.removeUnsupportedAnnotation('oldName')


if __name__ == "__main__":

    if len(sys.argv) < 3:
        print ("Usage: restore_names <input_copasi_file> <output_copasi_file>")
        sys.exit(0)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    restore_names(input_file, output_file)
