# Microsoft Developer Studio Project File - Name="trajectory" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=trajectory - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "trajectory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "trajectory.mak" CFG="trajectory - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "trajectory - Win32 Build" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build"
# PROP BASE Intermediate_Dir "Build"
# PROP BASE Cmd_Line "nmake /f "Makefile""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "../lib/trajectory.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "../lib/trajectory.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "trajectory - Win32 Build"

!IF  "$(CFG)" == "trajectory - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CHybridMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CHybridNextReactionRKMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CLsodaMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CStochDirectMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CStochMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CStochNextReactionMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CTauLeapMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CTimeSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryProblem.cpp
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryTask.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CHybridMethod.h
# End Source File
# Begin Source File

SOURCE=.\CHybridNextReactionRKMethod.h
# End Source File
# Begin Source File

SOURCE=.\CLsodaMethod.h
# End Source File
# Begin Source File

SOURCE=.\CStochDirectMethod.h
# End Source File
# Begin Source File

SOURCE=.\CStochMethod.h
# End Source File
# Begin Source File

SOURCE=.\CStochNextReactionMethod.h
# End Source File
# Begin Source File

SOURCE=.\CTauLeapMethod.h
# End Source File
# Begin Source File

SOURCE=.\CTimeSeries.h
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryMethod.h
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryProblem.h
# End Source File
# Begin Source File

SOURCE=.\CTrajectoryTask.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\common.pri
# End Source File
# Begin Source File

SOURCE=..\lib.pri
# End Source File
# Begin Source File

SOURCE=.\trajectory.pro
# End Source File
# End Target
# End Project
