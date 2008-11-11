// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/GetResultResponseDocumentImpl.java,v $ 
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
 * Localname: GetResultResponse
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one GetResultResponse(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class GetResultResponseDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument {
    private static final javax.xml.namespace.QName GETRESULTRESPONSE$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "GetResultResponse");

    public GetResultResponseDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "GetResultResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse getGetResultResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse) get_store()
                                                                                                                                .find_element_user(GETRESULTRESPONSE$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "GetResultResponse" element
     */
    public void setGetResultResponse(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse getResultResponse) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse) get_store()
                                                                                                                                .find_element_user(GETRESULTRESPONSE$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse) get_store()
                                                                                                                                    .add_element_user(GETRESULTRESPONSE$0);
            }

            target.set(getResultResponse);
        }
    }

    /**
     * Appends and returns a new empty "GetResultResponse" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse addNewGetResultResponse() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse) get_store()
                                                                                                                                .add_element_user(GETRESULTRESPONSE$0);

            return target;
        }
    }

    /**
     * An XML GetResultResponse(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class GetResultResponseImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.GetResultResponse {
        private static final javax.xml.namespace.QName OUTPUTRESULT$0 = new javax.xml.namespace.QName("",
                "outputResult");

        public GetResultResponseImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType);
        }

        /**
         * Gets the "outputResult" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.OutputResult getOutputResult() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.OutputResult target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.OutputResult) get_store()
                                                                                                     .find_element_user(OUTPUTRESULT$0,
                        0);

                if (target == null) {
                    return null;
                }

                return target;
            }
        }

        /**
         * Sets the "outputResult" element
         */
        public void setOutputResult(
            org.copasi.copasiws.services.parameterestimationws.types.OutputResult outputResult) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.OutputResult target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.OutputResult) get_store()
                                                                                                     .find_element_user(OUTPUTRESULT$0,
                        0);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.OutputResult) get_store()
                                                                                                         .add_element_user(OUTPUTRESULT$0);
                }

                target.set(outputResult);
            }
        }

        /**
         * Appends and returns a new empty "outputResult" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.OutputResult addNewOutputResult() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.OutputResult target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.OutputResult) get_store()
                                                                                                     .add_element_user(OUTPUTRESULT$0);

                return target;
            }
        }
    }
}
