#! /usr/bin/perl -w
#
# Virginia Bioinformatics Institute, Virginia Tech
# Biochemical Networks Modeling Group
# 
# This module written by Pedro Mendes, September 2002
#
# A-Biochem
#
# layout.pl 
# This module processes all the .dot files using the GraphViz package,
# all the gnuplot files, using gnuplot
#

use POSIX;

# All configuration parameters here

# file extension for graph files
$GRAPHEXTENSION = "dot";

$counter = 0;
unlink( "layout.log" );

# processing
while( defined($gfile = <*.$GRAPHEXTENSION>) )
{
	$counter++;
    $gfile =~ s/\.$GRAPHEXTENSION//;
	print "$counter, $gfile ";

    system "layout.pl $gfile";
}
system "agnindex.pl";

unlink("offset.txt");
unlink("temp.plt");
unlink("tmp.gvz");