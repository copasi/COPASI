#!/bin/bash

TMPDIR=/tmp
RELEASE="12"

SETFILE=/Developer/Tools/SetFile
HDIUTIL=/usr/bin/hdiutil
SED=/usr/bin/sed
CUT=/usr/bin/cut
GREP=/usr/bin/grep
STRIP=/usr/bin/strip
OTOOL=/usr/bin/otool

#EXAMPLES="brusselator.cps YeastGlycolysis.gps CircadianClock.cps Metabolism-2000Poo.xml"
EXAMPLES=`find ./TestSuite/distribution/ -type f -maxdepth 1` 

# check if the binary is there
if test -e ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI ; then
# test if the binary is statically linked agains libqt
    if ${OTOOL} -L ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI | grep libqt 2>&1 > /dev/null ;then
        echo ""
        echo "CopasiUI is dynamicall linked against Qt."
        echo "Please link the binary statically before making an image."
        echo ""
        exit 1
    fi
# strip the binary
    echo "Removing debugging symbols from the binary."
    ${STRIP} ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI  
    
# make a temporary directory and copy the CopasiUI.app directory there.
    echo "Creating temporary directory."
    mkdir ${TMPDIR}/copasi;
    echo "Copying application bundle."
    cp -r copasi/CopasiUI/CopasiUI.app ${TMPDIR}/copasi/

# copy the icon into the Resources directory
    echo "Creating Resources directory."
    mkdir -p ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources
    echo "Copy the icon file to the bundle."
    cp copasi.icns ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/

# set the icon in the Info.plist file in the Contents directory
# the icon file name is located between <string></string> tags in the line after
# <key>CFBundleIconFile</key>
# Maybe this would better be done with a dom parser.
echo "Set the icon in the Info.plist file."
    LINE=`${GREP} -n "CFBundleIconFile" ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist | cut -c1`
    LINE=$((LINE+1))
    ${SED} -e "${LINE}s%<string>.*</string>%<string>copasi.icns</string>%" ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist > ${TMPDIR}/tmp.plist
    mv ${TMPDIR}/tmp.plist ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist

# copy the examples into the Resources directory
    echo "Make example directory."
    mkdir -p ${TMPDIR}/copasi/examples
    echo "Copy examples to example directory."
    for EXAMPLE in $EXAMPLES;do
        cp ${EXAMPLE} ${TMPDIR}/copasi/examples/
    done

# copy the files for the wizard into the Resources directory
    echo "Making directory for wizard."
    mkdir -p ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html
    echo "Copying files for wizard."
    cp ./copasi/wizard/help_html/*.html ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html/
    cp -r ./copasi/wizard/help_html/figures ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html/

# add the readme to the image
    echo "Copying readme file."
    cp README_MAC.rtf ${TMPDIR}/copasi/COPASI-README.rtf

# set the bundles flag with SetFile
    echo "Setting the bundle flag."
    ${SETFILE} -a b ${TMPDIR}/copasi/CopasiUI.app

# make an image with hdiutil from the folder
    echo "Creating compressed image."
    ${HDIUTIL} create -srcfolder ${TMPDIR}/copasi  -uid 99 -gid 99 -scrub -volname Copasi-${RELEASE} ${TMPDIR}/Copasi-${RELEASE}-Darwin.dmg 

# move the image to this directory and delete the temporary diretory
    echo "Cleaning up in temporary directory."
    mv ${TMPDIR}/Copasi-${RELEASE}-Darwin.dmg .
    rm -rf ${TMPDIR}/copasi
 else
    echo ""
    echo "Please build the copasi executable first."
    echo ""
    exit 1;
   
fi

