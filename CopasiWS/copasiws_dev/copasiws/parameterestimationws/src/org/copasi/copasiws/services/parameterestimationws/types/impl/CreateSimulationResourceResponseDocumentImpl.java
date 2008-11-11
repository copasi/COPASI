// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/CreateSimulationResourceResponseDocumentImpl.java,v $ 
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
 * An XML document type.
 * Localname: CreateSimulationResourceResponse
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one CreateSimulationResourceResponse(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class CreateSimulationResourceResponseDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument {
    private static final javax.xml.namespace.QName CREATESIMULATIONRESOURCERESPONSE$0 =
        new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "CreateSimulationResourceResponse");

    public CreateSimulationResourceResponseDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "CreateSimulationResourceResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse getCreateSimulationResourceResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse) get_store()
                                                                                                                                                              .find_element_user(CREATESIMULATIONRESOURCERESPONSE$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "CreateSimulationResourceResponse" element
     */
    public void setCreateSimulationResourceResponse(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse createSimulationResourceResponse) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse) get_store()
                                                                                                                                                              .find_element_user(CREATESIMULATIONRESOURCERESPONSE$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse) get_store()
                                                                                                                                                                  .add_element_user(CREATESIMULATIONRESOURCERESPONSE$0);
            }

            target.set(createSimulationResourceResponse);
        }
    }

    /**
     * Appends and returns a new empty "CreateSimulationResourceResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse addNewCreateSimulationResourceResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse) get_store()
                                                                                                                                                              .add_element_user(CREATESIMULATIONRESOURCERESPONSE$0);

            return target;
        }
    }

    /**
     * An XML CreateSimulationResourceResponse(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class CreateSimulationResourceResponseImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName STATUS$2 = new javax.xml.namespace.QName("",
                "status");

        public CreateSimulationResourceResponseImpl(
            org.apache.xmlbeans.SchemaType sType) {
            super(sType);
        }

        /**
         * Gets the "resourceId" element
         */
        public int getResourceId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(RESOURCEID$0,
                        0);

                if (target == null) {
                    return 0;
                }

                return target.getIntValue();
            }
        }

        /**
         * Gets (as xml) the "resourceId" element
         */
        public org.apache.xmlbeans.XmlInt xgetResourceId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlInt target = null;
                target = (org.apache.xmlbeans.XmlInt) get_store()
                                                          .find_element_user(RESOURCEID$0,
                        0);

                return target;
            }
        }

        /**
         * Sets the "resourceId" element
         */
        public void setResourceId(int resourceId) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(RESOURCEID$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(RESOURCEID$0);
                }

                target.setIntValue(resourceId);
            }
        }

        /**
         * Sets (as xml) the "resourceId" element
         */
        public void xsetResourceId(org.apache.xmlbeans.XmlInt resourceId) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlInt target = null;
                target = (org.apache.xmlbeans.XmlInt) get_store()
                                                          .find_element_user(RESOURCEID$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlInt) get_store()
                                                              .add_element_user(RESOURCEID$0);
                }

                target.set(resourceId);
            }
        }

        /**
         * Gets the "status" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.Status getStatus() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Status target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Status) get_store()
                                                                                               .find_element_user(STATUS$2,
                        0);

                if (target == null) {
                    return null;
                }

                return target;
            }
        }

        /**
         * Sets the "status" element
         */
        public void setStatus(
            org.copasi.copasiws.services.parameterestimationws.types.Status status) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Status target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Status) get_store()
                                                                                               .find_element_user(STATUS$2,
                        0);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.Status) get_store()
                                                                                                   .add_element_user(STATUS$2);
                }

                target.set(status);
            }
        }

        /**
         * Appends and returns a new empty "status" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.Status addNewStatus() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Status target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Status) get_store()
                                                                                               .add_element_user(STATUS$2);

                return target;
            }
        }
    }
}
