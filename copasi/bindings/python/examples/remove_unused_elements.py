import COPASI
import sys

dm = COPASI.CRootContainer.addDatamodel()
assert (isinstance(dm, COPASI.CDataModel))


def is_cn_used(model, cn):
    # type: (COPASI.CModel, str) -> bool
    """
    Utility function that looks whether the given cn is being used by elements in the model
    :param model: the copasi model
    :param cn: the cn to an element
    :return: True, if the element is being used False otherwise
    """

    model.compileIfNecessary()

    element = dm.getObject(cn)
    cn = str(cn)

    if element is None:
        return True

    key = element.getKey()

    # go through expressions of compartments
    for comp in model.getCompartments():
        assert (isinstance(comp, COPASI.CCompartment))
        if cn in comp.getInitialExpression():
            return True
        if cn in comp.getExpression():
            return True

    # go through expressions of species
    for species in model.getMetabolites():
        assert (isinstance(species, COPASI.CMetab))
        if cn in species.getInitialExpression():
            return True
        if cn in species.getExpression():
            return True

    # go through expressions of global parameters
    for param in model.getModelValues():
        assert (isinstance(param, COPASI.CModelValue))
        if cn in param .getInitialExpression():
            return True
        if cn in param .getExpression():
            return True

    # go through chemical formula of reactions
    for reaction in model.getReactions():
        assert (isinstance(reaction, COPASI.CReaction))
        chem_eq = reaction.getChemEq()
        assert (isinstance(chem_eq, COPASI.CChemEq))
        for reactant in chem_eq.getSubstrates():
            assert (isinstance(reactant, COPASI.CChemEqElement))
            if reactant.getMetaboliteKey() == key:
                return True
        for reactant in chem_eq.getProducts():
            assert (isinstance(reactant, COPASI.CChemEqElement))
            if reactant.getMetaboliteKey() == key:
                return True

        for reactant in chem_eq.getModifiers():
            assert (isinstance(reactant, COPASI.CChemEqElement))
            if reactant.getMetaboliteKey() == key:
                return True

        if reaction.getScalingCompartment() and reaction.getScalingCompartment().getCN() == cn:
            return True

        params = reaction.getParameters()
        for j in range(params.size()):
            current = params.getParameter(j)
            current_mapping = reaction.getParameterMapping(current.getObjectName())
            for item in current_mapping:
                if item == key:
                    return True

    # go through events and event assignments
    for event in model.getEvents():
        assert (isinstance(event, COPASI.CEvent))
        if cn in event.getTriggerExpression():
            return True
        if cn in event.getDelayExpression():
            return True
        for assignment in event.getAssignments():
            assert (isinstance(assignment, COPASI.CEventAssignment))
            if assignment.getTargetKey() == key:
                return True
            if cn in assignment.getExpression():
                return True

    # if we haven't seen it till now, then it might just not be used
    return False


def remove_unused_species(model):
    # type: (COPASI.CModel) -> None
    """
    Goes through all species of the model, and removes all that are not being used by
    other parts of the model.

    :param model: the model
    """

    to_delete = []

    for metab in model.getMetabolites():
        assert (isinstance(metab, COPASI.CMetab))
        if is_cn_used(model, metab.getCN()):
            continue

        to_delete.append(metab)

    for metab in to_delete:
        print ('  Unused species found and will be deleted: %s' % metab.getObjectDisplayName())
        model.removeMetabolite(metab)

    model.setCompileFlag()


def remove_unused_compartments(model):
    # type: (COPASI.CModel) -> None
    """
    Goes through all compartments of the model, and removes all that are not being used by
    other parts of the model.

    :param model: the model
    """

    to_delete = []

    for comp in model.getCompartments():
        assert (isinstance(comp, COPASI.CCompartment))

        if comp.getMetabolites().size() > 0:
            continue

        if is_cn_used(model, comp.getCN()):
            continue

        to_delete.append(comp)

    for comp in to_delete:
        print ('  Unused compartment found and will be deleted: %s' % comp.getObjectDisplayName())
        model.removeCompartment(comp)

    model.setCompileFlag()


def remove_unused_parameters(model):
    # type: (COPASI.CModel) -> None
    """
    Goes through all global parameters of the model, and removes all that are not being used by
    other parts of the model.

    :param model: the model
    """

    to_delete = []
    for param in model.getModelValues():
        assert (isinstance(param, COPASI.CModelValue))

        if is_cn_used(model, param.getCN()):
            continue

        to_delete.append(param)

    for param in to_delete:
        print ('  Unused Global Parameter found and will be deleted: %s' % param.getObjectDisplayName())
        model.removeModelValue(param)

    model.setCompileFlag()


if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args < 2:
        print("usage: remove_unused_elements <input file> <output_file>")
        sys.exit(1)
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]

    print('Using COPASI %s' % COPASI.CVersion.VERSION.getVersion())

    if not dm.loadModel(input_file):
        print("Loading the model failed.")
        print(COPASI.CCopasiMessage.getAllMessageText())
        sys.exit(1)

    copasi_model = dm.getModel()

    print('removing unused species: ')
    remove_unused_species(copasi_model)
    print('removing unused parameters: ')
    remove_unused_parameters(copasi_model)
    print('removing unused compartments: ')
    remove_unused_compartments(copasi_model)

    dm.saveModel(output_file, True)
