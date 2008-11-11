// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ServiceFaultDocumentImpl.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:55 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/*
 * An XML document type.
 * Localname: ServiceFault
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one ServiceFault(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class ServiceFaultDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument {
    private static final javax.xml.namespace.QName SERVICEFAULT$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "ServiceFault");

    public ServiceFaultDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "ServiceFault" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault getServiceFault() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault) get_store()
                                                                                                                      .find_element_user(SERVICEFAULT$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "ServiceFault" element
     */
    public void setServiceFault(
        org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault serviceFault) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault) get_store()
                                                                                                                      .find_element_user(SERVICEFAULT$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault) get_store()
                                                                                                                          .add_element_user(SERVICEFAULT$0);
            }

            target.set(serviceFault);
        }
    }

    /**
     * Appends and returns a new empty "ServiceFault" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault addNewServiceFault() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault) get_store()
                                                                                                                      .add_element_user(SERVICEFAULT$0);

            return target;
        }
    }

    /**
     * An XML ServiceFault(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class ServiceFaultImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.ServiceFault {
        private static final javax.xml.namespace.QName ERRORMESSAGE$0 = new javax.xml.namespace.QName("",
                "errorMessage");

        public ServiceFaultImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType);
        }

        /**
         * Gets the "errorMessage" element
         */
        public java.lang.String getErrorMessage() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(ERRORMESSAGE$0,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "errorMessage" element
         */
        public org.apache.xmlbeans.XmlString xgetErrorMessage() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(ERRORMESSAGE$0,
                        0);

                return target;
            }
        }

        /**
         * Sets the "errorMessage" element
         */
        public void setErrorMessage(java.lang.String errorMessage) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(ERRORMESSAGE$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(ERRORMESSAGE$0);
                }

                target.setStringValue(errorMessage);
            }
        }

        /**
         * Sets (as xml) the "errorMessage" element
         */
        public void xsetErrorMessage(org.apache.xmlbeans.XmlString errorMessage) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(ERRORMESSAGE$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(ERRORMESSAGE$0);
                }

                target.set(errorMessage);
            }
        }
    }
}
