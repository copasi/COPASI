// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

import org.COPASI.*;

/**
 * This example demonstrates how to use the unit validator to calculate the
 * units of local parameters of a reaction. (Since those units are not actually
 * stored on local parameter elements, they will have to be calculated on the
 * fly)
 * 
 * The CUnitValidator class can also be used to calculate units of other
 * expressions.
 */
public class CalculateUnits {

    public static void main(String[] args) {

        if (args.length == 0) {
            System.out.println("usage: CalculateUnits <cps file> ");
            return;
        }

        CDataModel dataModel = CRootContainer.addDatamodel();

        // load a model
        if (!dataModel.loadModel(args[0])) {
            System.out.println("Couldn't open the model: ");
            System.out.println(CCopasiMessage.getAllMessageText());
            return;
        }

        // get model, and set initial values
        CModel model = dataModel.getModel();
        model.applyInitialValues();
        CMathContainer maths = model.getMathContainer();

        // go through reactions and print the units of their
        // constituents
        for (int i = 0; i < model.getNumReactions(); i++) {
            CReaction reaction = model.getReaction(i);
            printUnits(reaction, maths);
        }

    }

    private static void printUnits(CReaction reaction, CMathContainer maths) {
        System.out.println("Units for reaction: " + reaction.getObjectName());

        CReactionInterface ri = new CReactionInterface();
        ri.init(reaction);

        CUnitStdVector variables = new CUnitStdVector();

        for (int i = 0; i < ri.size(); i++) {

            switch (ri.getUsage(i)) {
                case CFunctionParameter.Role_SUBSTRATE:
                case CFunctionParameter.Role_PRODUCT:
                case CFunctionParameter.Role_MODIFIER: {
                    if (ri.isVector(i)) {
                        StringStdVector units = ri.getUnitVector(i);
                        for (int j = 0; j < units.size(); j++) {
                            variables.add(new CUnit(units.get(j)));
                        }
                    } else {
                        variables.add(new CUnit(ri.getUnit(i)));
                    }
                    break;
                }
                case CFunctionParameter.Role_PARAMETER:
                case CFunctionParameter.Role_TIME:
                case CFunctionParameter.Role_VOLUME: {
                    variables.add(new CUnit(ri.getUnit(i)));
                    break;
                }
                default: {
                    break;
                }
            }
        }

        CUnitValidator validator = new CUnitValidator(maths, ri.getFunction());

        validator.validateUnits(new CUnit(ri.getEffectiveKineticLawUnit()), variables);

        CValidatedUnitStdVector validated = validator.getVariableUnits();

        for (int i = 0; i < ri.size(); i++) {
            if (i < validated.size()) {
                CValidatedUnit unit = validated.get(i);
                if (unit.conflict())
                    System.err
                            .println("\t Conflicting Unit for " + ri.getParameterName(i) + ": " + unit.getExpression());
                else
                    System.out.println("\t Unit for " + ri.getParameterName(i) + ": " + unit.getExpression());
            }
        }

    }
}
