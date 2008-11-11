// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/GetSimulatorStatusDocumentImpl.java,v $ 
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
 * Localname: GetSimulatorStatus
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one GetSimulatorStatus(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class GetSimulatorStatusDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument {
    private static final javax.xml.namespace.QName GETSIMULATORSTATUS$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "GetSimulatorStatus");

    public GetSimulatorStatusDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "GetSimulatorStatus" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus getGetSimulatorStatus() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus) get_store()
                                                                                                                                  .find_element_user(GETSIMULATORSTATUS$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "GetSimulatorStatus" element
     */
    public void setGetSimulatorStatus(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus getSimulatorStatus) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus) get_store()
                                                                                                                                  .find_element_user(GETSIMULATORSTATUS$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus) get_store()
                                                                                                                                      .add_element_user(GETSIMULATORSTATUS$0);
            }

            target.set(getSimulatorStatus);
        }
    }

    /**
     * Appends and returns a new empty "GetSimulatorStatus" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus addNewGetSimulatorStatus() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus) get_store()
                                                                                                                                  .add_element_user(GETSIMULATORSTATUS$0);

            return target;
        }
    }

    /**
     * An XML GetSimulatorStatus(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class GetSimulatorStatusImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.GetSimulatorStatus {
        private static final javax.xml.namespace.QName USERID$0 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName RESOURCEID$2 = new javax.xml.namespace.QName("",
                "resourceId");

        public GetSimulatorStatusImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType);
        }

        /**
         * Gets the "userId" element
         */
        public java.lang.String getUserId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(USERID$0,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "userId" element
         */
        public org.apache.xmlbeans.XmlString xgetUserId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(USERID$0,
                        0);

                return target;
            }
        }

        /**
         * Sets the "userId" element
         */
        public void setUserId(java.lang.String userId) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(USERID$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(USERID$0);
                }

                target.setStringValue(userId);
            }
        }

        /**
         * Sets (as xml) the "userId" element
         */
        public void xsetUserId(org.apache.xmlbeans.XmlString userId) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(USERID$0,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(USERID$0);
                }

                target.set(userId);
            }
        }

        /**
         * Gets the "resourceId" element
         */
        public int getResourceId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(RESOURCEID$2,
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
                                                          .find_element_user(RESOURCEID$2,
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
                                                               .find_element_user(RESOURCEID$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(RESOURCEID$2);
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
                                                          .find_element_user(RESOURCEID$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlInt) get_store()
                                                              .add_element_user(RESOURCEID$2);
                }

                target.set(resourceId);
            }
        }
    }
}
