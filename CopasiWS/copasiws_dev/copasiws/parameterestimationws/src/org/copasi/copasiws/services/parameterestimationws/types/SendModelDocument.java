// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/SendModelDocument.java,v $ 
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
 * An XML document type.
 * Localname: SendModel
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * A document containing one SendModel(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public interface SendModelDocument extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(SendModelDocument.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("sendmodel95fadoctype");

    /**
     * Gets the "SendModel" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel getSendModel();

    /**
     * Sets the "SendModel" element
     */
    void setSendModel(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel sendModel);

    /**
     * Appends and returns a new empty "SendModel" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel addNewSendModel();

    /**
     * An XML SendModel(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public interface SendModel extends org.apache.xmlbeans.XmlObject {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(SendModel.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("sendmodeld547elemtype");

        /**
         * Gets the "resourceId" element
         */
        int getResourceId();

        /**
         * Gets (as xml) the "resourceId" element
         */
        org.apache.xmlbeans.XmlInt xgetResourceId();

        /**
         * Sets the "resourceId" element
         */
        void setResourceId(int resourceId);

        /**
         * Sets (as xml) the "resourceId" element
         */
        void xsetResourceId(org.apache.xmlbeans.XmlInt resourceId);

        /**
         * Gets the "userId" element
         */
        java.lang.String getUserId();

        /**
         * Gets (as xml) the "userId" element
         */
        org.apache.xmlbeans.XmlString xgetUserId();

        /**
         * Sets the "userId" element
         */
        void setUserId(java.lang.String userId);

        /**
         * Sets (as xml) the "userId" element
         */
        void xsetUserId(org.apache.xmlbeans.XmlString userId);

        /**
         * Gets the "copasiml" element
         */
        java.lang.String getCopasiml();

        /**
         * Gets (as xml) the "copasiml" element
         */
        org.apache.xmlbeans.XmlString xgetCopasiml();

        /**
         * True if has "copasiml" element
         */
        boolean isSetCopasiml();

        /**
         * Sets the "copasiml" element
         */
        void setCopasiml(java.lang.String copasiml);

        /**
         * Sets (as xml) the "copasiml" element
         */
        void xsetCopasiml(org.apache.xmlbeans.XmlString copasiml);

        /**
         * Unsets the "copasiml" element
         */
        void unsetCopasiml();

        /**
         * Gets the "sbml" element
         */
        java.lang.String getSbml();

        /**
         * Gets (as xml) the "sbml" element
         */
        org.apache.xmlbeans.XmlString xgetSbml();

        /**
         * True if has "sbml" element
         */
        boolean isSetSbml();

        /**
         * Sets the "sbml" element
         */
        void setSbml(java.lang.String sbml);

        /**
         * Sets (as xml) the "sbml" element
         */
        void xsetSbml(org.apache.xmlbeans.XmlString sbml);

        /**
         * Unsets the "sbml" element
         */
        void unsetSbml();

        /**
         * Gets the "inputFormat" attribute
         */
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat.Enum getInputFormat();

        /**
         * Gets (as xml) the "inputFormat" attribute
         */
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat xgetInputFormat();

        /**
         * True if has "inputFormat" attribute
         */
        boolean isSetInputFormat();

        /**
         * Sets the "inputFormat" attribute
         */
        void setInputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat.Enum inputFormat);

        /**
         * Sets (as xml) the "inputFormat" attribute
         */
        void xsetInputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat inputFormat);

        /**
         * Unsets the "inputFormat" attribute
         */
        void unsetInputFormat();

        /**
         * An XML inputFormat(@).
         *
         * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument$SendModel$InputFormat.
         */
        public interface InputFormat extends org.apache.xmlbeans.XmlString {
            public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(InputFormat.class.getClassLoader(),
                    "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                                   .resolveHandle("inputformat4d10attrtype");
            static final Enum SBML = Enum.forString("SBML");
            static final Enum COPASI_ML = Enum.forString("CopasiML");
            static final int INT_SBML = Enum.INT_SBML;
            static final int INT_COPASI_ML = Enum.INT_COPASI_ML;

            org.apache.xmlbeans.StringEnumAbstractBase enumValue();

            void set(org.apache.xmlbeans.StringEnumAbstractBase e);

            /**
             * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument$SendModel$InputFormat.
             * These enum values can be used as follows:
             * <pre>
             * enum.toString(); // returns the string value of the enum
             * enum.intValue(); // returns an int value, useful for switches
             * // e.g., case Enum.INT_SBML
             * Enum.forString(s); // returns the enum value for a string
             * Enum.forInt(i); // returns the enum value for an int
             * </pre>
             * Enumeration objects are immutable singleton objects that
             * can be compared using == object equality. They have no
             * public constructor. See the constants defined within this
             * class for all the valid values.
             */
            static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
                static final int INT_SBML = 1;
                static final int INT_COPASI_ML = 2;
                public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
                    new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                            new Enum("SBML", INT_SBML),
                            new Enum("CopasiML", INT_COPASI_ML),
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

                public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat newValue(
                    java.lang.Object obj) {
                    return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) type.newValue(obj);
                }

                public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat newInstance() {
                    return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                          .newInstance(type,
                        null);
                }

                public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat newInstance(
                    org.apache.xmlbeans.XmlOptions options) {
                    return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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

            public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                          .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
