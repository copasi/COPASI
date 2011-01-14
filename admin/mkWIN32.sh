INNO_SETUP=${COPASI_INNO_SETUP:-"/cygdrive/c/Program Files/Inno Setup 5/ISCC.exe"}
INNO_FILE=${COPASI_INNO_FILE:-"copasi.iss"}
DEPDIR=${COPASI_DEPDIR:-"~/environment/distribution"}

MT={COPASI_MT:-"yes"}

VisualStudioPath="/cygdrive/c/Program Files/Microsoft Visual Studio 8"

# Create the unique product code based on version and application name
GUID=`md5sum << EOF
#define MyAppName "COPASI"
#define MyAppVersion "${major}.${minor}.${build}"
#define MyAppPublisher "copasi.org"
#define MyAppURL "http://www.copasi.org/"
#define MyAppExeName "bin\CopasiUI.exe"
EOF` 
GUID=`echo $GUID | sed 'y/abcdef/ABCDEF/'`
productcode=${GUID:0:8}-${GUID:8:4}-${GUID:12:4}-${GUID:16:4}-${GUID:20:12}

[ -e setup ] && rm -rf setup
mkdir setup
pushd setup

# Create directory structure
mkdir copasi
mkdir copasi/bin
mkdir copasi/share
mkdir copasi/share/copasi
mkdir copasi/share/copasi/doc
mkdir copasi/share/copasi/doc/html
mkdir copasi/share/copasi/doc/html/figures
mkdir copasi/share/copasi/examples
mkdir copasi/share/copasi/icons
mkdir copasi/share/copasi/config
chmod -R 755 copasi

# Copy README
cp ../README.$1 copasi/README.txt
chmod 644 copasi/README.txt

# Copy license
cp ../copasi/ArtisticLicense.txt copasi/LICENSE.txt
chmod 644 copasi/LICENSE.txt

# Copy executables and manifests 
cp ../copasi/CopasiUI/release/CopasiUI.exe*  copasi/bin
cp ../copasi/CopasiSE/release/CopasiSE.exe  copasi/bin

# Include the manifest in CopasiUI.exe
if [ x"$MT" = xyes ]; then
  "$VisualStudioPath/VC/bin/mt.exe" -nologo -hashupdate -makecdfs \
      -manifest copasi\\bin\\CopasiUI.exe.manifest \
      -outputresource:copasi\\bin\\CopasiUI.exe\;1
fi

chmod 755 copasi/bin/CopasiUI.exe
chmod 755 copasi/bin/CopasiSE.exe

# Copy dependencies
cp ${DEPDIR}/* copasi/bin
    
if [ x"$license" = xUS ]; then
  UPLOAD copasi/bin/CopasiSE.exe \
    $license/Copasi-AllSE/${PACKAGE}/CopasiSE-$build.exe
fi

# Copy configuration resources    
cp ../copasi/MIRIAM/MIRIAMResources.xml copasi/share/copasi/config
chmod 444 copasi/share/copasi/config/*

# Copy examples
cp ../TestSuite/distribution/* copasi/share/copasi/examples
chmod 444 copasi/share/copasi/examples/*
chmod 777 copasi/share/copasi/examples

# Copy icons
cp ../copasi/CopasiUI/icons/Copasi.ico copasi/share/copasi/icons
cp ../copasi/CopasiUI/icons/CopasiDoc.ico copasi/share/copasi/icons
chmod 644 copasi/share/copasi/icons/*

# Copy wizard resource
cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
chmod 644 copasi/share/copasi/doc/html/*.html

cp ../copasi/wizard/help_html/figures/*.png \
    copasi/share/copasi/doc/html/figures
chmod 644 copasi/share/copasi/doc/html/figures/*.png

# 
cd ../InnoSetup

workdir=`cygpath -wa .`
workdir=${workdir//\\/\\\\}

#   modify product code, product version, and package name
sed -e '/#define MyAppVersion/s/".*"/"'${major}.${minor}.${build}'"/' \
    -e '/#define MyBuild/s/".*"/"'${build}'"/' \
    -e '/#define MyAppId/s/".*"/"{{'${productcode}'}"/' \
    -e '/#define MyWorkDir/s/".*"/"'${workdir}'"/' \
    ${INNO_FILE} > tmp.iss

# Run Inno Setup to create package
"${INNO_SETUP}" tmp.iss
rm tmp.iss

# Move the package to its final location
mv Copasi-$build-${PACKAGE}.exe ..
chmod 755 ../Copasi-$build-${PACKAGE}.exe

popd
