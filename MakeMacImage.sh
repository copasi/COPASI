#!/bin/bash

TMPDIR=/tmp
RELEASE="11"
SETFILE=/Developer/Tools/SetFile
HDIUTIL=/usr/bin/hdiutil

# check if the binary is there
if test -e ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI ; then
    echo -n "Please build the copasi executable first.\n"
    exit 1;
else

# make a temporary directory and copy the CopasiUI.app directory there.
    mkdir ${TMPDIR}/copasi;
    cp -r copasi/CopasiUI/CopasiUI.app ${TMPDIR}/copasi/

# copy the icon into the Resources directory
    cp copasi.icns ${TMPDIR}/copasi/CopasiUI/CopasiUI.app/Contents/Resources/

# set the icon in the Info.plist file in the Contents directory


# copy the examples into the Resources directory
    mkdir ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/EXAMPLES


# copy the files for the wizard into the Resources directory
    mkdir -p ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html
    cp ./copasi/wizard/help_html/*.html ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/
    cp -r ./copasi/wizard/help_html/figures ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/

# add the readme to the image
    cp README_MAC.rtf ${TMPDIR}/copasi/

# set the bundles flag with SetFile
    ${SETFILE} -a b ${TMPDIR}/copasi/CopasiUI.app

# make an image with hdiutil from the folder
    ${HDIUTIL} create -size ${SIZE}k -format UDZ0 -srcfolder ${TMPDIR}/copasi -volname Copasi-${RELEASE} -uid 99 -gid 99 -scrub ${TMPDIR}/Copasi-${RELEASE}-Mac.dmg 


fi

