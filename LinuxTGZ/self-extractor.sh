#!/usr/bin/env bash
# Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 


echo ""
echo "COPASI %VERSION% Self Extracting Installer"
echo ""

# Find where the archive starts
ARCHIVE=$(awk '/^__ARCHIVE_BELOW__/ {print NR + 1; exit 0; }' "$0")

show_help() {
    echo "Install COPASI %VERSION%"
    echo "  Usage: $(basename $0) [-t tmp_dir] [-i install_dir] [-d desktop_dir]"
    echo "Only extract COPASI %VERSION% to destination (default: $(pwd))"
    echo "  Usage: $(basename $0) -e [destination]"
}

extract_only() {
} 

shopt -s globstar

OPTIND=1

while getopts "het:d:i:" opt; do
    case "$opt" in
        h)
            show_help
            exit 0
            ;;
        e)
            EXTRACT_DIR="$(pwd)"
            ;;
        t)
            TMP_DIR=$OPTARG
            ;;
        d)
            DESKTOP_DIR=$OPTARG
            ;;
        i)
            INSTALL_DIR=$OPTARG
            ;;
    esac
done

# We have an extract directory and will only extract to it
if [ -Z ${EXTRACT_DIR} ]; then
    # Check if the user specified a destination and use it
    [ -Z "$@" ] && EXTRACT_DIR="$@"

    tail -n+$ARCHIVE "$0" | tar -xv -C "${EXTRACT_DIR}"
    exit 0
fi

[ -Z "${TMP_DIR}"] || read -p "Temp directory: " -i "${TMP-:${TEMP-:/tmp}}" TMP_DIR

EXTRACT_DIR=$(mktemp -d "${TMP_DIR}"/copasi.XXXXXX)
tail -n+$ARCHIVE "$0" | tar -xv -C "${EXTRACT_DIR}"

[ -Z "${INSTALL_DIR}"] || read -p "Installation directory: " -i "/opt/COPASI/%VERSION%" INSTALL_DIR

mkdir --parent "${INSTALL_DIR}"
mv "${EXTRACT_DIR}"/%PACKAGE_NAME%/* "${INSTALL_DIR}"

[ -Z "${DESKTOP_DIR}"] || read -p "Desktop file location: " -i "~/.local/share/applications/" DESKTOP_DIR

echo "[Desktop Entry]
Encoding=UTF-8
Version=1.0
Exec=${INSTALL_DIR}/bin/CopasiUI %u
Icon=${INSTALL_DIR}/share/copasi/icons/Copasi48-Alpha.xpm
MimeType=application/xml;x-scheme-handler/copasi;application/x-copasi
Name=COPASI
NoDisplay=false
Type=Application
Categories=Science;Utility" > "${DESKTOP_DIR}"/COPASI.dektop

xdg-settings set default-url-scheme-handler copasi COPASI.desktop

rm -rf "${EXTRACT_DIR}"

exit 0

__ARCHIVE_BELOW__
