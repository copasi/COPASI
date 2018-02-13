#!/bin/env python

#
# This example registers a callback handler, so that when CTRL+C is pressed
# the running COPASI task is asked to be stopped
#

import COPASI
import sys
import signal


try:
    dataModel = COPASI.CCopasiRootContainer.addDatamodel()
except:
    dataModel = COPASI.CRootContainer.addDatamodel()

class PythonProgress(COPASI.CProcessReport):
    def __init__(self, maxTime=0):
        super(PythonProgress, self).__init__(maxTime)
        self.shouldProceed = True

    def progressItem(self, handle):
        print('progress on: {0} shouldProceed={1}'.format(handle, self.shouldProceed))
        return self.shouldProceed

    def proceed(self):
        return self.shouldProceed

    def askToStop(self):
        print('task should stop soon ...')
        self.shouldProceed = False

# instantiate progress report
progress = PythonProgress().__disown__()

# now setup a handler to ask to stop the processing
def sigint_handler(signum, frame):
    global progress
    progress.askToStop()

signal.signal(signal.SIGINT, sigint_handler)


def simulate_file_with_progress(file_name):

    if not dataModel.loadModel(file_name):
        print("could'nt load COPASI file due to: ")
        print(COPASI.CCopasiMessage.getAllMessageText())
        return

    # go through the processes and run the scheduled one
    for i in range(dataModel.getNumTasks()):
        task = dataModel.getTaskList().get(i)
        if task.isScheduled():
            print('Running Scheduled Task: {0}, stop anytime using CTRL+C'.format( task))
            # set progress support
            task.setCallBack(progress)
            # execute the task
            task.process(True)
            # unset
            task.clearCallBack()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print('usage: progress_report <cps file>')
        sys.exit(1)
    simulate_file_with_progress(sys.argv[1])