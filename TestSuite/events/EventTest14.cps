<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.12.70+ (Debug) (http://www.copasi.org) at 2014-02-04 22:13:02 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="12" versionDevel="70" copasiSourcesModified="1">
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
    <Function key="Function_40" name="function_4_cdc13T synthesis" type="UserDefined" reversible="false">
      <Expression>
        k1*M
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_254" name="M" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_264" name="k1" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="function_4_Targeting cdc13T to APC core" type="UserDefined" reversible="false">
      <Expression>
        (k2_prime+k2_double_prime*(ste9*cell)+k2_triple_prime*(slp1*cell))*cdc13T
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_274" name="cdc13T" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_268" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_258" name="k2_double_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_246" name="k2_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_270" name="k2_triple_prime" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_272" name="slp1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_266" name="ste9" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="function_4_wee1 dependent MPF inactivation" type="UserDefined" reversible="false">
      <Expression>
        kwee*(cdc13T*cell-preMPF*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_271" name="cdc13T" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_267" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_275" name="kwee" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_262" name="preMPF" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="function_4_preMPF inactivation" type="UserDefined" reversible="false">
      <Expression>
        (k2_prime+k2_double_prime*(ste9*cell)+k2_triple_prime*(slp1*cell))*preMPF
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_279" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_269" name="k2_double_prime" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_276" name="k2_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_281" name="k2_triple_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_285" name="preMPF" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_283" name="slp1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_277" name="ste9" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="function_4_slp1 dependent ste9 activation" type="UserDefined" reversible="false">
      <Expression>
        (k3_prime+k3_double_prime*(slp1*cell))*(1-ste9*cell)/(J3+1-ste9*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_290" name="J3" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_265" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_282" name="k3_double_prime" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_286" name="k3_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_278" name="slp1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_288" name="ste9" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="function_4_ste9 phosphorylation (inactivation) by starter kinase" type="UserDefined" reversible="false">
      <Expression>
        (k4_prime*(SK*cell)+k4*(MPF*cell))*ste9/(J4+ste9*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_298" name="J4" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_294" name="MPF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_287" name="SK" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_280" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_292" name="k4" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_291" name="k4_prime" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_296" name="ste9" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="function_4_slp1T activation by MPF" type="UserDefined" reversible="false">
      <Expression>
        (k5_prime+k5_double_prime*(MPF*cell)^4/(J5^4+(MPF*cell)^4))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_301" name="J5" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="MPF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_289" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_295" name="k5_double_prime" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_299" name="k5_prime" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="function_4_slp1 activation by intermediary enzyme" type="UserDefined" reversible="false">
      <Expression>
        k7*IEP*(slp1T*cell-slp1*cell)/(J7+slp1T*cell-slp1*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_273" name="IEP" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_308" name="J7" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_304" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_302" name="k7" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_306" name="slp1" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_297" name="slp1T" order="5" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="function_4_slp1 inactivation" type="UserDefined" reversible="false">
      <Expression>
        k8*slp1/(J8+slp1*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_293" name="J8" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_310" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_309" name="k8" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_305" name="slp1" order="3" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="function_4_Intermediary enzyme activation" type="UserDefined" reversible="false">
      <Expression>
        k9*MPF*(1-IEP*cell)/(J9+1-IEP*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_312" name="IEP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_316" name="J9" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="MPF" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_314" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_311" name="k9" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_IEP inactivation" type="UserDefined" reversible="false">
      <Expression>
        k10*IEP/(J10+IEP*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_313" name="IEP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_300" name="J10" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_319" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_317" name="k10" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_rum1T activation" type="UserDefined" reversible="false">
      <Expression>
        k11/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_307" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_320" name="k11" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_SK dependent rum1T inactivation" type="UserDefined" reversible="false">
      <Expression>
        (k12+k12_prime*(SK*cell)+k12_double_prime*(MPF*cell))*rum1T
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_329" name="MPF" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_323" name="SK" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_325" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_315" name="k12" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_327" name="k12_double_prime" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_321" name="k12_prime" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_331" name="rum1T" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_SK synthesis" type="UserDefined" reversible="false">
      <Expression>
        k13*TF/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_328" name="TF" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_324" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_332" name="k13" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_Cell growth" type="UserDefined" reversible="false">
      <Expression>
        mu*M
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_330" name="M" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_322" name="mu" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_4" name="Novak2001_FissionYeast_CellCycle" simulationType="time" timeUnit="min" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="dimensionless" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_4">
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
      <Compartment key="Compartment_1" name="cell" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
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
      <Metabolite key="Metabolite_1" name="Total cdc13" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="preMPF" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P04551" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="ste9" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:O13286" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="slp1T" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P78972" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="slp1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P78972" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="IEP" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_13" name="rum1T" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P40380" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="SK" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24865" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="Cell Mass" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_19" name="M-phase promoting factor" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:interpro:IPR015454" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P04551" />
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
      <ModelValue key="ModelValue_0" name="flag_MPF" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_1" name="sigma" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Kdiss],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="Kdiss" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_3" name="Trimer" simulationType="assignment">
        <Expression>
          2*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[sigma],Reference=Value&gt;^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Total cdc13],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[rum1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))^0.5)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="TF" simulationType="assignment">
        <Expression>
          2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J15],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J15],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_prime],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k16_double_prime],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;))*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k15],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[J16],Reference=Value&gt;)^(1/2))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="k15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_6" name="J16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_7" name="k16_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="k16_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_9" name="J15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_10" name="kwee" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_prime],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_double_prime],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[kwee_prime],Reference=Value&gt;)*(2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jawee],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vawee],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Jiwee],Reference=Value&gt;)^(1/2)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="kwee_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_12" name="kwee_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_13" name="Vawee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_14" name="Jiwee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_15" name="Viwee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_16" name="Jawee" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_17" name="k25" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_prime],Reference=Value&gt;+(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_double_prime],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[k25_prime],Reference=Value&gt;)*(2*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Va25],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;/(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ja25],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;+((&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ja25],Reference=Value&gt;+&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;)^2-4*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Vi25],Reference=Value&gt;-&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Va25],Reference=Value&gt;*(&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[M-phase promoting factor],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;)*&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Ji25],Reference=Value&gt;)^(1/2)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="k25_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_19" name="k25_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="Va25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_21" name="Ji25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="Vi25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="Ja25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_24" name="k1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_25" name="k2_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="k2_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_27" name="k2_triple_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_28" name="k3_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_29" name="k3_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_30" name="J3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_31" name="k4_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_32" name="k4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_33" name="J4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_34" name="k5_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_35" name="k5_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_36" name="J5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_37" name="k6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_38" name="k7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_39" name="J7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_40" name="k8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_41" name="J8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_42" name="k9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_43" name="J9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_44" name="k10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_45" name="J10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_46" name="k11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_47" name="k12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_48" name="k12_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_49" name="k12_double_prime" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_50" name="k13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_51" name="k14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_52" name="mu" simulationType="fixed">
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="cdc13T synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
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
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4065" name="k1" value="0.03"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Targeting cdc13T to APC core" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
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
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4066" name="k2_double_prime" value="1"/>
          <Constant key="Parameter_4067" name="k2_prime" value="0.03"/>
          <Constant key="Parameter_4068" name="k2_triple_prime" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_41">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="wee1 dependent MPF inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
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
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4069" name="kwee" value="1.25627"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="cdc25 dependent preMPF phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004725" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0010389" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_6257.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4070" name="k1" value="0.238217"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="preMPF inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0000216" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007092" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4071" name="k2_double_prime" value="1"/>
          <Constant key="Parameter_4072" name="k2_prime" value="0.03"/>
          <Constant key="Parameter_4073" name="k2_triple_prime" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_43">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="slp1 dependent ste9 activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0035307" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4074" name="J3" value="0.01"/>
          <Constant key="Parameter_4075" name="k3_double_prime" value="10"/>
          <Constant key="Parameter_4076" name="k3_prime" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_44">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="ste9 phosphorylation (inactivation) by starter kinase" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4077" name="J4" value="0.01"/>
          <Constant key="Parameter_4078" name="k4" value="35"/>
          <Constant key="Parameter_4079" name="k4_prime" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_45">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="slp1T activation by MPF" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4080" name="J5" value="0.3"/>
          <Constant key="Parameter_4081" name="k5_double_prime" value="0.3"/>
          <Constant key="Parameter_4082" name="k5_prime" value="0.005"/>
        </ListOfConstants>
        <KineticLaw function="Function_46">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="slp1T inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4083" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="slp1 activation by intermediary enzyme" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051443" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4084" name="J7" value="0.001"/>
          <Constant key="Parameter_4085" name="k7" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_47">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="slp1 inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4086" name="J8" value="0.001"/>
          <Constant key="Parameter_4087" name="k8" value="0.25"/>
        </ListOfConstants>
        <KineticLaw function="Function_48">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="slp1 inactivation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4088" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="Intermediary enzyme activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4089" name="J9" value="0.01"/>
          <Constant key="Parameter_4090" name="k9" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_49">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="IEP inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4091" name="J10" value="0.01"/>
          <Constant key="Parameter_4094" name="k10" value="0.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_50">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="rum1T activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031657" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4093" name="k11" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="SK dependent rum1T inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031657" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4095" name="k12" value="0.01"/>
          <Constant key="Parameter_4092" name="k12_double_prime" value="3"/>
          <Constant key="Parameter_4096" name="k12_prime" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_52">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="SK synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4097" name="TF" value="0.880381"/>
          <Constant key="Parameter_4098" name="k13" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_53">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="SK degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4099" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="Cell growth" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0016049" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4100" name="mu" value="0.005"/>
        </ListOfConstants>
        <KineticLaw function="Function_54">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_0" name="event_0000001" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_0">
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
          <Assignment targetKey="Metabolite_17">
            <Expression>
              &lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Vector=Metabolites[Cell Mass],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Values[Viwee],Reference=Value&gt;/2/&lt;CN=Root,Model=Novak2001_FissionYeast_CellCycle,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_0">
            <Expression>
              0
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_1" name="event_0000002" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
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
          <Assignment targetKey="ModelValue_0">
            <Expression>
              1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
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
      <StateTemplateVariable objectReference="Model_4"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_30"/>
      <StateTemplateVariable objectReference="ModelValue_31"/>
      <StateTemplateVariable objectReference="ModelValue_32"/>
      <StateTemplateVariable objectReference="ModelValue_33"/>
      <StateTemplateVariable objectReference="ModelValue_34"/>
      <StateTemplateVariable objectReference="ModelValue_35"/>
      <StateTemplateVariable objectReference="ModelValue_36"/>
      <StateTemplateVariable objectReference="ModelValue_37"/>
      <StateTemplateVariable objectReference="ModelValue_38"/>
      <StateTemplateVariable objectReference="ModelValue_39"/>
      <StateTemplateVariable objectReference="ModelValue_40"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
      <StateTemplateVariable objectReference="ModelValue_48"/>
      <StateTemplateVariable objectReference="ModelValue_49"/>
      <StateTemplateVariable objectReference="ModelValue_50"/>
      <StateTemplateVariable objectReference="ModelValue_51"/>
      <StateTemplateVariable objectReference="ModelValue_52"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 2.2 1 0 0.2 0 0 0 1 0.2 0.201 0 0.8803808142671367 1.256272780429718 0.2382171624981674 1 0 0.001 1.5 0.01 1 2 0.01 0.15 1.3 0.25 0.01 1 0.01 0.05 5 1 0.01 0.25 0.01 0.03 0.03 1 0.1 1 10 0.01 2 35 0.01 0.005 0.3 0.3 0.1 1 0.001 0.25 0.001 0.1 0.01 0.04 0.01 0.1 0.01 1 3 0.1 0.1 0.005 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_12" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_11" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_0" target="EventTest14.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="1000"/>
        <Parameter name="StepSize" type="float" value="0.5"/>
        <Parameter name="Duration" type="float" value="500"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_9" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_8" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_7" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_6" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_5" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_4" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_2" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_3" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_2" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_1" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
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
    <Task key="Task_13" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_8" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_7" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_6" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_5" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_4" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_1" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_0" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="7">
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
    <Report key="Report_18" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
  <SBMLReference file="BIOMD0000000111.xml">
    <SBMLMap SBMLid="IEP" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="J10" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="J15" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="J16" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="J3" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="J4" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="J5" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="J7" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="J8" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="J9" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="Ja25" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="Jawee" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="Ji25" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="Jiwee" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="Kdiss" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="M" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="MPF" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="R1" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="R10" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="R11" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="R12" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="R13" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="R14" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="R15" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="R16" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="R17" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="R18" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="R19" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="R2" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="R3" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="R4" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="R5" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="R6" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="R7" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="R8" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="R9" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="SK" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="TF" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="Trimer" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="Va25" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="Vawee" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="Vi25" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="Viwee" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="cdc13T" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="cell" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="flag_MPF" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="k1" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="k10" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="k11" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="k12" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="k12_double_prime" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="k12_prime" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="k13" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="k14" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="k15" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="k16_double_prime" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="k16_prime" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="k25" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="k25_double_prime" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="k25_prime" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="k2_double_prime" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="k2_prime" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="k2_triple_prime" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="k3_double_prime" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="k3_prime" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="k4" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="k4_prime" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="k5_double_prime" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="k5_prime" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="k6" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="k7" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="k8" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="k9" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="kwee" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="kwee_double_prime" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="kwee_prime" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="mu" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="preMPF" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="rum1T" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="sigma" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="slp1" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="slp1T" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="ste9" COPASIkey="Metabolite_5"/>
  </SBMLReference>
</COPASI>
