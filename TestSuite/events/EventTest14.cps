<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.12 (Build 81) (http://www.copasi.org) at 2014-05-09 18:05:49 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="12" versionDevel="81" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
   <rdf:Description rdf:about="#Function_13">
   <CopasiMT:is rdf:resource="urn:miriam:obo.sbo:SBO:0000041" />
   </rdf:Description>
   </rdf:RDF>
      </MiriamAnnotation>
      <Comment>
        <b xmlns="http://www.w3.org/1999/xhtml">
mass action rate law for first order irreversible reactions
</b>
<p>
Reaction scheme where the products are created from the reactants and the change of a product quantity is proportional to the product of reactant activities. The reaction scheme does not include any reverse process that creates the reactants from the products. The change of a product quantity is proportional to the quantity of one reactant.
</p>
      </Comment>
      <Expression>
        k1*PRODUCT&lt;substrate_i&gt;
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="function_4_cdc13T synthesis" type="UserDefined" reversible="false">
      <Expression>
        k1*M
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_421" name="M" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_419" name="k1" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="function_4_Targeting cdc13T to APC core" type="UserDefined" reversible="false">
      <Expression>
        (k2_prime+k2_double_prime*(ste9*cell)+k2_triple_prime*(slp1*cell))*cdc13T
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_433" name="cdc13T" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_427" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_423" name="k2_double_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_422" name="k2_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_429" name="k2_triple_prime" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_431" name="slp1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_425" name="ste9" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="function_4_wee1 dependent MPF inactivation" type="UserDefined" reversible="false">
      <Expression>
        kwee*(cdc13T*cell-preMPF*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_430" name="cdc13T" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_426" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_434" name="kwee" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_420" name="preMPF" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="function_4_preMPF inactivation" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:00:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

      </MiriamAnnotation>
      <Expression>
        (k2_prime+k2_double_prime*(ste9*cell)+k2_triple_prime*(slp1*cell))*preMPF
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_438" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_428" name="k2_double_prime" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_435" name="k2_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_440" name="k2_triple_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_444" name="preMPF" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_442" name="slp1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_436" name="ste9" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_slp1 dependent ste9 activation" type="UserDefined" reversible="false">
      <Expression>
        (k3_prime+k3_double_prime*(slp1*cell))*(1-ste9*cell)/(J3+1-ste9*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_449" name="J3" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_424" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_441" name="k3_double_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_445" name="k3_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_437" name="slp1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_447" name="ste9" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_ste9 phosphorylation (inactivation) by starter kinase" type="UserDefined" reversible="false">
      <Expression>
        (k4_prime*(SK*cell)+k4*(MPF*cell))*ste9/(J4+ste9*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_457" name="J4" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_453" name="MPF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_446" name="SK" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_439" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_451" name="k4" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_450" name="k4_prime" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_455" name="ste9" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_slp1T activation by MPF" type="UserDefined" reversible="false">
      <Expression>
        (k5_prime+k5_double_prime*(MPF*cell)^4/(J5^4+(MPF*cell)^4))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_460" name="J5" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_443" name="MPF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_448" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_454" name="k5_double_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_458" name="k5_prime" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_slp1 activation by intermediary enzyme" type="UserDefined" reversible="false">
      <Expression>
        k7*IEP*(slp1T*cell-slp1*cell)/(J7+slp1T*cell-slp1*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_432" name="IEP" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_467" name="J7" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_463" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_461" name="k7" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_465" name="slp1" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_456" name="slp1T" order="5" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_slp1 inactivation" type="UserDefined" reversible="false">
      <Expression>
        k8*slp1/(J8+slp1*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_452" name="J8" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_469" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_468" name="k8" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_464" name="slp1" order="3" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="function_4_Intermediary enzyme activation" type="UserDefined" reversible="false">
      <Expression>
        k9*MPF*(1-IEP*cell)/(J9+1-IEP*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_471" name="IEP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_475" name="J9" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_462" name="MPF" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_473" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_470" name="k9" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="function_4_IEP inactivation" type="UserDefined" reversible="false">
      <Expression>
        k10*IEP/(J10+IEP*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_472" name="IEP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_459" name="J10" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_478" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_476" name="k10" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="function_4_rum1T activation" type="UserDefined" reversible="false">
      <Expression>
        k11/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_466" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_479" name="k11" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="function_4_SK dependent rum1T inactivation" type="UserDefined" reversible="false">
      <Expression>
        (k12+k12_prime*(SK*cell)+k12_double_prime*(MPF*cell))*rum1T
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_488" name="MPF" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_482" name="SK" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_484" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_474" name="k12" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_486" name="k12_double_prime" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_480" name="k12_prime" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_490" name="rum1T" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="function_4_SK synthesis" type="UserDefined" reversible="false">
      <Expression>
        k13*TF/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_487" name="TF" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_483" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_491" name="k13" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="function_4_Cell growth" type="UserDefined" reversible="false">
      <Expression>
        mu*M
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_489" name="M" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_481" name="mu" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_5" name="Novak2001_FissionYeast_CellCycle" simulationType="time" timeUnit="min" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="dimensionless" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_5">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:12779461"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2007-04-13T05:35:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>hdharuri@cds.caltech.edu</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Dharuri</vCard:Family>
                <vCard:Given>Harish</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>California Institute of Technology</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:creator>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2009-10-07T13:38:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_152"/>
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:taxonomy:4894"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:BIOMD0000000111"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:MODEL6488296959"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:spo04111"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0000278"/>
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <p xmlns="http://www.w3.org/1999/xhtml">The model reproduces the time evolution of several species as depicted in Fig 4 of the paper. Events have been used to reset  cell mass when the value of M-phase promoting factor (MPF) decreases through 0.1. The model was successfully tested on Cell Designer. </p>
  <p xmlns="http://www.w3.org/1999/xhtml">This model originates from BioModels Database: A Database of Annotated Published Models (http://www.ebi.ac.uk/biomodels/). It is copyright (c) 2005-2010 The BioModels.net Team.<br />For more information see the <a href="http://www.ebi.ac.uk/biomodels/legal.html" target="_blank">terms of use</a>.<br />To cite BioModels Database, please use: <a href="http://www.ncbi.nlm.nih.gov/pubmed/20587024" target="_blank">Li C, Donizelli M, Rodriguez N, Dharuri H, Endler L, Chelliah V, Li L, He E, Henry A, Stefan MI, Snoep JL, Hucka M, Le Novère N, Laibe C (2010) BioModels Database: An enhanced, curated and annotated resource for published quantitative kinetic models. BMC Syst Biol., 4:92.</a>
</p>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_5" name="cell" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_5">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005623" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_15" name="Total cdc13" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="preMPF" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:59:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454"/>
        <rdf:li rdf:resource="urn:miriam:uniprot:P04551"/>
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="ste9" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:05:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:O13286"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="slp1T" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P78972" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="slp1" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P78972" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="IEP" simulationType="reactions" compartment="Compartment_5">
      </Metabolite>
      <Metabolite key="Metabolite_27" name="rum1T" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:52:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P40380"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="SK" simulationType="reactions" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24865" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="Cell Mass" simulationType="reactions" compartment="Compartment_5">
      </Metabolite>
      <Metabolite key="Metabolite_33" name="M-phase promoting factor" simulationType="assignment" compartment="Compartment_5">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:01:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454"/>
        <rdf:li rdf:resource="urn:miriam:uniprot:P04551"/>
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[preMPF],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Trimer],Reference=Value&gt;)/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_37" name="flag_MPF" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_38" name="sigma" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:02:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Kdiss],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="Kdiss" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:02:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="Trimer" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T14:01:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Expression>
          2*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value&gt;^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))^0.5)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="TF" simulationType="assignment">
        <Expression>
          2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J15],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J15],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;)^(1/2))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="k15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_43" name="J16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_44" name="k16_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_45" name="k16_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_46" name="J15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_47" name="kwee" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_prime],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_double_prime],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_prime],Reference=Value&gt;)*(2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;)^(1/2)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="kwee_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_49" name="kwee_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_50" name="Vawee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_51" name="Jiwee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_52" name="Viwee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_53" name="Jawee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_54" name="k25" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:57:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_prime],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_double_prime],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_prime],Reference=Value&gt;)*(2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Va25],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ja25],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ja25],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Va25],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;)^(1/2)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="k25_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_56" name="k25_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_57" name="Va25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_58" name="Ji25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_59" name="Vi25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_60" name="Ja25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_61" name="k1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_62" name="k2_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_63" name="k2_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_64" name="k2_triple_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_65" name="k3_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_66" name="k3_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_67" name="J3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_68" name="k4_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_69" name="k4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_70" name="J4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_71" name="k5_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="k5_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_73" name="J5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_74" name="k6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_75" name="k7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_76" name="J7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_77" name="k8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_78" name="J8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_79" name="k9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_80" name="J9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_81" name="k10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_82" name="J10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_83" name="k11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_84" name="k12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_85" name="k12_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_86" name="k12_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_87" name="k13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_88" name="k14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_89" name="mu" simulationType="fixed">
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_17" name="cdc13T synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007346" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4222" name="k1" value="0.03"/>
        </ListOfConstants>
        <KineticLaw function="Function_46">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="Targeting cdc13T to APC core" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007092" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4223" name="k2_double_prime" value="1"/>
          <Constant key="Parameter_4224" name="k2_prime" value="0.03"/>
          <Constant key="Parameter_4225" name="k2_triple_prime" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_47">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="wee1 dependent MPF inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0018108" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0045736" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.10.2" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_6178" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4226" name="kwee" value="1.25627"/>
        </ListOfConstants>
        <KineticLaw function="Function_48">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="cdc25 dependent preMPF phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:57:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004725"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0010389"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_6257.1"/>
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4227" name="k1" value="0.238217"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="preMPF inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:59:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0000216"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007092"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4228" name="k2_double_prime" value="1"/>
          <Constant key="Parameter_4229" name="k2_prime" value="0.03"/>
          <Constant key="Parameter_4230" name="k2_triple_prime" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_49">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="slp1 dependent ste9 activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_22">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0035307" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4231" name="J3" value="0.01"/>
          <Constant key="Parameter_4232" name="k3_double_prime" value="10"/>
          <Constant key="Parameter_4233" name="k3_prime" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_50">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="ste9 phosphorylation (inactivation) by starter kinase" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4234" name="J4" value="0.01"/>
          <Constant key="Parameter_4235" name="k4" value="35"/>
          <Constant key="Parameter_4236" name="k4_prime" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_51">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="slp1T activation by MPF" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4237" name="J5" value="0.3"/>
          <Constant key="Parameter_4238" name="k5_double_prime" value="0.3"/>
          <Constant key="Parameter_4239" name="k5_prime" value="0.005"/>
        </ListOfConstants>
        <KineticLaw function="Function_52">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="slp1T inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4242" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="slp1 activation by intermediary enzyme" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051443" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4241" name="J7" value="0.001"/>
          <Constant key="Parameter_4243" name="k7" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_53">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="slp1 inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4240" name="J8" value="0.001"/>
          <Constant key="Parameter_4244" name="k8" value="0.25"/>
        </ListOfConstants>
        <KineticLaw function="Function_54">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="slp1 inactivation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4245" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="Intermediary enzyme activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4246" name="J9" value="0.01"/>
          <Constant key="Parameter_4247" name="k9" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_55">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="IEP inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4248" name="J10" value="0.01"/>
          <Constant key="Parameter_4249" name="k10" value="0.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_56">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="rum1T activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031657" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4250" name="k11" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_57">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="SK dependent rum1T inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-09T13:52:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031657"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4251" name="k12" value="0.01"/>
          <Constant key="Parameter_4252" name="k12_double_prime" value="3"/>
          <Constant key="Parameter_4253" name="k12_prime" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_58">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="SK synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4254" name="TF" value="0.880381"/>
          <Constant key="Parameter_4255" name="k13" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_59">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_491">
              <SourceParameter reference="ModelValue_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="SK degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4256" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="Cell growth" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0016049" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4257" name="mu" value="0.005"/>
        </ListOfConstants>
        <KineticLaw function="Function_60">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_489">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="ModelValue_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_2" name="event_0000001" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-01-24T09:21:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <p xmlns="http://www.w3.org/1999/xhtml">The two events are used to reset the cell mass (divide by two) when MPF decreases through 0.1</p>
        </Comment>
        <TriggerExpression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[flag_MPF],Reference=Value&gt; eq 1 and &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt; le 0.1
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_31">
            <Expression>
              &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;/2/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_37">
            <Expression>
              0
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_3" name="event_0000002" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-01-24T09:21:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt; gt 0.1
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_37">
            <Expression>
              1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13]" value="0.2" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[preMPF]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[ste9]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1T]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1]" value="2.2" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[IEP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[SK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor]" value="0.2" type="Species" simulationType="assignment"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[flag_MPF]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma]" value="0.201" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Kdiss]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Trimer]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[TF]" value="0.8803808142671367" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15]" value="1.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J15]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee]" value="1.256272780429718" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_prime]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_double_prime]" value="1.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee]" value="0.25" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jawee]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25]" value="0.2382171624981674" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_prime]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_double_prime]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Va25]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25]" value="0.25" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ja25]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k1]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_prime]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_double_prime]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_triple_prime]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k3_prime]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k3_double_prime]" value="10" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J3]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k4_prime]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k4]" value="35" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J4]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k5_prime]" value="0.005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k5_double_prime]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J5]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k6]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k7]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J7]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k8]" value="0.25" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J8]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k9]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J9]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k10]" value="0.04" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J10]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k11]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12_prime]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12_double_prime]" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k13]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k14]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[mu]" value="0.005" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[cdc13T synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[cdc13T synthesis],ParameterGroup=Parameters,Parameter=k1" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Targeting cdc13T to APC core]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Targeting cdc13T to APC core],ParameterGroup=Parameters,Parameter=k2_double_prime" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_double_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Targeting cdc13T to APC core],ParameterGroup=Parameters,Parameter=k2_prime" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Targeting cdc13T to APC core],ParameterGroup=Parameters,Parameter=k2_triple_prime" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_triple_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[wee1 dependent MPF inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[wee1 dependent MPF inactivation],ParameterGroup=Parameters,Parameter=kwee" value="1.256272780429718" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[cdc25 dependent preMPF phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[cdc25 dependent preMPF phosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.2382171624981674" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[preMPF inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[preMPF inactivation],ParameterGroup=Parameters,Parameter=k2_double_prime" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_double_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[preMPF inactivation],ParameterGroup=Parameters,Parameter=k2_prime" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[preMPF inactivation],ParameterGroup=Parameters,Parameter=k2_triple_prime" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k2_triple_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 dependent ste9 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 dependent ste9 activation],ParameterGroup=Parameters,Parameter=J3" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J3],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 dependent ste9 activation],ParameterGroup=Parameters,Parameter=k3_double_prime" value="10" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k3_double_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 dependent ste9 activation],ParameterGroup=Parameters,Parameter=k3_prime" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k3_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[ste9 phosphorylation (inactivation) by starter kinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[ste9 phosphorylation (inactivation) by starter kinase],ParameterGroup=Parameters,Parameter=J4" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J4],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[ste9 phosphorylation (inactivation) by starter kinase],ParameterGroup=Parameters,Parameter=k4" value="35" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k4],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[ste9 phosphorylation (inactivation) by starter kinase],ParameterGroup=Parameters,Parameter=k4_prime" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k4_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T activation by MPF]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T activation by MPF],ParameterGroup=Parameters,Parameter=J5" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T activation by MPF],ParameterGroup=Parameters,Parameter=k5_double_prime" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k5_double_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T activation by MPF],ParameterGroup=Parameters,Parameter=k5_prime" value="0.005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k5_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1T inactivation],ParameterGroup=Parameters,Parameter=k1" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 activation by intermediary enzyme]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 activation by intermediary enzyme],ParameterGroup=Parameters,Parameter=J7" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J7],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 activation by intermediary enzyme],ParameterGroup=Parameters,Parameter=k7" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k7],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 inactivation],ParameterGroup=Parameters,Parameter=J8" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J8],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 inactivation],ParameterGroup=Parameters,Parameter=k8" value="0.25" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k8],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 inactivation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[slp1 inactivation_2],ParameterGroup=Parameters,Parameter=k1" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Intermediary enzyme activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Intermediary enzyme activation],ParameterGroup=Parameters,Parameter=J9" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J9],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Intermediary enzyme activation],ParameterGroup=Parameters,Parameter=k9" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k9],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[IEP inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[IEP inactivation],ParameterGroup=Parameters,Parameter=J10" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J10],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[IEP inactivation],ParameterGroup=Parameters,Parameter=k10" value="0.04" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k10],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[rum1T activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[rum1T activation],ParameterGroup=Parameters,Parameter=k11" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k11],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK dependent rum1T inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK dependent rum1T inactivation],ParameterGroup=Parameters,Parameter=k12" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK dependent rum1T inactivation],ParameterGroup=Parameters,Parameter=k12_double_prime" value="3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12_double_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK dependent rum1T inactivation],ParameterGroup=Parameters,Parameter=k12_prime" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k12_prime],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK synthesis],ParameterGroup=Parameters,Parameter=TF" value="0.8803808142671367" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[TF],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK synthesis],ParameterGroup=Parameters,Parameter=k13" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k13],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[SK degradation],ParameterGroup=Parameters,Parameter=k1" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k14],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Cell growth]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Reactions[Cell growth],ParameterGroup=Parameters,Parameter=mu" value="0.005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[mu],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_5"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="ModelValue_38"/>
      <StateTemplateVariable objectReference="ModelValue_40"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
      <StateTemplateVariable objectReference="ModelValue_54"/>
      <StateTemplateVariable objectReference="Compartment_5"/>
      <StateTemplateVariable objectReference="ModelValue_37"/>
      <StateTemplateVariable objectReference="ModelValue_39"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_48"/>
      <StateTemplateVariable objectReference="ModelValue_49"/>
      <StateTemplateVariable objectReference="ModelValue_50"/>
      <StateTemplateVariable objectReference="ModelValue_51"/>
      <StateTemplateVariable objectReference="ModelValue_52"/>
      <StateTemplateVariable objectReference="ModelValue_53"/>
      <StateTemplateVariable objectReference="ModelValue_55"/>
      <StateTemplateVariable objectReference="ModelValue_56"/>
      <StateTemplateVariable objectReference="ModelValue_57"/>
      <StateTemplateVariable objectReference="ModelValue_58"/>
      <StateTemplateVariable objectReference="ModelValue_59"/>
      <StateTemplateVariable objectReference="ModelValue_60"/>
      <StateTemplateVariable objectReference="ModelValue_61"/>
      <StateTemplateVariable objectReference="ModelValue_62"/>
      <StateTemplateVariable objectReference="ModelValue_63"/>
      <StateTemplateVariable objectReference="ModelValue_64"/>
      <StateTemplateVariable objectReference="ModelValue_65"/>
      <StateTemplateVariable objectReference="ModelValue_66"/>
      <StateTemplateVariable objectReference="ModelValue_67"/>
      <StateTemplateVariable objectReference="ModelValue_68"/>
      <StateTemplateVariable objectReference="ModelValue_69"/>
      <StateTemplateVariable objectReference="ModelValue_70"/>
      <StateTemplateVariable objectReference="ModelValue_71"/>
      <StateTemplateVariable objectReference="ModelValue_72"/>
      <StateTemplateVariable objectReference="ModelValue_73"/>
      <StateTemplateVariable objectReference="ModelValue_74"/>
      <StateTemplateVariable objectReference="ModelValue_75"/>
      <StateTemplateVariable objectReference="ModelValue_76"/>
      <StateTemplateVariable objectReference="ModelValue_77"/>
      <StateTemplateVariable objectReference="ModelValue_78"/>
      <StateTemplateVariable objectReference="ModelValue_79"/>
      <StateTemplateVariable objectReference="ModelValue_80"/>
      <StateTemplateVariable objectReference="ModelValue_81"/>
      <StateTemplateVariable objectReference="ModelValue_82"/>
      <StateTemplateVariable objectReference="ModelValue_83"/>
      <StateTemplateVariable objectReference="ModelValue_84"/>
      <StateTemplateVariable objectReference="ModelValue_85"/>
      <StateTemplateVariable objectReference="ModelValue_86"/>
      <StateTemplateVariable objectReference="ModelValue_87"/>
      <StateTemplateVariable objectReference="ModelValue_88"/>
      <StateTemplateVariable objectReference="ModelValue_89"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 2.2 1 0 0.2 0 0 0 1 0.2 0.201 0 0.8803808142671367 1.256272780429718 0.2382171624981674 1 0 0.001 1.5 0.01 1 2 0.01 0.15 1.3 0.25 0.01 1 0.01 0.05 5 1 0.01 0.25 0.01 0.03 0.03 1 0.1 1 10 0.01 2 35 0.01 0.005 0.3 0.3 0.1 1 0.001 0.25 0.001 0.1 0.01 0.04 0.01 0.1 0.01 1 3 0.1 0.1 0.005 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_26" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="1"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Maximum duration for forward integration" type="unsignedFloat" value="1000000000"/>
        <Parameter name="Maximum duration for backward integration" type="unsignedFloat" value="1000000"/>
      </Method>
    </Task>
    <Task key="Task_25" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_9" target="EventTest14.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="1000"/>
        <Parameter name="StepSize" type="float" value="0.5"/>
        <Parameter name="Duration" type="float" value="500"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_24" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_23" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_22" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Random Search" type="RandomSearch">
        <Parameter name="Number of Iterations" type="unsignedInteger" value="100000"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <Parameter name="Time-Course" type="cn" value="CN=Root,Vector=TaskList[Time-Course]"/>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_20" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_26"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_19" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_18" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="1e-06"/>
      </Method>
    </Task>
    <Task key="Task_17" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="SubtaskType" type="unsignedInteger" value="1"/>
        <ParameterGroup name="TargetFunctions">
          <Parameter name="SingleObject" type="cn" value=""/>
          <Parameter name="ObjectListType" type="unsignedInteger" value="7"/>
        </ParameterGroup>
        <ParameterGroup name="ListOfVariables">
          <ParameterGroup name="Variables">
            <Parameter name="SingleObject" type="cn" value=""/>
            <Parameter name="ObjectListType" type="unsignedInteger" value="41"/>
          </ParameterGroup>
        </ParameterGroup>
      </Problem>
      <Method name="Sensitivities Method" type="SensitivitiesMethod">
        <Parameter name="Delta factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Delta minimum" type="unsignedFloat" value="1e-12"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_15" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
        <Parameter name="LimitCrossings" type="bool" value="0"/>
        <Parameter name="NumCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitOutTime" type="bool" value="0"/>
        <Parameter name="LimitOutCrossings" type="bool" value="0"/>
        <Parameter name="PositiveDirection" type="bool" value="1"/>
        <Parameter name="NumOutCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitUntilConvergence" type="bool" value="0"/>
        <Parameter name="ConvergenceTolerance" type="float" value="1e-06"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-06"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
        <Parameter name="LimitTime" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_27" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_26"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_17" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_16" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_15" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Object=Description"/>
        <Object cn="String=\[Function Evaluations\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Value\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Parameters\]"/>
      </Header>
      <Body>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters"/>
      </Body>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_14" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Parameter Estimation],Object=Description"/>
        <Object cn="String=\[Function Evaluations\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Value\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Parameters\]"/>
      </Header>
      <Body>
        <Object cn="CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Function Evaluations"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Value"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Parameters"/>
      </Body>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Estimation],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_13" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_12" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_11" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="7">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[preMPF],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[ste9],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[SK],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[flag_MPF],Reference=Value"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Trimer],Reference=Value"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[TF],Reference=Value"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee],Reference=Value"/>
        <Object cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25],Reference=Value"/>
      </Table>
    </Report>
    <Report key="Report_19" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Result"/>
      </Footer>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[&quot;Total cdc13&quot;]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[preMPF]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[preMPF],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ste9]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[ste9],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[slp1T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[slp1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[slp1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IEP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[rum1T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SK]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[SK],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[&quot;Cell Mass&quot;]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[&quot;M-phase promoting factor&quot;]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[flag_MPF]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[flag_MPF],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[sigma]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Trimer]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Trimer],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[TF]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[TF],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[kwee]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[k25]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <ListOfLayouts xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <Layout key="Layout_0" name="COPASI autolayout">
      <Dimensions width="901.7006455249823" height="783.3543190005754"/>
      <ListOfMetabGlyphs>
        <MetaboliteGlyph key="Layout_2" name="MetabGlyph" metabolite="Metabolite_15">
          <BoundingBox>
            <Position x="470.0053066060423" y="156.2201609135879"/>
            <Dimensions width="180" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_4" name="MetabGlyph" metabolite="Metabolite_17">
          <BoundingBox>
            <Position x="383.8681274376316" y="122.9989903273405"/>
            <Dimensions width="100" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_6" name="MetabGlyph" metabolite="Metabolite_19">
          <BoundingBox>
            <Position x="341.4175860787097" y="288.8616148796044"/>
            <Dimensions width="68" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_8" name="MetabGlyph" metabolite="Metabolite_21">
          <BoundingBox>
            <Position x="463.394551865345" y="546.7202825474208"/>
            <Dimensions width="84" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_10" name="MetabGlyph" metabolite="Metabolite_23">
          <BoundingBox>
            <Position x="495.0377997088658" y="351.7965534687644"/>
            <Dimensions width="68" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_12" name="MetabGlyph" metabolite="Metabolite_25">
          <BoundingBox>
            <Position x="428.4155972759118" y="611.8494174599342"/>
            <Dimensions width="52" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_14" name="MetabGlyph" metabolite="Metabolite_27">
          <BoundingBox>
            <Position x="127.9198409277499" y="564.7832825169153"/>
            <Dimensions width="84" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_16" name="MetabGlyph" metabolite="Metabolite_29">
          <BoundingBox>
            <Position x="148.4747322427525" y="362.6941384134132"/>
            <Dimensions width="36" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_18" name="MetabGlyph" metabolite="Metabolite_31">
          <BoundingBox>
            <Position x="672.9111526135662" y="167.1602493047611"/>
            <Dimensions width="148" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_20" name="MetabGlyph" metabolite="Metabolite_33">
          <BoundingBox>
            <Position x="106.6944485519471" y="486.9049886694062"/>
            <Dimensions width="388" height="28"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_23" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="65.90894112345839" y="694.4094690855884"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_28" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="101.6667890113834" y="493.6681319778893"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_33" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="118.1612807563951" y="217.5732767124582"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_38" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="0" y="378.843769812852"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_41" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="900.7006455249823" y="184.755549189489"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_45" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="669.7277210399227" y="62.59732282594115"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_51" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="599.9325609951422" y="264.8274427403031"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_56" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="498.9029587231769" y="0"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_62" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="302.5285626183528" y="37.37144807746228"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_66" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="352.0999953665445" y="209.3409918475523"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_71" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="363.8657202165895" y="405.0290720281291"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_77" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="250.6217158945481" y="291.0215422866564"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_82" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="339.599695025132" y="561.8631372940908"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_88" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="651.9735696390546" y="638.4104122340882"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_91" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="619.6087731260277" y="484.8577776159851"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_98" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="696.2560841130694" y="359.0881869750117"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_102" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="421.2309543626125" y="461.9164969126999"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_105" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="321.2744576568356" y="702.0342667634518"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_111" name="MetabGlyph" metabolite="" objectRole="invisible">
          <BoundingBox>
            <Position x="503.9586740036386" y="782.3543190005754"/>
            <Dimensions width="1" height="1"/>
          </BoundingBox>
        </MetaboliteGlyph>
      </ListOfMetabGlyphs>
      <ListOfReactionGlyphs>
        <ReactionGlyph key="Layout_22" name="ReactionGlyph" reaction="Reaction_31">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="126.2272306543005" y="656.5078232050562"/>
                <End x="136.5783206347296" y="644.895204548189"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_24" name="MetabReferenceGlyph" metaboliteGlyph="Layout_23" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="126.2272306543005" y="656.5078232050562"/>
                    <End x="71.90894112345839" y="691.9309368244282"/>
                    <BasePoint1 x="115.8761406738713" y="668.1204418619235"/>
                    <BasePoint2 x="91.30476840355757" y="682.9288440073926"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_25" name="MetabReferenceGlyph" metaboliteGlyph="Layout_14" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="136.5783206347296" y="644.895204548189"/>
                    <End x="161.9047260750275" y="597.7832825169153"/>
                    <BasePoint1 x="146.9294106151588" y="633.2825858913217"/>
                    <BasePoint2 x="157.0048408402004" y="612.6297795399016"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_26" name="ReactionGlyph" reaction="Reaction_32">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="188.3197795207742" y="498.0343809425343"/>
                <End x="181.5444743291375" y="489.5728658886316"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_27" name="MetabReferenceGlyph" metaboliteGlyph="Layout_14" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="188.3197795207742" y="498.0343809425343"/>
                    <End x="176.5368961974552" y="559.7832825169153"/>
                    <BasePoint1 x="195.0950847124108" y="506.4958959964368"/>
                    <BasePoint2 x="187.5098167528422" y="535.2549680201518"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_29" name="MetabReferenceGlyph" metaboliteGlyph="Layout_28" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="181.5444743291375" y="489.5728658886316"/>
                    <End x="107.6667890113834" y="493.1790143186248"/>
                    <BasePoint1 x="174.7691691375009" y="481.111350834729"/>
                    <BasePoint2 x="139.524152776533" y="485.0298038132012"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_30" name="MetabReferenceGlyph" metaboliteGlyph="Layout_16" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="170.9759723422131" y="395.6941384134132"/>
                    <End x="192.7380722808862" y="487.5532460589565"/>
                    <BasePoint1 x="181.8570223115497" y="441.6236922361848"/>
                    <BasePoint2 x="200.5440176368166" y="481.30286870233"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_31" name="MetabReferenceGlyph" metaboliteGlyph="Layout_20" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="101.6944485519471" y="499.534518760934"/>
                    <End x="177.1261815690255" y="500.0540007722094"/>
                    <BasePoint1 x="139.4103150604863" y="499.7942597665717"/>
                    <BasePoint2 x="169.3202362130951" y="506.3043781288359"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_32" name="ReactionGlyph" reaction="Reaction_33">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="138.9017170704604" y="287.3997946606185"/>
                <End x="143.6830622190961" y="303.261880830714"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_34" name="MetabReferenceGlyph" metaboliteGlyph="Layout_33" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="138.9017170704604" y="287.3997946606185"/>
                    <End x="120.2515903993145" y="223.5732767124582"/>
                    <BasePoint1 x="134.1203719218247" y="271.537708490523"/>
                    <BasePoint2 x="125.9906448734107" y="243.5899710589667"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_35" name="MetabReferenceGlyph" metaboliteGlyph="Layout_16" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="143.6830622190961" y="303.261880830714"/>
                    <End x="160.530748331833" y="357.6941384134132"/>
                    <BasePoint1 x="148.4644073677319" y="319.1239670008095"/>
                    <BasePoint2 x="155.6929141369414" y="342.3745742496352"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_36" name="ReactionGlyph" reaction="Reaction_34">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="89.15724755126871" y="381.9642294723635"/>
                <End x="72.55977432699348" y="382.2291926123074"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_37" name="MetabReferenceGlyph" metaboliteGlyph="Layout_16" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="89.15724755126871" y="381.9642294723635"/>
                    <End x="143.4747322427525" y="378.590019842871"/>
                    <BasePoint1 x="105.754720775544" y="381.6992663324196"/>
                    <BasePoint2 x="128.764094815217" y="380.0784023026594"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_39" name="MetabReferenceGlyph" metaboliteGlyph="Layout_38" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="72.55977432699348" y="382.2291926123074"/>
                    <End x="6" y="379.6561824304714"/>
                    <BasePoint1 x="55.96230110271823" y="382.4941557522512"/>
                    <BasePoint2 x="26.8317822452903" y="381.1414098763473"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_40" name="ReactionGlyph" reaction="Reaction_35">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="830.615656126148" y="192.3200346266997"/>
                <End x="815.1867068350064" y="191.9105046382269"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_42" name="MetabReferenceGlyph" metaboliteGlyph="Layout_41" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="830.615656126148" y="192.3200346266997"/>
                    <End x="895.7006455249823" y="186.0008362833594"/>
                    <BasePoint1 x="846.0446054172896" y="192.7295646151725"/>
                    <BasePoint2 x="874.7298627939214" y="189.4675829463841"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_43" name="MetabReferenceGlyph" metaboliteGlyph="Layout_18" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="815.1867068350064" y="191.9105046382269"/>
                    <End x="825.9111526135662" y="196.6185233666788"/>
                    <BasePoint1 x="799.7577575438647" y="191.5009746497541"/>
                    <BasePoint2 x="808.97721775593" y="193.9573665110983"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_44" name="ReactionGlyph" reaction="Reaction_17">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="648.4356325454895" y="134.007237057978"/>
                <End x="637.4133911021014" y="144.7195208667426"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_46" name="MetabReferenceGlyph" metaboliteGlyph="Layout_45" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="648.4356325454895" y="134.007237057978"/>
                    <End x="669.2437261822472" y="68.59732282594115"/>
                    <BasePoint1 x="659.4578739888775" y="123.2949532492133"/>
                    <BasePoint2 x="667.1063604464093" y="93.26806708538604"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_47" name="MetabReferenceGlyph" metaboliteGlyph="Layout_2" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="637.4133911021014" y="144.7195208667426"/>
                    <End x="645.2974782101297" y="151.2201609135879"/>
                    <BasePoint1 x="626.3911496587134" y="155.4318046755073"/>
                    <BasePoint2 x="633.0887535735745" y="156.0040537467388"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_48" name="MetabReferenceGlyph" metaboliteGlyph="Layout_18" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="693.6753819260595" y="162.1602493047611"/>
                    <End x="649.8940299388861" y="146.5345585894108"/>
                    <BasePoint1 x="671.7847059324728" y="154.3474039470859"/>
                    <BasePoint2 x="656.8635480539767" y="153.7057382164612"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_49" name="ReactionGlyph" reaction="Reaction_18">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="517.5702060466265" y="250.8345926291692"/>
                <End x="521.6129314855364" y="260.3453208118407"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_50" name="MetabReferenceGlyph" metaboliteGlyph="Layout_2" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="517.5702060466265" y="250.8345926291692"/>
                    <End x="547.5857187352154" y="189.2201609135879"/>
                    <BasePoint1 x="513.5274806077165" y="241.3238644464976"/>
                    <BasePoint2 x="529.5459183117384" y="212.8943306343749"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_52" name="MetabReferenceGlyph" metaboliteGlyph="Layout_51" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="521.6129314855364" y="260.3453208118407"/>
                    <End x="594.9325609951422" y="265.6605313417596"/>
                    <BasePoint1 x="525.6556569244464" y="269.8560489945122"/>
                    <BasePoint2 x="561.3047903195218" y="270.1359722138038"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_53" name="MetabReferenceGlyph" metaboliteGlyph="Layout_6" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="414.4175860787097" y="290.3327774593698"/>
                    <End x="510.3884915748418" y="259.5019089456841"/>
                    <BasePoint1 x="462.4030388267757" y="274.9173432025269"/>
                    <BasePoint2 x="501.1854143836022" y="263.4138611708634"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_54" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="525.7042653042278" y="346.7965534687644"/>
                    <End x="510.3884915748418" y="259.5019089456841"/>
                    <BasePoint1 x="518.0463784395348" y="303.1492312072243"/>
                    <BasePoint2 x="501.1854143836022" y="263.4138611708634"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_55" name="ReactionGlyph" reaction="Reaction_19">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="501.3391867707597" y="76.05172861679098"/>
                <End x="494.7857036422052" y="89.70162764952504"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_57" name="MetabReferenceGlyph" metaboliteGlyph="Layout_56" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="501.3391867707597" y="76.05172861679098"/>
                    <End x="500.1572726389772" y="6"/>
                    <BasePoint1 x="507.8926698993143" y="62.40182958405693"/>
                    <BasePoint2 x="505.6633420512844" y="30.78844003384495"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_58" name="MetabReferenceGlyph" metaboliteGlyph="Layout_4" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="494.7857036422052" y="89.70162764952504"/>
                    <End x="464.566363100793" y="117.9989903273405"/>
                    <BasePoint1 x="488.2322205136507" y="103.3515266822591"/>
                    <BasePoint2 x="474.7609210250832" y="114.0877332629833"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_59" name="MetabReferenceGlyph" metaboliteGlyph="Layout_2" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="547.8914929114261" y="151.2201609135879"/>
                    <End x="507.0772811350042" y="87.20481089242435"/>
                    <BasePoint1 x="527.4843870232152" y="119.2124859030061"/>
                    <BasePoint2 x="516.0921170635258" y="91.53294365169069"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_60" name="ReactionGlyph" reaction="Reaction_20">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="372.7265634683864" y="90.94335764496908"/>
                <End x="359.6426069864585" y="81.03060341998126"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_61" name="MetabReferenceGlyph" metaboliteGlyph="Layout_4" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="372.7265634683864" y="90.94335764496908"/>
                    <End x="408.6046569773121" y="117.9989903273405"/>
                    <BasePoint1 x="385.8105199503142" y="100.8561118699569"/>
                    <BasePoint2 x="400.4785775842951" y="111.9057396548957"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_63" name="MetabReferenceGlyph" metaboliteGlyph="Layout_62" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="359.6426069864585" y="81.03060341998126"/>
                    <End x="308.5285626183528" y="42.07211053935645"/>
                    <BasePoint1 x="346.5586505045306" y="71.11784919499344"/>
                    <BasePoint2 x="324.2726174409597" y="54.11679131092799"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_64" name="ReactionGlyph" reaction="Reaction_21">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="438.5757884978881" y="226.6268744410833"/>
                <End x="430.4489752907794" y="233.9110745931045"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_65" name="MetabReferenceGlyph" metaboliteGlyph="Layout_4" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="438.5757884978881" y="226.6268744410833"/>
                    <End x="436.8295568921761" y="155.9989903273405"/>
                    <BasePoint1 x="446.7026017049969" y="219.3426742890621"/>
                    <BasePoint2 x="443.7977826003636" y="185.849782270196"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_67" name="MetabReferenceGlyph" metaboliteGlyph="Layout_66" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="430.4489752907794" y="233.9110745931045"/>
                    <End x="358.0999953665445" y="212.314359559091"/>
                    <BasePoint1 x="422.3221620836707" y="241.1952747451257"/>
                    <BasePoint2 x="388.1793754233304" y="228.5758671901136"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_68" name="MetabReferenceGlyph" metaboliteGlyph="Layout_6" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="387.8613128924112" y="283.8616148796044"/>
                    <End x="427.8379011401203" y="222.8224111042414"/>
                    <BasePoint1 x="407.8496070162657" y="253.3420129919229"/>
                    <BasePoint2 x="421.1634203859068" y="215.375847691389"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_69" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="516.005674712635" y="346.7965534687644"/>
                    <End x="441.1868626485473" y="237.7155379299464"/>
                    <BasePoint1 x="478.5962686805912" y="292.2560456993554"/>
                    <BasePoint2 x="447.8613434027608" y="245.1621013427988"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_70" name="ReactionGlyph" reaction="Reaction_22">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="428.2426714905338" y="360.9041973817225"/>
                <End x="429.3478580767459" y="350.63745166687"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_72" name="MetabReferenceGlyph" metaboliteGlyph="Layout_71" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="428.2426714905338" y="360.9041973817225"/>
                    <End x="369.8657202165895" y="402.5186467188582"/>
                    <BasePoint1 x="427.1374849043218" y="371.1709430965749"/>
                    <BasePoint2 x="398.2253059139026" y="389.4114813364297"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_73" name="MetabReferenceGlyph" metaboliteGlyph="Layout_6" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="429.3478580767459" y="350.63745166687"/>
                    <End x="403.2954600341727" y="321.8616148796044"/>
                    <BasePoint1 x="430.4530446629579" y="340.3707059520175"/>
                    <BasePoint2 x="417.1505489951184" y="328.5494739870978"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_74" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="490.0377997088658" y="361.9287543642834"/>
                    <End x="438.7378239049086" y="356.8411133264772"/>
                    <BasePoint1 x="464.3878118068872" y="359.3849338453803"/>
                    <BasePoint2 x="448.6803830261774" y="357.9114021286582"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_75" name="ReactionGlyph" reaction="Reaction_23">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="297.6972700871469" y="361.4764617577257"/>
                <End x="285.2676830687307" y="360.3424544984309"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_76" name="MetabReferenceGlyph" metaboliteGlyph="Layout_6" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="297.6972700871469" y="361.4764617577257"/>
                    <End x="354.6552824596861" y="321.8616148796044"/>
                    <BasePoint1 x="310.126857105563" y="362.6104690170205"/>
                    <BasePoint2 x="335.4984665372286" y="342.5195437631362"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_78" name="MetabReferenceGlyph" metaboliteGlyph="Layout_77" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="285.2676830687307" y="360.3424544984309"/>
                    <End x="252.886312620319" y="297.0215422866564"/>
                    <BasePoint1 x="272.8380960503145" y="359.2084472391361"/>
                    <BasePoint2 x="259.7548075807127" y="327.8314929480725"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_79" name="MetabReferenceGlyph" metaboliteGlyph="Layout_16" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="189.4747322427525" y="375.614365369734"/>
                    <End x="290.5739050140221" y="370.868097478574"/>
                    <BasePoint1 x="240.0243186283873" y="373.241231424154"/>
                    <BasePoint2 x="289.6653334501054" y="380.8267368290698"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_80" name="MetabReferenceGlyph" metaboliteGlyph="Layout_20" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="299.2157118222418" y="481.9049886694062"/>
                    <End x="290.5739050140221" y="370.868097478574"/>
                    <BasePoint1 x="294.8948084181319" y="426.3865430739901"/>
                    <BasePoint2 x="289.6653334501054" y="380.8267368290698"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_81" name="ReactionGlyph" reaction="Reaction_24">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="406.9723478552548" y="543.8520810772299"/>
                <End x="423.5018335392761" y="543.6877956025629"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_83" name="MetabReferenceGlyph" metaboliteGlyph="Layout_82" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="406.9723478552548" y="543.8520810772299"/>
                    <End x="345.599695025132" y="560.3587493145022"/>
                    <BasePoint1 x="390.4428621712335" y="544.0163665518969"/>
                    <BasePoint2 x="363.8889071771774" y="552.2286293018662"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_84" name="MetabReferenceGlyph" metaboliteGlyph="Layout_8" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="423.5018335392761" y="543.6877956025629"/>
                    <End x="458.394551865345" y="548.3547940143807"/>
                    <BasePoint1 x="440.0313192232974" y="543.5235101278959"/>
                    <BasePoint2 x="453.3453069653265" y="545.8980807024716"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_85" name="MetabReferenceGlyph" metaboliteGlyph="Layout_20" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="366.8557919531557" y="519.9049886694062"/>
                    <End x="415.1377062613851" y="533.7704322153968"/>
                    <BasePoint1 x="390.9967491072704" y="526.8377104424014"/>
                    <BasePoint2 x="415.0383218255047" y="523.7709260908972"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_86" name="ReactionGlyph" reaction="Reaction_25">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="574.8177266143738" y="596.1963349230924"/>
                <End x="589.5256283917448" y="604.0153478917592"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_87" name="MetabReferenceGlyph" metaboliteGlyph="Layout_8" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="574.8177266143738" y="596.1963349230924"/>
                    <End x="542.9831806105531" y="579.7202825474208"/>
                    <BasePoint1 x="560.1098248370029" y="588.3773219544257"/>
                    <BasePoint2 x="547.8695272794353" y="582.0940490087565"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_89" name="MetabReferenceGlyph" metaboliteGlyph="Layout_88" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="589.5256283917448" y="604.0153478917592"/>
                    <End x="646.9735696390546" y="635.8233856853653"/>
                    <BasePoint1 x="604.2335301691157" y="611.8343608604259"/>
                    <BasePoint2 x="629.280525348428" y="625.7836265150623"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_90" name="ReactionGlyph" reaction="Reaction_26">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="542.4790985582912" y="480.4984255610913"/>
                <End x="533.3720012165751" y="468.5423031463691"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_92" name="MetabReferenceGlyph" metaboliteGlyph="Layout_91" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="542.4790985582912" y="480.4984255610913"/>
                    <End x="614.6087731260277" y="485.9274035489139"/>
                    <BasePoint1 x="551.5861959000074" y="492.4545479758133"/>
                    <BasePoint2 x="585.3742588484465" y="492.1800063660442"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_93" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="533.3720012165751" y="468.5423031463691"/>
                    <End x="528.038951893536" y="384.7965534687644"/>
                    <BasePoint1 x="524.2649038748589" y="456.5861807316471"/>
                    <BasePoint2 x="523.8751535487684" y="417.7023364965252"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_94" name="MetabReferenceGlyph" metaboliteGlyph="Layout_12" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="464.2975193271457" y="606.8494174599342"/>
                    <End x="529.9704856491558" y="480.5798158936701"/>
                    <BasePoint1 x="497.1340024881507" y="543.7146166768022"/>
                    <BasePoint2 x="522.0154214108784" y="486.63926743361"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_95" name="MetabReferenceGlyph" metaboliteGlyph="Layout_8" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="511.22110568253" y="541.7202825474208"/>
                    <End x="529.9704856491558" y="480.5798158936701"/>
                    <BasePoint1 x="520.5957956658428" y="511.1500492205454"/>
                    <BasePoint2 x="522.0154214108784" y="486.63926743361"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_96" name="ReactionGlyph" reaction="Reaction_27">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="607.7620182876708" y="364.9992992283965"/>
                <End x="624.5338467280912" y="364.3784625790212"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_97" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="607.7620182876708" y="364.9992992283965"/>
                    <End x="568.0377997088658" y="365.6854958318703"/>
                    <BasePoint1 x="590.9901898472505" y="365.6201358777718"/>
                    <BasePoint2 x="575.3210376679531" y="365.8080250171648"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_99" name="MetabReferenceGlyph" metaboliteGlyph="Layout_98" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="624.5338467280912" y="364.3784625790212"/>
                    <End x="691.2560841130694" y="360.0017441459501"/>
                    <BasePoint1 x="641.3056751685116" y="363.7576259296459"/>
                    <BasePoint2 x="670.4738367508955" y="361.7244758754542"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_100" name="ReactionGlyph" reaction="Reaction_28">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="490.020095468316" y="419.2363370721466"/>
                <End x="479.2894109336907" y="428.8983314165401"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_101" name="MetabReferenceGlyph" metaboliteGlyph="Layout_10" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="490.020095468316" y="419.2363370721466"/>
                    <End x="516.7609491983707" y="384.7965534687644"/>
                    <BasePoint1 x="500.7507800029413" y="409.574342727753"/>
                    <BasePoint2 x="511.4385357343124" y="394.7699495121603"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_103" name="MetabReferenceGlyph" metaboliteGlyph="Layout_102" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="479.2894109336907" y="428.8983314165401"/>
                    <End x="427.2309543626125" y="459.6145497854145"/>
                    <BasePoint1 x="468.5587263990654" y="438.5603257609337"/>
                    <BasePoint2 x="445.2121692471826" y="451.5029363592724"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_104" name="ReactionGlyph" reaction="Reaction_29">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="356.734502011839" y="634.8096271112775"/>
                <End x="369.9986159737466" y="627.1411421809257"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_106" name="MetabReferenceGlyph" metaboliteGlyph="Layout_105" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="356.734502011839" y="634.8096271112775"/>
                    <End x="323.7613916807462" y="697.0342667634518"/>
                    <BasePoint1 x="343.4703880499313" y="642.4781120416292"/>
                    <BasePoint2 x="330.2998613748618" y="671.6733106351285"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_107" name="MetabReferenceGlyph" metaboliteGlyph="Layout_12" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="369.9986159737466" y="627.1411421809257"/>
                    <End x="423.4155972759118" y="623.0711799288331"/>
                    <BasePoint1 x="383.2627299356542" y="619.472657250574"/>
                    <BasePoint2 x="406.6551920962598" y="619.3547973571156"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_108" name="MetabReferenceGlyph" metaboliteGlyph="Layout_20" role="modifier">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="309.7187878338239" y="519.9049886694062"/>
                    <End x="358.3614468056434" y="622.3180841434016"/>
                    <BasePoint1 x="334.0401173197337" y="571.111536406404"/>
                    <BasePoint2 x="353.3563346184941" y="613.6607836407017"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_109" name="ReactionGlyph" reaction="Reaction_30">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="473.8847498510983" y="701.0037079315947"/>
                <End x="478.889057523871" y="716.7041980856587"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_110" name="MetabReferenceGlyph" metaboliteGlyph="Layout_12" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="473.8847498510983" y="701.0037079315947"/>
                    <End x="459.0382126794307" y="644.8494174599342"/>
                    <BasePoint1 x="468.8804421783256" y="685.3032177775306"/>
                    <BasePoint2 x="462.708250510685" y="661.1511950802164"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_112" name="MetabReferenceGlyph" metaboliteGlyph="Layout_111" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="478.889057523871" y="716.7041980856587"/>
                    <End x="502.2166516789432" y="777.3543190005754"/>
                    <BasePoint1 x="483.8933651966437" y="732.4046882397229"/>
                    <BasePoint2 x="494.3060853559866" y="758.8046261586651"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
      </ListOfReactionGlyphs>
      <ListOfTextGlyphs>
        <TextGlyph key="Layout_3" name="TextGlyph" graphicalObject="Layout_2" originOfText="Metabolite_15">
          <BoundingBox>
            <Position x="470.0053066060423" y="156.2201609135879"/>
            <Dimensions width="176" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_5" name="TextGlyph" graphicalObject="Layout_4" originOfText="Metabolite_17">
          <BoundingBox>
            <Position x="383.8681274376316" y="122.9989903273405"/>
            <Dimensions width="96" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_7" name="TextGlyph" graphicalObject="Layout_6" originOfText="Metabolite_19">
          <BoundingBox>
            <Position x="341.4175860787097" y="288.8616148796044"/>
            <Dimensions width="64" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_9" name="TextGlyph" graphicalObject="Layout_8" originOfText="Metabolite_21">
          <BoundingBox>
            <Position x="463.394551865345" y="546.7202825474208"/>
            <Dimensions width="80" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_11" name="TextGlyph" graphicalObject="Layout_10" originOfText="Metabolite_23">
          <BoundingBox>
            <Position x="495.0377997088658" y="351.7965534687644"/>
            <Dimensions width="64" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_13" name="TextGlyph" graphicalObject="Layout_12" originOfText="Metabolite_25">
          <BoundingBox>
            <Position x="428.4155972759118" y="611.8494174599342"/>
            <Dimensions width="48" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_15" name="TextGlyph" graphicalObject="Layout_14" originOfText="Metabolite_27">
          <BoundingBox>
            <Position x="127.9198409277499" y="564.7832825169153"/>
            <Dimensions width="80" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_17" name="TextGlyph" graphicalObject="Layout_16" originOfText="Metabolite_29">
          <BoundingBox>
            <Position x="148.4747322427525" y="362.6941384134132"/>
            <Dimensions width="32" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_19" name="TextGlyph" graphicalObject="Layout_18" originOfText="Metabolite_31">
          <BoundingBox>
            <Position x="672.9111526135662" y="167.1602493047611"/>
            <Dimensions width="144" height="24"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_21" name="TextGlyph" graphicalObject="Layout_20" originOfText="Metabolite_33">
          <BoundingBox>
            <Position x="106.6944485519471" y="486.9049886694062"/>
            <Dimensions width="384" height="24"/>
          </BoundingBox>
        </TextGlyph>
      </ListOfTextGlyphs>
      <ListOfAdditionalGraphicalObjects>
        <AdditionalGraphicalObject key="Layout_113" name="GeneralGlyph" objectRole="rule">
          <BoundingBox>
            <Position x="299.0719682546477" y="525.7231922093972"/>
            <Dimensions width="10" height="10"/>
          </BoundingBox>
        </AdditionalGraphicalObject>
      </ListOfAdditionalGraphicalObjects>
    </Layout>
  </ListOfLayouts>
  <SBMLReference file="BIOMD0000000111.xml">
    <SBMLMap SBMLid="IEP" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="J10" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="J15" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="J16" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="J3" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="J4" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="J5" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="J7" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="J8" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="J9" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="Ja25" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="Jawee" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="Ji25" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="Jiwee" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="Kdiss" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="M" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="MPF" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="R1" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="R10" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="R11" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="R12" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="R13" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="R14" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="R15" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="R16" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="R17" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="R18" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="R19" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="R2" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="R3" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="R4" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="R5" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="R6" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="R7" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="R8" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="R9" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="SK" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="TF" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="Trimer" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="Va25" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="Vawee" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="Vi25" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="Viwee" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="cdc13T" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="cell" COPASIkey="Compartment_5"/>
    <SBMLMap SBMLid="flag_MPF" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="k1" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="k10" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="k11" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="k12" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="k12_double_prime" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="k12_prime" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="k13" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="k14" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="k15" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="k16_double_prime" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="k16_prime" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="k25" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="k25_double_prime" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="k25_prime" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="k2_double_prime" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="k2_prime" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="k2_triple_prime" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="k3_double_prime" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="k3_prime" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="k4" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="k4_prime" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="k5_double_prime" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="k5_prime" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="k6" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="k7" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="k8" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="k9" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="kwee" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="kwee_double_prime" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="kwee_prime" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="mu" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="preMPF" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="rum1T" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="sigma" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="slp1" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="slp1T" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="ste9" COPASIkey="Metabolite_19"/>
  </SBMLReference>
</COPASI>
