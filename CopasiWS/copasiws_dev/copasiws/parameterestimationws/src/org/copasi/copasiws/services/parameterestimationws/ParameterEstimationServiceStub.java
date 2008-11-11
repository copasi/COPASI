// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/ParameterEstimationServiceStub.java,v $ 
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
 * ParameterEstimationServiceStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis2 version: 1.3  Built on : Aug 10, 2007 (04:45:47 LKT)
 */
package org.copasi.copasiws.services.parameterestimationws;


/*
 *  ParameterEstimationServiceStub java implementation
 */
public class ParameterEstimationServiceStub extends org.apache.axis2.client.Stub {
    protected org.apache.axis2.description.AxisOperation[] _operations;

    //hashmaps to keep the fault mapping
    private java.util.HashMap faultExceptionNameMap = new java.util.HashMap();
    private java.util.HashMap faultExceptionClassNameMap = new java.util.HashMap();
    private java.util.HashMap faultMessageMap = new java.util.HashMap();
    private javax.xml.namespace.QName[] opNameArray = null;

    /**
     *Constructor that takes in a configContext
     */
    public ParameterEstimationServiceStub(
        org.apache.axis2.context.ConfigurationContext configurationContext,
        java.lang.String targetEndpoint) throws org.apache.axis2.AxisFault {
        this(configurationContext, targetEndpoint, false);
    }

    /**
     * Constructor that takes in a configContext  and useseperate listner
     */
    public ParameterEstimationServiceStub(
        org.apache.axis2.context.ConfigurationContext configurationContext,
        java.lang.String targetEndpoint, boolean useSeparateListener)
        throws org.apache.axis2.AxisFault {
        //To populate AxisService
        populateAxisService();
        populateFaults();

        _serviceClient = new org.apache.axis2.client.ServiceClient(configurationContext,
                _service);

        configurationContext = _serviceClient.getServiceContext()
                                             .getConfigurationContext();

        _serviceClient.getOptions()
                      .setTo(new org.apache.axis2.addressing.EndpointReference(
                targetEndpoint));
        _serviceClient.getOptions().setUseSeparateListener(useSeparateListener);
    }

    /**
     * Default Constructor
     */
    public ParameterEstimationServiceStub(
        org.apache.axis2.context.ConfigurationContext configurationContext)
        throws org.apache.axis2.AxisFault {
        this(configurationContext,
            "http://localhost:8080/axis2/services/ParameterEstimationService");
    }

    /**
     * Default Constructor
     */
    public ParameterEstimationServiceStub() throws org.apache.axis2.AxisFault {
        this("http://localhost:8080/axis2/services/ParameterEstimationService");
    }

    /**
     * Constructor taking the target endpoint
     */
    public ParameterEstimationServiceStub(java.lang.String targetEndpoint)
        throws org.apache.axis2.AxisFault {
        this(null, targetEndpoint);
    }

