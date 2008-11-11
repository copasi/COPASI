// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ModelToExperimentMapImpl.java,v $ 
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
 * XML Type:  ModelToExperimentMap
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML ModelToExperimentMap(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ModelToExperimentMapImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap {
    private static final javax.xml.namespace.QName EXPERIMENTDATAID$0 = new javax.xml.namespace.QName("",
            "experimentDataId");
    private static final javax.xml.namespace.QName DATAFIRSTROW$2 = new javax.xml.namespace.QName("",
            "dataFirstRow");
    private static final javax.xml.namespace.QName DATALASTROW$4 = new javax.xml.namespace.QName("",
            "dataLastRow");
    private static final javax.xml.namespace.QName EXPERIMENTTYPE$6 = new javax.xml.namespace.QName("",
            "experimentType");
    private static final javax.xml.namespace.QName DATAISROWORIENTED$8 = new javax.xml.namespace.QName("",
            "dataIsRowOriented");
    private static final javax.xml.namespace.QName WEIGHTMETHOD$10 = new javax.xml.namespace.QName("",
            "weightMethod");
    private static final javax.xml.namespace.QName NUMBEROFCOLUMN$12 = new javax.xml.namespace.QName("",
            "numberOfColumn");
    private static final javax.xml.namespace.QName MODELOBJECT$14 = new javax.xml.namespace.QName("",
            "modelObject");
    private static final javax.xml.namespace.QName EXPERIMENTSERIALNUMBER$16 = new javax.xml.namespace.QName("",
            "experimentSerialNumber");

    public ModelToExperimentMapImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "experimentDataId" element
     */
    public java.lang.String getExperimentDataId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "experimentDataId" element
     */
    public org.apache.xmlbeans.XmlString xgetExperimentDataId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(EXPERIMENTDATAID$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "experimentDataId" element
     */
    public void setExperimentDataId(java.lang.String experimentDataId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(EXPERIMENTDATAID$0);
            }

            target.setStringValue(experimentDataId);
        }
    }

    /**
     * Sets (as xml) the "experimentDataId" element
     */
    public void xsetExperimentDataId(
        org.apache.xmlbeans.XmlString experimentDataId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(EXPERIMENTDATAID$0);
            }

            target.set(experimentDataId);
        }
    }

    /**
     * Gets the "dataFirstRow" element
     */
    public java.math.BigInteger getDataFirstRow() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAFIRSTROW$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "dataFirstRow" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetDataFirstRow() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(DATAFIRSTROW$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "dataFirstRow" element
     */
    public void setDataFirstRow(java.math.BigInteger dataFirstRow) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAFIRSTROW$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(DATAFIRSTROW$2);
            }

            target.setBigIntegerValue(dataFirstRow);
        }
    }

    /**
     * Sets (as xml) the "dataFirstRow" element
     */
    public void xsetDataFirstRow(
        org.apache.xmlbeans.XmlNonNegativeInteger dataFirstRow) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(DATAFIRSTROW$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(DATAFIRSTROW$2);
            }

            target.set(dataFirstRow);
        }
    }

    /**
     * Gets the "dataLastRow" element
     */
    public java.math.BigInteger getDataLastRow() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATALASTROW$4,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "dataLastRow" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetDataLastRow() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(DATALASTROW$4,
                    0);

            return target;
        }
    }

    /**
     * Sets the "dataLastRow" element
     */
    public void setDataLastRow(java.math.BigInteger dataLastRow) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATALASTROW$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(DATALASTROW$4);
            }

            target.setBigIntegerValue(dataLastRow);
        }
    }

    /**
     * Sets (as xml) the "dataLastRow" element
     */
    public void xsetDataLastRow(
        org.apache.xmlbeans.XmlNonNegativeInteger dataLastRow) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(DATALASTROW$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(DATALASTROW$4);
            }

            target.set(dataLastRow);
        }
    }

    /**
     * Gets the "experimentType" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.Enum getExperimentType() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTTYPE$6,
                    0);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "experimentType" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ExperimentType xgetExperimentType() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ExperimentType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) get_store()
                                                                                                   .find_element_user(EXPERIMENTTYPE$6,
                    0);

            return target;
        }
    }

    /**
     * Sets the "experimentType" element
     */
    public void setExperimentType(
        org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.Enum experimentType) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTTYPE$6,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(EXPERIMENTTYPE$6);
            }

            target.setEnumValue(experimentType);
        }
    }

    /**
     * Sets (as xml) the "experimentType" element
     */
    public void xsetExperimentType(
        org.copasi.copasiws.services.parameterestimationws.types.ExperimentType experimentType) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ExperimentType target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) get_store()
                                                                                                   .find_element_user(EXPERIMENTTYPE$6,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) get_store()
                                                                                                       .add_element_user(EXPERIMENTTYPE$6);
            }

            target.set(experimentType);
        }
    }

    /**
     * Gets the "dataIsRowOriented" element
     */
    public boolean getDataIsRowOriented() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAISROWORIENTED$8,
                    0);

            if (target == null) {
                return false;
            }

            return target.getBooleanValue();
        }
    }

    /**
     * Gets (as xml) the "dataIsRowOriented" element
     */
    public org.apache.xmlbeans.XmlBoolean xgetDataIsRowOriented() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlBoolean target = null;
            target = (org.apache.xmlbeans.XmlBoolean) get_store()
                                                          .find_element_user(DATAISROWORIENTED$8,
                    0);

            return target;
        }
    }

    /**
     * Sets the "dataIsRowOriented" element
     */
    public void setDataIsRowOriented(boolean dataIsRowOriented) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAISROWORIENTED$8,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(DATAISROWORIENTED$8);
            }

            target.setBooleanValue(dataIsRowOriented);
        }
    }

    /**
     * Sets (as xml) the "dataIsRowOriented" element
     */
    public void xsetDataIsRowOriented(
        org.apache.xmlbeans.XmlBoolean dataIsRowOriented) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlBoolean target = null;
            target = (org.apache.xmlbeans.XmlBoolean) get_store()
                                                          .find_element_user(DATAISROWORIENTED$8,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlBoolean) get_store()
                                                              .add_element_user(DATAISROWORIENTED$8);
            }

            target.set(dataIsRowOriented);
        }
    }

    /**
     * Gets the "weightMethod" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.WeightMethod.Enum getWeightMethod() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(WEIGHTMETHOD$10,
                    0);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.WeightMethod.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "weightMethod" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.WeightMethod xgetWeightMethod() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.WeightMethod target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.WeightMethod) get_store()
                                                                                                 .find_element_user(WEIGHTMETHOD$10,
                    0);

            return target;
        }
    }

    /**
     * Sets the "weightMethod" element
     */
    public void setWeightMethod(
        org.copasi.copasiws.services.parameterestimationws.types.WeightMethod.Enum weightMethod) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(WEIGHTMETHOD$10,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(WEIGHTMETHOD$10);
            }

            target.setEnumValue(weightMethod);
        }
    }

    /**
     * Sets (as xml) the "weightMethod" element
     */
    public void xsetWeightMethod(
        org.copasi.copasiws.services.parameterestimationws.types.WeightMethod weightMethod) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.WeightMethod target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.WeightMethod) get_store()
                                                                                                 .find_element_user(WEIGHTMETHOD$10,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.WeightMethod) get_store()
                                                                                                     .add_element_user(WEIGHTMETHOD$10);
            }

            target.set(weightMethod);
        }
    }

    /**
     * Gets the "numberOfColumn" element
     */
    public java.math.BigInteger getNumberOfColumn() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(NUMBEROFCOLUMN$12,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "numberOfColumn" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetNumberOfColumn() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(NUMBEROFCOLUMN$12,
                    0);

            return target;
        }
    }

    /**
     * Sets the "numberOfColumn" element
     */
    public void setNumberOfColumn(java.math.BigInteger numberOfColumn) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(NUMBEROFCOLUMN$12,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(NUMBEROFCOLUMN$12);
            }

            target.setBigIntegerValue(numberOfColumn);
        }
    }

    /**
     * Sets (as xml) the "numberOfColumn" element
     */
    public void xsetNumberOfColumn(
        org.apache.xmlbeans.XmlNonNegativeInteger numberOfColumn) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(NUMBEROFCOLUMN$12,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(NUMBEROFCOLUMN$12);
            }

            target.set(numberOfColumn);
        }
    }

    /**
     * Gets array of all "modelObject" elements
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject[] getModelObjectArray() {
        synchronized (monitor()) {
            check_orphaned();

            java.util.List targetList = new java.util.ArrayList();
            get_store().find_all_element_users(MODELOBJECT$14, targetList);

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject[] result =
                new org.copasi.copasiws.services.parameterestimationws.types.ModelObject[targetList.size()];
            targetList.toArray(result);

            return result;
        }
    }

    /**
     * Gets ith "modelObject" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject getModelObjectArray(
        int i) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject) get_store()
                                                                                                .find_element_user(MODELOBJECT$14,
                    i);

            if (target == null) {
                throw new IndexOutOfBoundsException();
            }

            return target;
        }
    }

    /**
     * Returns number of "modelObject" element
     */
    public int sizeOfModelObjectArray() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(MODELOBJECT$14);
        }
    }

    /**
     * Sets array of all "modelObject" element
     */
    public void setModelObjectArray(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject[] modelObjectArray) {
        synchronized (monitor()) {
            check_orphaned();
            arraySetterHelper(modelObjectArray, MODELOBJECT$14);
        }
    }

    /**
     * Sets ith "modelObject" element
     */
    public void setModelObjectArray(int i,
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject modelObject) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject) get_store()
                                                                                                .find_element_user(MODELOBJECT$14,
                    i);

            if (target == null) {
                throw new IndexOutOfBoundsException();
            }

            target.set(modelObject);
        }
    }

    /**
     * Inserts and returns a new empty value (as xml) as the ith "modelObject" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject insertNewModelObject(
        int i) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject) get_store()
                                                                                                .insert_element_user(MODELOBJECT$14,
                    i);

            return target;
        }
    }

    /**
     * Appends and returns a new empty value (as xml) as the last "modelObject" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelObject addNewModelObject() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelObject target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelObject) get_store()
                                                                                                .add_element_user(MODELOBJECT$14);

            return target;
        }
    }

    /**
     * Removes the ith "modelObject" element
     */
    public void removeModelObject(int i) {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(MODELOBJECT$14, i);
        }
    }

    /**
     * Gets the "experimentSerialNumber" attribute
     */
    public int getExperimentSerialNumber() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(EXPERIMENTSERIALNUMBER$16);

            if (target == null) {
                return 0;
            }

            return target.getIntValue();
        }
    }

    /**
     * Gets (as xml) the "experimentSerialNumber" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber xgetExperimentSerialNumber() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) get_store()
                                                                                                                                .find_attribute_user(EXPERIMENTSERIALNUMBER$16);

            return target;
        }
    }

    /**
     * True if has "experimentSerialNumber" attribute
     */
    public boolean isSetExperimentSerialNumber() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(EXPERIMENTSERIALNUMBER$16) != null;
        }
    }

    /**
     * Sets the "experimentSerialNumber" attribute
     */
    public void setExperimentSerialNumber(int experimentSerialNumber) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(EXPERIMENTSERIALNUMBER$16);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(EXPERIMENTSERIALNUMBER$16);
            }

            target.setIntValue(experimentSerialNumber);
        }
    }

    /**
     * Sets (as xml) the "experimentSerialNumber" attribute
     */
    public void xsetExperimentSerialNumber(
        org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber experimentSerialNumber) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) get_store()
                                                                                                                                .find_attribute_user(EXPERIMENTSERIALNUMBER$16);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) get_store()
                                                                                                                                    .add_attribute_user(EXPERIMENTSERIALNUMBER$16);
            }

            target.set(experimentSerialNumber);
        }
    }

    /**
     * Unsets the "experimentSerialNumber" attribute
     */
    public void unsetExperimentSerialNumber() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(EXPERIMENTSERIALNUMBER$16);
        }
    }

    /**
     * An XML experimentSerialNumber(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap$ExperimentSerialNumber.
     */
    public static class ExperimentSerialNumberImpl extends org.apache.xmlbeans.impl.values.JavaIntHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber {
        public ExperimentSerialNumberImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected ExperimentSerialNumberImpl(
            org.apache.xmlbeans.SchemaType sType, boolean b) {
            super(sType, b);
        }
    }
}
