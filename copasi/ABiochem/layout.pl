#! /usr/bin/perl
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

$gfile = $ARGV[0];

	# read statistics first
	$statfile = $gfile . ".netstat";
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

	$psfile = $gfile . ".eps";
	$pngfilen = $gfile . ".n.png";
	$gfile .= ".dot";
    # don't bother laying out if more than 500 vertices
    if ($vertex < 500)
	{
	  # Layout the graph into postscript
#	  system "$NEATO -Tps -G\"page=8.5,11\" -G\"size=7.5,10\" -o$psfile $gfile 2>>layout.log";

# 	  print ".";

	  # Layout the graph into a picture (png)
	  system "$NEATO -G\"size=8,8\" -Tpng -o$pngfilen $gfile 2>>layout.log";
	  print ".";
	}
	else
	{
	  # create a replacement graph ...
	  open( DTFILE, ">tmp.gvz" );
	  print( DTFILE "digraph \"$gfile\" { graph[ label=\"too many nodes to layout, use Pajek!\" ]\nNO -> IMAGE\n}");
	  close( DTFILE );

 	  print ".";

	  system "$NEATO -G\"size=8,8\" -Tpng -o$pngfilen tmp.gvz 2>>layout.log";
	} 

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
	if ($vertex < 500)
	 {system "$DOT -G\"size=8,8\" -Tpng -o$pngfiled $gfile 2>>layout.log";}
	else
	 {system "$DOT -G\"size=8,8\" -Tpng -o$pngfiled tmp.gvz 2>>layout.log";}

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

    # create HTML
	$hfile = $gfile;
	$hfile =~ s/\.$GRAPHEXTENSION/\.html/;
	$gfile =~ s/\.$GRAPHEXTENSION//;
	open( HTFILE, ">$hfile" );
    # file with cmd line
	$cfile = $gfile . ".cmd";
	open( CFILE, "$cfile" );
	$cline = <CFILE>;
	chop( $cline );
	close( CFILE );
    # write the HTML header
	$strtime = localtime();
	print( HTFILE "<html>\n<!-- Created by A-Biochem, $strtime -->\n");
	print( HTFILE "<head>\n<style type=\"text/css\" media=\"all\">\@import \"nets.css\";</style>\n");
	print( HTFILE "<title>$gfile</title>\n</head>\n");
	# write the HTML body
	print( HTFILE "<body>\n");
	print( HTFILE "<div id=\"topmenu\">\n<center>\n");
	print( HTFILE "<a href=\"http://www.vbi.vt.edu/~mendes\">Biochemical Networks Modeling Group</a> |\n");
	print( HTFILE "<a href=\"../index.html\">AGN project Home</a> |\n");
	print( HTFILE "<a href=\"index.html\">Data set index</a>\n");
	print( HTFILE "</center></div>\n");
	print( HTFILE "<div id=\"main\">\n<center>\n");
	print( HTFILE "<h1>Artificial Gene Network <em>$gfile</em></h1>\n");
	print( HTFILE "<p>Generated with: <code>$cline</code></p>\n");
	print( HTFILE "<div id=\"menu\">\n");
	print( HTFILE "<a href=\"#neato\">Force field layout</a> |\n");
	print( HTFILE "<a href=\"#dot\">Hierarchical layout</a> |\n");
	print( HTFILE "<a href=\"#deg\">Degree distribution</a> |\n");
	print( HTFILE "<a href=\"#files\">Files</a>\n");
	print( HTFILE "</div>\n");
	print( HTFILE "<h2>Network statistics</h2>\n<table>\n");
    foreach $line (@stats)
	{ 
	  chop($line);
      $line =~ s/\t/<\/td><td>/;
      print( HTFILE "<tr><td>$line</td></tr>\n");
	}
	print( HTFILE "</table>\n");
	print( HTFILE "<h2><a name=\"neato\">Force field layout</a></h2>\n<img src=\"$pngfilen\">\n");
	print( HTFILE "<h2><a name=\"dot\">Hierarchical layout</a></h2>\n<img src=\"$pngfiled\">\n");
	print( HTFILE "<h2><a name=\"deg\">Degree distribution</a></h2>\n<img src=\"$pngfileg\">\n");
	print( HTFILE "<h2><a name=\"files\">Files</a></h2>\n<table>\n");
	print( HTFILE "<tr><td>Gepasi</td><td><a href=\"$gfile.gps\">$gfile.gps</a></td></tr>\n");
	print( HTFILE "<tr><td>SBML</td><td><a href=\"$gfile.xml\">$gfile.xml</a></td></tr>\n");
	print( HTFILE "<tr><td>Graphviz</td><td><a href=\"$gfile.dot\">$gfile.dot</a></td></tr>\n");
	print( HTFILE "<tr><td>Pajek</td><td><a href=\"$gfile.net\">$gfile.net</a></td></tr>\n");
	print( HTFILE "<tr><td>Gnuplot degree distribution</td><td><a href=\"$gfile.distri.plt\">$gfile.distri.plt</a></td></tr>\n");
#	print( HTFILE "<tr><td>Network statistics</td><td><a href=\"$gfile.netstat\">$gfile.netstat</a></td></tr>\n");
	print( HTFILE "<tr><td>Gepasi report file</td><td><a href=\"$gfile.txt\">$gfile.txt</a></td></tr>\n");
	print( HTFILE "</table>\n");
	print( HTFILE "</center>\n</div>\n");
	print( HTFILE "</body>\n</html>");
	close( HTFILE );

	print ".";

	# run Gepasi
#	$sfile = $gfile . ".gps";
#	$sfile =~ s/\.$GRAPHEXTENSION/\.gps/;
#	system "$GEPASI $sfile";

	print ".\n";

	# cleanup the mess
	unlink($bfile);
	unlink($b1file);
