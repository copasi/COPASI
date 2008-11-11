// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/StatusImpl.java,v $ 
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
 * XML Type:  Status
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.Status
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML Status(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class StatusImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.Status {
    private static final javax.xml.namespace.QName CODE$0 = new javax.xml.namespace.QName("",
            "code");
    private static final javax.xml.namespace.QName MESSAGE$2 = new javax.xml.namespace.QName("",
            "message");

    public StatusImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "code" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.StatusCode.Enum getCode() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(CODE$0,
                    0);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.StatusCode.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "code" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.StatusCode xgetCode() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.StatusCode target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) get_store()
                                                                                               .find_element_user(CODE$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "code" element
     */
    public void setCode(
        org.copasi.copasiws.services.parameterestimationws.types.StatusCode.Enum code) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(CODE$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(CODE$0);
            }

            target.setEnumValue(code);
        }
    }

    /**
     * Sets (as xml) the "code" element
     */
    public void xsetCode(
        org.copasi.copasiws.services.parameterestimationws.types.StatusCode code) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.StatusCode target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) get_store()
                                                                                               .find_element_user(CODE$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.StatusCode) get_store()
                                                                                                   .add_element_user(CODE$0);
            }

            target.set(code);
        }
    }

    /**
     * Gets the "message" element
     */
    public java.lang.String getMessage() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(MESSAGE$2,
                    0);

            if (target == null) {
                return null;
            }

            return target.getStringValue();
        }
    }

    /**
     * Gets (as xml) the "message" element
     */
    public org.apache.xmlbeans.XmlString xgetMessage() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(MESSAGE$2,
                    0);

            return target;
        }
    }

    /**
     * True if has "message" element
     */
    public boolean isSetMessage() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(MESSAGE$2) != 0;
        }
    }

    /**
     * Sets the "message" element
     */
    public void setMessage(java.lang.String message) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(MESSAGE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(MESSAGE$2);
            }

            target.setStringValue(message);
        }
    }

    /**
     * Sets (as xml) the "message" element
     */
    public void xsetMessage(org.apache.xmlbeans.XmlString message) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlString target = null;
            target = (org.apache.xmlbeans.XmlString) get_store()
                                                         .find_element_user(MESSAGE$2,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .add_element_user(MESSAGE$2);
            }

            target.set(message);
        }
    }

    /**
     * Unsets the "message" element
     */
    public void unsetMessage() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(MESSAGE$2, 0);
        }
    }
}
