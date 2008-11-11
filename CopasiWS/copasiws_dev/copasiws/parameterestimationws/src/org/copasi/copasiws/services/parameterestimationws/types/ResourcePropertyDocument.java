// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/ResourcePropertyDocument.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:52 $ 
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
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * A document containing one ResourceProperty(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public interface ResourcePropertyDocument extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ResourcePropertyDocument.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("resourceproperty088edoctype");

    /**
     * Gets the "ResourceProperty" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty getResourceProperty();

    /**
     * Sets the "ResourceProperty" element
     */
    void setResourceProperty(
        org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty resourceProperty);

    /**
     * Appends and returns a new empty "ResourceProperty" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty addNewResourceProperty();

    /**
     * An XML ResourceProperty(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public interface ResourceProperty extends org.apache.xmlbeans.XmlObject {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(ResourceProperty.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("resourcepropertybd6felemtype");

        /**
         * Gets the "resourceId" element
         */
        int getResourceId();

        /**
         * Gets (as xml) the "resourceId" element
         */
        org.apache.xmlbeans.XmlInt xgetResourceId();

        /**
         * Sets the "resourceId" element
         */
        void setResourceId(int resourceId);

        /**
         * Sets (as xml) the "resourceId" element
         */
        void xsetResourceId(org.apache.xmlbeans.XmlInt resourceId);

        /**
         * Gets the "resultFile" element
         */
        java.lang.String getResultFile();

        /**
         * Gets (as xml) the "resultFile" element
         */
        org.apache.xmlbeans.XmlString xgetResultFile();

        /**
         * Sets the "resultFile" element
         */
        void setResultFile(java.lang.String resultFile);

        /**
         * Sets (as xml) the "resultFile" element
         */
        void xsetResultFile(org.apache.xmlbeans.XmlString resultFile);

        /**
         * Gets the "modelFile" element
         */
        java.lang.String getModelFile();

        /**
         * Gets (as xml) the "modelFile" element
         */
        org.apache.xmlbeans.XmlString xgetModelFile();

        /**
         * Sets the "modelFile" element
         */
        void setModelFile(java.lang.String modelFile);

        /**
         * Sets (as xml) the "modelFile" element
         */
        void xsetModelFile(org.apache.xmlbeans.XmlString modelFile);

        /**
         * A factory class with static methods for creating instances
         * of this type.
         */
        public static final class Factory {
            private Factory() {
            } // No instance of this class allowed

            public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                        .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument.ResourceProperty) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                        .newInstance(type,
                    options);
            }
        }
    }

    /**
     * A factory class with static methods for creating instances
     * of this type.
     */
    public static final class Factory {
        private Factory() {
        } // No instance of this class allowed

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.ResourcePropertyDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                   .parse(xis,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, options);
        }
    }
}
