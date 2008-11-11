// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/LifeTimeDocumentImpl.java,v $ 
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
 * Localname: lifeTime
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.LifeTimeDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * A document containing one lifeTime(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public class LifeTimeDocumentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.LifeTimeDocument {
    private static final javax.xml.namespace.QName LIFETIME$0 = new javax.xml.namespace.QName("http://parameterestimationws.services.copasiws.copasi.org/types",
            "lifeTime");

    public LifeTimeDocumentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "lifeTime" element
     */
    public java.math.BigInteger getLifeTime() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(LIFETIME$0,
                    0);

            if (target == null) {
                return null;
            }

            return target.getBigIntegerValue();
        }
    }

    /**
     * Gets (as xml) the "lifeTime" element
     */
    public org.apache.xmlbeans.XmlInteger xgetLifeTime() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlInteger target = null;
            target = (org.apache.xmlbeans.XmlInteger) get_store()
                                                          .find_element_user(LIFETIME$0,
                    0);

            return target;
        }
    }

    /**
     * Sets the "lifeTime" element
     */
    public void setLifeTime(java.math.BigInteger lifeTime) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_element_user(LIFETIME$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_element_user(LIFETIME$0);
            }

            target.setBigIntegerValue(lifeTime);
        }
    }

    /**
     * Sets (as xml) the "lifeTime" element
     */
    public void xsetLifeTime(org.apache.xmlbeans.XmlInteger lifeTime) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.XmlInteger target = null;
            target = (org.apache.xmlbeans.XmlInteger) get_store()
                                                          .find_element_user(LIFETIME$0,
                    0);

            if (target == null) {
                target = (org.apache.xmlbeans.XmlInteger) get_store()
                                                              .add_element_user(LIFETIME$0);
            }

            target.set(lifeTime);
        }
    }
}
