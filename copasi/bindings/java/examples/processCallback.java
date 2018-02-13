/**
 * This is an example on how to build models with the COPASI backend API.
 */
import org.COPASI.*;
import java.io.*;

public class processCallback extends org.COPASI.CProcessReport
{
  
  boolean _shouldProceed;
  
  public processCallback ()
  {
    this(0);
  }
  
  public processCallback (long maxTime)
  {
    super(maxTime);
    _shouldProceed = true;
  }
  
  public void askToStop()
  {
    _shouldProceed = false;
  }
  
  @Override
  public boolean progressItem(long handle)
  {
    System.out.println(String.format("progress on: %d shouldProceed=%b",handle, _shouldProceed));
    return _shouldProceed;
  }
  
  @Override
  public boolean proceed()
  {
    return _shouldProceed;
  }
  

 public static void main(String[] args) throws Exception
 {
   if (args.length == 0)
   {
     System.out.println("usage: process_callback <cps file>");
     return;
   }
   
   CDataModel dataModel = CRootContainer.addDatamodel();
   
   if (!dataModel.loadModel(args[0]))
   {
     System.out.println("Couldn't open the model: ");
     System.out.println(CCopasiMessage.getAllMessageText());
     return;
   }
   
   final processCallback progress = new processCallback();
   
    Runtime.getRuntime().addShutdownHook(new Thread() {
      public void run() {
        System.out.println("Stop requested ... waiting 20 seconds for process to finish");
      progress.askToStop();
      
      try
      {
      Thread.sleep(20000);
      }
      catch (Exception ex)
      {
        //
      }
      }
    });
   
   
   for (int i = 0; i < dataModel.getNumTasks(); ++i)
   {
     CCopasiTask task = dataModel.getTask(i);
     if (!task.isScheduled())
       continue;
     System.out.println(String.format("Running Scheduled Task: %s, stop anytime using CTRL+C",task.getObjectName()));
     
     // set progress support
     task.setCallBack(progress);
     
     // execute the task
     task.process(true);
     
     // unset
     task.clearCallBack();
   }
   System.out.println("done ... ");
 }
}