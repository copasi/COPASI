// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/RunTests.java,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/04/10 10:36:26 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

package org.COPASI.unittests;

import junit.framework.Test;
import junit.framework.TestSuite;

public class RunTests extends TestSuite
{
  public static Test suite()
  {
    TestSuite suite = new TestSuite( "Java bindings test-suite" );
    suite.addTestSuite( org.COPASI.unittests.Test_CreateSimpleModel.class );
    suite.addTestSuite( org.COPASI.unittests.Test_RunSimulations.class );
    suite.addTestSuite( org.COPASI.unittests.Test_RunOptimization.class );
    return suite;
  }
}

