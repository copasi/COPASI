// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/CreateSimulationResourceDocumentImpl.java,v $ 
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
 * Localname: CreateSimulationResource
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one CreateSimulationResource(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class CreateSimulationResourceDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument {
    private static final javax.xml.namespace.QName CREATESIMULATIONRESOURCE$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "CreateSimulationResource");

    public CreateSimulationResourceDocumentImpl(
        org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "CreateSimulationResource" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource getCreateSimulationResource() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource) get_store()
                                                                                                                                              .find_element_user(CREATESIMULATIONRESOURCE$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * Sets the "CreateSimulationResource" element
     */
    public void setCreateSimulationResource(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource createSimulationResource) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource) get_store()
                                                                                                                                              .find_element_user(CREATESIMULATIONRESOURCE$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource) get_store()
                                                                                                                                                  .add_element_user(CREATESIMULATIONRESOURCE$0);
            }

            target.set(createSimulationResource);
        }
    }

    /**
     * Appends and returns a new empty "CreateSimulationResource" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource addNewCreateSimulationResource() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource) get_store()
                                                                                                                                              .add_element_user(CREATESIMULATIONRESOURCE$0);

            return target;
        }
    }

    /**
     * An XML CreateSimulationResource(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public static class CreateSimulationResourceImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
        implements org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.CreateSimulationResource {
        private static final javax.xml.namespace.QName USER$0 = new javax.xml.namespace.QName("",
                "user");

        public CreateSimulationResourceImpl(
            org.apache.xmlbeans.SchemaType sType) {
            super(sType);
        }

        /**
         * Gets the "user" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.User getUser() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.User target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.User) get_store()
                                                                                             .find_element_user(USER$0,
                        0);

                if (target == null) {
                    return null;
                }

                return target;
            }
        }

        /**
         * Sets the "user" element
         */
        public void setUser(
            org.copasi.copasiws.services.parameterestimationws.types.User user) {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.User target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.User) get_store()
                                                                                             .find_element_user(USER$0,
                        0);

                if (target == null) {
                    target = (org.copasi.copasiws.services.parameterestimationws.types.User) get_store()
                                                                                                 .add_element_user(USER$0);
                }

                target.set(user);
            }
        }

        /**
         * Appends and returns a new empty "user" element
         */
        public org.copasi.copasiws.services.parameterestimationws.types.User addNewUser() {
            synchronized (monitor()) {
                check_orphaned();

                org.copasi.copasiws.services.parameterestimationws.types.User target =
                    null;
                target = (org.copasi.copasiws.services.parameterestimationws.types.User) get_store()
                                                                                             .add_element_user(USER$0);

                return target;
            }
        }
    }
}
