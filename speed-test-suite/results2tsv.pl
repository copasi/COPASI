#!/usr/bin/perl -w
#
# results2tsv.pl
# extracts data in .out files and puts them in a tsv
# This does not deal with missing data very well:
# it ignores missing data and adds all numeric results
# one after the other separated by tabs

if( $#ARGV < 0 ) { die "usage: results2tsv.pl datafile\n"; }

$ofile = $ARGV[0];
open( OFILE, ">$ofile" )  || die "can't create file $ofile";

while( defined($ifile = <*.out>) )
{
  open( IFILE, "<$ifile") || next;

  $name = $ifile;
  $name =~ s/\.out//;
  printf(OFILE "$name");

  $header = 0;
  while( <IFILE> )
  {
    #read data when it starts a line
    if( /^(\d+\.\d*)$/ )
    {
      printf(OFILE "\t$1" ); 
      # this was not a header...
      $header = 0;
    }
    else
    {
      if( $header == 1 ) 
      {
	# if the previous line was a header there is missing data!
	printf(OFILE "\t");
      }
      # this was a header
      $header = 1;
    }
  }
  if ( $header == 1 )
  {
    # last line was a header, so there is missing data
    printf(OFILE "\t");
  }  
  printf(OFILE "\n" );    
  close( IFILE );
}
close(OFILE);