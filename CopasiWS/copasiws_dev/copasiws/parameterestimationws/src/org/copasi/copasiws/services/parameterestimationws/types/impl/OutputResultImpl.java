// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/OutputResultImpl.java,v $ 
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
 * XML Type:  OutputResult
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.OutputResult
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML OutputResult(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class OutputResultImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.OutputResult {
    private static final javax.xml.namespace.QName TEXTRESULT$0 = new javax.xml.namespace.QName("",
            "TextResult");
    private static final javax.xml.namespace.QName SBRMLRESULT$2 = new javax.xml.namespace.QName("",
            "SBRMLResult");

    public OutputResultImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "TextResult" element
     */
    public java.lang.String getTextResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(TEXTRESULT$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "TextResult" element
     */
    public org.apache.xmlbeans.XmlString xgetTextResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(TEXTRESULT$0,
                    0);

            return target;
        }
    }

    /**
     * True if has "TextResult" element
     */
    public boolean isSetTextResult() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(TEXTRESULT$0) != 0;
        }
    }

    /**
     * Sets the "TextResult" element
     */
    public void setTextResult(java.lang.String textResult) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(TEXTRESULT$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(TEXTRESULT$0);
            }

            target.setStringValue(textResult);
        }
    }

    /**
     * Sets (as xml) the "TextResult" element
     */
    public void xsetTextResult(org.apache.xmlbeans.XmlString textResult) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(TEXTRESULT$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(TEXTRESULT$0);
            }

            target.set(textResult);
        }
    }

    /**
     * Unsets the "TextResult" element
     */
    public void unsetTextResult() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(TEXTRESULT$0, 0);
        }
    }

    /**
     * Gets the "SBRMLResult" element
     */
    public java.lang.String getSBRMLResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SBRMLRESULT$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "SBRMLResult" element
     */
    public org.apache.xmlbeans.XmlString xgetSBRMLResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(SBRMLRESULT$2,
                    0);

            return target;
        }
    }

    /**
     * True if has "SBRMLResult" element
     */
    public boolean isSetSBRMLResult() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(SBRMLRESULT$2) != 0;
        }
    }

    /**
     * Sets the "SBRMLResult" element
     */
    public void setSBRMLResult(java.lang.String sbrmlResult) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(SBRMLRESULT$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(SBRMLRESULT$2);
            }

            target.setStringValue(sbrmlResult);
        }
    }

    /**
     * Sets (as xml) the "SBRMLResult" element
     */
    public void xsetSBRMLResult(org.apache.xmlbeans.XmlString sbrmlResult) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(SBRMLRESULT$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(SBRMLRESULT$2);
            }

            target.set(sbrmlResult);
        }
    }

    /**
     * Unsets the "SBRMLResult" element
     */
    public void unsetSBRMLResult() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(SBRMLRESULT$2, 0);
        }
    }
}
