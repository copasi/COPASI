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
		$tick = $vertex/10;
	    last;
	  }
	}

    # read the original gepasi file and keep it all in memory
	open( GPSFILE, "$gfile" );
	@gpsfile = <GPSFILE>;
	close(GPSFILE);


    ########################################
    # HETEROZYGOUS STEADY STATE EXPERIMENT #
    ########################################
	$hssfile = $gfile;
	$hssfile =~ s/\.$GEPASIEXTENSION/\.hss\.$GEPASIEXTENSION/;
    # open the results file
	$resultsfile = $statfile;
	$resultsfile =~ s/\.$STATEXTENSION/\.hss.dat/;
	open( RESULTS, ">$resultsfile" );

    # one gene at a time, but start without changes
	for( $g=0; $g<=$vertex; $g++ )
	{
	  # write new files based on the original, with 
	  # 50% lower expression rate for each gene
	  open( HSSFILE, ">$hssfile" );
	  $r = 0;
      foreach $line (@gpsfile) 
	  {
	    if ($line =~ /^Report=1/) 
		{ 
		  print( HSSFILE "Report=0\n"); 
		  next;
		}
	    if ($line =~ /^ReportFile=(.+)\.([^.]*)\n/)
		{ 
		  print( HSSFILE "DynamicsFile=$1.hss.$2\n"); 
		  next; 
		}
	    if ($line =~ /^DynamicsFile=(.+)\.([^.]*)\n/)
		{ 
		  print( HSSFILE "DynamicsFile=$1.hss.$2\n"); 
		  next; 
		}
	    if ($line =~ /^SSFile=(.+)\.(.*)\n/) 
		{ 
		  $ssfile = "$1.hss.$2";
		  print( HSSFILE "SSFile=$ssfile\n");
		  next; 
		}
	    if ($line =~ /^Title=/) 
		{ 
		  print( HSSFILE "Title=$name heterozygous gene $g steady state experiment\n");
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
		    $rate = $1 / 2.0;
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
	    if( $wt[$i]>1.0E-6 ) 
		{ 
		  $val = $mt[$i] / $wt[$i];
		}
		else { $val = 0.0; }
		if( $i!=0 ) { print( REDRESULTS "\t"); }
		print( REDRESULTS "$val");
	  }
	  print( REDRESULTS "\n" );
	}
    close(RESULTS);
    close(REDRESULTS);

    #######################################
    # PERTURBATION TIME COURSE EXPERIMENT #
    #######################################
	$ptcfile = $gfile;
	$ptcfile =~ s/\.$GEPASIEXTENSION/\.ptc\.$GEPASIEXTENSION/;

    # one gene at a time, but start without changes
	#for( $g=0; $g<=$vertex; $g++ )
	#{
	  open( PTCFILE, ">$ptcfile" );
	  $r = 0;
      foreach $line (@gpsfile) 
	  {
	    if ($line =~ /^Report=1/) 
		{ 
		  print( PTCFILE "Report=0\n"); 
		  next;
		}
	    if ($line =~ /^ReportFile=(.+)\.([^.]*)\n/)
		{ 
		  print( PTCFILE "DynamicsFile=$1.ptc.$2\n"); 
		  next; 
		}
	    if ($line =~ /^DynamicsFile=(.+)\.([^.]*)\n/)
		{ 
		  print( PTCFILE "DynamicsFile=$1.ptc.$2\n"); 
		  next; 
		}
	    if ($line =~ /^SSFile=(.+)\.(.*)\n/) 
		{ 
		  $ssfile = "$1.ptc.$2";
		  print( PTCFILE "SSFile=$ssfile\n");
		  next; 
		}
	    if ($line =~ /^Title=/) 
		{ 
		  print( PTCFILE "Title=$name perturbation time course experiment\n");
		  next;
		}
        if ($line =~ /^Scan/)
	    {
		  # we're in the scan section
	      $r = 1;
	    }
		if( ( $r==1 ) && ( $line =~ /^Enabled=/ ) )
		{
		    print( PTCFILE "Enabled=1\n");
			# change $r so that we don't also change the degradation rate
			$r = 0;
			next;
		}
        print( PTCFILE $line );
	  }
	  close(PTCFILE);
	  # run Gepasi
	  system "$GEPASI $ptcfile";
      print ".";
#	}
    print "\n";
}