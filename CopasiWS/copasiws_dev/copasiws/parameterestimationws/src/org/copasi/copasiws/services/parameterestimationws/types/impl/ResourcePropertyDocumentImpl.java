// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/ResourcePropertyDocumentImpl.java,v $ 
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
 * Localname: ResourceProperty
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one ResourceProperty(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class ResourcePropertyDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument {
    private static final javax.xml.namespace.QName RESOURCEPROPERTY$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "ResourceProperty");

    public ResourcePropertyDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "ResourceProperty" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty getResourceProperty() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) get_store()
                                                                                                                              .find_element_user(RESOURCEPROPERTY$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "ResourceProperty" element
     */
    public void setResourceProperty(
        org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty resourceProperty) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) get_store()
                                                                                                                              .find_element_user(RESOURCEPROPERTY$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) get_store()
                                                                                                                                  .add_element_user(RESOURCEPROPERTY$0);
            }

            target.set(resourceProperty);
        }
    }

    /**
     * Appends and returns a new empty "ResourceProperty" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty addNewResourceProperty() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) get_store()
                                                                                                                              .add_element_user(RESOURCEPROPERTY$0);

            return target;
        }
    }

    /**
     * An XML ResourceProperty(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class ResourcePropertyImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
                "resourceId");
        private static final javax.xml.namespace.QName RESULTFILE$2 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
                "resultFile");
        private static final javax.xml.namespace.QName MODELFILE$4 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
                "modelFile");

        public ResourcePropertyImpl(org.apache.xmlbeans.SchemaType sType) {
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
         * Gets the "resultFile" element
         */
        public java.lang.String getResultFile() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(RESULTFILE$2,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "resultFile" element
         */
        public org.apache.xmlbeans.XmlString xgetResultFile() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(RESULTFILE$2,
                        0);

                return target;
            }
        }

        /**
         * Sets the "resultFile" element
         */
        public void setResultFile(java.lang.String resultFile) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(RESULTFILE$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(RESULTFILE$2);
                }

                target.setStringValue(resultFile);
            }
        }

        /**
         * Sets (as xml) the "resultFile" element
         */
        public void xsetResultFile(org.apache.xmlbeans.XmlString resultFile) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(RESULTFILE$2,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(RESULTFILE$2);
                }

                target.set(resultFile);
            }
        }

        /**
         * Gets the "modelFile" element
         */
        public java.lang.String getModelFile() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(MODELFILE$4,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "modelFile" element
         */
        public org.apache.xmlbeans.XmlString xgetModelFile() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(MODELFILE$4,
                        0);

                return target;
            }
        }

        /**
         * Sets the "modelFile" element
         */
        public void setModelFile(java.lang.String modelFile) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(MODELFILE$4,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(MODELFILE$4);
                }

                target.setStringValue(modelFile);
            }
        }

        /**
         * Sets (as xml) the "modelFile" element
         */
        public void xsetModelFile(org.apache.xmlbeans.XmlString modelFile) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(MODELFILE$4,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(MODELFILE$4);
                }

                target.set(modelFile);
            }
        }
    }
}
