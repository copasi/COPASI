#! /bin/sh
#
# cvs.sh
#
# This file contains support code from Makefile.common
# It defines a shell function for each known target
# and then does a case to call the correct function.

call_and_fix_autoconf()
{
  $AUTOCONF || exit 1
  if test -r configure.in.in ; then
    perl -pi -e "print \"if test \\\"x\\\$with_fast_perl\\\" = \\\"xyes\\\"; then\
    \\n  perl -i.bak \\\$ac_aux_dir/conf.change.pl \\\$CONFIG_STATUS\
    \\\\\\n    || mv \\\$CONFIG_STATUS.bak \\\$CONFIG_STATUS\
    \\n  rm -f \\\$CONFIG_STATUS.bak\\nfi\
    \\n\" if /^\\s*chmod\\s+.*\\+x\\s+.*CONFIG_STATUS/;" configure
  fi
}

cvs()
{

AUTOCONF_VERSION=`$AUTOCONF --version | head -1`
case "$AUTOCONF_VERSION" in
  Autoconf*2.5* | autoconf*2.5* ) : ;;
  "" )
    echo "*** AUTOCONF NOT FOUND!."
    echo "*** KDE requires autoconf 2.52 or 2.53"
    exit 1
    ;;
  * )
    echo "*** YOU'RE USING $AUTOCONF_VERSION."
    echo "*** KDE requires autoconf 2.52 or 2.53"
    exit 1
    ;;
esac
 
AUTOHEADER_VERSION=`$AUTOHEADER --version | head -1`
case "$AUTOHEADER_VERSION" in
  Autoconf*2.5* | autoheader*2.5* ) : ;;
  "" )
    echo "*** AUTOHEADER NOT FOUND!."
    echo "*** KDE requires autoheader 2.52 or 2.53 (part of autoconf)"
    exit 1
    ;;
  * )
    echo "*** YOU'RE USING $AUTOHEADER_VERSION."
    echo "*** KDE requires autoheader 2.52 or 2.53 (part of autoconf)"
    exit 1
    ;;
esac

AUTOMAKE_STRING=`$AUTOMAKE --version | head -1`
case "$AUTOMAKE_STRING" in
  automake*1.5d* )
    echo "*** YOU'RE USING $AUTOMAKE_STRING."
    echo "*** KDE requires automake 1.5"
    exit 1
    ;;
  automake*1.5* | automake*1.5-* ) : ;;
  "" )
    echo "*** AUTOMAKE NOT FOUND!."
    echo "*** KDE requires automake 1.5"
    exit 1
    ;;
  unsermake* ) :
    echo "*** YOU'RE USING UNSERMAKE."
    echo "*** GOOD LUCK!! :)"
    ;;
  * )
    echo "*** YOU'RE USING $AUTOMAKE_STRING."
    echo "*** KDE requires automake 1.5"
    exit 1
    ;;
esac
 
### Produce acinclude.m4
if grep '$(top_srcdir)/acinclude.m4:' $makefile_am >/dev/null; then
  echo "*** Creating acinclude.m4"
  rm -f acinclude.m4 configure.files
  $MAKE -f $makefile_am top_srcdir=. ./acinclude.m4
fi

echo "!!! If you get recursion errors from autoconf, it is advisable to set the"
echo "    environment variable M4 to something including \"--nesting-limit=500\""

### Make new subdirs and configure.in.
### The make calls could be optimized away here,
### with a little thought.
if test -r configure.in.in; then
  rm -f subdirs configure.in
  echo "*** Creating list of subdirectories"
  $MAKE -f $makefile_am top_srcdir=. ./subdirs || exit 1
  echo "*** Creating configure.in"
  $MAKE -f $makefile_am top_srcdir=. ./configure.in || exit 1
fi

echo "*** Creating aclocal.m4"
$ACLOCAL || exit 1
echo "*** Creating configure"
call_and_fix_autoconf

