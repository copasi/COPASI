// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SetFitItemsAndMethodDocumentImpl.java,v $ 
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
 * Localname: SetFitItemsAndMethod
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one SetFitItemsAndMethod(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class SetFitItemsAndMethodDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument {
    private static final javax.xml.namespace.QName SETFITITEMSANDMETHOD$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "SetFitItemsAndMethod");

    public SetFitItemsAndMethodDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "SetFitItemsAndMethod" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod getSetFitItemsAndMethod() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod) get_store()
                                                                                                                                      .find_element_user(SETFITITEMSANDMETHOD$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "SetFitItemsAndMethod" element
     */
    public void setSetFitItemsAndMethod(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod setFitItemsAndMethod) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod) get_store()
                                                                                                                                      .find_element_user(SETFITITEMSANDMETHOD$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod) get_store()
                                                                                                                                          .add_element_user(SETFITITEMSANDMETHOD$0);
            }

            target.set(setFitItemsAndMethod);
        }
    }

    /**
     * Appends and returns a new empty "SetFitItemsAndMethod" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod addNewSetFitItemsAndMethod() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod) get_store()
                                                                                                                                      .add_element_user(SETFITITEMSANDMETHOD$0);

            return target;
        }
    }

    /**
     * An XML SetFitItemsAndMethod(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class SetFitItemsAndMethodImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.SetFitItemsAndMethod {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName USERID$2 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName ITEMTOFIT$4 = new javax.xml.namespace.QName("",
                "itemToFit");
        private static final javax.xml.namespace.QName METHOD$6 = new javax.xml.namespace.QName("",
                "method");

        public SetFitItemsAndMethodImpl(org.apache.xmlbeans.SchemaType sType) {
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
         * Gets array of all "itemToFit" elements
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit[] getItemToFitArray() {
            synchronized (monitor()) {
                check_orphaned();

                java.util.List targetList = new java.util.ArrayList();
                get_store().find_all_element_users(ITEMTOFIT$4, targetList);

                org.copasi.copasiws.services.parameterestimationws.types.ItemToFit[] result =
                    new org.copasi.copasiws.services.parameterestimationws.types.ItemToFit[targetList.size()];
                targetList.toArray(result);

                return result;
            }
        }

        /**
         * Gets ith "itemToFit" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit getItemToFitArray(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ItemToFit target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) get_store()
                                                                                                  .find_element_user(ITEMTOFIT$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                return target;
            }
        }

        /**
         * Returns number of "itemToFit" element
         */
        public int sizeOfItemToFitArray() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(ITEMTOFIT$4);
            }
        }

        /**
         * Sets array of all "itemToFit" element
         */
        public void setItemToFitArray(
            org.copasi.copasiws.services.parameterestimationws.types.ItemToFit[] itemToFitArray) {
            synchronized (monitor()) {
                check_orphaned();
                arraySetterHelper(itemToFitArray, ITEMTOFIT$4);
            }
        }

        /**
         * Sets ith "itemToFit" element
         */
        public void setItemToFitArray(int i,
            org.copasi.copasiws.services.parameterestimationws.types.ItemToFit itemToFit) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ItemToFit target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) get_store()
                                                                                                  .find_element_user(ITEMTOFIT$4,
                        i);

                if (target == null) {
                    throw new IndexOutOfBoundsException();
                }

                target.set(itemToFit);
            }
        }

        /**
         * Inserts and returns a new empty value (as xml) as the ith "itemToFit" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit insertNewItemToFit(
            int i) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ItemToFit target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) get_store()
                                                                                                  .insert_element_user(ITEMTOFIT$4,
                        i);

                return target;
            }
        }

        /**
         * Appends and returns a new empty value (as xml) as the last "itemToFit" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.ItemToFit addNewItemToFit() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.ItemToFit target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.ItemToFit) get_store()
                                                                                                  .add_element_user(ITEMTOFIT$4);

                return target;
            }
        }

        /**
         * Removes the ith "itemToFit" element
         */
        public void removeItemToFit(int i) {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(ITEMTOFIT$4, i);
            }
        }

        /**
         * Gets the "method" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.Method getMethod() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Method target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Method) get_store()
                                                                                               .find_element_user(METHOD$6,
                        0);

                if (target == null) {
                    return null;
                }

                return target;
            }
        }

        /**
         * True if has "method" element
         */
        public boolean isSetMethod() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(METHOD$6) != 0;
            }
        }

        /**
         * Sets the "method" element
         */
        public void setMethod(
            org.copasi.copasiws.services.parameterestimationws.types.Method method) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Method target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Method) get_store()
                                                                                               .find_element_user(METHOD$6,
                        0);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.Method) get_store()
                                                                                                   .add_element_user(METHOD$6);
                }

                target.set(method);
            }
        }

        /**
         * Appends and returns a new empty "method" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.Method addNewMethod() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.Method target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.Method) get_store()
                                                                                               .add_element_user(METHOD$6);

                return target;
            }
        }

        /**
         * Unsets the "method" element
         */
        public void unsetMethod() {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(METHOD$6, 0);
            }
        }
    }
}
