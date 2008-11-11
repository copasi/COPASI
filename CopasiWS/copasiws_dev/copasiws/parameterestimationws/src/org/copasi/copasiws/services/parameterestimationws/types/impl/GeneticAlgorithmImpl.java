// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/GeneticAlgorithmImpl.java,v $ 
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
 * XML Type:  GeneticAlgorithm
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML GeneticAlgorithm(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class GeneticAlgorithmImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm {
    private static final javax.xml.namespace.QName NUMBEROFGENERATIONS$0 = new javax.xml.namespace.QName("",
            "numberOfGenerations");
    private static final javax.xml.namespace.QName POPULATIONSIZE$2 = new javax.xml.namespace.QName("",
            "populationSize");
    private static final javax.xml.namespace.QName RANDOMNUMBERGENERATOR$4 = new javax.xml.namespace.QName("",
            "randomNumberGenerator");
    private static final javax.xml.namespace.QName SEED$6 = new javax.xml.namespace.QName("",
            "seed");

    public GeneticAlgorithmImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "numberOfGenerations" element
     */
    public java.math.BigInteger getNumberOfGenerations() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(NUMBEROFGENERATIONS$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "numberOfGenerations" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetNumberOfGenerations() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(NUMBEROFGENERATIONS$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "numberOfGenerations" element
     */
    public void setNumberOfGenerations(java.math.BigInteger numberOfGenerations) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(NUMBEROFGENERATIONS$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(NUMBEROFGENERATIONS$0);
            }

            target.setBigIntegerValue(numberOfGenerations);
        }
    }

    /**
     * Sets (as xml) the "numberOfGenerations" element
     */
    public void xsetNumberOfGenerations(
        org.apache.xmlbeans.XmlNonNegativeInteger numberOfGenerations) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(NUMBEROFGENERATIONS$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(NUMBEROFGENERATIONS$0);
            }

            target.set(numberOfGenerations);
        }
    }

    /**
     * Gets the "populationSize" element
     */
    public java.math.BigInteger getPopulationSize() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(POPULATIONSIZE$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "populationSize" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetPopulationSize() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(POPULATIONSIZE$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "populationSize" element
     */
    public void setPopulationSize(java.math.BigInteger populationSize) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(POPULATIONSIZE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(POPULATIONSIZE$2);
            }

            target.setBigIntegerValue(populationSize);
        }
    }

    /**
     * Sets (as xml) the "populationSize" element
     */
    public void xsetPopulationSize(
        org.apache.xmlbeans.XmlNonNegativeInteger populationSize) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(POPULATIONSIZE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(POPULATIONSIZE$2);
            }

            target.set(populationSize);
        }
    }

    /**
     * Gets the "randomNumberGenerator" element
     */
    public java.math.BigInteger getRandomNumberGenerator() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(RANDOMNUMBERGENERATOR$4,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "randomNumberGenerator" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetRandomNumberGenerator() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(RANDOMNUMBERGENERATOR$4,
                    0);

            return target;
        }
    }

    /**
     * Sets the "randomNumberGenerator" element
     */
    public void setRandomNumberGenerator(
        java.math.BigInteger randomNumberGenerator) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(RANDOMNUMBERGENERATOR$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(RANDOMNUMBERGENERATOR$4);
            }

            target.setBigIntegerValue(randomNumberGenerator);
        }
    }

    /**
     * Sets (as xml) the "randomNumberGenerator" element
     */
    public void xsetRandomNumberGenerator(
        org.apache.xmlbeans.XmlNonNegativeInteger randomNumberGenerator) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(RANDOMNUMBERGENERATOR$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(RANDOMNUMBERGENERATOR$4);
            }

            target.set(randomNumberGenerator);
        }
    }

    /**
     * Gets the "seed" element
     */
    public java.math.BigInteger getSeed() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SEED$6,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "seed" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetSeed() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(SEED$6,
                    0);

            return target;
        }
    }

    /**
     * Sets the "seed" element
     */
    public void setSeed(java.math.BigInteger seed) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SEED$6,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(SEED$6);
            }

            target.setBigIntegerValue(seed);
        }
    }

    /**
     * Sets (as xml) the "seed" element
     */
    public void xsetSeed(org.apache.xmlbeans.XmlNonNegativeInteger seed) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(SEED$6,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(SEED$6);
            }

            target.set(seed);
        }
    }
}
