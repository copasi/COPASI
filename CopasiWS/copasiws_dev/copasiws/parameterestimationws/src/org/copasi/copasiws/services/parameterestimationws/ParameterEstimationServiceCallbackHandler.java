// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/ParameterEstimationServiceCallbackHandler.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:57 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * ParameterEstimationServiceCallbackHandler.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis2 version: 1.3  Built on : Aug 10, 2007 (04:45:47 LKT)
 */
package org.copasi.copasiws.services.parameterestimationws;


/**
 *  ParameterEstimationServiceCallbackHandler Callback class, Users can extend this class and implement
 *  their own receiveResult and receiveError methods.
 */
public abstract class ParameterEstimationServiceCallbackHandler {
    protected Object clientData;

    /**
     * User can pass in any object that needs to be accessed once the NonBlocking
     * Web service call is finished and appropriate method of this CallBack is called.
     * @param clientData Object mechanism by which the user can pass in user data
     * that will be avilable at the time this callback is called.
     */
    public ParameterEstimationServiceCallbackHandler(Object clientData) {
        this.clientData = clientData;
    }

    /**
     * Please use this constructor if you don't want to set any clientData
     */
    public ParameterEstimationServiceCallbackHandler() {
        this.clientData = null;
    }

    /**
     * Get the client data
     */
    public Object getClientData() {
        return clientData;
    }

    /**
     * auto generated Axis2 call back method for createSimulationResource method
     * override this method for handling normal response from createSimulationResource operation
     */
    public void receiveResultcreateSimulationResource(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from createSimulationResource operation
     */
    public void receiveErrorcreateSimulationResource(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for sendModel method
     * override this method for handling normal response from sendModel operation
     */
    public void receiveResultsendModel(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from sendModel operation
     */
    public void receiveErrorsendModel(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for sendExperimentalData method
     * override this method for handling normal response from sendExperimentalData operation
     */
    public void receiveResultsendExperimentalData(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from sendExperimentalData operation
     */
    public void receiveErrorsendExperimentalData(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for setModelToExperimentMap method
     * override this method for handling normal response from setModelToExperimentMap operation
     */
    public void receiveResultsetModelToExperimentMap(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from setModelToExperimentMap operation
     */
    public void receiveErrorsetModelToExperimentMap(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for setFitItemsAndMethod method
     * override this method for handling normal response from setFitItemsAndMethod operation
     */
    public void receiveResultsetFitItemsAndMethod(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from setFitItemsAndMethod operation
     */
    public void receiveErrorsetFitItemsAndMethod(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for startSimulator method
     * override this method for handling normal response from startSimulator operation
     */
    public void receiveResultstartSimulator(
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from startSimulator operation
     */
    public void receiveErrorstartSimulator(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for getSimulatorStatus method
     * override this method for handling normal response from getSimulatorStatus operation
     */
    public void receiveResultgetSimulatorStatus(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from getSimulatorStatus operation
     */
    public void receiveErrorgetSimulatorStatus(java.lang.Exception e) {
    }

    /**
     * auto generated Axis2 call back method for getResult method
     * override this method for handling normal response from getResult operation
     */
    public void receiveResultgetResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument result) {
    }

    /**
     * auto generated Axis2 Error handler
     * override this method for handling error response from getResult operation
     */
    public void receiveErrorgetResult(java.lang.Exception e) {
    }
}
