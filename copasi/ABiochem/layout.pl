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
	# Layout the graph into postscript
	$psfile = $gfile;
	$psfile =~ s/\.$GRAPHEXTENSION/\.eps/;
	system "$NEATO -Tps -G\"page=8.5,11\" -G\"size=7.5,10\" -o$psfile $gfile 2>>layout.log";

	print ".";

	# Layout the graph into a picture (png)
	$pngfilen = $gfile;
	$pngfilen =~ s/\.$GRAPHEXTENSION/\.n\.png/;
	system "$NEATO -G\"size=8,8\" -Tpng -o$pngfilen $gfile 2>>layout.log";

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
	system "$DOT -G\"size=8,8\" -Tpng -o$pngfiled $gfile 2>>layout.log";

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
	print( HTFILE "<head>\n<title>$gfile</title>\n</head>\n");
	# write the HTML body
	print( HTFILE "<body>\n<center>\n");
	print( HTFILE "<h1>$gfile</h1>\n[ <a href=\"$lasthfile\">$lastgfile</a> ]\n");
	print( HTFILE "<p>[ <a href=\"#dot\">hierarchical layout</a> ] ");
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
}

unlink("offset.txt");
unlink("temp.plt");
