// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/impl/MethodImpl.java,v $ 
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
 * XML Type:  Method
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.Method
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types.impl;

/**
 * An XML Method(@http://parameterestimationws.services.copasiws.copasi.org/types).
 *
 * This is a complex type.
 */
public class MethodImpl extends org.apache.xmlbeans.impl.values.XmlComplexContentImpl
    implements org.copasi.copasiws.services.parameterestimationws.types.Method {
    private static final javax.xml.namespace.QName GENETICALGORITHM$0 = new javax.xml.namespace.QName("",
            "geneticAlgorithm");
    private static final javax.xml.namespace.QName LEVENBERGMARQUARDT$2 = new javax.xml.namespace.QName("",
            "levenbergMarquardt");
    private static final javax.xml.namespace.QName PARTICLESWARM$4 = new javax.xml.namespace.QName("",
            "particleSwarm");
    private static final javax.xml.namespace.QName SIMULATEDANNEALING$6 = new javax.xml.namespace.QName("",
            "simulatedAnnealing");
    private static final javax.xml.namespace.QName METHODNAME$8 = new javax.xml.namespace.QName("",
            "methodName");

    public MethodImpl(org.apache.xmlbeans.SchemaType sType) {
        super(sType);
    }

    /**
     * Gets the "geneticAlgorithm" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm getGeneticAlgorithm() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) get_store()
                                                                                                     .find_element_user(GENETICALGORITHM$0,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "geneticAlgorithm" element
     */
    public boolean isSetGeneticAlgorithm() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(GENETICALGORITHM$0) != 0;
        }
    }

    /**
     * Sets the "geneticAlgorithm" element
     */
    public void setGeneticAlgorithm(
        org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm geneticAlgorithm) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) get_store()
                                                                                                     .find_element_user(GENETICALGORITHM$0,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) get_store()
                                                                                                         .add_element_user(GENETICALGORITHM$0);
            }

            target.set(geneticAlgorithm);
        }
    }

    /**
     * Appends and returns a new empty "geneticAlgorithm" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm addNewGeneticAlgorithm() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm) get_store()
                                                                                                     .add_element_user(GENETICALGORITHM$0);

            return target;
        }
    }

    /**
     * Unsets the "geneticAlgorithm" element
     */
    public void unsetGeneticAlgorithm() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(GENETICALGORITHM$0, 0);
        }
    }

    /**
     * Gets the "levenbergMarquardt" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt getLevenbergMarquardt() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt) get_store()
                                                                                                       .find_element_user(LEVENBERGMARQUARDT$2,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "levenbergMarquardt" element
     */
    public boolean isSetLevenbergMarquardt() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(LEVENBERGMARQUARDT$2) != 0;
        }
    }

    /**
     * Sets the "levenbergMarquardt" element
     */
    public void setLevenbergMarquardt(
        org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt levenbergMarquardt) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt) get_store()
                                                                                                       .find_element_user(LEVENBERGMARQUARDT$2,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt) get_store()
                                                                                                           .add_element_user(LEVENBERGMARQUARDT$2);
            }

            target.set(levenbergMarquardt);
        }
    }

    /**
     * Appends and returns a new empty "levenbergMarquardt" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt addNewLevenbergMarquardt() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt) get_store()
                                                                                                       .add_element_user(LEVENBERGMARQUARDT$2);

            return target;
        }
    }

    /**
     * Unsets the "levenbergMarquardt" element
     */
    public void unsetLevenbergMarquardt() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(LEVENBERGMARQUARDT$2, 0);
        }
    }

    /**
     * Gets the "particleSwarm" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm getParticleSwarm() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) get_store()
                                                                                                  .find_element_user(PARTICLESWARM$4,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "particleSwarm" element
     */
    public boolean isSetParticleSwarm() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(PARTICLESWARM$4) != 0;
        }
    }

    /**
     * Sets the "particleSwarm" element
     */
    public void setParticleSwarm(
        org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm particleSwarm) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) get_store()
                                                                                                  .find_element_user(PARTICLESWARM$4,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) get_store()
                                                                                                      .add_element_user(PARTICLESWARM$4);
            }

            target.set(particleSwarm);
        }
    }

    /**
     * Appends and returns a new empty "particleSwarm" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm addNewParticleSwarm() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm) get_store()
                                                                                                  .add_element_user(PARTICLESWARM$4);

            return target;
        }
    }

    /**
     * Unsets the "particleSwarm" element
     */
    public void unsetParticleSwarm() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(PARTICLESWARM$4, 0);
        }
    }

    /**
     * Gets the "simulatedAnnealing" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing getSimulatedAnnealing() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing) get_store()
                                                                                                       .find_element_user(SIMULATEDANNEALING$6,
                    0);

            if (target == null) {
                return null;
            }

            return target;
        }
    }

    /**
     * True if has "simulatedAnnealing" element
     */
    public boolean isSetSimulatedAnnealing() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().count_elements(SIMULATEDANNEALING$6) != 0;
        }
    }

    /**
     * Sets the "simulatedAnnealing" element
     */
    public void setSimulatedAnnealing(
        org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing simulatedAnnealing) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing) get_store()
                                                                                                       .find_element_user(SIMULATEDANNEALING$6,
                    0);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing) get_store()
                                                                                                           .add_element_user(SIMULATEDANNEALING$6);
            }

            target.set(simulatedAnnealing);
        }
    }

    /**
     * Appends and returns a new empty "simulatedAnnealing" element
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing addNewSimulatedAnnealing() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing) get_store()
                                                                                                       .add_element_user(SIMULATEDANNEALING$6);

            return target;
        }
    }

    /**
     * Unsets the "simulatedAnnealing" element
     */
    public void unsetSimulatedAnnealing() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_element(SIMULATEDANNEALING$6, 0);
        }
    }

    /**
     * Gets the "methodName" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName.Enum getMethodName() {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(METHODNAME$8);

            if (target == null) {
                return null;
            }

            return (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName.Enum) target.getEnumValue();
        }
    }

    /**
     * Gets (as xml) the "methodName" attribute
     */
    public org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName xgetMethodName() {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) get_store()
                                                                                                      .find_attribute_user(METHODNAME$8);

            return target;
        }
    }

    /**
     * True if has "methodName" attribute
     */
    public boolean isSetMethodName() {
        synchronized (monitor()) {
            check_orphaned();

            return get_store().find_attribute_user(METHODNAME$8) != null;
        }
    }

    /**
     * Sets the "methodName" attribute
     */
    public void setMethodName(
        org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName.Enum methodName) {
        synchronized (monitor()) {
            check_orphaned();

            org.apache.xmlbeans.SimpleValue target = null;
            target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                           .find_attribute_user(METHODNAME$8);

            if (target == null) {
                target = (org.apache.xmlbeans.SimpleValue) get_store()
                                                               .add_attribute_user(METHODNAME$8);
            }

            target.setEnumValue(methodName);
        }
    }

    /**
     * Sets (as xml) the "methodName" attribute
     */
    public void xsetMethodName(
        org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName methodName) {
        synchronized (monitor()) {
            check_orphaned();

            org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName target =
                null;
            target = (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) get_store()
                                                                                                      .find_attribute_user(METHODNAME$8);

            if (target == null) {
                target = (org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName) get_store()
                                                                                                          .add_attribute_user(METHODNAME$8);
            }

            target.set(methodName);
        }
    }

    /**
     * Unsets the "methodName" attribute
     */
    public void unsetMethodName() {
        synchronized (monitor()) {
            check_orphaned();
            get_store().remove_attribute(METHODNAME$8);
        }
    }

    /**
     * An XML methodName(@).
     *
     * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.Method$MethodName.
     */
    public static class MethodNameImpl extends org.apache.xmlbeans.impl.values.JavaStringEnumerationHolderEx
        implements org.copasi.copasiws.services.parameterestimationws.types.Method.MethodName {
        public MethodNameImpl(org.apache.xmlbeans.SchemaType sType) {
            super(sType, false);
        }

        protected MethodNameImpl(org.apache.xmlbeans.SchemaType sType, boolean b) {
            super(sType, b);
        }
    }
}
