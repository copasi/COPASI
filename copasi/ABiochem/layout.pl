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

$lasthfile = ".";
$lastgfile = "top level";

# processing
while( defined($gfile = <*.$GRAPHEXTENSION>) )
{
	$counter++;
	print "$counter, $gfile ";

	# read statistics first
	$statfile = $gfile;
	$statfile =~ s/\.$GRAPHEXTENSION/\.netstat/;
	open( STATFILE, "<$statfile" );
	$vertex = 0;
	@stats = <STATFILE>;
	close(STATFILE);
    foreach $line (@stats) 
      if( $line =~ /number of vertices\t([0..9]+)/ )
	  {
	    $vertex = $1;
	    last;
	  }

	$psfile = $gfile;
	$psfile =~ s/\.$GRAPHEXTENSION/\.eps/;
	$pngfilen = $gfile;
    $pngfilen =~ s/\.$GRAPHEXTENSION/\.n\.png/;
    # don't bother laying out if more than 500 vertices
    if( $vertex lt 500 )
	{
	  # Layout the graph into postscript
	  system "$NEATO -Tps -G\"page=8.5,11\" -G\"size=7.5,10\" -o$psfile $gfile 2>>layout.log";

 	  print ".";

	  # Layout the graph into a picture (png)
	  system "$NEATO -G\"size=8,8\" -Tpng -o$pngfilen $gfile 2>>layout.log";
	}
	else
	{
	  # create a replacement graph ...
	  open( DTFILE, ">tmp.dot" );
	  print( DTFILE "digraph \"$gfile\" { graph[ label=\"too many nodes to layout, use Pajek!\" ]\nNO -> GRAPH\n}");
	  close( FTFILE );

 	  print ".";

	  system "$NEATO -G\"size=8,8\" -Tpng -o$pngfilen tmp.dot 2>>layout.log";
	} 

	print ".";

	# convert to PBM, process, and convert back to desired bitmap format
	$bfile = $gfile;
	$bfile =~ s/\.$GRAPHEXTENSION/\.pnm/;
	system "$TOPBM $pngfilen >$bfile 2>>layout.log";
	$b1file = $bfile;
	$b1file =~ s/\.pnm/\.1\.pnm/;
	system "$PBMOPS $bfile >$b1file 2>offset.txt";
	system "$FROMPBM $b1file > $pngfilen 2>>layout.log";

	print ".";

	# Layout the graph into a picture (png)
	$pngfiled = $gfile;
	$pngfiled =~ s/\.$GRAPHEXTENSION/\.d\.png/;
	if( $vertex lt 500 )
	 system "$DOT -G\"size=8,8\" -Tpng -o$pngfiled $gfile 2>>layout.log";
	else
	 system "$DOT -G\"size=8,8\" -Tpng -o$pngfiled tmp.dot 2>>layout.log";


    print ".";

	# convert to PBM, process, and convert back to desired bitmap format
	$bfile = $gfile;
	$bfile =~ s/\.$GRAPHEXTENSION/\.pnm/;
	system "$TOPBM $pngfiled >$bfile 2>>layout.log";
	$b1file = $bfile;
	$b1file =~ s/\.pnm/\.1\.pnm/;
	system "$PBMOPS $bfile >$b1file 2>offset.txt";
	system "$FROMPBM $b1file > $pngfiled 2>>layout.log";

	print ".";

	# make the graph of comulative distribution (png)
	$gplfilei = $gfile;
	$gplfilei =~ s/\.$GRAPHEXTENSION/\.distri\.plt/;
	$pngfileg = $gfile;
	$pngfileg =~ s/\.$GRAPHEXTENSION/\.distri\.png/;
	open( GPFILE, ">temp.plt" );
	print( GPFILE "set terminal png medium color\n");
	print( GPFILE "set data style points\n");
	print( GPFILE "set logscale\n");
	print( GPFILE "set output \'$pngfileg\'\n");
    # copy the contents of the file
	open( GPFILE2, "<$gplfilei" ) || print "could not open $gplfilei\n";
    while( <GPFILE2> ){ print( GPFILE $_ );}
	print( GPFILE "exit\n");
	close( GPFILE );
	close( GPFILE2 );
	system "$GNUPLOT temp.plt";

	print ".";

    # get map coordinates, create coordinate file and HTML with imagemap
	$hfile = $gfile;
	$hfile =~ s/\.$GRAPHEXTENSION/\.html/;
	$gfile =~ s/\.$GRAPHEXTENSION//;
	open( HTFILE, ">$hfile" );
    # write the HTML header
	$strtime = localtime();
	print( HTFILE "<html>\n<!-- Created by A-Biochem, $strtime -->\n");
	print( HTFILE "<head>\n<style type=\"text/css\" media=\"all\">@import \"nets.css\";</style>\n");
	print( HTFILE "<title>$gfile</title>\n</head>\n");
	# write the HTML body
	print( HTFILE "<body>\n<center>\n");
	print( HTFILE "<div id=\"topmenu\">\n<ul>\n");
	print( HTFILE "<li class=\"first\"><a href=\"http://www.vbi.vt.edu/~mendes\">Biochemical Networks Modeling Group</a></li>\n");
	print( HTFILE "<li><a href=\"..\">Artificial Gene Networks</a></li>\n");
	print( HTFILE "</ul></div>\n");
	print( HTFILE "<h1>Artificial Gene Network $gfile</h1>\n");
	print( HTFILE "<h2>statistics</h2>\n<table>");
    foreach $line (@stats)
	{ 
      $line =~ s/\t/<\/td><td>/
      print( HTFILE "<tr><td>$line</td></tr>");
	}
	print( HTFILE "</table>\n");
	print( HTFILE "<div id=\"menu\">\n<ul>\n");
	print( HTFILE "<li class=\"first\"><a href=\"#neato\">Force field layout</a></li>\n");
	print( HTFILE "<li><a href=\"#dot\">Hierarchical layout</a></li>\n");
	print( HTFILE "<li><a href=\"#deg\">Degree distribution</a></li>\n");
	print( HTFILE "</ul></div>\n");
	print( HTFILE "[ <a href=\"#deg\">degree distribution</a> ]</p>\n");
	print( HTFILE "<h2><a name=\"neato\">neato</a></h2>\n<img border=\"0\" src=\"$pngfilen\">\n");
	print( HTFILE "<h2><a name=\"dot\">dot</a></h2>\n<img border=\"0\" src=\"$pngfiled\">\n");
	print( HTFILE "<h2><a name=\"deg\">Degree distribution</a></h2>\n<img border=\"0\" src=\"$pngfileg\">\n");
	print( HTFILE "</center>\n</body>\n</html>");
	close( HTFILE );
	$lasthfile=$hfile;
	$lastgfile=$gfile;

	print ".";

	# run Gepasi
	$sfile = $gfile . ".gps";
#	$sfile =~ s/\.$GRAPHEXTENSION/\.gps/;
	system "$GEPASI $sfile";

	print ".\n";

	# cleanup the mess
	unlink($bfile);
	unlink($b1file);
	if( $vertex ge 500 ) unlink("tmp.dot");
}

unlink("offset.txt");
unlink("temp.plt");
