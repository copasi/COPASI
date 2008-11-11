// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/ExperimentType.java,v $ 
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
 * XML Type:  ExperimentType
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ExperimentType
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML ExperimentType(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.
 */
public interface ExperimentType extends org.apache.xmlbeans.XmlString {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ExperimentType.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("experimenttype1992type");
    static final Enum TIME_COURSE = Enum.forString("Time Course");
    static final Enum STEADY_STATE = Enum.forString("Steady State");
    static final int INT_TIME_COURSE = Enum.INT_TIME_COURSE;
    static final int INT_STEADY_STATE = Enum.INT_STEADY_STATE;

    org.apache.xmlbeans.StringEnumAbstractBase enumValue();

    void set(org.apache.xmlbeans.StringEnumAbstractBase e);

    /**
     * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.ExperimentType.
     * These enum values can be used as follows:
     * <pre>
     * enum.toString(); // returns the string value of the enum
     * enum.intValue(); // returns an int value, useful for switches
     * // e.g., case Enum.INT_TIME_COURSE
     * Enum.forString(s); // returns the enum value for a string
     * Enum.forInt(i); // returns the enum value for an int
     * </pre>
     * Enumeration objects are immutable singleton objects that
     * can be compared using == object equality. They have no
     * public constructor. See the constants defined within this
     * class for all the valid values.
     */
    static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
        static final int INT_TIME_COURSE = 1;
        static final int INT_STEADY_STATE = 2;
        public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
            new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                    new Enum("Time Course", INT_TIME_COURSE),
                    new Enum("Steady State", INT_STEADY_STATE),
                });
        private static final long serialVersionUID = 1L;

        private Enum(java.lang.String s, int i) {
            super(s, i);
        }

        /**
         * Returns the enum value for a string, or null if none.
         */
        public static Enum forString(java.lang.String s) {
            return (Enum) table.forString(s);
        }

        /**
         * Returns the enum value corresponding to an int, or null if none.
         */
        public static Enum forInt(int i) {
            return (Enum) table.forInt(i);
        }

        private java.lang.Object readResolve() {
            return forInt(intValue());
        }
    }

    /**
     * A factory class with static methods for creating instances
     * of this type.
     */
    public static final class Factory {
        private Factory() {
        } // No instance of this class allowed

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType newValue(
            java.lang.Object obj) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) type.newValue(obj);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                         .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ExperimentType parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ExperimentType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
