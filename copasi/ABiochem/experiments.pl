#! /usr/bin/perl -w
#
# Virginia Bioinformatics Institute, Virginia Tech
# Biochemical Networks Modeling Group
# 
# This module written by Pedro Mendes, September 2002
#
# A-Biochem
#
# experiments.pl 
# This module processes all the Gepasi files,
# carrying out simulations of several experiments
#

use POSIX;

# All configuration parameters here

# file extension for graph files
$GEPASIEXTENSION = "gps";
# gnuplot
#$GNUPLOT = "/usr/local/bin/gnuplot";
# Gepasi
$GEPASI = "/usr/local/bin/gepasi -r";

$counter = 0;
unlink( "layout.log" );

# processing
while( defined($gfile = <*.$GEPASIEXTENSION>) )
{
	$counter++;
	print "$counter, $gfile ";

	# read statistics first
	$statfile = $gfile;
	$statfile =~ s/\.$GEPASIEXTENSION/\.netstat/;
	open( STATFILE, "$statfile" );
	$vertex = 0;
	@stats = <STATFILE>;
	close(STATFILE);
    foreach $line (@stats) 
	{
      if ($line =~ /number of vertices\t([0-9]+)/)
	  {
	    $vertex = $1;
	    last;
	  }
	}

    # HETEROZYGOUS STEADY STATE EXPERIMENT
	$hssfile = $gfile;
	$hssfile =~ s/\.$GEPASIEXTENSION/\.hss\.$GEPASIEXTENSION/;
	# copy original Gepasi file
	system "cp $gfile $hssfile";

	open( HSSFILE, "$hssfile" );
    foreach $line (@stats) 
	{
      if ($line =~ /number of vertices\t([0-9]+)/)
	  {
	    $vertex = $1;
	    last;
	  }
	}

    for( $i=0; $i<$vertex; $i++ )
	{
	  # search for i'th reaction
	  $rname = "Equation= -> G$i";
	  while( <HSSFILE> )
	  {
	    if ( /Equation= -> G[0-9]+/ )
		{
		  # found the right reaction, now search the parameter
		}
	  }
	}
	close(HSSFILE);

exit;

	print ".";

	# run Gepasi
	$sfile = $gfile . ".gps";
#	$sfile =~ s/\.$GRAPHEXTENSION/\.gps/;
	system "$GEPASI $sfile";

	print ".\n";

	# cleanup the mess
}

