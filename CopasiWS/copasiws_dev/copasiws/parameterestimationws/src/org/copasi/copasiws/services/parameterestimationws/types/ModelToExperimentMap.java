// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/ModelToExperimentMap.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:51 $ 
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
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML ModelToExperimentMap(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface ModelToExperimentMap extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ModelToExperimentMap.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("modeltoexperimentmap80f6type");

    /**
     * Gets the "experimentDataId" element
     */
    java.lang.String getExperimentDataId();

    /**
     * Gets (as xml) the "experimentDataId" element
     */
    org.apache.xmlbeans.XmlString xgetExperimentDataId();

    /**
     * Sets the "experimentDataId" element
     */
    void setExperimentDataId(java.lang.String experimentDataId);

    /**
     * Sets (as xml) the "experimentDataId" element
     */
    void xsetExperimentDataId(org.apache.xmlbeans.XmlString experimentDataId);

    /**
     * Gets the "dataFirstRow" element
     */
    java.math.BigInteger getDataFirstRow();

    /**
     * Gets (as xml) the "dataFirstRow" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetDataFirstRow();

    /**
     * Sets the "dataFirstRow" element
     */
    void setDataFirstRow(java.math.BigInteger dataFirstRow);

    /**
     * Sets (as xml) the "dataFirstRow" element
     */
    void xsetDataFirstRow(
        org.apache.xmlbeans.XmlNonNegativeInteger dataFirstRow);

    /**
     * Gets the "dataLastRow" element
     */
    java.math.BigInteger getDataLastRow();

    /**
     * Gets (as xml) the "dataLastRow" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetDataLastRow();

    /**
     * Sets the "dataLastRow" element
     */
    void setDataLastRow(java.math.BigInteger dataLastRow);

    /**
     * Sets (as xml) the "dataLastRow" element
     */
    void xsetDataLastRow(org.apache.xmlbeans.XmlNonNegativeInteger dataLastRow);

    /**
     * Gets the "experimentType" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.Enum getExperimentType();

    /**
     * Gets (as xml) the "experimentType" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ExperimentType xgetExperimentType();

    /**
     * Sets the "experimentType" element
     */
    void setExperimentType(
        org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.Enum experimentType);

    /**
     * Sets (as xml) the "experimentType" element
     */
    void xsetExperimentType(
        org.copasi.copasiws.services.parameterestimationws.types.ExperimentType experimentType);

    /**
     * Gets the "dataIsRowOriented" element
     */
    boolean getDataIsRowOriented();

    /**
     * Gets (as xml) the "dataIsRowOriented" element
     */
    org.apache.xmlbeans.XmlBoolean xgetDataIsRowOriented();

    /**
     * Sets the "dataIsRowOriented" element
     */
    void setDataIsRowOriented(boolean dataIsRowOriented);

    /**
     * Sets (as xml) the "dataIsRowOriented" element
     */
    void xsetDataIsRowOriented(org.apache.xmlbeans.XmlBoolean dataIsRowOriented);

    /**
     * Gets the "weightMethod" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.WeightMethod.Enum getWeightMethod();

    /**
     * Gets (as xml) the "weightMethod" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.WeightMethod xgetWeightMethod();

    /**
     * Sets the "weightMethod" element
     */
    void setWeightMethod(
        org.copasi.copasiws.services.parameterestimationws.types.WeightMethod.Enum weightMethod);

    /**
     * Sets (as xml) the "weightMethod" element
     */
    void xsetWeightMethod(
        org.copasi.copasiws.services.parameterestimationws.types.WeightMethod weightMethod);

    /**
     * Gets the "numberOfColumn" element
     */
    java.math.BigInteger getNumberOfColumn();

    /**
     * Gets (as xml) the "numberOfColumn" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetNumberOfColumn();

    /**
     * Sets the "numberOfColumn" element
     */
    void setNumberOfColumn(java.math.BigInteger numberOfColumn);

    /**
     * Sets (as xml) the "numberOfColumn" element
     */
    void xsetNumberOfColumn(
        org.apache.xmlbeans.XmlNonNegativeInteger numberOfColumn);

    /**
     * Gets array of all "modelObject" elements
     */
    org.copasi.copasiws.services.parameterestimationws.types.ModelObject[] getModelObjectArray();

    /**
     * Gets ith "modelObject" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ModelObject getModelObjectArray(
        int i);

    /**
     * Returns number of "modelObject" element
     */
    int sizeOfModelObjectArray();

    /**
     * Sets array of all "modelObject" element
     */
    void setModelObjectArray(
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject[] modelObjectArray);

    /**
     * Sets ith "modelObject" element
     */
    void setModelObjectArray(int i,
        org.copasi.copasiws.services.parameterestimationws.types.ModelObject modelObject);

    /**
     * Inserts and returns a new empty value (as xml) as the ith "modelObject" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ModelObject insertNewModelObject(
        int i);

    /**
     * Appends and returns a new empty value (as xml) as the last "modelObject" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ModelObject addNewModelObject();

    /**
     * Removes the ith "modelObject" element
     */
    void removeModelObject(int i);

    /**
     * Gets the "experimentSerialNumber" attribute
     */
    int getExperimentSerialNumber();

    /**
     * Gets (as xml) the "experimentSerialNumber" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber xgetExperimentSerialNumber();

    /**
     * True if has "experimentSerialNumber" attribute
     */
    boolean isSetExperimentSerialNumber();

    /**
     * Sets the "experimentSerialNumber" attribute
     */
    void setExperimentSerialNumber(int experimentSerialNumber);

    /**
     * Sets (as xml) the "experimentSerialNumber" attribute
     */
    void xsetExperimentSerialNumber(
        org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber experimentSerialNumber);

    /**
     * Unsets the "experimentSerialNumber" attribute
     */
    void unsetExperimentSerialNumber();

    /**
     * An XML experimentSerialNumber(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap$ExperimentSerialNumber.
     */
    public interface ExperimentSerialNumber extends org.apache.xmlbeans.XmlInt {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ExperimentSerialNumber.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("experimentserialnumberad9cattrtype");

        /**
         * A factory class with static methods for creating instances
         * of this type.
         */
        public static final class Factory {
            private Factory() {
            } // No instance of this class allowed

            public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber newValue(
                java.lang.Object obj) {
                return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) type.newValue(obj);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                          .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap.ExperimentSerialNumber) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                          .newInstance(type,
                    options);
            }
        }
    }

    /**
     * A factory class with static methods for creating instances
     * of this type.
     */
    public static final class Factory {
        private Factory() {
        } // No instance of this class allowed

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                               .parse(xis,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, options);
        }
    }
}
