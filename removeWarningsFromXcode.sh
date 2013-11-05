#!/bin/bash
if [ ! -f ./COPASI.xcodeproj/project.pbxproj ]; then
  echo "Please run this script from within a build dir configured for XCode"
  exit
fi

# now just remove the warning flags. 
sed -n '/WARNING_CFLA/!p' ./COPASI.xcodeproj/project.pbxproj > /tmp/project.pbxproj_new && mv /tmp/project.pbxproj_new ./COPASI.xcodeproj/project.pbxproj
