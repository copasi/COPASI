// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SetModelToExperimentMapDocumentImpl.java,v $ 
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
 * Localname: SetModelToExperimentMap
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one SetModelToExperimentMap(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class SetModelToExperimentMapDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument {
    private static final javax.xml.namespace.QName SETMODELTOEXPERIMENTMAP$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "SetModelToExperimentMap");

    public SetModelToExperimentMapDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "SetModelToExperimentMap" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap getSetModelToExperimentMap() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap) get_store()
                                                                                                                                            .find_element_user(SETMODELTOEXPERIMENTMAP$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "SetModelToExperimentMap" element
     */
    public void setSetModelToExperimentMap(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap setModelToExperimentMap) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap) get_store()
                                                                                                                                            .find_element_user(SETMODELTOEXPERIMENTMAP$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap) get_store()
                                                                                                                                                .add_element_user(SETMODELTOEXPERIMENTMAP$0);
            }

            target.set(setModelToExperimentMap);
        }
    }

    /**
     * Appends and returns a new empty "SetModelToExperimentMap" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap addNewSetModelToExperimentMap() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap) get_store()
                                                                                                                                            .add_element_user(SETMODELTOEXPERIMENTMAP$0);

            return target;
        }
    }

    /**
     * An XML SetModelToExperimentMap(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class SetModelToExperimentMapImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.SetModelToExperimentMap {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName USERID$2 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName MODELTOEXPERIMENTMAP$4 = new javax.xml.namespace.QName("",
                "modelToExperimentMap");

        public SetModelToExperimentMapImpl(org.apache.xmlbeans.SchemaType sType) {
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
         * Gets array of all "modelToExperimentMap" elements
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap[] getModelToExperimentMapArray() {
            synchronized (monitor()) {
                check_orphaned();

                java.util.List targetList = new java.util.ArrayList();
                get_store()
                    .find_all_element_users(MODELTOEXPERIMENTMAP$4, targetList);

                org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap[] result =
                    new org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap[targetList.size()];
                targetList.toArray(result);

                return result;
            }
        }

        /**
         * Gets ith "modelToExperimentMap" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap getModelToExperimentMapArray(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) get_store()
                                                                                                             .find_element_user(MODELTOEXPERIMENTMAP$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                return target;
            }
        }

        /**
         * Returns number of "modelToExperimentMap" element
         */
        public int sizeOfModelToExperimentMapArray() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(MODELTOEXPERIMENTMAP$4);
            }
        }

        /**
         * Sets array of all "modelToExperimentMap" element
         */
        public void setModelToExperimentMapArray(
            org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap[] modelToExperimentMapArray) {
            synchronized (monitor()) {
                check_orphaned();
                arraySetterHelper(modelToExperimentMapArray,
                    MODELTOEXPERIMENTMAP$4);
            }
        }

        /**
         * Sets ith "modelToExperimentMap" element
         */
        public void setModelToExperimentMapArray(int i,
            org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap modelToExperimentMap) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) get_store()
                                                                                                             .find_element_user(MODELTOEXPERIMENTMAP$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                target.set(modelToExperimentMap);
            }
        }

        /**
         * Inserts and returns a new empty value (as xml) as the ith "modelToExperimentMap" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap insertNewModelToExperimentMap(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) get_store()
                                                                                                             .insert_element_user(MODELTOEXPERIMENTMAP$4,
                        i);

                return target;
            }
        }

        /**
         * Appends and returns a new empty value (as xml) as the last "modelToExperimentMap" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap addNewModelToExperimentMap() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap) get_store()
                                                                                                             .add_element_user(MODELTOEXPERIMENTMAP$4);

                return target;
            }
        }

        /**
         * Removes the ith "modelToExperimentMap" element
         */
        public void removeModelToExperimentMap(int i) {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(MODELTOEXPERIMENTMAP$4, i);
            }
        }
    }
}
