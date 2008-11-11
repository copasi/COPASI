// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/ParticleSwarm.java,v $ 
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
 * XML Type:  ParticleSwarm
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML ParticleSwarm(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface ParticleSwarm extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ParticleSwarm.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("particleswarmcc9btype");

    /**
     * Gets the "iterationLimit" element
     */
    java.math.BigInteger getIterationLimit();

    /**
     * Gets (as xml) the "iterationLimit" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetIterationLimit();

    /**
     * Sets the "iterationLimit" element
     */
    void setIterationLimit(java.math.BigInteger iterationLimit);

    /**
     * Sets (as xml) the "iterationLimit" element
     */
    void xsetIterationLimit(
        org.apache.xmlbeans.XmlNonNegativeInteger iterationLimit);

    /**
     * Gets the "swarmSize" element
     */
    java.math.BigInteger getSwarmSize();

    /**
     * Gets (as xml) the "swarmSize" element
     */
    org.apache.xmlbeans.XmlNonNegativeInteger xgetSwarmSize();

    /**
     * Sets the "swarmSize" element
     */
    void setSwarmSize(java.math.BigInteger swarmSize);

    /**
     * Sets (as xml) the "swarmSize" element
     */
    void xsetSwarmSize(org.apache.xmlbeans.XmlNonNegativeInteger swarmSize);

    /**
     * Gets the "standardDeviation" element
     */
    float getStandardDeviation();

    /**
     * Gets (as xml) the "standardDeviation" element
     */
    org.apache.xmlbeans.XmlFloat xgetStandardDeviation();

    /**
     * Sets the "standardDeviation" element
     */
    void setStandardDeviation(float standardDeviation);

    /**
     * Sets (as xml) the "standardDeviation" element
     */
    void xsetStandardDeviation(org.apache.xmlbeans.XmlFloat standardDeviation);

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

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                        .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
