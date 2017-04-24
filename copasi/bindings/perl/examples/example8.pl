#  
#  This is an example on how to calculate and output the Jacobian matrix
#  in COPASI
#  
use strict;
use warnings;

use COPASI;


my $MODEL_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <!-- Created by COPASI version 4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. -->\n <sbml xmlns=\"http:#www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n <listOfUnitDefinitions>\n <unitDefinition id=\"volume\" name=\"volume\">\n <listOfUnits>\n <unit kind=\"litre\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"substance\" name=\"substance\">\n <listOfUnits>\n <unit kind=\"mole\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"unit_0\">\n <listOfUnits>\n <unit kind=\"second\" exponent=\"-1\"/>\n </listOfUnits>\n </unitDefinition>\n </listOfUnitDefinitions>\n <listOfCompartments>\n <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n </listOfCompartments>\n <listOfSpecies>\n <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n </listOfSpecies>\n <listOfReactions>\n <reaction metaid=\"COPASI5\" id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_1\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_2\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http:#www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_1 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.2\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n <reaction metaid=\"COPASI6\" id=\"reaction_2\" name=\"reaction_2\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_2\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_3\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http:#www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_2 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.1\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n </listOfReactions>\n </model>\n </sbml>\n";


unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed.\n";die;}
# create a new datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(defined($dataModel)){warn "Assertion failed.\n";die;}
unless(COPASI::CRootContainer::getDatamodelList()->size() == 1){warn "Assertion failed.\n";die;}
# next we import a simple SBML model from a string

# clear the message queue so that we only have error messages from the import in the queue
COPASI::CCopasiMessage::clearDeque();
my $result=1;
eval {
  $result = $dataModel->importSBMLFromString($MODEL_STRING);
} or do {
    warn"Import of model failed miserably.\n";
    die;
};

# check if the import was successful
my $mostSevere = COPASI::CCopasiMessage::getHighestSeverity();
# if it was a filtered error, we convert it to an unfiltered type
# the filtered error messages have the same value as the unfiltered, but they
# have the 7th bit set which basically adds 128 to the value
$mostSevere = $mostSevere & 127;

# we assume that the import succeeded if the return value is 1 and
# the most severe error message is not an error or an exception
if ((!$result) &&  ($mostSevere < $COPASI::CCopasiMessage::ERROR)) {
    warn "Sorry. Model could not be imported.\n";
    die;
}

#
# now we tell the model object to calculate the jacobian
#
my $model = $dataModel->getModel();
unless(defined($model)){warn "Assertion failed.\n";die;};

if (defined($model)) {
    # running a task, e.g. a trajectory will automatically make sure that
    # the initial values are transferred to the current state before the calculation begins.
    # If we use low level calculation methods like the one to calculate the jacobian, we
    # have to make sure the the initial values are applied to the state
    $model->applyInitialValues();
    # we need an array that stores the result
    # the size of the matrix does not really matter because
    # the calculateJacobian autoamtically resizes it to the correct
    # size
    my $jacobian=new COPASI::FloatMatrix();
    # the first parameter to the calculation function is a reference to
    # the matrix where the result is to be stored
    # the second parameter is the derivationFactor for the calculation
    # it basically represents a relative delta value for the calculation of the derivatives
    # the third parameter termed resolution in the C++ API is currently ignores
    # so it does not matter what value you give here.
    $model->calculateJacobian($jacobian, 1e-12, 1.0);
    # now we print the result
    # the jacobian stores the values in the order they are
    # given in the user order in the state template so it is not really straight
    # forward to find out which column/row corresponds to which species
    my $stateTemplate = $model->getStateTemplate();
    # and we need the user order
    my $userOrder = $stateTemplate->getUserOrder();
    # from those two, we can construct an new vector that contains
    # the names of the entities in the jacobian in the order in which they appear in
    # the jacobian
    my @nameVector=();
    my $entity;
    my $status=-1;

    for (my $i=0;$i < $userOrder->size();$i++) {
        $entity = $stateTemplate->getEntity($userOrder->get($i));
        unless(defined($entity)){warn "Assertion failed.\n";die;}
        # now we need to check if the entity is actually
        # determined by an ODE or a reaction
        $status = $entity->getStatus();

        if ($status == $COPASI::CModelEntity::ODE || ($status == $COPASI::CModelEntity::REACTIONS && $entity->isUsed())) {
            push(@nameVector, $entity->getObjectName());
        }
    }

    unless((@nameVector + 0) == $jacobian->numRows()){warn "Assertion failed.\n";die;}
    # now we print the matrix, for this we assume that no
    # entity name is longer then 5 character which is a save bet since
    # we know the model
    print "Jacobian Matrix:\n";
    print "\n";
    printf "%7s", " ";

    for (my $i=0;$i < (@nameVector + 0);$i++) {
        printf "%7s" , $nameVector[$i];
    }

    print "\n";

    for (my $i=0;$i < (@nameVector + 0);$i++) {
        printf "%7s" , $nameVector[$i];

        for (my $j=0;$j < (@nameVector + 0);$j++)  {
            printf "%7.3f" , $jacobian->get($i,$j);
        }

        print "\n";
    }

    # we can also calculate the jacobian of the reduced system
    # in a similar way
    $model->calculateJacobianX($jacobian, 1e-12, 1.0);
    # this time generating the output is actually simpler because the rows
    # and columns are ordered in the same way as the independent variables of the state temple
    print "\n";
    print "\n";
    print "Reduced Jacobian Matrix:\n";
    print "\n";
    printf "%7s", " ";
    
    my $iMax = $stateTemplate->getNumIndependent();
    
    for (my $i=0; $i < $iMax; $i++) {
      printf "%7s", $stateTemplate->getIndependent($i)->getObjectName();
    }

    print "\n";

    for (my $i=0; $i < $iMax; $i++) {
        printf "%7s", $stateTemplate->getIndependent($i)->getObjectName();

        for( my $j=0; $j < $iMax; $j++) {
            printf "%7.3f" , $jacobian->get($i,$j);
        }
        print "\n";
    }
}

