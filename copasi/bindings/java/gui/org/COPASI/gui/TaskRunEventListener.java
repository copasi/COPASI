// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/gui/org/COPASI/gui/TaskRunEventListener.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/20 14:01:24 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package org.COPASI.gui;

import java.util.EventListener;
import org.COPASI.gui.TaskRunEvent;

interface TaskRunEventListener extends EventListener 
{
    public void taskRun(TaskRunEvent event);        
};