    private void populateAxisService() throws org.apache.axis2.AxisFault {
        //creating the Service with a unique name
        _service = new org.apache.axis2.description.AxisService(
                "ParameterEstimationService" + this.hashCode());

        //creating the operations
        org.apache.axis2.description.AxisOperation __operation;

        _operations = new org.apache.axis2.description.AxisOperation[8];

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "createSimulationResource"));
        _service.addOperation(__operation);

        _operations[0] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "sendModel"));
        _service.addOperation(__operation);

        _operations[1] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "sendExperimentalData"));
        _service.addOperation(__operation);

        _operations[2] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "setModelToExperimentMap"));
        _service.addOperation(__operation);

        _operations[3] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "setFitItemsAndMethod"));
        _service.addOperation(__operation);

        _operations[4] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "startSimulator"));
        _service.addOperation(__operation);

        _operations[5] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "getSimulatorStatus"));
        _service.addOperation(__operation);

        _operations[6] = __operation;

        __operation = new org.apache.axis2.description.OutInAxisOperation();

        __operation.setName(new javax.xml.namespace.QName(
                "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                "getResult"));
        _service.addOperation(__operation);

        _operations[7] = __operation;
    }

    //populates the faults
    private void populateFaults() {
        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");

        faultExceptionNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultExceptionClassNameMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage");
        faultMessageMap.put(new javax.xml.namespace.QName(
                "http://parameterestimationws.services.copasiws.copasi.org/types",
                "ServiceFault"),
            "org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument");
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#createSimulationResource
     * @param createSimulationResource96
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument createSimulationResource(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument createSimulationResource96)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[0].getName());
            _operationClient.getOptions().setAction("CreateSimulationResource");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    createSimulationResource96,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "createSimulationResource")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startcreateSimulationResource
     * @param createSimulationResource96
     */
    public void startcreateSimulationResource(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument createSimulationResource96,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[0].getName());
        _operationClient.getOptions().setAction("CreateSimulationResource");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                createSimulationResource96,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "createSimulationResource")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultcreateSimulationResource((org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorcreateSimulationResource(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorcreateSimulationResource((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorcreateSimulationResource(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorcreateSimulationResource(f);
                                }
                            } else {
                                callback.receiveErrorcreateSimulationResource(f);
                            }
                        } else {
                            callback.receiveErrorcreateSimulationResource(f);
                        }
                    } else {
                        callback.receiveErrorcreateSimulationResource(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[0].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[0].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#sendModel
     * @param sendModel98
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument sendModel(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument sendModel98)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[1].getName());
            _operationClient.getOptions().setAction("SendModel");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    sendModel98,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "sendModel")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startsendModel
     * @param sendModel98
     */
    public void startsendModel(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument sendModel98,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[1].getName());
        _operationClient.getOptions().setAction("SendModel");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                sendModel98,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "sendModel")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultsendModel((org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorsendModel(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorsendModel((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorsendModel(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendModel(f);
                                }
                            } else {
                                callback.receiveErrorsendModel(f);
                            }
                        } else {
                            callback.receiveErrorsendModel(f);
                        }
                    } else {
                        callback.receiveErrorsendModel(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[1].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[1].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#sendExperimentalData
     * @param sendExperimentalData100
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument sendExperimentalData(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument sendExperimentalData100)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[2].getName());
            _operationClient.getOptions().setAction("SendExperimentalData");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    sendExperimentalData100,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "sendExperimentalData")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startsendExperimentalData
     * @param sendExperimentalData100
     */
    public void startsendExperimentalData(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument sendExperimentalData100,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[2].getName());
        _operationClient.getOptions().setAction("SendExperimentalData");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                sendExperimentalData100,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "sendExperimentalData")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultsendExperimentalData((org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorsendExperimentalData(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorsendExperimentalData((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorsendExperimentalData(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsendExperimentalData(f);
                                }
                            } else {
                                callback.receiveErrorsendExperimentalData(f);
                            }
                        } else {
                            callback.receiveErrorsendExperimentalData(f);
                        }
                    } else {
                        callback.receiveErrorsendExperimentalData(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[2].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[2].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#setModelToExperimentMap
     * @param setModelToExperimentMap102
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument setModelToExperimentMap(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument setModelToExperimentMap102)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[3].getName());
            _operationClient.getOptions().setAction("SetModelToExperimentMap");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    setModelToExperimentMap102,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "setModelToExperimentMap")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startsetModelToExperimentMap
     * @param setModelToExperimentMap102
     */
    public void startsetModelToExperimentMap(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument setModelToExperimentMap102,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[3].getName());
        _operationClient.getOptions().setAction("SetModelToExperimentMap");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                setModelToExperimentMap102,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "setModelToExperimentMap")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultsetModelToExperimentMap((org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorsetModelToExperimentMap(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorsetModelToExperimentMap((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorsetModelToExperimentMap(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetModelToExperimentMap(f);
                                }
                            } else {
                                callback.receiveErrorsetModelToExperimentMap(f);
                            }
                        } else {
                            callback.receiveErrorsetModelToExperimentMap(f);
                        }
                    } else {
                        callback.receiveErrorsetModelToExperimentMap(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[3].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[3].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#setFitItemsAndMethod
     * @param setFitItemsAndMethod104
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument setFitItemsAndMethod(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument setFitItemsAndMethod104)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[4].getName());
            _operationClient.getOptions().setAction("SetFitItemsAndMethod");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    setFitItemsAndMethod104,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "setFitItemsAndMethod")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startsetFitItemsAndMethod
     * @param setFitItemsAndMethod104
     */
    public void startsetFitItemsAndMethod(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument setFitItemsAndMethod104,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[4].getName());
        _operationClient.getOptions().setAction("SetFitItemsAndMethod");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                setFitItemsAndMethod104,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "setFitItemsAndMethod")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultsetFitItemsAndMethod((org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorsetFitItemsAndMethod(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorsetFitItemsAndMethod((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorsetFitItemsAndMethod(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorsetFitItemsAndMethod(f);
                                }
                            } else {
                                callback.receiveErrorsetFitItemsAndMethod(f);
                            }
                        } else {
                            callback.receiveErrorsetFitItemsAndMethod(f);
                        }
                    } else {
                        callback.receiveErrorsetFitItemsAndMethod(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[4].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[4].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startSimulator
     * @param startSimulator106
     */
    public org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument startSimulator(
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument startSimulator106)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[5].getName());
            _operationClient.getOptions().setAction("StartSimulator");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    startSimulator106,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "startSimulator")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startstartSimulator
     * @param startSimulator106
     */
    public void startstartSimulator(
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument startSimulator106,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[5].getName());
        _operationClient.getOptions().setAction("StartSimulator");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                startSimulator106,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "startSimulator")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultstartSimulator((org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorstartSimulator(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorstartSimulator((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorstartSimulator(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorstartSimulator(f);
                                }
                            } else {
                                callback.receiveErrorstartSimulator(f);
                            }
                        } else {
                            callback.receiveErrorstartSimulator(f);
                        }
                    } else {
                        callback.receiveErrorstartSimulator(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[5].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[5].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#getSimulatorStatus
     * @param getSimulatorStatus108
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument getSimulatorStatus(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument getSimulatorStatus108)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[6].getName());
            _operationClient.getOptions().setAction("GetSimulatorStatus");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    getSimulatorStatus108,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "getSimulatorStatus")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startgetSimulatorStatus
     * @param getSimulatorStatus108
     */
    public void startgetSimulatorStatus(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument getSimulatorStatus108,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[6].getName());
        _operationClient.getOptions().setAction("GetSimulatorStatus");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                getSimulatorStatus108,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "getSimulatorStatus")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultgetSimulatorStatus((org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorgetSimulatorStatus(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorgetSimulatorStatus((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorgetSimulatorStatus(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetSimulatorStatus(f);
                                }
                            } else {
                                callback.receiveErrorgetSimulatorStatus(f);
                            }
                        } else {
                            callback.receiveErrorgetSimulatorStatus(f);
                        }
                    } else {
                        callback.receiveErrorgetSimulatorStatus(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[6].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[6].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     * Auto generated method signature
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#getResult
     * @param getResult110
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument getResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument getResult110)
        throws java.rmi.RemoteException,
            org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage {
        try {
            org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[7].getName());
            _operationClient.getOptions().setAction("GetResult");
            _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

            addPropertyToOperationClient(_operationClient,
                org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
                "&");

            // create a message context
            org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

            // create SOAP envelope with that payload
            org.apache.axiom.soap.SOAPEnvelope env = null;

            env = toEnvelope(getFactory(_operationClient.getOptions()
                                                        .getSoapVersionURI()),
                    getResult110,
                    optimizeContent(
                        new javax.xml.namespace.QName(
                            "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                            "getResult")));

            //adding SOAP soap_headers
            _serviceClient.addHeadersToEnvelope(env);
            // set the message context with that soap envelope
            _messageContext.setEnvelope(env);

            // add the message contxt to the operation client
            _operationClient.addMessageContext(_messageContext);

            //execute the operation client
            _operationClient.execute(true);

            org.apache.axis2.context.MessageContext _returnMessageContext = _operationClient.getMessageContext(org.apache.axis2.wsdl.WSDLConstants.MESSAGE_LABEL_IN_VALUE);
            org.apache.axiom.soap.SOAPEnvelope _returnEnv = _returnMessageContext.getEnvelope();

            java.lang.Object object = fromOM(_returnEnv.getBody()
                                                       .getFirstElement(),
                    org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.class,
                    getEnvelopeNamespaces(_returnEnv));
            _messageContext.getTransportOut().getSender()
                           .cleanup(_messageContext);

            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument) object;
        } catch (org.apache.axis2.AxisFault f) {
            org.apache.axiom.om.OMElement faultElt = f.getDetail();

            if (faultElt != null) {
                if (faultExceptionNameMap.containsKey(faultElt.getQName())) {
                    //make the fault by reflection
                    try {
                        java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                        java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                        java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                        //message class
                        java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                        java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                        java.lang.Object messageObject = fromOM(faultElt,
                                messageClass, null);
                        java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                new java.lang.Class[] { messageClass });
                        m.invoke(ex, new java.lang.Object[] { messageObject });

                        if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                            throw (org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex;
                        }

                        throw new java.rmi.RemoteException(ex.getMessage(), ex);
                    } catch (java.lang.ClassCastException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.ClassNotFoundException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.NoSuchMethodException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.reflect.InvocationTargetException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.IllegalAccessException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    } catch (java.lang.InstantiationException e) {
                        // we cannot intantiate the class - throw the original Axis fault
                        throw f;
                    }
                } else {
                    throw f;
                }
            } else {
                throw f;
            }
        }
    }

    /**
     * Auto generated method signature for Asynchronous Invocations
     * @see org.copasi.copasiws.services.parameterestimationws.ParameterEstimationService#startgetResult
     * @param getResult110
     */
    public void startgetResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument getResult110,
        final org.copasi.copasiws.services.parameterestimationws.ParameterEstimationServiceCallbackHandler callback)
        throws java.rmi.RemoteException {
        org.apache.axis2.client.OperationClient _operationClient = _serviceClient.createClient(_operations[7].getName());
        _operationClient.getOptions().setAction("GetResult");
        _operationClient.getOptions().setExceptionToBeThrownOnSOAPFault(true);

        addPropertyToOperationClient(_operationClient,
            org.apache.axis2.description.WSDL2Constants.ATTR_WHTTP_QUERY_PARAMETER_SEPARATOR,
            "&");

        // create SOAP envelope with that payload
        org.apache.axiom.soap.SOAPEnvelope env = null;
        org.apache.axis2.context.MessageContext _messageContext = new org.apache.axis2.context.MessageContext();

        //Style is Doc.
        env = toEnvelope(getFactory(_operationClient.getOptions()
                                                    .getSoapVersionURI()),
                getResult110,
                optimizeContent(
                    new javax.xml.namespace.QName(
                        "http://services.copasiws.copasi.org/parameterestimationws.wsdl",
                        "getResult")));

        // adding SOAP soap_headers
        _serviceClient.addHeadersToEnvelope(env);
        // create message context with that soap envelope
        _messageContext.setEnvelope(env);

        // add the message context to the operation client
        _operationClient.addMessageContext(_messageContext);

        _operationClient.setCallback(new org.apache.axis2.client.async.AxisCallback() {
                public void onMessage(
                    org.apache.axis2.context.MessageContext resultContext) {
                    try {
                        org.apache.axiom.soap.SOAPEnvelope resultEnv = resultContext.getEnvelope();

                        java.lang.Object object = fromOM(resultEnv.getBody()
                                                                  .getFirstElement(),
                                org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.class,
                                getEnvelopeNamespaces(resultEnv));
                        callback.receiveResultgetResult((org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument) object);
                    } catch (org.apache.axis2.AxisFault e) {
                        callback.receiveErrorgetResult(e);
                    }
                }

                public void onError(java.lang.Exception error) {
                    if (error instanceof org.apache.axis2.AxisFault) {
                        org.apache.axis2.AxisFault f = (org.apache.axis2.AxisFault) error;
                        org.apache.axiom.om.OMElement faultElt = f.getDetail();

                        if (faultElt != null) {
                            if (faultExceptionNameMap.containsKey(
                                        faultElt.getQName())) {
                                //make the fault by reflection
                                try {
                                    java.lang.String exceptionClassName = (java.lang.String) faultExceptionClassNameMap.get(faultElt.getQName());
                                    java.lang.Class exceptionClass = java.lang.Class.forName(exceptionClassName);
                                    java.lang.Exception ex = (java.lang.Exception) exceptionClass.newInstance();

                                    //message class
                                    java.lang.String messageClassName = (java.lang.String) faultMessageMap.get(faultElt.getQName());
                                    java.lang.Class messageClass = java.lang.Class.forName(messageClassName);
                                    java.lang.Object messageObject = fromOM(faultElt,
                                            messageClass, null);
                                    java.lang.reflect.Method m = exceptionClass.getMethod("setFaultMessage",
                                            new java.lang.Class[] { messageClass });
                                    m.invoke(ex,
                                        new java.lang.Object[] { messageObject });

                                    if (ex instanceof org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) {
                                        callback.receiveErrorgetResult((org.copasi.copasiws.services.parameterestimationws.ServiceFaultMessage) ex);

                                        return;
                                    }

                                    callback.receiveErrorgetResult(new java.rmi.RemoteException(
                                            ex.getMessage(), ex));
                                } catch (java.lang.ClassCastException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (java.lang.ClassNotFoundException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (java.lang.NoSuchMethodException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (java.lang.reflect.InvocationTargetException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (java.lang.IllegalAccessException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (java.lang.InstantiationException e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                } catch (org.apache.axis2.AxisFault e) {
                                    // we cannot intantiate the class - throw the original Axis fault
                                    callback.receiveErrorgetResult(f);
                                }
                            } else {
                                callback.receiveErrorgetResult(f);
                            }
                        } else {
                            callback.receiveErrorgetResult(f);
                        }
                    } else {
                        callback.receiveErrorgetResult(error);
                    }
                }

                public void onFault(
                    org.apache.axis2.context.MessageContext faultContext) {
                    org.apache.axis2.AxisFault fault = org.apache.axis2.util.Utils.getInboundFaultFromMessageContext(faultContext);
                    onError(fault);
                }

                public void onComplete() {
                    // Do nothing by default
                }
            });

        org.apache.axis2.util.CallbackReceiver _callbackReceiver = null;

        if ((_operations[7].getMessageReceiver() == null) &&
                _operationClient.getOptions().isUseSeparateListener()) {
            _callbackReceiver = new org.apache.axis2.util.CallbackReceiver();
            _operations[7].setMessageReceiver(_callbackReceiver);
        }

        //execute the operation client
        _operationClient.execute(false);
    }

    /**
     *  A utility method that copies the namepaces from the SOAPEnvelope
     */
    private java.util.Map getEnvelopeNamespaces(
        org.apache.axiom.soap.SOAPEnvelope env) {
        java.util.Map returnMap = new java.util.HashMap();
        java.util.Iterator namespaceIterator = env.getAllDeclaredNamespaces();

        while (namespaceIterator.hasNext()) {
            org.apache.axiom.om.OMNamespace ns = (org.apache.axiom.om.OMNamespace) namespaceIterator.next();
            returnMap.put(ns.getPrefix(), ns.getNamespaceURI());
        }

        return returnMap;
    }

    private boolean optimizeContent(javax.xml.namespace.QName opName) {
        if (opNameArray == null) {
            return false;
        }

        for (int i = 0; i < opNameArray.length; i++) {
            if (opName.equals(opNameArray[i])) {
                return true;
            }
        }

        return false;
    }

    //http://localhost:8080/axis2/services/ParameterEstimationService
    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.om.OMElement toOM(
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.om.impl.builder.StAXOMBuilder builder = new org.apache.axiom.om.impl.builder.StAXOMBuilder(org.apache.axiom.om.OMAbstractFactory.getOMFactory(),
                new org.apache.axis2.util.StreamWrapper(param.newXMLStreamReader()));
        org.apache.axiom.om.OMElement documentElement = builder.getDocumentElement();

        ((org.apache.axiom.om.impl.OMNodeEx) documentElement).setParent(null);

        return documentElement;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    /**
     *  get the default envelope
     */
    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory) {
        return factory.getDefaultEnvelope();
    }

    public org.apache.xmlbeans.XmlObject fromOM(
        org.apache.axiom.om.OMElement param, java.lang.Class type,
        java.util.Map extraNamespaces) throws org.apache.axis2.AxisFault {
        try {
            if (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }

            if (org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.class.equals(
                        type)) {
                if (extraNamespaces != null) {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching(),
                        new org.apache.xmlbeans.XmlOptions().setLoadAdditionalNamespaces(
                            extraNamespaces));
                } else {
                    return org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument.Factory.parse(param.getXMLStreamReaderWithoutCaching());
                }
            }
        } catch (java.lang.Exception e) {
            throw org.apache.axis2.AxisFault.makeFault(e);
        }

        return null;
    }
}
