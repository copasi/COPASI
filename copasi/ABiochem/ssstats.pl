#! /usr/bin/perl -w
#
# Virginia Bioinformatics Institute, Virginia Tech
# Biochemical Networks Modeling Group
# 
# This module written by Pedro Mendes, May 2003
#
# A-Biochem
#
# ssstats.pl 
# This module calculates statistics about the steady state
# of all Gepasi generated files in the current directoryu
#

use POSIX;

# All configuration parameters here

# low value to be considered zero
$EPSILON = 1e-3;
$DBL_MAX = 1e+308;
# file extension for graph files
$GEPASIEXTENSION = "gps";
# file extension for stats files
$STATEXTENSION = "netstat";
# gnuplot
$GNUPLOT = "/usr/local/bin/gnuplot";

$counter = 0;
$totfin = 0;

    for( $j=0; $j<10; $j++ )
	{
	  $hist[$j]=0;
	}

# processing
while( defined($statfile = <*.$STATEXTENSION>) )
{
	$counter++;
	$name = $statfile;
	$name =~ s/\.$STATEXTENSION//;
	# Gepasi filename
	$gfile = "$name.$GEPASIEXTENSION";

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

    # read the original gepasi file and keep it all in memory
	open( GPSFILE, "$gfile" );
	@gpsfile = <GPSFILE>;
	close(GPSFILE);

    foreach $line (@gpsfile) 
	{
	  if ($line =~ /^SSFile=(.*)/) 
	  { 
		 $ssfile = $1; 
	     print "$counter\t$ssfile";
	     open( SS, "$ssfile" );
         $line = <SS>;
	     @level = sort {$b <=> $a} split(' ',$line);
		 $finite = $vertex;
		 for( $i=0; $i<$vertex; $i++ )
		 {
		   if( $level[$i] < $EPSILON )
		   {
		     $finite = $i;
			 last;
		   }
		 }
		 $finperc = $finite / $vertex;
         print "\t$vertex\t$finite\t$finperc";
		 $totfin += $finite;
		 if ($finperc<0.1) {$hist[0]++;}
		 else
		 {
		  if ($finperc<0.2) {$hist[1]++;}
		  else
		  {
		    if ($finperc<0.3) {$hist[2]++;}
			else
			{
		      if ($finperc<0.4) {$hist[3]++;}
			  else
			  {
		        if ($finperc<0.5) {$hist[4]++;}
				else
				{
		          if ($finperc<0.6) {$hist[5]++;}
				  else
				  {
		            if ($finperc<0.7) {$hist[6]++;}
					else
					{
		              if ($finperc<0.8) {$hist[7]++;}
					  else
					  {
		                if ($finperc<0.9) {$hist[8]++;}
						else {$hist[9]++;}
					  }
					}
				  }
				}
			  }
			}
		  }
		 }
	     close(SS);
		 last;
	  }
	}

    print "\n";
}
$avg = $totfin / $counter;
$finperc = $avg / $vertex;
print "0\taverage\t$vertex\t$avg\t$finperc\n";
open( GPFILE, ">temp.plt" );
print( GPFILE "set terminal png small color\n");
print( GPFILE "set size 0.6,0.6\n");
print( GPFILE "set data style histeps\n");
print( GPFILE "set nologscale\n");
print( GPFILE "set nokey\n");
print( GPFILE "set output \'ss-histogram.png\'\n");
print( GPFILE "set title \'distribution of finite expression levels\'\n");
print( GPFILE "set xlabel \'proportion of finite gene expression levels\'\n");
print( GPFILE "set ylabel \'# networks\'\n");
print( GPFILE "set xrange [0.05:1.05]\n");
print( GPFILE "set yrange [0:$vertex]\n");
print( GPFILE "plot \'-\'\n");
print( GPFILE "0.1\t$hist[0]\n");
print( GPFILE "0.2\t$hist[1]\n");
print( GPFILE "0.3\t$hist[2]\n");
print( GPFILE "0.4\t$hist[3]\n");
print( GPFILE "0.5\t$hist[4]\n");
print( GPFILE "0.6\t$hist[5]\n");
print( GPFILE "0.7\t$hist[6]\n");
print( GPFILE "0.8\t$hist[7]\n");
print( GPFILE "0.9\t$hist[8]\n");
print( GPFILE "1.0\t$hist[9]\n");
print( GPFILE "e\n");
print( GPFILE "exit\n");
close( GPFILE );
system "$GNUPLOT temp.plt";
#unlink( "temp.plt");
