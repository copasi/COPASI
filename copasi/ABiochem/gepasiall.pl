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
# Gepasi
$GEPASI = "/usr/local/bin/gepasi -r";

$counter = 0;
# processing
while( defined($gfile = <*.$GRAPHEXTENSION>) )
{
    if( $gfile != 'template.gps' )
	{
 	 $counter++;
     $gfile =~ s/\.$GRAPHEXTENSION//;
	 print "$counter, $gfile ";

	 # run Gepasi
	 $sfile = $gfile . ".gps";
	 system "$GEPASI $sfile";
	}

	print ".\n";
}
