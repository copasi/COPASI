#! /usr/bin/perl -w
#
# Virginia Bioinformatics Institute, Virginia Tech
# Biochemical Networks Modeling Group
# 
# This module written by Pedro Mendes, September 2002
#
# A-Biochem
#
# nullmutants.pl 
# This module processes all the Gepasi files,
# carrying out simulations of null mutant experiments
#

use POSIX;

# All configuration parameters here

# low value to be considered zero
$EPSILON = 1e-50;
$DBL_MAX = 1e+308;
# file extension for graph files
$GEPASIEXTENSION = "gps";
# file extension for stats files
$STATEXTENSION = "netstat";
# gnuplot
#$GNUPLOT = "/usr/local/bin/gnuplot";
# Gepasi
$GEPASI = "/usr/local/bin/gepasi -r";

$counter = 0;

# processing
while( defined($statfile = <*.$STATEXTENSION>) )
{
	$counter++;
	$name = $statfile;
	$name =~ s/\.$STATEXTENSION//;
	# Gepasi filename
	$gfile = "$name.$GEPASIEXTENSION";
	print "$counter, $gfile ";

	open( STATFILE, "$statfile" );
	$vertex = 0;
	@stats = <STATFILE>;
	close(STATFILE);
    foreach $line (@stats) 
	{
      if ($line =~ /number of vertices\t([0-9]+)/)
	  {
	    $vertex = $1;
		if($vertex>10) {$tick = $vertex % 10};
		else {$tick = 1;}
	    last;
	  }
	}

    # read the original gepasi file and keep it all in memory
	open( GPSFILE, "$gfile" );
	@gpsfile = <GPSFILE>;
	close(GPSFILE);


    ########################################
    # NULL MUTANTS STEADY STATE EXPERIMENT #
    ########################################
	$hssfile = $gfile;
	$hssfile =~ s/\.$GEPASIEXTENSION/\.nmss\.$GEPASIEXTENSION/;
    # open the results file
	$resultsfile = $statfile;
	$resultsfile =~ s/\.$STATEXTENSION/\.nmss.dat/;
	open( RESULTS, ">$resultsfile" );

    # one gene at a time, but start without changes
	for( $g=0; $g<=$vertex; $g++ )
	{
	  # write new files based on the original, with 
	  # no expression rate for each gene and no
	  # initial concentration of that gene
	  open( HSSFILE, ">$hssfile" );
	  $r = 0; $m=0; $t=0;
      foreach $line (@gpsfile) 
	  {
	    if ($line =~ /^Report=1/) 
		{ 
		  print( HSSFILE "Report=0\n"); 
		  next;
		}
	    if ($line =~ /^ReportFile=(.+)\.([^.]*)\n/)
		{ 
		  print( HSSFILE "DynamicsFile=$1.nmss.$2\n"); 
		  next; 
		}
	    if ($line =~ /^DynamicsFile=(.+)\.([^.]*)\n/)
		{ 
		  print( HSSFILE "DynamicsFile=$1.nmss.$2\n"); 
		  next; 
		}
	    if ($line =~ /^SSFile=(.+)\.(.*)\n/) 
		{ 
		  $ssfile = "$1.nmss.$2";
		  print( HSSFILE "SSFile=$ssfile\n");
		  next; 
		}
	    if ( ($t==0) && ($line =~ /^Title=/) )
		{ 
		  print( HSSFILE "Title=$name G$g null mutant steady state experiment\n");
		  $t = 1;
		  next;
		}
        if ($line =~ /Metabolite=G([0-9]+)/)
	    {
		  # we're in the correct metabolite
	      $m = $1;
	    }
		if( ( $m==$g ) && ( $line =~ /Concentration=([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?)/ ) )
		{
		    # this is the initial concentration
		    $conc = 0.0;
		    print( HSSFILE "Concentration=$conc\n");
			# change $m so that we don't also change the degradation rate
			$m = 0;
			next;
		}
        if ($line =~ /Equation= -> G([0-9]+)/)
	    {
		  # we're in the correct reaction
	      $r = $1;
	    }
		if( ( $r==$g ) && ( $line =~ /Param0=([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?)/ ) )
		{
		    # this is the basal rate of transcription
		    $rate = 0.0;
		    print( HSSFILE "Param0=$rate\n");
			# change $r so that we don't also change the degradation rate
			$r = 0;
		}
		else { print( HSSFILE $line ); }
	  }
	  close(HSSFILE);
	  # run Gepasi
	  system "$GEPASI $hssfile";
	  # and append the ss results to the result file
	  open( SSFILE, "$ssfile" );
	  while( <SSFILE> )
	  { print( RESULTS $_ ); }
	  close(SSFILE);
	  if( $g % ($tick) == 0 ) { print "."; } 
	}
    close(RESULTS);
	open( RESULTS, "$resultsfile" );
	$rrfile = "$resultsfile.xls";
	open( REDRESULTS, ">$rrfile" );
	# read first line
	$line = <RESULTS>;
	@wt = split(/\t/,$line);
	# calculate relative values, using first line
	for( $g=0; $g<$vertex; $g++ )
	{
	  $line = <RESULTS>;
	  @mt = split(/\t/, $line);
	  for( $i=0; $i<$vertex; $i++ )
	  {
	    if( $wt[$i]>$EPSILON ) 
		{ 
		  $val = $mt[$i] / $wt[$i];
		}
		else { $val = $DBL_MAX; }
		if( $i!=0 ) { print( REDRESULTS "\t"); }
		print( REDRESULTS "$val");
	  }
	  print( REDRESULTS "\n" );
	}
    close(RESULTS);
    close(REDRESULTS);

    print "\n";
}