if egrep "^AM_CONFIG_HEADER" configure.in >/dev/null 2>&1; then
  echo "*** Creating config.h template"
  $AUTOHEADER || exit 1
fi

echo "*** Creating Makefile templates"
$AUTOMAKE || exit 1
if test -z "$UNSERMAKE"; then
  echo "*** Postprocessing Makefile templates"
  perl admin/am_edit || exit 1
fi

if egrep "^cvs-local:" $makefile_am >/dev/null; then \
  $MAKE -f $makefile_am cvs-local || exit 1
fi

echo "*** Creating date/time stamp"
touch stamp-h.in

echo "*** Finished"
echo "    Don't forget to run ./configure"
echo "    If you haven't done so in a while, run ./configure --help"
}

dist()
{
###
### First build all of the files necessary to do just "make"
###
if grep -e '$(top_srcdir)/acinclude.m4:' $makefile_am >/dev/null; then
  $MAKE -f $makefile_am top_srcdir=. ./acinclude.m4
fi
if test -r configure.in.in; then
  $MAKE -f $makefile_am top_srcdir=. ./subdirs ./configure.in
fi
aclocal
$AUTOHEADER
$AUTOMAKE --foreign --include-deps
perl admin/am_edit
call_and_fix_autoconf
touch stamp-h.in
if grep -e "^cvs-local:" $makefile_am >/dev/null; then
  $MAKE -f $makefile_am cvs-local
fi

###
### Then make messages
###
if test -d po; then
 LIST=`find ./po -name "*.po"`
 for i in $LIST; do
  file2=`echo $i | sed -e "s#\.po#\.gmo#"`
  msgfmt -o $file2 $i || touch $file2
 done
fi
if grep -e "^cvs-dist-local:" $makefile_am >/dev/null; then
  $MAKE -f $makefile_am cvs-dist-local
fi
}

configure_in()
{
rm -f configure.in configure.in.new
kde_use_qt_param=
test -f configure.files || { echo "need configure.files for configure.in"; exit 1; }
cat `cat configure.files | egrep -v "^configure.in.bot"` > configure.in.new
echo "KDE_CREATE_SUBDIRSLIST" >> configure.in.new
if test -f Makefile.am.in; then
  subdirs=`cat subdirs`
  for dir in $subdirs; do
    dir=`echo $dir | sed -e "s,[-+],_,g"`
    echo "AM_CONDITIONAL($dir""_SUBDIR_included, test \"x\$$dir""_SUBDIR_included\" = xyes)" >> configure.in.new
  done
fi
# echo "AC_OUTPUT( \\" >> configure.in.new
mfs=`find . -type d -print | fgrep -v "/." | \
     sed -e "s#\./##" -e "/^debian/d" | sort`
for i in $mfs; do
  topleveldir=`echo $i| sed -e "s#/.*##"`
  if test -f $topleveldir/configure.in; then
	continue
  fi
  if test ! -f $i/Makefile.am; then
	continue
  fi
  if test -s inst-apps; then
    if grep \"^$topleveldir\" inst-apps > /dev/null 2>&1; then
	continue
    fi
  fi
  echo "AC_CONFIG_FILES([ $i/Makefile ])" >> configure.in.new
  if test -n "$UNSERMAKE"; then
    echo "AC_CONFIG_FILES([ $i/Makefile.rules ])" >> configure.in.new
  fi
done
egrep '^dnl AC_OUTPUT\(.*\)' `cat configure.files` | sed -e "s#^.*dnl AC_OUTPUT(\(.*\))#AC_CONFIG_FILES([ \1 ])#" >> configure.in.new
if test -n "$UNSERMAKE"; then
  echo "AC_CONFIG_FILES([ MakeVars ])" >> configure.in.new
fi
echo "AC_OUTPUT" >> configure.in.new
modulename=
if test -f configure.in.in; then
   if head -2 configure.in.in | egrep "^#MIN_CONFIG\(.*\)$" > /dev/null; then
      kde_use_qt_param=`cat configure.in.in | sed -n -e "s/#MIN_CONFIG(\(.*\))/\1/p"`
   fi
   if head -2 configure.in.in | egrep "^#MIN_CONFIG" > /dev/null; then
      line=`egrep "^AM_INIT_AUTOMAKE\(" configure.in.in`
      if test -n "$line"; then
	  modulename=`echo $line | sed -e "s#AM_INIT_AUTOMAKE(\([^,]*\),.*#\1#"`
	  VERSION=`echo $line | sed -e "s#AM_INIT_AUTOMAKE([^,]*, *\([^)]*\)).*#\1#"`
      fi
      sed -e "s#AM_INIT_AUTOMAKE([^@].*#dnl PACKAGE set before#" \
          configure.in.new > configure.in && mv configure.in configure.in.new
   fi
fi
if test -z "$modulename" || test "$modulename" = "@MODULENAME@"; then
   modulename=`pwd`; modulename=`basename $modulename`
fi
if test -z "$VERSION" || test "$VERSION" = "@VERSION@"; then
     VERSION="\"3.0\""
fi
if test -n "$kde_use_qt_param"; then
      sed -e "s#^dnl KDE_USE_QT#KDE_USE_QT($kde_use_qt_param)#" \
      	configure.in.new > configure.in && mv configure.in configure.in.new
fi
sed -e "s#@MODULENAME@#$modulename#" configure.in.new |
	sed -e "s#@VERSION@#$VERSION#" > configure.in
if test -f configure.in.bot ; then cat configure.in.bot >> configure.in ; fi
rm -f configure.in.new
}

