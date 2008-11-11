// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/ServiceFaultMessage.java,v $ 
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
 * ServiceFaultMessage.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis2 version: 1.3  Built on : Aug 10, 2007 (04:45:47 LKT)
 */
package org.copasi.copasiws.services.parameterestimationws;

public class ServiceFaultMessage extends java.lang.Exception {
    private org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument faultMessage;

    public ServiceFaultMessage() {
        super("ServiceFaultMessage");
    }

    public ServiceFaultMessage(java.lang.String s) {
        super(s);
    }

    public ServiceFaultMessage(java.lang.String s, java.lang.Throwable ex) {
        super(s, ex);
    }

    public void setFaultMessage(
        org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument msg) {
        faultMessage = msg;
    }

    public org.copasi.copasiws.services.parameterestimationws.types.ServiceFaultDocument getFaultMessage() {
        return faultMessage;
    }
}
