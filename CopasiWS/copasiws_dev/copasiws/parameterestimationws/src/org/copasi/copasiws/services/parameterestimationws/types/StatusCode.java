// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/StatusCode.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:52 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/*
 * XML Type:  StatusCode
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.StatusCode
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML StatusCode(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.StatusCode.
 */
public interface StatusCode extends org.apache.xmlbeans.XmlString {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(StatusCode.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("statuscodeb63atype");
    static final Enum SUCCESS = Enum.forString("SUCCESS");
    static final Enum FAIL = Enum.forString("FAIL");
    static final Enum INCORRECTOBJECTMAP = Enum.forString("INCORRECTOBJECTMAP");
    static final Enum UNKNOWNTRANSACTION = Enum.forString("UNKNOWNTRANSACTION");
    static final Enum NOEXPERIMENTALDATA = Enum.forString("NOEXPERIMENTALDATA");
    static final Enum INCOMPLETEDATA = Enum.forString("INCOMPLETEDATA");
    static final Enum ALREADYEXISTS = Enum.forString("ALREADYEXISTS");
    static final Enum NO_OF_RESOURCES_EXCEEDED = Enum.forString(
            "NO_OF_RESOURCES_EXCEEDED");
    static final Enum COMPLETED = Enum.forString("COMPLETED");
    static final Enum SCHEDULE_TO_START = Enum.forString("SCHEDULE_TO_START");
    static final Enum RUNNING = Enum.forString("RUNNING");
    static final Enum UNKNOWN = Enum.forString("UNKNOWN");
    static final Enum SUSPENDED = Enum.forString("SUSPENDED");
    static final Enum RESOURCE_ALREADY_DELETED = Enum.forString(
            "RESOURCE_ALREADY_DELETED");
    static final Enum CANNOT_BE_STARTED = Enum.forString("CANNOT_BE_STARTED");
    static final int INT_SUCCESS = Enum.INT_SUCCESS;
    static final int INT_FAIL = Enum.INT_FAIL;
    static final int INT_INCORRECTOBJECTMAP = Enum.INT_INCORRECTOBJECTMAP;
    static final int INT_UNKNOWNTRANSACTION = Enum.INT_UNKNOWNTRANSACTION;
    static final int INT_NOEXPERIMENTALDATA = Enum.INT_NOEXPERIMENTALDATA;
    static final int INT_INCOMPLETEDATA = Enum.INT_INCOMPLETEDATA;
    static final int INT_ALREADYEXISTS = Enum.INT_ALREADYEXISTS;
    static final int INT_NO_OF_RESOURCES_EXCEEDED = Enum.INT_NO_OF_RESOURCES_EXCEEDED;
    static final int INT_COMPLETED = Enum.INT_COMPLETED;
    static final int INT_SCHEDULE_TO_START = Enum.INT_SCHEDULE_TO_START;
    static final int INT_RUNNING = Enum.INT_RUNNING;
    static final int INT_UNKNOWN = Enum.INT_UNKNOWN;
    static final int INT_SUSPENDED = Enum.INT_SUSPENDED;
    static final int INT_RESOURCE_ALREADY_DELETED = Enum.INT_RESOURCE_ALREADY_DELETED;
    static final int INT_CANNOT_BE_STARTED = Enum.INT_CANNOT_BE_STARTED;

    org.apache.xmlbeans.StringEnumAbstractBase enumValue();

    void set(org.apache.xmlbeans.StringEnumAbstractBase e);

    /**
     * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.StatusCode.
     * These enum values can be used as follows:
     * <pre>
     * enum.toString(); // returns the string value of the enum
     * enum.intValue(); // returns an int value, useful for switches
     * // e.g., case Enum.INT_SUCCESS
     * Enum.forString(s); // returns the enum value for a string
     * Enum.forInt(i); // returns the enum value for an int
     * </pre>
     * Enumeration objects are immutable singleton objects that
     * can be compared using == object equality. They have no
     * public constructor. See the constants defined within this
     * class for all the valid values.
     */
    static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
        static final int INT_SUCCESS = 1;
        static final int INT_FAIL = 2;
        static final int INT_INCORRECTOBJECTMAP = 3;
        static final int INT_UNKNOWNTRANSACTION = 4;
        static final int INT_NOEXPERIMENTALDATA = 5;
        static final int INT_INCOMPLETEDATA = 6;
        static final int INT_ALREADYEXISTS = 7;
        static final int INT_NO_OF_RESOURCES_EXCEEDED = 8;
        static final int INT_COMPLETED = 9;
        static final int INT_SCHEDULE_TO_START = 10;
        static final int INT_RUNNING = 11;
        static final int INT_UNKNOWN = 12;
        static final int INT_SUSPENDED = 13;
        static final int INT_RESOURCE_ALREADY_DELETED = 14;
        static final int INT_CANNOT_BE_STARTED = 15;
        public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
            new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                    new Enum("SUCCESS", INT_SUCCESS), new Enum("FAIL", INT_FAIL),
                    new Enum("INCORRECTOBJECTMAP", INT_INCORRECTOBJECTMAP),
                    new Enum("UNKNOWNTRANSACTION", INT_UNKNOWNTRANSACTION),
                    new Enum("NOEXPERIMENTALDATA", INT_NOEXPERIMENTALDATA),
                    new Enum("INCOMPLETEDATA", INT_INCOMPLETEDATA),
                    new Enum("ALREADYEXISTS", INT_ALREADYEXISTS),
                    new Enum("NO_OF_RESOURCES_EXCEEDED",
                        INT_NO_OF_RESOURCES_EXCEEDED),
                    new Enum("COMPLETED", INT_COMPLETED),
                    new Enum("SCHEDULE_TO_START", INT_SCHEDULE_TO_START),
                    new Enum("RUNNING", INT_RUNNING),
                    new Enum("UNKNOWN", INT_UNKNOWN),
                    new Enum("SUSPENDED", INT_SUSPENDED),
                    new Enum("RESOURCE_ALREADY_DELETED",
                        INT_RESOURCE_ALREADY_DELETED),
                    new Enum("CANNOT_BE_STARTED", INT_CANNOT_BE_STARTED),
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

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode newValue(
            java.lang.Object obj) {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) type.newValue(obj);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                     .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.StatusCode parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