configure_files()
{
admindir=NO
for i in . .. ../.. ../../..; do
  if test -x $i/admin; then admindir=$i/admin; break; fi
done
rm -f configure.files
touch configure.files
if test -f configure.in.in && head -2 configure.in.in | egrep "^#MIN_CONFIG" > /dev/null; then
	echo $admindir/configure.in.min >> configure.files
fi
test -f configure.in.in && echo configure.in.in >> configure.files
list=`find . -name "configure.in.in" | sort`
for i in $list; do if test -f $i && test ! `dirname $i` = "." ; then
  echo $i >> configure.files
fi; done
test -f configure.in.mid && echo configure.in.mid >> configure.files
test -f configure.in.bot && echo configure.in.bot >> configure.files
}

subdirs()
{
files=`ls -1 | sort`
dirs=
compilefirst=`grep '^COMPILE_FIRST[ ]*=' $makefile_am |
	  sed -e 's#^COMPILE_FIRST[ ]*=[ ]*#|#' | sed -e 's#$#|#' | sed -e 's# #|#g'`
compilelast=`grep '^COMPILE_LAST[ ]*=' $makefile_am |
	 sed -e 's#^COMPILE_LAST[ ]*=[ ]*#|#' | sed -e 's#$#|#' | sed -e 's# #|#g'`
for i in $files; do if test -d $i; then
    if test -f $i/Makefile.am; then
	if echo $compilefirst | grep "|$i|" >/dev/null; then
		:
	elif echo $compilelast | grep "|$i|" >/dev/null; then
		:
	else dirs="$dirs $i"
	fi
     fi
   fi
done
rm -f _SUBDIRS
for i in $dirs; do
echo $i >> ./_SUBDIRS
done
if test -f Makefile.am.in; then
  cp Makefile.am.in Makefile.am
  topsubdirs=
  if test -n "$compilefirst"; then
     topsubdirs='$(COMPILE_FIRST)'
  fi
  for i in $dirs; do
     vari=`echo $i | sed -e "s,[-+],_,g"`
     echo "if $vari""_SUBDIR_included" >> Makefile.am
     echo "$vari""_SUBDIR=$i" >> Makefile.am
     echo "endif" >> Makefile.am
     topsubdirs="$topsubdirs \$($vari""_SUBDIR)"
  done
  if test -n "$compilelast"; then
     topsubdirs="$topsubdirs "'$(COMPILE_LAST)'
  fi
  echo "SUBDIRS=$topsubdirs" >> Makefile.am
fi
if test -r subdirs && diff subdirs _SUBDIRS > /dev/null; then
  rm -f _SUBDIRS
fi
test -r _SUBDIRS && mv _SUBDIRS subdirs || true
}

