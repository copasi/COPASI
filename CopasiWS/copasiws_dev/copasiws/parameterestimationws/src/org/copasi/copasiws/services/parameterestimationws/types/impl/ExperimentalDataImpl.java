// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ExperimentalDataImpl.java,v $ 
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
 * XML Type:  ExperimentalData
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML ExperimentalData(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class ExperimentalDataImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData {
    private static final javax.xml.namespace.QName EXPERIMENTDATAID$0 = new javax.xml.namespace.QName("",
            "experimentDataId");
    private static final javax.xml.namespace.QName DATAFILEINSTRINGFORMAT$2 = new javax.xml.namespace.QName("",
            "dataFileInStringFormat");

    public ExperimentalDataImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "experimentDataId" element
     */
    public java.lang.String getExperimentDataId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "experimentDataId" element
     */
    public org.apache.xmlbeans.XmlString xgetExperimentDataId() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(EXPERIMENTDATAID$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "experimentDataId" element
     */
    public void setExperimentDataId(java.lang.String experimentDataId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(EXPERIMENTDATAID$0);
            }

            target.setStringValue(experimentDataId);
        }
    }

    /**
     * Sets (as xml) the "experimentDataId" element
     */
    public void xsetExperimentDataId(
        org.apache.xmlbeans.XmlString experimentDataId) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(EXPERIMENTDATAID$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(EXPERIMENTDATAID$0);
            }

            target.set(experimentDataId);
        }
    }

    /**
     * Gets the "dataFileInStringFormat" element
     */
    public java.lang.String getDataFileInStringFormat() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAFILEINSTRINGFORMAT$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "dataFileInStringFormat" element
     */
    public org.apache.xmlbeans.XmlString xgetDataFileInStringFormat() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(DATAFILEINSTRINGFORMAT$2,
                    0);

            return target;
        }
    }

    /**
     * Sets the "dataFileInStringFormat" element
     */
    public void setDataFileInStringFormat(
        java.lang.String dataFileInStringFormat) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(DATAFILEINSTRINGFORMAT$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(DATAFILEINSTRINGFORMAT$2);
            }

            target.setStringValue(dataFileInStringFormat);
        }
    }

    /**
     * Sets (as xml) the "dataFileInStringFormat" element
     */
    public void xsetDataFileInStringFormat(
        org.apache.xmlbeans.XmlString dataFileInStringFormat) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(DATAFILEINSTRINGFORMAT$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(DATAFILEINSTRINGFORMAT$2);
            }

            target.set(dataFileInStringFormat);
        }
    }
}
