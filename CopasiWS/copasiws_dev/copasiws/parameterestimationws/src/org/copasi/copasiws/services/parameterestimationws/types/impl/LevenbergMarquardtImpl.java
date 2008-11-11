// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/LevenbergMarquardtImpl.java,v $ 
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
 * XML Type:  LevenbergMarquardt
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML LevenbergMarquardt(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class LevenbergMarquardtImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt {
    private static final javax.xml.namespace.QName ITERATIONLIMIT$0 = new javax.xml.namespace.QName("",
            "iterationLimit");
    private static final javax.xml.namespace.QName TOLERANCE$2 = new javax.xml.namespace.QName("",
            "tolerance");

    public LevenbergMarquardtImpl(org.apache.xmlbeans.SchemaType sType) {
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
     * Gets the "tolerance" element
     */
    public float getTolerance() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(TOLERANCE$2,
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
                                                        .find_element_user(TOLERANCE$2,
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
                                                           .find_element_user(TOLERANCE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(TOLERANCE$2);
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
                                                        .find_element_user(TOLERANCE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlFloat) get_store()
                                                            .add_element_user(TOLERANCE$2);
            }

            target.set(tolerance);
        }
    }
}