cvs_clean()
{
if test ! -d CVS; then
  echo "You don't have a toplevel CVS directory."
  echo "You most certainly didn't use cvs to get these sources."
  echo "But this function depends on cvs's information."
  exit 1
fi
perl $admindir/cvs-clean.pl
}

package_merge()
{
catalogs=$POFILES
for cat in $catalogs; do
  msgmerge -o $cat.new $cat $PACKAGE.pot
  if test -s $cat.new; then
    grep -v "\"POT-Creation" $cat.new > $cat.new.2
    grep -v "\"POT-Creation" $cat >> $cat.new.1
    if diff $cat.new.1 $cat.new.2; then
	rm $cat.new
    else
	mv $cat.new $cat
    fi
    rm -f $cat.new.1 $cat.new.2
  fi
done
}

package_messages()
{
rm -rf po.backup
mkdir po.backup

for i in `ls -1 po/*.pot 2>/dev/null | sed -e "s#po/##"`; do
  egrep -v '^#([^:]|$)' po/$i | egrep '^.*[^ ]+.*$' | grep -v "\"POT-Creation" > po.backup/$i
  cp po/$i po.backup/backup_$i
  touch -r po/$i po.backup/backup_$i
  rm po/$i
done

podir=${podir:-$PWD/po}
files=`find . -name Makefile.am | xargs egrep -l '^messages:' `
dirs=`for i in $files; do echo \`dirname $i\`; done`
tmpname="$PWD/messages.log"
if test -z "$EXTRACTRC"; then EXTRACTRC=extractrc ; fi
if test -z "$PREPARETIPS"; then PREPARETIPS=preparetips ; fi
export EXTRACTRC PREPARETIPS

for subdir in $dirs; do
  test -z "$VERBOSE" || echo "Making messages in $subdir"
  (cd $subdir
   if test -n "`grep -e '^messages:.*rc.cpp' Makefile.am`"; then
	$EXTRACTRC *.rc *.ui > rc.cpp
   else
	candidates=`ls -1 *.rc *.ui 2>/dev/null`
	if test -n "$candidates"; then
	    echo "$subdir has *.rc or *.ui files, but not correct messages line"
	fi
   fi
   if test -n "`grep -r KAboutData *.c* *.C* 2>/dev/null`"; then
	echo -e 'i18n("_: NAME OF TRANSLATORS\\n"\n"Your names")\ni18n("_: EMAIL OF TRANSLATORS\\n"\n"Your emails")' > _translatorinfo.cpp
   else echo " " > _translatorinfo.cpp
   fi
   perl -e '$mes=0; while (<STDIN>) { if (/^messages:/) { $mes=1; print $_; next; } if ($mes) { if (/$\\(XGETTEXT\)/ && / -o/) { s/ -o \$\(podir\)/ _translatorinfo.cpp -o \$\(podir\)/ } print $_; } else { print $_; } }' < Makefile.am > _transMakefile

   $MAKE -s -f _transMakefile podir=$podir EXTRACTRC="$EXTRACTRC" PREPARETIPS="$PREPARETIPS" \
	XGETTEXT="${XGETTEXT:-xgettext} -C -ki18n -ktr2i18n -kI18N_NOOP -ktranslate -kaliasLocale -x ${includedir:-$KDEDIR/include}/kde.pot" \
	messages 
   ) 2>&1 | grep -v '^make\[1\]' > $tmpname
   test -s $tmpname && { echo $subdir ; cat "$tmpname"; }
   test ! -f $subdir/rc.cpp || rm -f $subdir/rc.cpp
   rm -f $subdir/_translatorinfo.cpp
   rm -f $subdir/_transMakefile
done
rm -f $tmpname
for i in `ls -1 po.backup/*.pot 2>/dev/null | sed -e "s#po.backup/##" | egrep -v '^backup_'`; do
  if test ! -f po/$i; then echo "disappeared: $i"; fi
done
for i in `ls -1 po/*.pot 2>/dev/null | sed -e "s#po/##"`; do
   msgmerge -q -o po/$i po/$i po/$i
   egrep -v '^#([^:]|$)' po/$i | egrep '^.*[^ ]+.*$' | grep -v "\"POT-Creation" > temp.pot
  if test -f po.backup/$i && test -n "`diff temp.pot po.backup/$i`"; then
	echo "will update $i"
	msgmerge -q po.backup/backup_$i po/$i > temp.pot
	mv temp.pot po/$i
  else
    if test -f po.backup/backup_$i; then
      test -z "$VERBOSE" || echo "I'm restoring $i"
      mv po.backup/backup_$i po/$i
      rm po.backup/$i
    else
      echo "will add $i"
    fi
  fi
done
rm -f temp.pot
rm -rf po.backup
}

