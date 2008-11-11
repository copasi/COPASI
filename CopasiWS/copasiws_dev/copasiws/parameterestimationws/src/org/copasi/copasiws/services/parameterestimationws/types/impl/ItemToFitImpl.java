// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ItemToFitImpl.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:54 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/*
 * XML Type:  ItemToFit
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ItemToFit
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML ItemToFit(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ItemToFitImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ItemToFit {
    private static final javax.xml.namespace.QName SPECIES$0 = new javax.xml.namespace.QName("",
            "species");
    private static final javax.xml.namespace.QName REACTION$2 = new javax.xml.namespace.QName("",
            "reaction");
    private static final javax.xml.namespace.QName ARBITRARYVARIABLE$4 = new javax.xml.namespace.QName("",
            "arbitraryVariable");
    private static final javax.xml.namespace.QName AFFECTEDEXPERIMENT$6 = new javax.xml.namespace.QName("",
            "affectedExperiment");
    private static final javax.xml.namespace.QName MODELOBJECTTYPE$8 = new javax.xml.namespace.QName("",
            "modelObjectType");
    private static final javax.xml.namespace.QName LOWERBOUND$10 = new javax.xml.namespace.QName("",
            "lowerBound");
    private static final javax.xml.namespace.QName UPPERBOUND$12 = new javax.xml.namespace.QName("",
            "upperBound");
    private static final javax.xml.namespace.QName STARTVALUE$14 = new javax.xml.namespace.QName("",
            "startValue");

    public ItemToFitImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "species" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Species getSpecies() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Species target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Species) get_store()
                                                                                            .find_element_user(SPECIES$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "species" element
     */
    public boolean isSetSpecies() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(SPECIES$0) != 0;
        }
    }

    /**
     * Sets the "species" element
     */
    public void setSpecies(
        org.copasi.copasiws.services.parameterestimationws.types.Species species) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Species target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Species) get_store()
                                                                                            .find_element_user(SPECIES$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.Species) get_store()
                                                                                                .add_element_user(SPECIES$0);
            }

            target.set(species);
        }
    }

    /**
     * Appends and returns a new empty "species" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Species addNewSpecies() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Species target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Species) get_store()
                                                                                            .add_element_user(SPECIES$0);

            return target;
        }
    }

    /**
     * Unsets the "species" element
     */
    public void unsetSpecies() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(SPECIES$0, 0);
        }
    }

    /**
     * Gets the "reaction" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Reaction getReaction() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Reaction target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction) get_store()
                                                                                             .find_element_user(REACTION$2,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "reaction" element
     */
    public boolean isSetReaction() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(REACTION$2) != 0;
        }
    }

    /**
     * Sets the "reaction" element
     */
    public void setReaction(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction reaction) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Reaction target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction) get_store()
                                                                                             .find_element_user(REACTION$2,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction) get_store()
                                                                                                 .add_element_user(REACTION$2);
            }

            target.set(reaction);
        }
    }

    /**
     * Appends and returns a new empty "reaction" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Reaction addNewReaction() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Reaction target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction) get_store()
                                                                                             .add_element_user(REACTION$2);

            return target;
        }
    }

    /**
     * Unsets the "reaction" element
     */
    public void unsetReaction() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(REACTION$2, 0);
        }
    }

    /**
     * Gets the "arbitraryVariable" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable getArbitraryVariable() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable) get_store()
                                                                                                      .find_element_user(ARBITRARYVARIABLE$4,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "arbitraryVariable" element
     */
    public boolean isSetArbitraryVariable() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(ARBITRARYVARIABLE$4) != 0;
        }
    }

    /**
     * Sets the "arbitraryVariable" element
     */
    public void setArbitraryVariable(
        org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable arbitraryVariable) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable) get_store()
                                                                                                      .find_element_user(ARBITRARYVARIABLE$4,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable) get_store()
                                                                                                          .add_element_user(ARBITRARYVARIABLE$4);
            }

            target.set(arbitraryVariable);
        }
    }

    /**
     * Appends and returns a new empty "arbitraryVariable" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable addNewArbitraryVariable() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable) get_store()
                                                                                                      .add_element_user(ARBITRARYVARIABLE$4);

            return target;
        }
    }

    /**
     * Unsets the "arbitraryVariable" element
     */
    public void unsetArbitraryVariable() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(ARBITRARYVARIABLE$4, 0);
        }
    }

    /**
     * Gets array of all "affectedExperiment" elements
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[] getAffectedExperimentArray() {
        synchronized (monitor()) {
            check_orphaned();

            java.util.List targetList = new java.util.ArrayList();
            get_store().find_all_element_users(AFFECTEDEXPERIMENT$6, targetList);

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[] result =
                new org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[targetList.size()];
            targetList.toArray(result);

            return result;
        }
    }

    /**
     * Gets ith "affectedExperiment" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment getAffectedExperimentArray(
        int i) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment) get_store()
                                                                                                       .find_element_user(AFFECTEDEXPERIMENT$6,
                    i);

            if (target == null) {
                throw new IndexOutOfBoundsException();
            }

            return target;
        }
    }

    /**
     * Returns number of "affectedExperiment" element
     */
    public int sizeOfAffectedExperimentArray() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(AFFECTEDEXPERIMENT$6);
        }
    }

    /**
     * Sets array of all "affectedExperiment" element
     */
    public void setAffectedExperimentArray(
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[] affectedExperimentArray) {
        synchronized (monitor()) {
            check_orphaned();
            arraySetterHelper(affectedExperimentArray, AFFECTEDEXPERIMENT$6);
        }
    }

    /**
     * Sets ith "affectedExperiment" element
     */
    public void setAffectedExperimentArray(int i,
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment affectedExperiment) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment) get_store()
                                                                                                       .find_element_user(AFFECTEDEXPERIMENT$6,
                    i);

            if (target == null) {
                throw new IndexOutOfBoundsException();
            }

            target.set(affectedExperiment);
        }
    }

    /**
     * Inserts and returns a new empty value (as xml) as the ith "affectedExperiment" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment insertNewAffectedExperiment(
        int i) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment) get_store()
                                                                                                       .insert_element_user(AFFECTEDEXPERIMENT$6,
                    i);

            return target;
        }
    }

    /**
     * Appends and returns a new empty value (as xml) as the last "affectedExperiment" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment addNewAffectedExperiment() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment) get_store()
                                                                                                       .add_element_user(AFFECTEDEXPERIMENT$6);

            return target;
        }
    }

    /**
     * Removes the ith "affectedExperiment" element
     */
    public void removeAffectedExperiment(int i) {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(AFFECTEDEXPERIMENT$6, i);
        }
    }

    /**
     * Gets the "modelObjectType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType.Enum getModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(MODELOBJECTTYPE$8);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "modelObjectType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType xgetModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) get_store()
                                                                                                              .find_attribute_user(MODELOBJECTTYPE$8);

            return target;
        }
    }

    /**
     * True if has "modelObjectType" attribute
     */
    public boolean isSetModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(MODELOBJECTTYPE$8) != null;
        }
    }

    /**
     * Sets the "modelObjectType" attribute
     */
    public void setModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType.Enum modelObjectType) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(MODELOBJECTTYPE$8);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(MODELOBJECTTYPE$8);
            }

            target.setEnumValue(modelObjectType);
        }
    }

    /**
     * Sets (as xml) the "modelObjectType" attribute
     */
    public void xsetModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType modelObjectType) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) get_store()
                                                                                                              .find_attribute_user(MODELOBJECTTYPE$8);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) get_store()
                                                                                                                  .add_attribute_user(MODELOBJECTTYPE$8);
            }

            target.set(modelObjectType);
        }
    }

    /**
     * Unsets the "modelObjectType" attribute
     */
    public void unsetModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(MODELOBJECTTYPE$8);
        }
    }

    /**
     * Gets the "lowerBound" attribute
     */
    public double getLowerBound() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(LOWERBOUND$10);

            if (target == null) {
                return 0.0;
            }

            return target.getDoubleValue();
        }
    }

    /**
     * Gets (as xml) the "lowerBound" attribute
     */
    public org.apache.xmlbeans.XmlDouble xgetLowerBound() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlDouble target = null;
            target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                         .find_attribute_user(LOWERBOUND$10);

            return target;
        }
    }

    /**
     * True if has "lowerBound" attribute
     */
    public boolean isSetLowerBound() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(LOWERBOUND$10) != null;
        }
    }

    /**
     * Sets the "lowerBound" attribute
     */
    public void setLowerBound(double lowerBound) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(LOWERBOUND$10);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(LOWERBOUND$10);
            }

            target.setDoubleValue(lowerBound);
        }
    }

    /**
     * Sets (as xml) the "lowerBound" attribute
     */
    public void xsetLowerBound(org.apache.xmlbeans.XmlDouble lowerBound) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlDouble target = null;
            target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                         .find_attribute_user(LOWERBOUND$10);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                             .add_attribute_user(LOWERBOUND$10);
            }

            target.set(lowerBound);
        }
    }

    /**
     * Unsets the "lowerBound" attribute
     */
    public void unsetLowerBound() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(LOWERBOUND$10);
        }
    }

    /**
     * Gets the "upperBound" attribute
     */
    public double getUpperBound() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(UPPERBOUND$12);

            if (target == null) {
                return 0.0;
            }

            return target.getDoubleValue();
        }
    }

    /**
     * Gets (as xml) the "upperBound" attribute
     */
    public org.apache.xmlbeans.XmlDouble xgetUpperBound() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlDouble target = null;
            target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                         .find_attribute_user(UPPERBOUND$12);

            return target;
        }
    }

    /**
     * True if has "upperBound" attribute
     */
    public boolean isSetUpperBound() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(UPPERBOUND$12) != null;
        }
    }

    /**
     * Sets the "upperBound" attribute
     */
    public void setUpperBound(double upperBound) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(UPPERBOUND$12);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(UPPERBOUND$12);
            }

            target.setDoubleValue(upperBound);
        }
    }

    /**
     * Sets (as xml) the "upperBound" attribute
     */
    public void xsetUpperBound(org.apache.xmlbeans.XmlDouble upperBound) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlDouble target = null;
            target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                         .find_attribute_user(UPPERBOUND$12);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlDouble) get_store()
                                                             .add_attribute_user(UPPERBOUND$12);
            }

            target.set(upperBound);
        }
    }

    /**
     * Unsets the "upperBound" attribute
     */
    public void unsetUpperBound() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(UPPERBOUND$12);
        }
    }

    /**
     * Gets the "startValue" attribute
     */
    public float getStartValue() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(STARTVALUE$14);

            if (target == null) {
                return 0.0f;
            }

            return target.getFloatValue();
        }
    }

    /**
     * Gets (as xml) the "startValue" attribute
     */
    public org.apache.xmlbeans.XmlFloat xgetStartValue() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_attribute_user(STARTVALUE$14);

            return target;
        }
    }

    /**
     * True if has "startValue" attribute
     */
    public boolean isSetStartValue() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(STARTVALUE$14) != null;
        }
    }

    /**
     * Sets the "startValue" attribute
     */
    public void setStartValue(float startValue) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(STARTVALUE$14);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(STARTVALUE$14);
            }

            target.setFloatValue(startValue);
        }
    }

    /**
     * Sets (as xml) the "startValue" attribute
     */
    public void xsetStartValue(org.apache.xmlbeans.XmlFloat startValue) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_attribute_user(STARTVALUE$14);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                            .add_attribute_user(STARTVALUE$14);
            }

            target.set(startValue);
        }
    }

    /**
     * Unsets the "startValue" attribute
     */
    public void unsetStartValue() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(STARTVALUE$14);
        }
    }

    /**
     * An XML modelObjectType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ItemToFit$ModelObjectType.
     */
    public static class ModelObjectTypeImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType {
        public ModelObjectTypeImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected ModelObjectTypeImpl(org.apache.xmlbeans.SchemaType sType,
            boolean b) {
            super(sType, b);
        }
    }
}
