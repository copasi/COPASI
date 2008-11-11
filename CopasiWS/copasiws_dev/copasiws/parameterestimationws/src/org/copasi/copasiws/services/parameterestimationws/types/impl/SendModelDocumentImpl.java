// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SendModelDocumentImpl.java,v $ 
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
 * Localname: SendModel
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one SendModel(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class SendModelDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument {
    private static final javax.xml.namespace.QName SENDMODEL$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "SendModel");

    public SendModelDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "SendModel" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel getSendModel() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) get_store()
                                                                                                                .find_element_user(SENDMODEL$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "SendModel" element
     */
    public void setSendModel(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel sendModel) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) get_store()
                                                                                                                .find_element_user(SENDMODEL$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) get_store()
                                                                                                                    .add_element_user(SENDMODEL$0);
            }

            target.set(sendModel);
        }
    }

    /**
     * Appends and returns a new empty "SendModel" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel addNewSendModel() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel) get_store()
                                                                                                                .add_element_user(SENDMODEL$0);

            return target;
        }
    }

    /**
     * An XML SendModel(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class SendModelImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel {
        private static final javax.xml.namespace.QName RESOURCEID$0 = new javax.xml.namespace.QName("",
                "resourceId");
        private static final javax.xml.namespace.QName USERID$2 = new javax.xml.namespace.QName("",
                "userId");
        private static final javax.xml.namespace.QName COPASIML$4 = new javax.xml.namespace.QName("",
                "copasiml");
        private static final javax.xml.namespace.QName SBML$6 = new javax.xml.namespace.QName("",
                "sbml");
        private static final javax.xml.namespace.QName INPUTFORMAT$8 = new javax.xml.namespace.QName("",
                "inputFormat");

        public SendModelImpl(org.apache.xmlbeans.SchemaType sType) {
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
         * Gets the "copasiml" element
         */
        public java.lang.String getCopasiml() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(COPASIML$4,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "copasiml" element
         */
        public org.apache.xmlbeans.XmlString xgetCopasiml() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(COPASIML$4,
                        0);

                return target;
            }
        }

        /**
         * True if has "copasiml" element
         */
        public boolean isSetCopasiml() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(COPASIML$4) != 0;
            }
        }

        /**
         * Sets the "copasiml" element
         */
        public void setCopasiml(java.lang.String copasiml) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(COPASIML$4,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(COPASIML$4);
                }

                target.setStringValue(copasiml);
            }
        }

        /**
         * Sets (as xml) the "copasiml" element
         */
        public void xsetCopasiml(org.apache.xmlbeans.XmlString copasiml) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(COPASIML$4,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(COPASIML$4);
                }

                target.set(copasiml);
            }
        }

        /**
         * Unsets the "copasiml" element
         */
        public void unsetCopasiml() {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(COPASIML$4, 0);
            }
        }

        /**
         * Gets the "sbml" element
         */
        public java.lang.String getSbml() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(SBML$6,
                        0);

                if (target == null) {
                    return null;
                }

                return target.getStringValue();
            }
        }

        /**
         * Gets (as xml) the "sbml" element
         */
        public org.apache.xmlbeans.XmlString xgetSbml() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(SBML$6,
                        0);

                return target;
            }
        }

        /**
         * True if has "sbml" element
         */
        public boolean isSetSbml() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().count_elements(SBML$6) != 0;
            }
        }

        /**
         * Sets the "sbml" element
         */
        public void setSbml(java.lang.String sbml) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_element_user(SBML$6,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_element_user(SBML$6);
                }

                target.setStringValue(sbml);
            }
        }

        /**
         * Sets (as xml) the "sbml" element
         */
        public void xsetSbml(org.apache.xmlbeans.XmlString sbml) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.XmlString target = null;
                target = (org.apache.xmlbeans.XmlString) get_store()
                                                             .find_element_user(SBML$6,
                        0);

                if (target == null) {
                    target = (org.apache.xmlbeans.XmlString) get_store()
                                                                 .add_element_user(SBML$6);
                }

                target.set(sbml);
            }
        }

        /**
         * Unsets the "sbml" element
         */
        public void unsetSbml() {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_element(SBML$6, 0);
            }
        }

        /**
         * Gets the "inputFormat" attribute
         */
        public org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat.Enum getInputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_attribute_user(INPUTFORMAT$8);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_default_attribute_value(INPUTFORMAT$8);
                }

                if (target == null) {
                    return null;
                }

                return (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat.Enum) target.getEnumValue();
            }
        }

        /**
         * Gets (as xml) the "inputFormat" attribute
         */
        public org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat xgetInputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) get_store()
                                                                                                                                .find_attribute_user(INPUTFORMAT$8);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) get_default_attribute_value(INPUTFORMAT$8);
                }

                return target;
            }
        }

        /**
         * True if has "inputFormat" attribute
         */
        public boolean isSetInputFormat() {
            synchronized (monitor()) {
                check_orphaned();

                return get_store().find_attribute_user(INPUTFORMAT$8) != null;
            }
        }

        /**
         * Sets the "inputFormat" attribute
         */
        public void setInputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat.Enum inputFormat) {
            synchronized (monitor()) {
                check_orphaned();

                org.apache.xmlbeans.SimpleValue target = null;
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .find_attribute_user(INPUTFORMAT$8);

                if (target == null) {
                    target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                                   .add_attribute_user(INPUTFORMAT$8);
                }

                target.setEnumValue(inputFormat);
            }
        }

        /**
         * Sets (as xml) the "inputFormat" attribute
         */
        public void xsetInputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat inputFormat) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) get_store()
                                                                                                                                .find_attribute_user(INPUTFORMAT$8);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat) get_store()
                                                                                                                                    .add_attribute_user(INPUTFORMAT$8);
                }

                target.set(inputFormat);
            }
        }

        /**
         * Unsets the "inputFormat" attribute
         */
        public void unsetInputFormat() {
            synchronized (monitor()) {
                check_orphaned();
                get_store().remove_attribute(INPUTFORMAT$8);
            }
        }

        /**
         * An XML inputFormat(@).
         *
         * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument$SendModel$InputFormat.
         */
        public static class InputFormatImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
            implements org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.SendModel.InputFormat {
            public InputFormatImpl(org.apache.xmlbeans.SchemaType sType) {
                super(sType, false);
            }

            protected InputFormatImpl(org.apache.xmlbeans.SchemaType sType,
                boolean b) {
                super(sType, b);
            }
        }
    }
}
