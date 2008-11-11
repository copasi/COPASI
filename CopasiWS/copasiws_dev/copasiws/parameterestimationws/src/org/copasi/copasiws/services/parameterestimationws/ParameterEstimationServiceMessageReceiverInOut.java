// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/ParameterEstimationServiceMessageReceiverInOut.java,v $ 
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
 * ParameterEstimationServiceMessageReceiverInOut.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis2 version: 1.3  Built on : Aug 10, 2007 (04:45:47 LKT)
 */
package org.copasi.copasiws.services.parameterestimationws;


/**
 *  ParameterEstimationServiceMessageReceiverInOut message receiver
 */
public class ParameterEstimationServiceMessageReceiverInOut extends org.apache.axis2.receivers.AbstractInOutSyncMessageReceiver {
    public void invokeBusinessLogic(
        org.apache.axis2.context.MessageContext msgContext,
        org.apache.axis2.context.MessageContext newMsgContext)
        throws org.apache.axis2.AxisFault {
        try {
            // get the implementation class for the Web Service
            Object obj = getTheImplementationObject(msgContext);

            ParameterEstimationServiceSkeleton skel = (ParameterEstimationServiceSkeleton) obj;

            //Out Envelop
            org.apache.axiom.soap.SOAPEnvelope envelope = null;

            //Find the axisOperation that has been set by the Dispatch phase.
            org.apache.axis2.description.AxisOperation op = msgContext.getOperationContext()
                                                                      .getAxisOperation();

            if (op == null) {
                throw new org.apache.axis2.AxisFault(
                    "Operation is not located, if this is doclit style the SOAP-ACTION should specified via the SOAP Action to use the RawXMLProvider");
            }

            java.lang.String methodName;

            if ((op.getName() != null) &&
                    ((methodName = org.apache.axis2.util.JavaUtils.xmlNameToJava(
                            op.getName().getLocalPart())) != null)) {
                if ("createSimulationResource".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument createSimulationResourceResponse1 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument) fromOM(msgContext.getEnvelope()
                                                                                                                                     .getBody()
                                                                                                                                     .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    createSimulationResourceResponse1 = skel.createSimulationResource(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            createSimulationResourceResponse1, false);
                } else if ("sendModel".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument sendModelResponse3 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument) fromOM(msgContext.getEnvelope()
                                                                                                                      .getBody()
                                                                                                                      .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    sendModelResponse3 = skel.sendModel(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            sendModelResponse3, false);
                } else if ("sendExperimentalData".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument sendExperimentalDataResponse5 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument) fromOM(msgContext.getEnvelope()
                                                                                                                                 .getBody()
                                                                                                                                 .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    sendExperimentalDataResponse5 = skel.sendExperimentalData(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            sendExperimentalDataResponse5, false);
                } else if ("setModelToExperimentMap".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument setModelToExperimentMapResponse7 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument) fromOM(msgContext.getEnvelope()
                                                                                                                                    .getBody()
                                                                                                                                    .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    setModelToExperimentMapResponse7 = skel.setModelToExperimentMap(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            setModelToExperimentMapResponse7, false);
                } else if ("setFitItemsAndMethod".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument setFitItemsAndMethodResponse9 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument) fromOM(msgContext.getEnvelope()
                                                                                                                                 .getBody()
                                                                                                                                 .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    setFitItemsAndMethodResponse9 = skel.setFitItemsAndMethod(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            setFitItemsAndMethodResponse9, false);
                } else if ("startSimulator".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument startSimulatorResponse11 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument) fromOM(msgContext.getEnvelope()
                                                                                                                           .getBody()
                                                                                                                           .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    startSimulatorResponse11 = skel.startSimulator(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            startSimulatorResponse11, false);
                } else if ("getSimulatorStatus".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument getSimulatorStatusResponse13 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument) fromOM(msgContext.getEnvelope()
                                                                                                                               .getBody()
                                                                                                                               .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    getSimulatorStatusResponse13 = skel.getSimulatorStatus(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            getSimulatorStatusResponse13, false);
                } else if ("getResult".equals(methodName)) {
                    org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument getResultResponse15 =
                        null;
                    org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument wrappedParam =
                        (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) fromOM(msgContext.getEnvelope()
                                                                                                                      .getBody()
                                                                                                                      .getFirstElement(),
                            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.class,
                            getEnvelopeNamespaces(msgContext.getEnvelope()));

                    getResultResponse15 = skel.getResult(wrappedParam);

                    envelope = toEnvelope(getSOAPFactory(msgContext),
                            getResultResponse15, false);
                } else {
                    throw new java.lang.RuntimeException("method not found");
                }

                newMsgContext.setEnvelope(envelope);
            }
        } catch (ServiceFaultMessage e) {
            msgContext.setProperty(org.apache.axis2.Constants.FAULT_NAME,
                "ServiceFault");

            org.apache.axis2.AxisFault f = createAxisFault(e);

            if (e.getFaultMessage() != null) {
                f.setDetail(toOM(e.getFaultMessage(), false));
            }

            throw f;
        } catch (java.lang.Exception e) {
            throw org.apache.axis2.AxisFault.makeFault(e);
        }
    }

    //
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
        org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument param,
        boolean optimizeContent) throws org.apache.axis2.AxisFault {
        org.apache.axiom.soap.SOAPEnvelope envelope = factory.getDefaultEnvelope();

        if (param != null) {
            envelope.getBody().addChild(toOM(param, optimizeContent));
        }

        return envelope;
    }

    private org.apache.axiom.soap.SOAPEnvelope toEnvelope(
        org.apache.axiom.soap.SOAPFactory factory,
        org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument param,
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

    private org.apache.axis2.AxisFault createAxisFault(java.lang.Exception e) {
        org.apache.axis2.AxisFault f;
        Throwable cause = e.getCause();

        if (cause != null) {
            f = new org.apache.axis2.AxisFault(e.getMessage(), cause);
        } else {
            f = new org.apache.axis2.AxisFault(e.getMessage());
        }

        return f;
    }
} //end of class
