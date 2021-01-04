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

  while( <IFILE> )
  {
    #read only lines with a single numerical value
    if( /^(\d+\.\d*)$/ )
    {
      printf(OFILE "\t$1" );  
    }
  }
  printf(OFILE "\n" );    
  close( IFILE );
}
close(OFILE);