admindir=`echo "$0" | sed 's%[\\/][^\\/][^\\/]*$%%'`
test "x$admindir" = "x$0" && admindir=.

test "x$MAKE" = x && MAKE=make
makefile_am=Makefile.am
if test -f Makefile.am.in; then
  makefile_am=Makefile.am.in
fi

### KEEP IN SYNC WITH "missing"!!
### Handle special autoconf cases first.
autoconf_2_53=`type -p autoconf-2.53`
autoconf_2_52=`type -p autoconf-2.52`
autoconf_2_50=`type -p autoconf2.50`
if test -x "$autoconf_2_53" ; then
   AUTOCONF="$autoconf_2_53"
elif test -x "$autoconf_2_52" ; then
   AUTOCONF="$autoconf_2_52"
elif test -x "$autoconf_2_50" ; then
   AUTOCONF="$autoconf_2_50"
else
   AUTOCONF="autoconf"
fi
export AUTOCONF

autoheader_2_53=`type -p autoheader-2.53`
autom4te_2_53=`type -p autom4te-2.53`
autoheader_2_52=`type -p autoheader-2.52`
autoheader_2_50=`type -p autoheader2.50`
if test -x "$autoheader_2_53" ; then
   AUTOHEADER="$autoheader_2_53"
   AUTOM4TE="$autom4te_2_53"
elif test -x "$autoheader_2_52" ; then
   AUTOHEADER="$autoheader_2_52"
elif test -x "$autoheader_2_50" ; then
   AUTOHEADER="$autoheader_2_50"
else
   AUTOHEADER="autoheader"
   AUTOM4TE="autom4te"
fi
export AUTOM4TE
export AUTOHEADER

automake_1_5=`type -p automake-1.5`
aclocal_1_5=`type -p aclocal-1.5`
if test -z "$UNSERMAKE"; then
  if test -x "$automake_1_5" ; then
     AUTOMAKE="$automake_1_5"
     ACLOCAL="$aclocal_1_5"
  else
     AUTOMAKE="automake"
     ACLOCAL="aclocal"
  fi
else
     AUTOMAKE="$UNSERMAKE"
     ACLOCAL="aclocal"
fi

export AUTOMAKE
export ACLOCAL

###
### Main
###

arg=`echo $1 | tr '\-.' __`
case "$arg" in
  cvs | dist | configure_in | configure_files | subdirs | \
  cvs_clean | package_merge | package_messages ) $arg ;;
  * ) echo "Usage: cvs.sh <target>"
      echo "Target can be one of:"
      echo "    cvs cvs-clean dist"
      echo "    configure.in configure.files"
      echo "    package-merge package-messages"
      echo ""
      echo "Usage: anything but $1"
      exit 1 ;;
esac
exit 0
