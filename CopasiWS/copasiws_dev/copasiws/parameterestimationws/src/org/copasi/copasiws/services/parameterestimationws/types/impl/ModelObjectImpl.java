// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ModelObjectImpl.java,v $ 
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
 * XML Type:  ModelObject
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ModelObject
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML ModelObject(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ModelObjectImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ModelObject {
    private static final javax.xml.namespace.QName SPECIES$0 = new javax.xml.namespace.QName("",
            "species");
    private static final javax.xml.namespace.QName REACTION$2 = new javax.xml.namespace.QName("",
            "reaction");
    private static final javax.xml.namespace.QName ARBITRARYVARIABLE$4 = new javax.xml.namespace.QName("",
            "arbitraryVariable");
    private static final javax.xml.namespace.QName COLUMNINEXPERIMENTALDATA$6 = new javax.xml.namespace.QName("",
            "columnInExperimentalData");
    private static final javax.xml.namespace.QName VARIABLETYPE$8 = new javax.xml.namespace.QName("",
            "variableType");
    private static final javax.xml.namespace.QName MODELOBJECTTYPE$10 = new javax.xml.namespace.QName("",
            "modelObjectType");

    public ModelObjectImpl(org.apache.xmlbeans.SchemaType sType) {
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
     * Gets the "columnInExperimentalData" attribute
     */
    public java.math.BigInteger getColumnInExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(COLUMNINEXPERIMENTALDATA$6);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "columnInExperimentalData" attribute
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetColumnInExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_attribute_user(COLUMNINEXPERIMENTALDATA$6);

            return target;
        }
    }

    /**
     * True if has "columnInExperimentalData" attribute
     */
    public boolean isSetColumnInExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(COLUMNINEXPERIMENTALDATA$6) != null;
        }
    }

    /**
     * Sets the "columnInExperimentalData" attribute
     */
    public void setColumnInExperimentalData(
        java.math.BigInteger columnInExperimentalData) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(COLUMNINEXPERIMENTALDATA$6);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(COLUMNINEXPERIMENTALDATA$6);
            }

            target.setBigIntegerValue(columnInExperimentalData);
        }
    }

    /**
     * Sets (as xml) the "columnInExperimentalData" attribute
     */
    public void xsetColumnInExperimentalData(
        org.apache.xmlbeans.XmlNonNegativeInteger columnInExperimentalData) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_attribute_user(COLUMNINEXPERIMENTALDATA$6);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_attribute_user(COLUMNINEXPERIMENTALDATA$6);
            }

            target.set(columnInExperimentalData);
        }
    }

    /**
     * Unsets the "columnInExperimentalData" attribute
     */
    public void unsetColumnInExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(COLUMNINEXPERIMENTALDATA$6);
        }
    }

    /**
     * Gets the "variableType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType.Enum getVariableType() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(VARIABLETYPE$8);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "variableType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType xgetVariableType() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType) get_store()
                                                                                                             .find_attribute_user(VARIABLETYPE$8);

            return target;
        }
    }

    /**
     * True if has "variableType" attribute
     */
    public boolean isSetVariableType() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(VARIABLETYPE$8) != null;
        }
    }

    /**
     * Sets the "variableType" attribute
     */
    public void setVariableType(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType.Enum variableType) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(VARIABLETYPE$8);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(VARIABLETYPE$8);
            }

            target.setEnumValue(variableType);
        }
    }

    /**
     * Sets (as xml) the "variableType" attribute
     */
    public void xsetVariableType(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType variableType) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType) get_store()
                                                                                                             .find_attribute_user(VARIABLETYPE$8);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType) get_store()
                                                                                                                 .add_attribute_user(VARIABLETYPE$8);
            }

            target.set(variableType);
        }
    }

    /**
     * Unsets the "variableType" attribute
     */
    public void unsetVariableType() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(VARIABLETYPE$8);
        }
    }

    /**
     * Gets the "modelObjectType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType.Enum getModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(MODELOBJECTTYPE$10);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "modelObjectType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType xgetModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType) get_store()
                                                                                                                .find_attribute_user(MODELOBJECTTYPE$10);

            return target;
        }
    }

    /**
     * True if has "modelObjectType" attribute
     */
    public boolean isSetModelObjectType() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(MODELOBJECTTYPE$10) != null;
        }
    }

    /**
     * Sets the "modelObjectType" attribute
     */
    public void setModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType.Enum modelObjectType) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(MODELOBJECTTYPE$10);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(MODELOBJECTTYPE$10);
            }

            target.setEnumValue(modelObjectType);
        }
    }

    /**
     * Sets (as xml) the "modelObjectType" attribute
     */
    public void xsetModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType modelObjectType) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType) get_store()
                                                                                                                .find_attribute_user(MODELOBJECTTYPE$10);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType) get_store()
                                                                                                                    .add_attribute_user(MODELOBJECTTYPE$10);
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
            get_store().remove_attribute(MODELOBJECTTYPE$10);
        }
    }

    /**
     * An XML variableType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ModelObject$VariableType.
     */
    public static class VariableTypeImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.ModelObject.VariableType {
        public VariableTypeImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected VariableTypeImpl(org.apache.xmlbeans.SchemaType sType,
            boolean b) {
            super(sType, b);
        }
    }

    /**
     * An XML modelObjectType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ModelObject$ModelObjectType.
     */
    public static class ModelObjectTypeImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.ModelObject.ModelObjectType {
        public ModelObjectTypeImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected ModelObjectTypeImpl(org.apache.xmlbeans.SchemaType sType,
            boolean b) {
            super(sType, b);
        }
    }
}
