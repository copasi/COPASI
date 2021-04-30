#!/usr/bin/env bash
# Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

echo ""
echo "COPASI %VERSION% Self Extracting Installer"
echo ""

show_help() {
    echo "Install COPASI %VERSION%"
    echo "  Usage: $(basename $0) [-t tmp_dir] [-i install_dir] [-d desktop_dir]"
    echo "Only extract COPASI %VERSION% to destination (default: $(pwd))"
    echo "  Usage: $(basename $0) -e [destination]"
}

prompt() {
    RESULT="$(echo $3 | sed -e 's?^~?'"${HOME}"'?')"
    while :
    do
        if [ _"${RESULT}" != _ ]; then
            [ -d "${RESULT}" ] || mkdir -p "${RESULT}"
            [ -d "${RESULT}" ] && [ -w "${RESULT}" ] && break
        fi
        
        read -e -i "$1" -p "$2: " RESULT
        RESULT="$(echo ${RESULT} | sed -e 's?^~?'"${HOME}"'?')"
    done

    echo RESULT: \"${RESULT}\"
}

EXTRACT_DIR=
TMP_DIR=
DESKTOP_DIR=
INSTALL_DIR=

shopt -s globstar

OPTIND=1

while getopts "het:d:i:" opt; do
    case "$opt" in
        h)
            show_help
            exit 0
            ;;
        e)
            shift
            EXTRACT_DIR="${@:-$(pwd)}"
            ;;
        t)
            TMP_DIR="$OPTARG"
            ;;
        d)
            DESKTOP_DIR="$OPTARG"
            ;;
        i)
            INSTALL_DIR="$OPTARG"
            ;;
    esac
done

shift $((OPTIND-1))

# Find where the archive starts
ARCHIVE=$(awk '/^__ARCHIVE_BELOW__/ {print NR + 1; exit 0; }' "$0")

# We have an extract directory and will only extract to it
if [ _"${EXTRACT_DIR}" != _ ]; then
    prompt "${EXTRACT_DIR}" "Extract directory: " "${EXTRACT_DIR}"
    EXTRACT_DIR="$(readlink -f ${RESULT})"
    
    echo tail -n+$ARCHIVE "$0" '| 'tar -xzv -C "${EXTRACT_DIR}"
    tail -n+$ARCHIVE "$0" | tar -xzv -C "${EXTRACT_DIR}"
    exit 0
fi

prompt "${TMP-${TEMP-/tmp}}" "Temp directory: " "${TMP_DIR}"
TMP_DIR="$(readlink -f ${RESULT})"

EXTRACT_DIR=$(mktemp -d "${TMP_DIR}"/copasi.XXXXXX)

echo tail -n+$ARCHIVE "$0" '| 'tar -xzv -C "${EXTRACT_DIR}"
tail -n+$ARCHIVE "$0" | tar -xzv -C "${EXTRACT_DIR}"

prompt "/opt/COPASI/%VERSION%" "Installation directory: " "${INSTALL_DIR}"
INSTALL_DIR="$(readlink -f ${RESULT})"

echo cp -r "${EXTRACT_DIR}"/%PACKAGE_NAME%/'*' "${INSTALL_DIR}"
cp -r "${EXTRACT_DIR}"/%PACKAGE_NAME%/* "${INSTALL_DIR}"

prompt "~/.local/share/applications" "Desktop file location: " "${DESKTOP_DIR}"
DESKTOP_DIR="$(readlink -f ${RESULT})"

echo "[Desktop Entry]
Encoding=UTF-8
Version=1.0
Exec=${INSTALL_DIR}/bin/CopasiUI %u
Icon=${INSTALL_DIR}/share/copasi/icons/Copasi48-Alpha.xpm
MimeType=application/xml;x-scheme-handler/copasi;application/x-copasi
Name=COPASI
NoDisplay=false
Type=Application
Categories=Science;Utility" '> '"${DESKTOP_DIR}"/COPASI.desktop

echo "[Desktop Entry]
Encoding=UTF-8
Version=1.0
Exec=${INSTALL_DIR}/bin/CopasiUI %u
Icon=${INSTALL_DIR}/share/copasi/icons/Copasi48-Alpha.xpm
MimeType=application/xml;x-scheme-handler/copasi;application/x-copasi
Name=COPASI
NoDisplay=false
Type=Application
Categories=Science;Utility" > "${DESKTOP_DIR}"/COPASI.desktop

xdg-settings set default-url-scheme-handler copasi COPASI.desktop

rm -rf "${EXTRACT_DIR}"

exit 0

__ARCHIVE_BELOW__
