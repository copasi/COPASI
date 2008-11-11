// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SimulatedAnnealingImpl.java,v $ 
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
 * XML Type:  SimulatedAnnealing
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML SimulatedAnnealing(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class SimulatedAnnealingImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing {
    private static final javax.xml.namespace.QName STARTTEMPERATURE$0 = new javax.xml.namespace.QName("",
            "startTemperature");
    private static final javax.xml.namespace.QName COOLINGFACTOR$2 = new javax.xml.namespace.QName("",
            "coolingFactor");
    private static final javax.xml.namespace.QName TOLERANCE$4 = new javax.xml.namespace.QName("",
            "tolerance");
    private static final javax.xml.namespace.QName RANDOMNUMBERGENERATOR$6 = new javax.xml.namespace.QName("",
            "randomNumberGenerator");
    private static final javax.xml.namespace.QName SEED$8 = new javax.xml.namespace.QName("",
            "seed");

    public SimulatedAnnealingImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "startTemperature" element
     */
    public java.math.BigInteger getStartTemperature() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(STARTTEMPERATURE$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "startTemperature" element
     */
    public org.apache.xmlbeans.XmlNonNegativeInteger xgetStartTemperature() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(STARTTEMPERATURE$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "startTemperature" element
     */
    public void setStartTemperature(java.math.BigInteger startTemperature) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(STARTTEMPERATURE$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(STARTTEMPERATURE$0);
            }

            target.setBigIntegerValue(startTemperature);
        }
    }

    /**
     * Sets (as xml) the "startTemperature" element
     */
    public void xsetStartTemperature(
        org.apache.xmlbeans.XmlNonNegativeInteger startTemperature) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlNonNegativeInteger target = null;
            target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                     .find_element_user(STARTTEMPERATURE$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlNonNegativeInteger) get_store()
                                                                         .add_element_user(STARTTEMPERATURE$0);
            }

            target.set(startTemperature);
        }
    }

    /**
     * Gets the "coolingFactor" element
     */
    public float getCoolingFactor() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(COOLINGFACTOR$2,
                    0);

            if (target == null) {
                return 0.0f;
            }

            return target.getFloatValue();
        }
    }

    /**
     * Gets (as xml) the "coolingFactor" element
     */
    public org.apache.xmlbeans.XmlFloat xgetCoolingFactor() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(COOLINGFACTOR$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "coolingFactor" element
     */
    public void setCoolingFactor(float coolingFactor) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(COOLINGFACTOR$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(COOLINGFACTOR$2);
            }

            target.setFloatValue(coolingFactor);
        }
    }

    /**
     * Sets (as xml) the "coolingFactor" element
     */
    public void xsetCoolingFactor(org.apache.xmlbeans.XmlFloat coolingFactor) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(COOLINGFACTOR$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                            .add_element_user(COOLINGFACTOR$2);
            }

            target.set(coolingFactor);
        }
    }

    /**
     * Gets the "tolerance" element
     */
    public float getTolerance() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(TOLERANCE$4,
                    0);

            if (target == null) {
                return 0.0f;
            }

            return target.getFloatValue();
        }
    }

    /**
     * Gets (as xml) the "tolerance" element
     */
    public org.apache.xmlbeans.XmlFloat xgetTolerance() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(TOLERANCE$4,
                    0);

            return target;
        }
    }

    /**
     * Sets the "tolerance" element
     */
    public void setTolerance(float tolerance) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(TOLERANCE$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(TOLERANCE$4);
            }

            target.setFloatValue(tolerance);
        }
    }

    /**
     * Sets (as xml) the "tolerance" element
     */
    public void xsetTolerance(org.apache.xmlbeans.XmlFloat tolerance) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlFloat target = null;
            target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                        .find_element_user(TOLERANCE$4,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                            .add_element_user(TOLERANCE$4);
            }

            target.set(tolerance);
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
