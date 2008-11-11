// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ParticleSwarmImpl.java,v $ 
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
 * XML Type:  ParticleSwarm
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML ParticleSwarm(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ParticleSwarmImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm {
    private static final javax.xml.namespace.QName ITERATIONLIMIT$0 = new javax.xml.namespace.QName("",
            "iterationLimit");
    private static final javax.xml.namespace.QName SWARMSIZE$2 = new javax.xml.namespace.QName("",
            "swarmSize");
    private static final javax.xml.namespace.QName STANDARDDEVIATION$4 = new javax.xml.namespace.QName("",
            "standardDeviation");
    private static final javax.xml.namespace.QName RANDOMNUMBERGENERATOR$6 = new javax.xml.namespace.QName("",
            "randomNumberGenerator");
    private static final javax.xml.namespace.QName SEED$8 = new javax.xml.namespace.QName("",
            "seed");

    public ParticleSwarmImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "iterationLimit" element
     */
    public java.math.BigInteger getIterationLimit() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(ITERATIONLIMIT$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "iterationLimit" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetIterationLimit() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(ITERATIONLIMIT$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "iterationLimit" element
     */
    public void setIterationLimit(java.math.BigInteger iterationLimit) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(ITERATIONLIMIT$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(ITERATIONLIMIT$0);
            }

            target.setBigIntegerValue(iterationLimit);
        }
    }

    /**
     * Sets (as xml) the "iterationLimit" element
     */
    public void xsetIterationLimit(
        org.apache.xmlbeans.XmlNonNegativeInteger iterationLimit) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(ITERATIONLIMIT$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(ITERATIONLIMIT$0);
            }

            target.set(iterationLimit);
        }
    }

    /**
     * Gets the "swarmSize" element
     */
    public java.math.BigInteger getSwarmSize() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SWARMSIZE$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "swarmSize" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetSwarmSize() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(SWARMSIZE$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "swarmSize" element
     */
    public void setSwarmSize(java.math.BigInteger swarmSize) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SWARMSIZE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(SWARMSIZE$2);
            }

            target.setBigIntegerValue(swarmSize);
        }
    }

    /**
     * Sets (as xml) the "swarmSize" element
     */
    public void xsetSwarmSize(
        org.apache.xmlbeans.XmlNonNegativeInteger swarmSize) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(SWARMSIZE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(SWARMSIZE$2);
            }

            target.set(swarmSize);
        }
    }

    /**
     * Gets the "standardDeviation" element
     */
    public float getStandardDeviation() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(STANDARDDEVIATION$4,
                    0);

            if (target == null) {
                return 0.0f;
            }

            return target.getFloatValue();
        }
    }

    /**
     * Gets (as xml) the "standardDeviation" element
     */
    public org.apache.xmlbeans.XmlFloat xgetStandardDeviation() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(STANDARDDEVIATION$4,
                    0);

            return target;
        }
    }

    /**
     * Sets the "standardDeviation" element
     */
    public void setStandardDeviation(float standardDeviation) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(STANDARDDEVIATION$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(STANDARDDEVIATION$4);
            }

            target.setFloatValue(standardDeviation);
        }
    }

    /**
     * Sets (as xml) the "standardDeviation" element
     */
    public void xsetStandardDeviation(
        org.apache.xmlbeans.XmlFloat standardDeviation) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(STANDARDDEVIATION$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                            .add_element_user(STANDARDDEVIATION$4);
            }

            target.set(standardDeviation);
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
                                                           .find_element_user(RANDOMNUMBERGENERATOR$6,
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
                                                                     .find_element_user(RANDOMNUMBERGENERATOR$6,
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
                                                           .find_element_user(RANDOMNUMBERGENERATOR$6,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(RANDOMNUMBERGENERATOR$6);
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
                                                                     .find_element_user(RANDOMNUMBERGENERATOR$6,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(RANDOMNUMBERGENERATOR$6);
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
                                                           .find_element_user(SEED$8,
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
                                                                     .find_element_user(SEED$8,
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
                                                           .find_element_user(SEED$8,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(SEED$8);
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
                                                                     .find_element_user(SEED$8,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(SEED$8);
            }

            target.set(seed);
        }
    }
}
