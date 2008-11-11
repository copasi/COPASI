// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/GeneticAlgorithm.java,v $ 
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
 * XML Type:  GeneticAlgorithm
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML GeneticAlgorithm(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface GeneticAlgorithm extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(GeneticAlgorithm.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("geneticalgorithmb191type");

    /**
     * Gets the "numberOfGenerations" element
     */
    java.math.BigInteger getNumberOfGenerations();

    /**
     * Gets (as xml) the "numberOfGenerations" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetNumberOfGenerations();

    /**
     * Sets the "numberOfGenerations" element
     */
    void setNumberOfGenerations(java.math.BigInteger numberOfGenerations);

    /**
     * Sets (as xml) the "numberOfGenerations" element
     */
    void xsetNumberOfGenerations(
        org.apache.xmlbeans.XmlNonNegativeInteger numberOfGenerations);

    /**
     * Gets the "populationSize" element
     */
    java.math.BigInteger getPopulationSize();

    /**
     * Gets (as xml) the "populationSize" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetPopulationSize();

    /**
     * Sets the "populationSize" element
     */
    void setPopulationSize(java.math.BigInteger populationSize);

    /**
     * Sets (as xml) the "populationSize" element
     */
    void xsetPopulationSize(
        org.apache.xmlbeans.XmlNonNegativeInteger populationSize);

    /**
     * Gets the "randomNumberGenerator" element
     */
    java.math.BigInteger getRandomNumberGenerator();

    /**
     * Gets (as xml) the "randomNumberGenerator" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetRandomNumberGenerator();

    /**
     * Sets the "randomNumberGenerator" element
     */
    void setRandomNumberGenerator(java.math.BigInteger randomNumberGenerator);

    /**
     * Sets (as xml) the "randomNumberGenerator" element
     */
    void xsetRandomNumberGenerator(
        org.apache.xmlbeans.XmlNonNegativeInteger randomNumberGenerator);

    /**
     * Gets the "seed" element
     */
    java.math.BigInteger getSeed();

    /**
     * Gets (as xml) the "seed" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetSeed();

    /**
     * Sets the "seed" element
     */
    void setSeed(java.math.BigInteger seed);

    /**
     * Sets (as xml) the "seed" element
     */
    void xsetSeed(org.apache.xmlbeans.XmlNonNegativeInteger seed);

    /**
     * A factory class with static methods for creating instances
     * of this type.
     */
    public static final class Factory {
        private Factory() {
        } // No instance of this class allowed

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                           .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
