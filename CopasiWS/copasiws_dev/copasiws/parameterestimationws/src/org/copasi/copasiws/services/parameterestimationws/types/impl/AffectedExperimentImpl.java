// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/AffectedExperimentImpl.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:55 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/*
 * XML Type:  AffectedExperiment
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML AffectedExperiment(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class AffectedExperimentImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment {
    private static final javax.xml.namespace.QName EXPERIMENT$0 = new javax.xml.namespace.QName("",
            "experiment");

    public AffectedExperimentImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "experiment" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment.Enum getExperiment() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(EXPERIMENT$0);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "experiment" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment xgetExperiment() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment) get_store()
                                                                                                                  .find_attribute_user(EXPERIMENT$0);

            return target;
        }
    }

    /**
     * True if has "experiment" attribute
     */
    public boolean isSetExperiment() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(EXPERIMENT$0) != null;
        }
    }

    /**
     * Sets the "experiment" attribute
     */
    public void setExperiment(
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment.Enum experiment) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(EXPERIMENT$0);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(EXPERIMENT$0);
            }

            target.setEnumValue(experiment);
        }
    }

    /**
     * Sets (as xml) the "experiment" attribute
     */
    public void xsetExperiment(
        org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment experiment) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment) get_store()
                                                                                                                  .find_attribute_user(EXPERIMENT$0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment) get_store()
                                                                                                                      .add_attribute_user(EXPERIMENT$0);
            }

            target.set(experiment);
        }
    }

    /**
     * Unsets the "experiment" attribute
     */
    public void unsetExperiment() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(EXPERIMENT$0);
        }
    }

    /**
     * An XML experiment(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment$Experiment.
     */
    public static class ExperimentImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment.Experiment {
        public ExperimentImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected ExperimentImpl(org.apache.xmlbeans.SchemaType sType, boolean b) {
            super(sType, b);
        }
    }
}
