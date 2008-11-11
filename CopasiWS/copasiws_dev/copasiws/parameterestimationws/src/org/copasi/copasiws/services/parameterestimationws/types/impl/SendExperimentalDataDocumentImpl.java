// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SendExperimentalDataDocumentImpl.java,v $ 
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
 * Localname: SendExperimentalData
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one SendExperimentalData(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class SendExperimentalDataDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument {
    private static final javax.xml.namespace.QName SENDEXPERIMENTALDATA$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "SendExperimentalData");

    public SendExperimentalDataDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "SendExperimentalData" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData getSendExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData) get_store()
                                                                                                                                      .find_element_user(SENDEXPERIMENTALDATA$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "SendExperimentalData" element
     */
    public void setSendExperimentalData(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData sendExperimentalData) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData) get_store()
                                                                                                                                      .find_element_user(SENDEXPERIMENTALDATA$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData) get_store()
                                                                                                                                          .add_element_user(SENDEXPERIMENTALDATA$0);
            }

            target.set(sendExperimentalData);
        }
    }

    /**
     * Appends and returns a new empty "SendExperimentalData" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData addNewSendExperimentalData() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData) get_store()
                                                                                                                                      .add_element_user(SENDEXPERIMENTALDATA$0);

            return target;
        }
    }

    /**
     * An XML SendExperimentalData(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class SendExperimentalDataImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.SendExperimentalData {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName USERID$2 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName EXPERIMENTALDATA$4 = new javax.xml.namespace.QName("",
                "experimentalData");

        public SendExperimentalDataImpl(org.apache.xmlbeans.SchemaType sType) {
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
         * Gets the "userId" element
         */
        public java.lang.String getUserId() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(USERID$2,
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
                                                             .find_element_user(USERID$2,
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
                                                               .find_element_user(USERID$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(USERID$2);
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
                                                             .find_element_user(USERID$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(USERID$2);
                }

                target.set(userId);
            }
        }

        /**
         * Gets array of all "experimentalData" elements
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData[] getExperimentalDataArray() {
            synchronized (monitor()) {
                check_orphaned();

                java.util.List targetList = new java.util.ArrayList();
                get_store()
                    .find_all_element_users(EXPERIMENTALDATA$4, targetList);

                org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData[] result =
                    new org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData[targetList.size()];
                targetList.toArray(result);

                return result;
            }
        }

        /**
         * Gets ith "experimentalData" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData getExperimentalDataArray(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData) get_store()
                                                                                                         .find_element_user(EXPERIMENTALDATA$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                return target;
            }
        }

        /**
         * Returns number of "experimentalData" element
         */
        public int sizeOfExperimentalDataArray() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(EXPERIMENTALDATA$4);
            }
        }

        /**
         * Sets array of all "experimentalData" element
         */
        public void setExperimentalDataArray(
            org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData[] experimentalDataArray) {
            synchronized (monitor()) {
                check_orphaned();
                arraySetterHelper(experimentalDataArray, EXPERIMENTALDATA$4);
            }
        }

        /**
         * Sets ith "experimentalData" element
         */
        public void setExperimentalDataArray(int i,
            org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData experimentalData) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData) get_store()
                                                                                                         .find_element_user(EXPERIMENTALDATA$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                target.set(experimentalData);
            }
        }

        /**
         * Inserts and returns a new empty value (as xml) as the ith "experimentalData" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData insertNewExperimentalData(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData) get_store()
                                                                                                         .insert_element_user(EXPERIMENTALDATA$4,
                        i);

                return target;
            }
        }

        /**
         * Appends and returns a new empty value (as xml) as the last "experimentalData" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData addNewExperimentalData() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData) get_store()
                                                                                                         .add_element_user(EXPERIMENTALDATA$4);

                return target;
            }
        }

        /**
         * Removes the ith "experimentalData" element
         */
        public void removeExperimentalData(int i) {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(EXPERIMENTALDATA$4, i);
            }
        }
    }
}
