// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/ItemToFit.java,v $ 
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
 * XML Type:  ItemToFit
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ItemToFit
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML ItemToFit(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface ItemToFit extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ItemToFit.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("itemtofit39cctype");

    /**
     * Gets the "species" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.Species getSpecies();

    /**
     * True if has "species" element
     */
    boolean isSetSpecies();

    /**
     * Sets the "species" element
     */
    void setSpecies(
        org.copasi.copasiws.services.parameterestimationws.types.Species species);

    /**
     * Appends and returns a new empty "species" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.Species addNewSpecies();

    /**
     * Unsets the "species" element
     */
    void unsetSpecies();

    /**
     * Gets the "reaction" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.Reaction getReaction();

    /**
     * True if has "reaction" element
     */
    boolean isSetReaction();

    /**
     * Sets the "reaction" element
     */
    void setReaction(
        org.copasi.copasiws.services.parameterestimationws.types.Reaction reaction);

    /**
     * Appends and returns a new empty "reaction" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.Reaction addNewReaction();

    /**
     * Unsets the "reaction" element
     */
    void unsetReaction();

    /**
     * Gets the "arbitraryVariable" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable getArbitraryVariable();

    /**
     * True if has "arbitraryVariable" element
     */
    boolean isSetArbitraryVariable();

    /**
     * Sets the "arbitraryVariable" element
     */
    void setArbitraryVariable(
        org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable arbitraryVariable);

    /**
     * Appends and returns a new empty "arbitraryVariable" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable addNewArbitraryVariable();

    /**
     * Unsets the "arbitraryVariable" element
     */
    void unsetArbitraryVariable();

    /**
     * Gets array of all "affectedExperiment" elements
     */
    org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[] getAffectedExperimentArray();

    /**
     * Gets ith "affectedExperiment" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment getAffectedExperimentArray(
        int i);

    /**
     * Returns number of "affectedExperiment" element
     */
    int sizeOfAffectedExperimentArray();

    /**
     * Sets array of all "affectedExperiment" element
     */
    void setAffectedExperimentArray(
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment[] affectedExperimentArray);

    /**
     * Sets ith "affectedExperiment" element
     */
    void setAffectedExperimentArray(int i,
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment affectedExperiment);

    /**
     * Inserts and returns a new empty value (as xml) as the ith "affectedExperiment" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment insertNewAffectedExperiment(
        int i);

    /**
     * Appends and returns a new empty value (as xml) as the last "affectedExperiment" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment addNewAffectedExperiment();

    /**
     * Removes the ith "affectedExperiment" element
     */
    void removeAffectedExperiment(int i);

    /**
     * Gets the "modelObjectType" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType.Enum getModelObjectType();

    /**
     * Gets (as xml) the "modelObjectType" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType xgetModelObjectType();

    /**
     * True if has "modelObjectType" attribute
     */
    boolean isSetModelObjectType();

    /**
     * Sets the "modelObjectType" attribute
     */
    void setModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType.Enum modelObjectType);

    /**
     * Sets (as xml) the "modelObjectType" attribute
     */
    void xsetModelObjectType(
        org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType modelObjectType);

    /**
     * Unsets the "modelObjectType" attribute
     */
    void unsetModelObjectType();

    /**
     * Gets the "lowerBound" attribute
     */
    double getLowerBound();

    /**
     * Gets (as xml) the "lowerBound" attribute
     */
    org.apache.xmlbeans.XmlDouble xgetLowerBound();

    /**
     * True if has "lowerBound" attribute
     */
    boolean isSetLowerBound();

    /**
     * Sets the "lowerBound" attribute
     */
    void setLowerBound(double lowerBound);

    /**
     * Sets (as xml) the "lowerBound" attribute
     */
    void xsetLowerBound(org.apache.xmlbeans.XmlDouble lowerBound);

    /**
     * Unsets the "lowerBound" attribute
     */
    void unsetLowerBound();

    /**
     * Gets the "upperBound" attribute
     */
    double getUpperBound();

    /**
     * Gets (as xml) the "upperBound" attribute
     */
    org.apache.xmlbeans.XmlDouble xgetUpperBound();

    /**
     * True if has "upperBound" attribute
     */
    boolean isSetUpperBound();

    /**
     * Sets the "upperBound" attribute
     */
    void setUpperBound(double upperBound);

    /**
     * Sets (as xml) the "upperBound" attribute
     */
    void xsetUpperBound(org.apache.xmlbeans.XmlDouble upperBound);

    /**
     * Unsets the "upperBound" attribute
     */
    void unsetUpperBound();

    /**
     * Gets the "startValue" attribute
     */
    float getStartValue();

    /**
     * Gets (as xml) the "startValue" attribute
     */
    org.apache.xmlbeans.XmlFloat xgetStartValue();

    /**
     * True if has "startValue" attribute
     */
    boolean isSetStartValue();

    /**
     * Sets the "startValue" attribute
     */
    void setStartValue(float startValue);

    /**
     * Sets (as xml) the "startValue" attribute
     */
    void xsetStartValue(org.apache.xmlbeans.XmlFloat startValue);

    /**
     * Unsets the "startValue" attribute
     */
    void unsetStartValue();

    /**
     * An XML modelObjectType(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.ItemToFit$ModelObjectType.
     */
    public interface ModelObjectType extends org.apache.xmlbeans.XmlString {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ModelObjectType.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("modelobjecttypece56attrtype");
        static final Enum SPECIES = Enum.forString("species");
        static final Enum REACTION = Enum.forString("reaction");
        static final Enum ARBITRARY_VARIABLE = Enum.forString(
                "arbitraryVariable");
        static final int INT_SPECIES = Enum.INT_SPECIES;
        static final int INT_REACTION = Enum.INT_REACTION;
        static final int INT_ARBITRARY_VARIABLE = Enum.INT_ARBITRARY_VARIABLE;

        org.apache.xmlbeans.StringEnumAbstractBase enumValue();

        void set(org.apache.xmlbeans.StringEnumAbstractBase e);

        /**
         * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.ItemToFit$ModelObjectType.
         * These enum values can be used as follows:
         * <pre>
         * enum.toString(); // returns the string value of the enum
         * enum.intValue(); // returns an int value, useful for switches
         * // e.g., case Enum.INT_SPECIES
         * Enum.forString(s); // returns the enum value for a string
         * Enum.forInt(i); // returns the enum value for an int
         * </pre>
         * Enumeration objects are immutable singleton objects that
         * can be compared using == object equality. They have no
         * public constructor. See the constants defined within this
         * class for all the valid values.
         */
        static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
            static final int INT_SPECIES = 1;
            static final int INT_REACTION = 2;
            static final int INT_ARBITRARY_VARIABLE = 3;
            public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
                new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                        new Enum("species", INT_SPECIES),
                        new Enum("reaction", INT_REACTION),
                        new Enum("arbitraryVariable", INT_ARBITRARY_VARIABLE),
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

            public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType newValue(
                java.lang.Object obj) {
                return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) type.newValue(obj);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                        .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit.ModelObjectType) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                    .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ItemToFit parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
