#! /usr/bin/perl -w
#
# Virginia Bioinformatics Institute, Virginia Tech
# Biochemical Networks Modeling Group
# 
# This module written by Pedro Mendes, September 2002
#
# A-Biochem
#
# index.pl 
# This module creates an index page for the 
# networks in the current directory
#

use POSIX;

$counter = 0;

$dirname="Dummy";

open( HTFILE, ">index.html" );
$strtime = localtime();
print( HTFILE "<html>\n<!-- Created by A-Biochem, $strtime -->\n");
print( HTFILE "<head>\n<style type=\"text/css\" media=\"all\">\@import \"nets.css\";</style>\n");
print( HTFILE "<title>$dirname data set - Artificial Gene Networks</title>\n</head>\n");
# write the HTML body
print( HTFILE "<body>\n");
print( HTFILE "<div id=\"topmenu\">\n<center>\n");
print( HTFILE "<a href=\"http://www.vbi.vt.edu/~mendes\">Biochemical Networks Modeling Group</a> |\n");
print( HTFILE "<a href=\"..\">Artificial Gene Networks Home</a>\n");
print( HTFILE "</center></div>\n");
print( HTFILE "<div id=\"main\">\n<center>\n");
print( HTFILE "<h1>Artificial Gene Network Data Set $dirname</h1>\n");
print( HTFILE "<h2>Statistics</h2>\n<table>\n");
while( defined($htmlfile = <*.html>) )
{
    if ($htmlfile eq "index.html") {next;}
	$counter++;
	$name = $htmlfile;
	$name =~ s/\.html//;
    print( HTFILE "<tr><td><a href=\"$htmlfile\">$name</a></td></tr>\n");
    print ".";
}
print( HTFILE "</table>\n");
print( HTFILE "</center>\n</div>\n");
print( HTFILE "</body>\n</html>");
close( HTFILE );
