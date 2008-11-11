// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/Reaction.java,v $ 
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
 * XML Type:  Reaction
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.Reaction
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML Reaction(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface Reaction extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(Reaction.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("reactiond5a4type");

    /**
     * Gets the "modelId" element
     */
    java.lang.String getModelId();

    /**
     * Gets (as xml) the "modelId" element
     */
    org.apache.xmlbeans.XmlString xgetModelId();

    /**
     * Sets the "modelId" element
     */
    void setModelId(java.lang.String modelId);

    /**
     * Sets (as xml) the "modelId" element
     */
    void xsetModelId(org.apache.xmlbeans.XmlString modelId);

    /**
     * Gets the "parameterID" element
     */
    java.lang.String getParameterID();

    /**
     * Gets (as xml) the "parameterID" element
     */
    org.apache.xmlbeans.XmlString xgetParameterID();

    /**
     * Sets the "parameterID" element
     */
    void setParameterID(java.lang.String parameterID);

    /**
     * Sets (as xml) the "parameterID" element
     */
    void xsetParameterID(org.apache.xmlbeans.XmlString parameterID);

    /**
     * Gets the "quantityType" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType.Enum getQuantityType();

    /**
     * Gets (as xml) the "quantityType" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType xgetQuantityType();

    /**
     * True if has "quantityType" attribute
     */
    boolean isSetQuantityType();

    /**
     * Sets the "quantityType" attribute
     */
    void setQuantityType(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType.Enum quantityType);

    /**
     * Sets (as xml) the "quantityType" attribute
     */
    void xsetQuantityType(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType quantityType);

    /**
     * Unsets the "quantityType" attribute
     */
    void unsetQuantityType();

    /**
     * An XML quantityType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.Reaction$QuantityType.
     */
    public interface QuantityType extends org.apache.xmlbeans.XmlString {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(QuantityType.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("quantitytype7fffattrtype");
        static final Enum PARAMETER_VALUE = Enum.forString("parameterValue");
        static final Enum FLUX = Enum.forString("flux");
        static final Enum PARTICLE_FLUX = Enum.forString("particleFlux");
        static final int INT_PARAMETER_VALUE = Enum.INT_PARAMETER_VALUE;
        static final int INT_FLUX = Enum.INT_FLUX;
        static final int INT_PARTICLE_FLUX = Enum.INT_PARTICLE_FLUX;

        org.apache.xmlbeans.StringEnumAbstractBase enumValue();

        void set(org.apache.xmlbeans.StringEnumAbstractBase e);

        /**
         * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.Reaction$QuantityType.
         * These enum values can be used as follows:
         * <pre>
         * enum.toString(); // returns the string value of the enum
         * enum.intValue(); // returns an int value, useful for switches
         * // e.g., case Enum.INT_PARAMETER_VALUE
         * Enum.forString(s); // returns the enum value for a string
         * Enum.forInt(i); // returns the enum value for an int
         * </pre>
         * Enumeration objects are immutable singleton objects that
         * can be compared using == object equality. They have no
         * public constructor. See the constants defined within this
         * class for all the valid values.
         */
        static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
            static final int INT_PARAMETER_VALUE = 1;
            static final int INT_FLUX = 2;
            static final int INT_PARTICLE_FLUX = 3;
            public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
                new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                        new Enum("parameterValue", INT_PARAMETER_VALUE),
                        new Enum("flux", INT_FLUX),
                        new Enum("particleFlux", INT_PARTICLE_FLUX),
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

            public static org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType newValue(
                java.lang.Object obj) {
                return (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) type.newValue(obj);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                    .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.Reaction.QuantityType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                   .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.Reaction parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Reaction) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
