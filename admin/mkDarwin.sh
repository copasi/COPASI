if otool -L ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI \
  | grep libqt 2>&1 > /dev/null; then
    echo ""
    echo "CopasiUI is dynamicall linked against Qt."
    echo "Please link the binary statically before making an image."
    echo ""
    exit 1
  fi
    
SETFILE=/Developer/Tools/SetFile

# Create temporary package image drive
hdiutil create Copasi-tmp.dmg -megabytes 400 -volname Copasi-$build-$1 \
  -fs HFS+ -layout NONE

# Mount temporary package image drive
drive=`hdid Copasi-tmp.dmg | ${AWK} -- '{print $1}'`
TMPDIR=`df -l | ${AWK} -- '$1 ~ "'$drive'" {print $6}'`
echo $drive '->' $TMPDIR

echo "Copying application bundle."
mkdir ${TMPDIR}/COPASI
cp -r copasi/CopasiUI/CopasiUI.app ${TMPDIR}/COPASI/

strip ${TMPDIR}/COPASI/CopasiUI.app/Contents/MacOS/CopasiUI

# copy the commandline version if it exists
if [ -e copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE ] ; then    
  cp copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE ${TMPDIR}/COPASI/
  strip ${TMPDIR}/COPASI/CopasiSE
      
  if [ x"$license" = xUS ]; then
    UPLOAD ${TMPDIR}/COPASI/CopasiSE \
      $license/Copasi-AllSE/$1/CopasiSE-$build
   fi
fi  
    
# copy the icon into the Resources directory
echo "Creating Resources directory."
mkdir -p ${TMPDIR}/COPASI/CopasiUI.app/Contents/Resources

echo "Copy the icon file to the bundle."
cp copasi.icns ${TMPDIR}/COPASI/CopasiUI.app/Contents/Resources/

# Create the Info.plist file
sed -e 's/%COPASI_VERSION%/'$major.$minor.$build'/g' \
  copasi/CopasiUI/CopasiUI.plist > ${TMPDIR}/COPASI/CopasiUI.app/Contents/Info.plist

# copy default configuration
echo "Make directory for default configuration"
mkdir -p ${TMPDIR}/COPASI/config
echo "Copy default configuration files"
cp ./copasi/MIRIAM/MIRIAMResources.xml ${TMPDIR}/COPASI/config

# copy the examples into the Resources directory
echo "Make example directory."
mkdir -p ${TMPDIR}/COPASI/examples
echo "Copy examples to example directory."
cp ./TestSuite/distribution/* \
  ${TMPDIR}/COPASI/examples/
# we have defer this to later so that we are able to chown
#    chmod 444 ${TMPDIR}/COPASI/examples/

# copy the files for the wizard into the Resources directory
echo "Making directory for wizard."
mkdir -p ${TMPDIR}/COPASI/CopasiUI.app/Contents/Resources/doc/html
echo "Copying files for wizard."
cp ./copasi/wizard/help_html/*.html \
  ${TMPDIR}/COPASI/CopasiUI.app/Contents/Resources/doc/html/
cp -r ./copasi/wizard/help_html/figures \
  ${TMPDIR}/COPASI/CopasiUI.app/Contents/Resources/doc/html/

# copy the Qt Framework into the image
echo "Copying Frameworks:"
pushd ${TMPDIR}/COPASI
macdeployqt CopasiUI.app/ -no-plugins
popd

# add the readme to the image
echo "Copying readme file."
cp README_MAC.rtf ${TMPDIR}/COPASI/COPASI-README.rtf

# add the license to the image
echo "Copying license file."
cp ./copasi/ArtisticLicense.txt ${TMPDIR}/COPASI/LICENSE.txt

# set the bundles flag with SetFile
echo "Setting the bundle flag."
${SETFILE} -a b ${TMPDIR}/COPASI/CopasiUI.app

chown -R 99:99 ${TMPDIR}/COPASI

# this had been deferred earlier
chmod 444 ${TMPDIR}/COPASI/examples/*.*
chmod 777 ${TMPDIR}/COPASI/examples

# Unmount temporary image
sleep 10
hdiutil eject ${drive} || (sleep 10; hdiutil eject ${drive} -force)

[ -e Copasi-$build-$1.dmg ] && rm -rf Copasi-$build-$1.dmg
hdiutil convert -format UDCO Copasi-tmp.dmg -o Copasi-$build-$1.dmg
rm -rf Copasi-tmp.dmg
