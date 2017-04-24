#
# This is an example on how to load a cps file
# and output some information on the model
#

use strict;
use warnings;

use COPASI;

unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed";die;}
# create a datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(COPASI::DataModelVector::size(COPASI::CRootContainer::getDatamodelList()) == 1){warn "Assertion failed";die;}
# the only argument to the main routine should be the name of a CPS file
if ($#ARGV + 1 == 1) {
    my $filename = $ARGV[0];
    print $ARGV[0];
    eval {
        # load the model without progress report
        $dataModel->loadModel($filename);
    }
    or do {
        warn "Error while loading the model from file named \"", $filename, "\".\n";
        die
    };
    my $model = $dataModel->getModel();
    unless(defined($model)){warn "Assertion failed";die;}
    print "Model statistics for model \"", $model->getObjectName(), "\".\n";

    # output number and names of all compartments
    my $iMax = $model->getCompartments()->size();
    print "Number of Compartments: " , $iMax, "\n";
    print "Compartments: \n";
    for(my $i=0; $i < $iMax; $i++) {
        my $compartment = $model->getCompartment($i);
        unless(defined($compartment)){warn "Assertion failed";die;}
        print "\t", $compartment->getObjectName(), "\n";
    }

    # output number and names of all metabolites
    $iMax = $model->getMetabolites()->size();
    print "Number of Metabolites: " , $iMax, "\n";
    print "Metabolites: \n";
    for ( my $i=0; $i < $iMax; $i++) {
        my $metab = $model->getMetabolite($i);
        unless(defined($metab)){warn "Assertion failed";die;}
        print "\t", $metab->getObjectName(), "\n";
    }
    # output number and names of all reactions
    $iMax = $model->getReactions()->size();
    print "Number of Reactions: " , $iMax, "\n";
    print "Reactions: \n";
    for (my $i=0; $i < $iMax; $i++) {
        my $reaction = $model->getReaction($i);
        unless(defined($reaction)){warn "Assertion failed";die;};
        print "\t" , $reaction->getObjectName(), "\n";
    }
}
else{
    warn "Usage: example2 CPSFILE";
    die;
}


