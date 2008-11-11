// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/SetModelToExperimentMapResponseDocumentImpl.java,v $ 
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
 * Localname: SetModelToExperimentMapResponse
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one SetModelToExperimentMapResponse(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class SetModelToExperimentMapResponseDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument {
    private static final javax.xml.namespace.QName SETMODELTOEXPERIMENTMAPRESPONSE$0 =
        new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "SetModelToExperimentMapResponse");

    public SetModelToExperimentMapResponseDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "SetModelToExperimentMapResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse getSetModelToExperimentMapResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse) get_store()
                                                                                                                                                            .find_element_user(SETMODELTOEXPERIMENTMAPRESPONSE$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "SetModelToExperimentMapResponse" element
     */
    public void setSetModelToExperimentMapResponse(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse setModelToExperimentMapResponse) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse) get_store()
                                                                                                                                                            .find_element_user(SETMODELTOEXPERIMENTMAPRESPONSE$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse) get_store()
                                                                                                                                                                .add_element_user(SETMODELTOEXPERIMENTMAPRESPONSE$0);
            }

            target.set(setModelToExperimentMapResponse);
        }
    }

    /**
     * Appends and returns a new empty "SetModelToExperimentMapResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse addNewSetModelToExperimentMapResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse) get_store()
                                                                                                                                                            .add_element_user(SETMODELTOEXPERIMENTMAPRESPONSE$0);

            return target;
        }
    }

    /**
     * An XML SetModelToExperimentMapResponse(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class SetModelToExperimentMapResponseImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse {
        private static final javax.xml.namespace.QName STATUS$0 = new javax.xml.namespace.QName("",
                "status");

        public SetModelToExperimentMapResponseImpl(
            org.apache.xmlbeans.SchemaType sType) {
            super(sType);
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
                                                                                               .find_element_user(STATUS$0,
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
                                                                                               .find_element_user(STATUS$0,
                        0);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.Status) get_store()
                                                                                                   .add_element_user(STATUS$0);
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
                                                                                               .add_element_user(STATUS$0);

                return target;
            }
        }
    }
}
