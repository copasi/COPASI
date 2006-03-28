#!/bin/bash
pushd ../..

AdvancedInstallerPath="/cygdrive/c/Program Files/Caphyon/Advanced Installer"

if [ x"$#" = x1 ]; then
  major=`gawk -- '$2 ~ "VERSION_MAJOR" {print $3}' copasi/copasiversion.h`
  minor=`gawk -- '$2 ~ "VERSION_MINOR" {print $3}' copasi/copasiversion.h`
  build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' copasi/copasiversion.h`

  license=`gawk -- ' BEGIN {license = "US"} $0 ~ "USE_LICENSE=DE" {license = "DE"} END {print license} ' copasi/Makefile`

  case x"$1" in 
  xWIN32)
    productcode=${build}{$minor}${major}32DDC6BEE41C
    productcode=${productcode:0:12}

    productversion=${major}.${minor}.${build}

    [ -e setup ] && rm -rf setup
    mkdir setup
    cd setup

    mkdir copasi
    mkdir copasi/bin
    mkdir copasi/share
    mkdir copasi/share/copasi
    mkdir copasi/share/copasi/doc
    mkdir copasi/share/copasi/doc/html
    mkdir copasi/share/copasi/doc/html/figures
    mkdir copasi/share/copasi/examples
    mkdir copasi/share/copasi/icons
    chmod -R 755 copasi

    cp ../README.$1 copasi/README.txt
    chmod 644 copasi/README.txt

    cp ../COPASI_License_${license}.txt copasi/LICENSE.txt
    chmod 644 copasi/LICENSE.txt

    cp ../copasi/CopasiUI/CopasiUI.exe  copasi/bin
    chmod 755 copasi/bin/CopasiUI.exe

    cp ../copasi/CopasiSE/CopasiSE.exe  copasi/bin
    chmod 755 copasi/bin/CopasiSE.exe

    cp ../TestSuite/distribution/* copasi/share/copasi/examples
    chmod 444 copasi/share/copasi/examples/*

    cp ../copasi/CopasiUI/icons/Copasi.ico copasi/share/copasi/icons
    cp ../copasi/CopasiUI/icons/CopasiDoc.ico copasi/share/copasi/icons
    chmod 644 copasi/share/copasi/icons/*

    cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
    chmod 644 copasi/share/copasi/doc/html/*.html

    cp ../copasi/wizard/help_html/figures/*.jpg \
       copasi/share/copasi/doc/html/figures
    chmod 644 copasi/share/copasi/doc/html/figures/*.jpg

    cd ../admin

#   replace defaults with COPASI bitmaps
    mv -- \
      "$AdvancedInstallerPath/resources/default-banner.bmp" \
      "$AdvancedInstallerPath/resources/default-dialog.bmp" .
    cp -- \
       ../copasi/CopasiUI/icons/install_banner.bmp \
       "$AdvancedInstallerPath/resources/default-banner.bmp"
    cp -- \
       ../copasi/CopasiUI/icons/install_dialog.bmp \
       "$AdvancedInstallerPath/resources/default-dialog.bmp"

#   modify product code, product version, and package name
    sed -e '/ProductCode/s/[0-9A-F]*}/'$productcode'}/' \
        -e '/ProductVersion/s/Value=".*"/Value="'$productversion'"/' \
        -e '/PackageName/s/Copasi-.*-WIN32/Copasi-'$build'-'$1'/' \
        copasi.aip > tmp.aip

#   run Advanced Installer to create msi package
    "$AdvancedInstallerPath/AdvancedInstaller" /build tmp.aip
    rm tmp.aip

#   restore defaults
    mv -- \
      default-banner.bmp default-dialog.bmp \
      "$AdvancedInstallerPath/resources"

#   assure proper access rights
    chmod 644 ../Copasi-$build-$1.msi

    cd ..
    ;;

  xDarwin)
    if otool -L ./copasi/CopasiUI/CopasiUI.app/Contents/MacOS/CopasiUI \
      | grep libqt 2>&1 > /dev/null ;then
        echo ""
        echo "CopasiUI is dynamicall linked against Qt."
        echo "Please link the binary statically before making an image."
        echo ""
        exit 1
    fi
    
    SETFILE=/Developer/Tools/SetFile

# Create temporary package image drive
    hdiutil create Copasi-tmp.dmg -megabytes 400 -volname Copasi-$build-$1 -fs HFS+ \
      -layout NONE

# Mount temporary package image drive
    drive=`hdid Copasi-tmp.dmg | gawk -- '{print $1}'`
    TMPDIR=`df -l | gawk -- '$1 ~ "'$drive'" {print $6}'`
    echo $drive '->' $TMPDIR

    echo "Copying application bundle."
    mkdir ${TMPDIR}/copasi
    cp -r copasi/CopasiUI/CopasiUI.app ${TMPDIR}/copasi/

    strip ${TMPDIR}/copasi/CopasiUI.app/Contents/MacOS/CopasiUI

# copy the commandline version if it exists
    if [ -e copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE ] ; then    
      cp copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE ${TMPDIR}/copasi/
      strip ${TMPDIR}/copasi/CopasiSE
    fi  
    
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
    LINE=`grep -n "CFBundleIconFile" ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist \
      | cut -c1`
    LINE=$((LINE+1))
    sed -e "${LINE}s%<string>.*</string>%<string>copasi.icns</string>%" \
      ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist > ${TMPDIR}/tmp.plist
    mv ${TMPDIR}/tmp.plist ${TMPDIR}/copasi/CopasiUI.app/Contents/Info.plist

# copy the examples into the Resources directory
    echo "Make example directory."
    mkdir -p ${TMPDIR}/copasi/examples
    echo "Copy examples to example directory."
    cp ./TestSuite/distribution/* \
      ${TMPDIR}/copasi/examples/
# we have defer this to later so that we are able to chown
#    chmod 444 ${TMPDIR}/copasi/examples/

# copy the files for the wizard into the Resources directory
    echo "Making directory for wizard."
    mkdir -p ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html
    echo "Copying files for wizard."
    cp ./copasi/wizard/help_html/*.html \
      ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html/
    cp -r ./copasi/wizard/help_html/figures \
      ${TMPDIR}/copasi/CopasiUI.app/Contents/Resources/doc/html/
# add the readme to the image
    echo "Copying readme file."
    cp README_MAC.rtf ${TMPDIR}/copasi/COPASI-README.rtf

# add the license to the image
    echo "Copying license file."
    cp COPASI_License_${license}.txt ${TMPDIR}/copasi/COPASI-LICENSE.txt

# set the bundles flag with SetFile
    echo "Setting the bundle flag."
    ${SETFILE} -a b ${TMPDIR}/copasi/CopasiUI.app

    chown -R 99:99 ${TMPDIR}/copasi
# this had been deferred earlier
    chmod 444 ${TMPDIR}/copasi/examples/*.*

# Unmount temporary image
    hdiutil eject ${drive}

    hdiutil convert -format UDCO Copasi-tmp.dmg -o Copasi-$build-$1.dmg
    rm -rf Copasi-tmp.dmg
    ;;

  xLinux|xSunOS)
    [ -e $build-$1 ] && rm -rf $build-$1
    mkdir $build-$1
    cd $build-$1

    mkdir copasi
    mkdir copasi/bin
    mkdir copasi/share
    mkdir copasi/share/copasi
    mkdir copasi/share/copasi/doc
    mkdir copasi/share/copasi/doc/html
    mkdir copasi/share/copasi/doc/html/figures
    mkdir copasi/share/copasi/examples
    mkdir copasi/share/copasi/icons
    chmod -R 755 copasi

    cp ../README.$1 copasi/README
    chmod 644 copasi/README

    cp ../COPASI_License_${license}.txt copasi/LICENSE
    chmod 644 copasi/LICENSE

    cp ../copasi/CopasiUI/CopasiUI  copasi/bin
    chmod 755 copasi/bin/CopasiUI

    cp ../copasi/CopasiSE/CopasiSE  copasi/bin
    chmod 755 copasi/bin/CopasiSE

    cp ../TestSuite/distribution/* copasi/share/copasi/examples
    chmod 444 copasi/share/copasi/examples/*

    cp ../copasi/CopasiUI/icons/Copasi??-Alpha.xpm copasi/share/copasi/icons
    cp ../copasi/CopasiUI/icons/CopasiDoc??-Alpha.xpm copasi/share/copasi/icons
    chmod 644 copasi/share/copasi/icons/*

    cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
    chmod 644 copasi/share/copasi/doc/html/*.html

    cp ../copasi/wizard/help_html/figures/*.jpg \
       copasi/share/copasi/doc/html/figures
    chmod 644 copasi/share/copasi/doc/html/figures/*.jpg

    tar -czf ../Copasi-$build-$1.tar.gz copasi

    if [ x"$1" == "xLinux" ]; then
      cp ../copasi/CopasiUI/CopasiUI-dynamic  copasi/bin/CopasiUI
      cp ../copasi/CopasiSE/CopasiSE-dynamic  copasi/bin/CopasiSE
      chmod 755 copasi/bin/CopasiUI

      tar -czf ../Copasi-$build-$1-Dynamic.tar.gz copasi
    fi

    cd ..
    ;;
  esac

  scp Copasi-$build-$1*.* \
    calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/alpha-test/$1/$license

else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
