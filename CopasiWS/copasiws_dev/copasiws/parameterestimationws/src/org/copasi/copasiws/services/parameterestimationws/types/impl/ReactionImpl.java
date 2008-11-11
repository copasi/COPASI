// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ReactionImpl.java,v $ 
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
 * XML Type:  Reaction
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.Reaction
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML Reaction(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ReactionImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.Reaction {
    private static final javax.xml.namespace.QName MODELID$0 = new javax.xml.namespace.QName("",
            "modelId");
    private static final javax.xml.namespace.QName PARAMETERID$2 = new javax.xml.namespace.QName("",
            "parameterID");
    private static final javax.xml.namespace.QName QUANTITYTYPE$4 = new javax.xml.namespace.QName("",
            "quantityType");

    public ReactionImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "modelId" element
     */
    public java.lang.String getModelId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(MODELID$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "modelId" element
     */
    public org.apache.xmlbeans.XmlString xgetModelId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(MODELID$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "modelId" element
     */
    public void setModelId(java.lang.String modelId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(MODELID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(MODELID$0);
            }

            target.setStringValue(modelId);
        }
    }

    /**
     * Sets (as xml) the "modelId" element
     */
    public void xsetModelId(org.apache.xmlbeans.XmlString modelId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(MODELID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(MODELID$0);
            }

            target.set(modelId);
        }
    }

    /**
     * Gets the "parameterID" element
     */
    public java.lang.String getParameterID() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(PARAMETERID$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "parameterID" element
     */
    public org.apache.xmlbeans.XmlString xgetParameterID() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(PARAMETERID$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "parameterID" element
     */
    public void setParameterID(java.lang.String parameterID) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(PARAMETERID$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(PARAMETERID$2);
            }

            target.setStringValue(parameterID);
        }
    }

    /**
     * Sets (as xml) the "parameterID" element
     */
    public void xsetParameterID(org.apache.xmlbeans.XmlString parameterID) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(PARAMETERID$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(PARAMETERID$2);
            }

            target.set(parameterID);
        }
    }

    /**
     * Gets the "quantityType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType.Enum getQuantityType() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(QUANTITYTYPE$4);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "quantityType" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType xgetQuantityType() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) get_store()
                                                                                                          .find_attribute_user(QUANTITYTYPE$4);

            return target;
        }
    }

    /**
     * True if has "quantityType" attribute
     */
    public boolean isSetQuantityType() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(QUANTITYTYPE$4) != null;
        }
    }

    /**
     * Sets the "quantityType" attribute
     */
    public void setQuantityType(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType.Enum quantityType) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(QUANTITYTYPE$4);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(QUANTITYTYPE$4);
            }

            target.setEnumValue(quantityType);
        }
    }

    /**
     * Sets (as xml) the "quantityType" attribute
     */
    public void xsetQuantityType(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType quantityType) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) get_store()
                                                                                                          .find_attribute_user(QUANTITYTYPE$4);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) get_store()
                                                                                                              .add_attribute_user(QUANTITYTYPE$4);
            }

            target.set(quantityType);
        }
    }

    /**
     * Unsets the "quantityType" attribute
     */
    public void unsetQuantityType() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(QUANTITYTYPE$4);
        }
    }

    /**
     * An XML quantityType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.Reaction$QuantityType.
     */
    public static class QuantityTypeImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType {
        public QuantityTypeImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected QuantityTypeImpl(org.apache.xmlbeans.SchemaType sType,
            boolean b) {
            super(sType, b);
        }
    }
}
