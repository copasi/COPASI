[ -e $build-${PACKAGE} ] && rm -rf $build-${PACKAGE}
mkdir $build-${PACKAGE}
pushd $build-${PACKAGE}

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
cp ../README.$1 copasi/README
chmod 644 copasi/README

# Copy license
cp ../copasi/ArtisticLicense.txt copasi/LICENSE
chmod 644 copasi/LICENSE

# Copy executables and manifests 
cp ../copasi/CopasiUI/CopasiUI  copasi/bin
chmod 755 copasi/bin/CopasiUI

cp ../copasi/CopasiSE/CopasiSE  copasi/bin
chmod 755 copasi/bin/CopasiSE

# Copy configuration resources    
cp ../copasi/MIRIAM/MIRIAMResources.xml copasi/share/copasi/config
chmod 444 copasi/share/copasi/config/*

# Copy examples
cp ../TestSuite/distribution/* copasi/share/copasi/examples
chmod 444 copasi/share/copasi/examples/*
chmod 777 copasi/share/copasi/examples

# Copy icons
cp ../copasi/CopasiUI/icons/Copasi??-Alpha.xpm copasi/share/copasi/icons
cp ../copasi/CopasiUI/icons/CopasiDoc??-Alpha.xpm copasi/share/copasi/icons
chmod 644 copasi/share/copasi/icons/*

# Copy wizard resource
cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
chmod 644 copasi/share/copasi/doc/html/*.html

cp ../copasi/wizard/help_html/figures/*.png \
  copasi/share/copasi/doc/html/figures
chmod 644 copasi/share/copasi/doc/html/figures/*.png

tar -czf ../Copasi-$build-${PACKAGE}.tar.gz copasi

UPLOAD copasi/bin/CopasiSE \
  $license/Copasi-AllSE/${PACKAGE}/CopasiSE-$build

popd
