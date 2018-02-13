/**
 * This is an example on how to build models with the COPASI backend API.
 */
using org.COPASI;
using System;
using System.Diagnostics;
using System.Threading;

public class ProcessCallback : CProcessReport
{
  bool ShouldProceed {get; set;}
  
  public ProcessCallback (uint maxTime=0) : base(maxTime)
  {
    ShouldProceed = true;
  }
  
  public override bool progressItem(uint handle)
  {
    Console.WriteLine(string.Format("progress on: {0} shouldProceed={1}",handle, ShouldProceed));
    return ShouldProceed;
  }
  
  public override bool proceed()
  {
    return ShouldProceed;
  }
  

 static void Main(string[] args)
 {
   if (args.Length == 0)
   {
     Console.WriteLine("usage: process_callback <cps file>");
     return;
   }
   
   var dataModel = CRootContainer.addDatamodel();
   
   if (!dataModel.loadModel(args[0]))
   {
     Console.WriteLine("Couldn't open the model: ");
     Console.WriteLine(CCopasiMessage.getAllMessageText());
     return;
   }
   
   var progress = new ProcessCallback();
   
   Console.CancelKeyPress += delegate {
      Console.WriteLine("Stop requested ... waiting for process to finish");
      progress.ShouldProceed = false;
      
      Thread.Sleep(30000);
      
    };
   
   
   for (uint i = 0; i < dataModel.getNumTasks(); ++i)
   {
     var task = dataModel.getTask(i);
     if (!task.isScheduled())
       continue;
     Console.WriteLine(string.Format("Running Scheduled Task: {0}, stop anytime using CTRL+C",task.getObjectName()));
     
     // set progress support
     task.setCallBack(progress);
     
     // execute the task
     task.process(true);
     
     // unset
     task.clearCallBack();
   }
   
 }
}