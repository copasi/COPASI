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
# graph layout program (force field)
$NEATO = "/usr/local/bin/neato";
# graph layout program (force field)
$DOT = "/usr/local/bin/dot";
# gnuplot
$GNUPLOT = "/usr/local/bin/gnuplot";
# Gepasi
$GEPASI = "/usr/local/bin/gepasi -r";
# converter to PBM format
$TOPBM = "/usr/local/bin/netpbm/pngtopnm";
# converter back to desired bitmap format
$FROMPBM = "/usr/local/bin/netpbm/pnmtopng";
# operations to carry out on image
$PBMOPS = "/usr/local/bin/netpbm/pnmcrop -verbose";

$counter = 0;
unlink( "layout.log" );

# processing
while( defined($gfile = <*.$GRAPHEXTENSION>) )
{
	$counter++;
    $gfile =~ s/\.$GRAPHEXTENSION//;
	print "$counter, $gfile ";

    system "layout.pl $gfile";
	system "agnindex.pl";
}

unlink("offset.txt");
unlink("temp.plt");
unlink("tmp.gvz");