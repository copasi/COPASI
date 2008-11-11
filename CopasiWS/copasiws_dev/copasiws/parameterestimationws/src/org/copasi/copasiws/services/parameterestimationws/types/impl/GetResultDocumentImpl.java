// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/GetResultDocumentImpl.java,v $ 
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
 * Localname: GetResult
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one GetResult(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class GetResultDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument {
    private static final javax.xml.namespace.QName GETRESULT$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "GetResult");

    public GetResultDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "GetResult" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult getGetResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) get_store()
                                                                                                                .find_element_user(GETRESULT$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "GetResult" element
     */
    public void setGetResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult getResult) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) get_store()
                                                                                                                .find_element_user(GETRESULT$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) get_store()
                                                                                                                    .add_element_user(GETRESULT$0);
            }

            target.set(getResult);
        }
    }

    /**
     * Appends and returns a new empty "GetResult" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult addNewGetResult() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) get_store()
                                                                                                                .add_element_user(GETRESULT$0);

            return target;
        }
    }

    /**
     * An XML GetResult(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class GetResultImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult {
        private static final javax.xml.namespace.QName USERID$0 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName RESOURCEID$2 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName OUTPUTFORMAT$4 = new javax.xml.namespace.QName("",
                "outputFormat");

        public GetResultImpl(org.apache.xmlbeans.SchemaType sType) {
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

        /**
         * Gets the "outputFormat" attribute
         */
        public org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat.Enum getOutputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_attribute_user(OUTPUTFORMAT$4);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_default_attribute_value(OUTPUTFORMAT$4);
                }

                if (target == null) {
                    return null;
                }

                return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat.Enum) target.getEnumValue();
            }
        }

        /**
         * Gets (as xml) the "outputFormat" attribute
         */
        public org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat xgetOutputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) get_store()
                                                                                                                                 .find_attribute_user(OUTPUTFORMAT$4);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) get_default_attribute_value(OUTPUTFORMAT$4);
                }

                return target;
            }
        }

        /**
         * True if has "outputFormat" attribute
         */
        public boolean isSetOutputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().find_attribute_user(OUTPUTFORMAT$4) != null;
            }
        }

        /**
         * Sets the "outputFormat" attribute
         */
        public void setOutputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat.Enum outputFormat) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_attribute_user(OUTPUTFORMAT$4);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_attribute_user(OUTPUTFORMAT$4);
                }

                target.setEnumValue(outputFormat);
            }
        }

        /**
         * Sets (as xml) the "outputFormat" attribute
         */
        public void xsetOutputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat outputFormat) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) get_store()
                                                                                                                                 .find_attribute_user(OUTPUTFORMAT$4);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) get_store()
                                                                                                                                     .add_attribute_user(OUTPUTFORMAT$4);
                }

                target.set(outputFormat);
            }
        }

        /**
         * Unsets the "outputFormat" attribute
         */
        public void unsetOutputFormat() {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_attribute(OUTPUTFORMAT$4);
            }
        }

        /**
         * An XML outputFormat(@).
         *
         * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument$GetResult$OutputFormat.
         */
        public static class OutputFormatImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
            implements org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat {
            public OutputFormatImpl(org.apache.xmlbeans.SchemaType sType) {
                super(sType, false);
            }

            protected OutputFormatImpl(org.apache.xmlbeans.SchemaType sType,
                boolean b) {
                super(sType, b);
            }
        }
    }
}
