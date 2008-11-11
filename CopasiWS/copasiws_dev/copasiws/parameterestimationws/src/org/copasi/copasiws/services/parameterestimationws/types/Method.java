// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/Method.java,v $ 
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
 * XML Type:  Method
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.Method
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * An XML Method(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public interface Method extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(Method.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("methodda9ctype");

    /**
     * Gets the "geneticAlgorithm" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm getGeneticAlgorithm();

    /**
     * True if has "geneticAlgorithm" element
     */
    boolean isSetGeneticAlgorithm();

    /**
     * Sets the "geneticAlgorithm" element
     */
    void setGeneticAlgorithm(
        org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm geneticAlgorithm);

    /**
     * Appends and returns a new empty "geneticAlgorithm" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm addNewGeneticAlgorithm();

    /**
     * Unsets the "geneticAlgorithm" element
     */
    void unsetGeneticAlgorithm();

    /**
     * Gets the "levenbergMarquardt" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt getLevenbergMarquardt();

    /**
     * True if has "levenbergMarquardt" element
     */
    boolean isSetLevenbergMarquardt();

    /**
     * Sets the "levenbergMarquardt" element
     */
    void setLevenbergMarquardt(
        org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt levenbergMarquardt);

    /**
     * Appends and returns a new empty "levenbergMarquardt" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt addNewLevenbergMarquardt();

    /**
     * Unsets the "levenbergMarquardt" element
     */
    void unsetLevenbergMarquardt();

    /**
     * Gets the "particleSwarm" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm getParticleSwarm();

    /**
     * True if has "particleSwarm" element
     */
    boolean isSetParticleSwarm();

    /**
     * Sets the "particleSwarm" element
     */
    void setParticleSwarm(
        org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm particleSwarm);

    /**
     * Appends and returns a new empty "particleSwarm" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm addNewParticleSwarm();

    /**
     * Unsets the "particleSwarm" element
     */
    void unsetParticleSwarm();

    /**
     * Gets the "simulatedAnnealing" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing getSimulatedAnnealing();

    /**
     * True if has "simulatedAnnealing" element
     */
    boolean isSetSimulatedAnnealing();

    /**
     * Sets the "simulatedAnnealing" element
     */
    void setSimulatedAnnealing(
        org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing simulatedAnnealing);

    /**
     * Appends and returns a new empty "simulatedAnnealing" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing addNewSimulatedAnnealing();

    /**
     * Unsets the "simulatedAnnealing" element
     */
    void unsetSimulatedAnnealing();

    /**
     * Gets the "methodName" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName.Enum getMethodName();

    /**
     * Gets (as xml) the "methodName" attribute
     */
    org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName xgetMethodName();

    /**
     * True if has "methodName" attribute
     */
    boolean isSetMethodName();

    /**
     * Sets the "methodName" attribute
     */
    void setMethodName(
        org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName.Enum methodName);

    /**
     * Sets (as xml) the "methodName" attribute
     */
    void xsetMethodName(
        org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName methodName);

    /**
     * Unsets the "methodName" attribute
     */
    void unsetMethodName();

    /**
     * An XML methodName(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.Method$MethodName.
     */
    public interface MethodName extends org.apache.xmlbeans.XmlString {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(MethodName.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("methodname2ff0attrtype");
        static final Enum GENETIC_ALGORITHM = Enum.forString(
                "Genetic Algorithm");
        static final Enum LEVENBERG_MARQUARDT = Enum.forString(
                "Levenberg-Marquardt");
        static final Enum PARTICLE_SWARM = Enum.forString("Particle Swarm");
        static final Enum SIMULATED_ANNEALING = Enum.forString(
                "Simulated Annealing");
        static final int INT_GENETIC_ALGORITHM = Enum.INT_GENETIC_ALGORITHM;
        static final int INT_LEVENBERG_MARQUARDT = Enum.INT_LEVENBERG_MARQUARDT;
        static final int INT_PARTICLE_SWARM = Enum.INT_PARTICLE_SWARM;
        static final int INT_SIMULATED_ANNEALING = Enum.INT_SIMULATED_ANNEALING;

        org.apache.xmlbeans.StringEnumAbstractBase enumValue();

        void set(org.apache.xmlbeans.StringEnumAbstractBase e);

        /**
         * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.Method$MethodName.
         * These enum values can be used as follows:
         * <pre>
         * enum.toString(); // returns the string value of the enum
         * enum.intValue(); // returns an int value, useful for switches
         * // e.g., case Enum.INT_GENETIC_ALGORITHM
         * Enum.forString(s); // returns the enum value for a string
         * Enum.forInt(i); // returns the enum value for an int
         * </pre>
         * Enumeration objects are immutable singleton objects that
         * can be compared using == object equality. They have no
         * public constructor. See the constants defined within this
         * class for all the valid values.
         */
        static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
            static final int INT_GENETIC_ALGORITHM = 1;
            static final int INT_LEVENBERG_MARQUARDT = 2;
            static final int INT_PARTICLE_SWARM = 3;
            static final int INT_SIMULATED_ANNEALING = 4;
            public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
                new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                        new Enum("Genetic Algorithm", INT_GENETIC_ALGORITHM),
                        new Enum("Levenberg-Marquardt", INT_LEVENBERG_MARQUARDT),
                        new Enum("Particle Swarm", INT_PARTICLE_SWARM),
                        new Enum("Simulated Annealing", INT_SIMULATED_ANNEALING),
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

            public static org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName newValue(
                java.lang.Object obj) {
                return (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) type.newValue(obj);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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

        public static org.copasi.copasiws.services.parameterestimationws.types.Method newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                 .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.Method parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.Method) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
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
