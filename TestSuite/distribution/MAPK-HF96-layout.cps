<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.12 (Build 79) (http://www.copasi.org) at 2014-04-15 07:36:25 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="12" versionDevel="79" copasiSourcesModified="0">
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
        <body xmlns="http://www.w3.org/1999/xhtml">
<b>Mass action rate law for first order irreversible reactions</b>
<p>
Reaction scheme where the products are created from the reactants and the change of a product quantity is proportional to the product of reactant activities. The reaction scheme does not include any reverse process that creates the reactants from the products. The change of a product quantity is proportional to the quantity of one reactant.
</p>
</body>
      </Comment>
      <Expression>
        k1*PRODUCT&lt;substrate_i&gt;
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_14" name="Mass action (reversible)" type="MassAction" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
   <rdf:Description rdf:about="#Function_14">
   <CopasiMT:is rdf:resource="urn:miriam:obo.sbo:SBO:0000042" />
   </rdf:Description>
   </rdf:RDF>
      </MiriamAnnotation>
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
<b>Mass action rate law for reversible reactions</b>
<p>
Reaction scheme where the products are created from the reactants and the change of a product quantity is proportional to the product of reactant activities. The reaction scheme does include a reverse process that creates the reactants from the products.
</p>
</body>
      </Comment>
      <Expression>
        k1*PRODUCT&lt;substrate_i&gt;-k2*PRODUCT&lt;product_j&gt;
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_62" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_39" name="substrate" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_67" name="k2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_71" name="product" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_11" name="MAPK cascade" simulationType="time" timeUnit="s" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="µmol" type="deterministic" avogadroConstant="6.0221415e+023">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_11">
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:8816754"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2005-02-10T23:39:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>raim@tbi.univie.ac.at</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Machne</vCard:Family>
                <vCard:Given>Rainer</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>University of Vienna</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>pedro.mendes@manchester.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Mendes</vCard:Family>
                <vCard:Given>Pedro</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>University of Manchester</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:creator>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2008-12-04T01:05:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:BIOMD0000000009"/>
        <rdf:li rdf:resource="urn:miriam:taxonomy:8355"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_634"/>
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0000165"/>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1" /></head><body style="font-family:DejaVu Sans">
<p><span style="font-weight:600">MAPK cascade model</span> from Huang and Ferrell (1996) Ultrasensitivity in the mitogen-activated protein kinase cascade. <span style="font-style:italic">Proc. Natl. Acad. Sci. USA 93</span>, 10078-83 </p>
<p>This COPASI file simulates a time course and includes a network diagram that can be used to visualize the results (under Model/Biochemical/Diagrams). </p>
<p style="margin-top:14px">This model was altered trivially from the original in Biomodels (BIOMD0000000009), by renaming the species &quot;MAPKKK activator&quot; to E1 and &quot;MAPKKK inactivator&quot; to E2, to conform with the notation of the original paper. The diagram was constructed with SBW&apos;s Network Layout tool.</p>
<p style="margin-top:14px">This model originated from BioModels Database: A Database of Annotated Published Models. It is copyright (c) 2005-2008 The BioModels Team. For more information see the <a href="http://www.ebi.ac.uk/biomodels/legal.html">terms of use</a>. </p>
<p>      </p>
</body></html>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_6" name="compartment" simulationType="fixed" dimensionality="3">
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_33" name="E1" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:interpro:IPR003577" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="E2" simulationType="reactions" compartment="Compartment_6">
      </Metabolite>
      <Metabolite key="Metabolite_9" name="MAPKKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P12965" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="P-MAPKKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P12965" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:Q05116" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_49" name="P-MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_49">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:Q05116" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_51" name="PP-MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_51">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:Q05116" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_53">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P26696" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_55" name="P-MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_55">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P26696" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_57" name="PP-MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_57">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P26696" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_59" name="MAPK-Pase" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_59">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q90W58" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_61" name="MAPKK-Pase" simulationType="reactions" compartment="Compartment_6">
      </Metabolite>
      <Metabolite key="Metabolite_63" name="MAPKKK_E1" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_63">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P12965" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_65" name="P-MAPKKK_E2" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_65">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:uniprot:P12965" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_67" name="P-MAPKKK_MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_67">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P12965" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q05116" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_69" name="P-MAPKKK_P-MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_69">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P12965" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q05116" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_71" name="PP-MAPKK_MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_71">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P26696" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q05116" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_73" name="PP-MAPKK_P-MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_73">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P26696" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q05116" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_75" name="MAPKK-Pase_PP-MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_75">
    <CopasiMT:hasPart rdf:resource="urn:miriam:uniprot:Q05116" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_77" name="MAPKK-Pase_P-MAPKK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_77">
    <CopasiMT:hasPart rdf:resource="urn:miriam:uniprot:Q05116" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_79" name="MAPK-Pase_PP-MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_79">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P26696" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q90W58" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_81" name="MAPK-Pase_P-MAPK" simulationType="reactions" compartment="Compartment_6">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_81">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P26696" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q90W58" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_15" name="MAPKKK_phosphorylation_ratio" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK],Reference=Concentration&gt;/(&lt;CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK],Reference=Concentration&gt;+&lt;CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKKK],Reference=Concentration&gt;)
        </Expression>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_11" name="binding of MAPKKK activator" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_996" />
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0031435" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4271" name="k1" value="1000"/>
          <Constant key="Parameter_4269" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4271"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4269"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="MAPKKK activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_525" />
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.1" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0000185" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0008349" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4267" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4267"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="binding of MAPKKK inactivator" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0031435" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4268" name="k1" value="1000"/>
          <Constant key="Parameter_4266" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4268"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_15"/>
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4266"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="MAPKKK inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.16" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006470" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0051390" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4265" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4265"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="binding P-MAPKKK and MAPKK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_143" />
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031434" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031435" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4276" name="k1" value="1000"/>
          <Constant key="Parameter_4275" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4276"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_23"/>
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4275"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="phosphorylation of MAPKK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_614" />
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.25" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0004709" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4274" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4274"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="binding MAPKK-Pase and P-MAPKK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0031434" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4273" name="k1" value="1000"/>
          <Constant key="Parameter_4272" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4273"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_49"/>
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4272"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="dephosphorylation of P-MAPKK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.16" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4270" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4270"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="binding P-MAPKKK and P-MAPKK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_143" />
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031434" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031435" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4282" name="k1" value="1000"/>
          <Constant key="Parameter_4281" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4282"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_49"/>
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4281"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="phosphorylation of P-MAPKK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_614" />
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.25" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0000186" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0004709" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4278" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4278"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="binding MAPKK-Pase and PP-MAPKK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0031434" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_75" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4279" name="k1" value="1000"/>
          <Constant key="Parameter_4277" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4279"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_51"/>
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4277"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_75"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_0" name="dephosphorylation of PP-MAPKK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.16" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006470" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0051389" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_75" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4280" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4280"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_75"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="binding MAPK and PP-MAPKK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1780" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_495" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031434" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0051019" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_71" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4288" name="k1" value="1000"/>
          <Constant key="Parameter_4287" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4288"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_53"/>
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4287"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="phosphorylation of MAPK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_136" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2247" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.12.2" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0004708" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_71" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4286" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4286"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="binding MAPK-Pase and P-MAPK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0051019" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4285" name="k1" value="1000"/>
          <Constant key="Parameter_4284" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4285"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_55"/>
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4284"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="dephosphorylation of P-MAPK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.16" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4283" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_4283"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="binding PP-MAPKK and P-MAPK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1780" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_495" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0031434" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0051019" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4102" name="k1" value="1000"/>
          <Constant key="Parameter_4103" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_4102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_55"/>
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_4103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="phosphorylation of P-MAPK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_136" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2247" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.12.2" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0000187" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0004708" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3861" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_3861"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="binding MAPK-Pase and PP-MAPK" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO:0051019" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3862" name="k1" value="1000"/>
          <Constant key="Parameter_3863" name="k2" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="Parameter_3862"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_57"/>
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="Parameter_3863"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="dephosphorylation of PP-MAPK" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.16" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0000188" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO:0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3864" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_3864"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=MAPK cascade" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment]" value="4e-012" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[E1]" value="72.265698" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[E2]" value="722.6569799999999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKKK]" value="7226.569799999999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKK]" value="2890627.92" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[PP-MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPK]" value="2890627.92" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[PP-MAPK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPK-Pase]" value="289062.792" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKK-Pase]" value="722.6569799999999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKKK_E1]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK_E2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK_MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[P-MAPKKK_P-MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[PP-MAPKK_MAPK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[PP-MAPKK_P-MAPK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKK-Pase_PP-MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPKK-Pase_P-MAPKK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPK-Pase_PP-MAPK]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Compartments[compartment],Vector=Metabolites[MAPK-Pase_P-MAPK]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Values[MAPKKK_phosphorylation_ratio]" value="0" type="ModelValue" simulationType="assignment"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK activator]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK activator],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK activator],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[MAPKKK activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[MAPKKK activation],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK inactivator]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK inactivator],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding of MAPKKK inactivator],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[MAPKKK inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[MAPKKK inactivation],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and MAPKK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and MAPKK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of MAPKK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and P-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and P-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and P-MAPKK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of P-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of P-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and P-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and P-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding P-MAPKKK and P-MAPKK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of P-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of P-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and PP-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and PP-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPKK-Pase and PP-MAPKK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of PP-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of PP-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK and PP-MAPKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK and PP-MAPKK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK and PP-MAPKK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of MAPK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and P-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and P-MAPK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and P-MAPK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of P-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of P-MAPK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding PP-MAPKK and P-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding PP-MAPKK and P-MAPK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding PP-MAPKK and P-MAPK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of P-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[phosphorylation of P-MAPK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and PP-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and PP-MAPK],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[binding MAPK-Pase and PP-MAPK],ParameterGroup=Parameters,Parameter=k2" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of PP-MAPK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=MAPK cascade,Vector=Reactions[dephosphorylation of PP-MAPK],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_11"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_59"/>
      <StateTemplateVariable objectReference="Metabolite_61"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_67"/>
      <StateTemplateVariable objectReference="Metabolite_57"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_71"/>
      <StateTemplateVariable objectReference="Metabolite_75"/>
      <StateTemplateVariable objectReference="Metabolite_79"/>
      <StateTemplateVariable objectReference="Metabolite_69"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_81"/>
      <StateTemplateVariable objectReference="Metabolite_73"/>
      <StateTemplateVariable objectReference="Metabolite_77"/>
      <StateTemplateVariable objectReference="Metabolite_63"/>
      <StateTemplateVariable objectReference="Metabolite_65"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="Compartment_6"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 289062.792 722.6569799999999 0 0 7226.569799999999 0 0 722.6569799999999 0 0 0 0 2890627.92 2890627.92 72.265698 0 0 0 0 0 0 4e-012 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_26" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1e-009"/>
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
    <Task key="Task_15" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_17" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_19" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_22" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="1e-006"/>
      </Method>
    </Task>
    <Task key="Task_23" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="Delta minimum" type="unsignedFloat" value="1e-012"/>
      </Method>
    </Task>
    <Task key="Task_24" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_25" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
        <Parameter name="ConvergenceTolerance" type="float" value="1e-006"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-006"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_27" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_26"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_9" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_11" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_12" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_14" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_15" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_16" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_17" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
  <GUI>
  </GUI>
  <ListOfLayouts xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <Layout key="Layout_140" name="layout_0">
      <Dimensions width="924.8503771136993" height="742.5632675405108"/>
      <ListOfMetabGlyphs>
        <MetaboliteGlyph key="Layout_2" name="sGlyph_0" metabolite="Metabolite_33">
          <BoundingBox>
            <Position x="296.2970630279131" y="88.34966316248098"/>
            <Dimensions width="41" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_4" name="sGlyph_1" metabolite="Metabolite_29">
          <BoundingBox>
            <Position x="373.3214208477608" y="155.9030708831204"/>
            <Dimensions width="41" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_6" name="sGlyph_2" metabolite="Metabolite_9">
          <BoundingBox>
            <Position x="334.8806978727152" y="0"/>
            <Dimensions width="73" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_8" name="sGlyph_3" metabolite="Metabolite_15">
          <BoundingBox>
            <Position x="289.4537483815041" y="286.9616708655706"/>
            <Dimensions width="89" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_10" name="sGlyph_4" metabolite="Metabolite_23">
          <BoundingBox>
            <Position x="102.9045723194321" y="465.986786497818"/>
            <Dimensions width="65" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_12" name="sGlyph_5" metabolite="Metabolite_49">
          <BoundingBox>
            <Position x="207.1799601310985" y="446.0135355708081"/>
            <Dimensions width="81" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_14" name="sGlyph_6" metabolite="Metabolite_51">
          <BoundingBox>
            <Position x="480.7684650375474" y="510.0723007241212"/>
            <Dimensions width="89" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_16" name="sGlyph_7" metabolite="Metabolite_53">
          <BoundingBox>
            <Position x="681.7200427387072" y="673.7508193326802"/>
            <Dimensions width="57" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_18" name="sGlyph_8" metabolite="Metabolite_55">
          <BoundingBox>
            <Position x="672.6619627073005" y="566.6902994637381"/>
            <Dimensions width="73" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_20" name="sGlyph_9" metabolite="Metabolite_57">
          <BoundingBox>
            <Position x="690.8328812568292" y="290.166672928395"/>
            <Dimensions width="81" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_24" name="sGlyph_10" metabolite="Metabolite_59">
          <BoundingBox>
            <Position x="829.5429520541562" y="520.0930352556493"/>
            <Dimensions width="97" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_28" name="sGlyph_11" metabolite="Metabolite_61">
          <BoundingBox>
            <Position x="221.1045850264778" y="633.8044484649134"/>
            <Dimensions width="105" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_31" name="sGlyph_12" metabolite="Metabolite_63">
          <BoundingBox>
            <Position x="141.0196229998448" y="88.71491496538314"/>
            <Dimensions width="97" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_37" name="sGlyph_13" metabolite="Metabolite_65">
          <BoundingBox>
            <Position x="465.2483264022186" y="182.1359716170413"/>
            <Dimensions width="113" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_43" name="sGlyph_14" metabolite="Metabolite_67">
          <BoundingBox>
            <Position x="66.07729152763226" y="297.3201612924149"/>
            <Dimensions width="137" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_49" name="sGlyph_15" metabolite="Metabolite_69">
          <BoundingBox>
            <Position x="332.444825635915" y="442.2855459870744"/>
            <Dimensions width="153" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_52" name="sGlyph_16" metabolite="Metabolite_71">
          <BoundingBox>
            <Position x="516.6006843339268" y="712.9404976509535"/>
            <Dimensions width="129" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_57" name="sGlyph_17" metabolite="Metabolite_73">
          <BoundingBox>
            <Position x="571.2022145852193" y="434.7015994753957"/>
            <Dimensions width="145" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_78" name="sGlyph_18" metabolite="Metabolite_75">
          <BoundingBox>
            <Position x="312.8651749768973" y="524.5169790192297"/>
            <Dimensions width="177" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_85" name="sGlyph_19" metabolite="Metabolite_77">
          <BoundingBox>
            <Position x="0" y="571.6918474406065"/>
            <Dimensions width="169" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_92" name="sGlyph_20" metabolite="Metabolite_79">
          <BoundingBox>
            <Position x="667.3840431843846" y="403.0350631470209"/>
            <Dimensions width="161" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
        <MetaboliteGlyph key="Layout_96" name="sGlyph_21" metabolite="Metabolite_81">
          <BoundingBox>
            <Position x="760.2622897819249" y="716.5047253834395"/>
            <Dimensions width="153" height="25"/>
          </BoundingBox>
        </MetaboliteGlyph>
      </ListOfMetabGlyphs>
      <ListOfReactionGlyphs>
        <ReactionGlyph key="Layout_100" name="rGlyph_0" reaction="Reaction_11">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="269.980054248107" y="15.58649979450822"/>
                <End x="254.5231285030601" y="20.04050813292248"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_104" name="curve00" metaboliteGlyph="Layout_6" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="269.980054248107" y="15.58649979450822"/>
                    <End x="329.8806978727152" y="11.83966546977138"/>
                    <BasePoint1 x="285.4369799931539" y="11.13249145609395"/>
                    <BasePoint2 x="311.5230703691963" y="10.3725763783291"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_108" name="curve01" metaboliteGlyph="Layout_2" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="269.980054248107" y="15.58649979450822"/>
                    <End x="310.6800461551084" y="83.34966316248098"/>
                    <BasePoint1 x="285.4369799931539" y="11.13249145609395"/>
                    <BasePoint2 x="301.9227445103929" y="46.1275752246839"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_112" name="curve00" metaboliteGlyph="Layout_31" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="254.5231285030601" y="20.04050813292248"/>
                    <End x="200.8212476366776" y="83.71491496538314"/>
                    <BasePoint1 x="239.0662027580131" y="24.49451647133675"/>
                    <BasePoint2 x="216.0794937610837" y="55.21821780296352"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_119" name="rGlyph_1" reaction="Reaction_10">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="257.4573105818026" y="185.3693817267073"/>
                <End x="271.042888852289" y="195.2634569315716"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_130" name="curve10" metaboliteGlyph="Layout_31" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="257.4573105818026" y="185.3693817267073"/>
                    <End x="202.3280918621129" y="118.7149149653831"/>
                    <BasePoint1 x="243.8717323113163" y="175.4753065218431"/>
                    <BasePoint2 x="219.703517519093" y="144.621591942397"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_23" name="curve10" metaboliteGlyph="Layout_2" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="271.042888852289" y="195.2634569315716"/>
                    <End x="311.4000547880029" y="118.349663162481"/>
                    <BasePoint1 x="284.6284671227754" y="205.1575321364358"/>
                    <BasePoint2 x="301.4106555230108" y="164.2271164506745"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_19" name="curve11" metaboliteGlyph="Layout_8" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="271.042888852289" y="195.2634569315716"/>
                    <End x="324.8004658887064" y="281.9616708655706"/>
                    <BasePoint1 x="284.6284671227754" y="205.1575321364358"/>
                    <BasePoint2 x="308.1108610733625" y="246.0331203022193"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_21" name="rGlyph_2" reaction="Reaction_9">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="430.0275119374917" y="258.6307688806719"/>
                <End x="445.8135861162504" y="254.7011289549415"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_27" name="curve20" metaboliteGlyph="Layout_8" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="430.0275119374917" y="258.6307688806719"/>
                    <End x="372.0292635725197" y="281.9616708655706"/>
                    <BasePoint1 x="414.2414377587331" y="262.5604088064023"/>
                    <BasePoint2 x="389.1888321209367" y="273.243449817419"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_25" name="curve21" metaboliteGlyph="Layout_4" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="430.0275119374917" y="258.6307688806719"/>
                    <End x="397.6166672281669" y="185.9030708831204"/>
                    <BasePoint1 x="414.2414377587331" y="262.5604088064023"/>
                    <BasePoint2 x="401.9825339487603" y="225.214149826194"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_22" name="curve20" metaboliteGlyph="Layout_37" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="445.8135861162504" y="254.7011289549415"/>
                    <End x="502.9972449942119" y="212.1359716170413"/>
                    <BasePoint1 x="461.599660295009" y="250.771489029211"/>
                    <BasePoint2 x="486.2449711893001" y="230.4713203416935"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_33" name="rGlyph_3" reaction="Reaction_8">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="469.3633190831844" y="96.39655463761595"/>
                <End x="455.4485923789864" y="85.97811102006783"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_29" name="curve30" metaboliteGlyph="Layout_37" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="469.3633190831844" y="96.39655463761595"/>
                    <End x="514.0823909771407" y="177.1359716170413"/>
                    <BasePoint1 x="483.2780457873825" y="106.8149982551641"/>
                    <BasePoint2 x="502.1589000583111" y="144.5800958404897"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_26" name="curve30" metaboliteGlyph="Layout_4" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="455.4485923789864" y="85.97811102006783"/>
                    <End x="402.8147122736556" y="150.9030708831204"/>
                    <BasePoint1 x="441.5338656747883" y="75.55966740251972"/>
                    <BasePoint2 x="418.6956072981724" y="110.626758238433"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_32" name="curve31" metaboliteGlyph="Layout_6" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="455.4485923789864" y="85.97811102006783"/>
                    <End x="390.8492502312267" y="30"/>
                    <BasePoint1 x="441.5338656747883" y="75.55966740251972"/>
                    <BasePoint2 x="412.712876276958" y="50.17522279687283"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_36" name="rGlyph_4" reaction="Reaction_7">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="202.6941730168981" y="382.7237341018961"/>
                <End x="192.6839861346146" y="374.8083273629682"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_34" name="curve40" metaboliteGlyph="Layout_10" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="202.6941730168981" y="382.7237341018961"/>
                    <End x="150.8033490598753" y="460.986786497818"/>
                    <BasePoint1 x="212.7043598991817" y="390.639140840824"/>
                    <BasePoint2 x="184.2564012000994" y="427.791815354053"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_30" name="curve41" metaboliteGlyph="Layout_8" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="202.6941730168981" y="382.7237341018961"/>
                    <End x="310.6819434167849" y="316.9616708655706"/>
                    <BasePoint1 x="212.7043598991817" y="390.639140840824"/>
                    <BasePoint2 x="264.1956983785542" y="355.7792575379293"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_40" name="curve40" metaboliteGlyph="Layout_43" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="192.6839861346146" y="374.8083273629682"/>
                    <End x="149.3249381289037" y="327.3201612924149"/>
                    <BasePoint1 x="182.673799252331" y="366.8929206240402"/>
                    <BasePoint2 x="163.4968219700465" y="345.1276892734956"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_38" name="rGlyph_5" reaction="Reaction_6">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="235.5958849151992" y="325.6549423940193"/>
                <End x="251.2198411880661" y="332.5716865865967"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_35" name="curve50" metaboliteGlyph="Layout_43" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="235.5958849151992" y="325.6549423940193"/>
                    <End x="208.0772915276323" y="317.4960029489942"/>
                    <BasePoint1 x="219.9719286423323" y="318.7381982014418"/>
                    <BasePoint2 x="210.1186210167656" y="316.3879145270736"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_45" name="curve50" metaboliteGlyph="Layout_12" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="251.2198411880661" y="332.5716865865967"/>
                    <End x="250.497577085599" y="441.0135355708081"/>
                    <BasePoint1 x="266.8437974609331" y="339.4884307791741"/>
                    <BasePoint2 x="262.5766763414828" y="391.9801692231355"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_41" name="curve51" metaboliteGlyph="Layout_8" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="251.2198411880661" y="332.5716865865967"/>
                    <End x="304.612773902307" y="316.9616708655706"/>
                    <BasePoint1 x="266.8437974609331" y="339.4884307791741"/>
                    <BasePoint2 x="289.6342747498367" y="329.9542368705166"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_39" name="rGlyph_6" reaction="Reaction_5">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="211.4027403094528" y="556.5921285796901"/>
                <End x="193.7885130515739" y="559.7704141219647"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_44" name="curve60" metaboliteGlyph="Layout_12" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="211.4027403094528" y="556.5921285796901"/>
                    <End x="244.2384289223525" y="476.0135355708081"/>
                    <BasePoint1 x="229.0169675673316" y="553.4138430374155"/>
                    <BasePoint2 x="241.0312550593118" y="513.9191179185432"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_48" name="curve61" metaboliteGlyph="Layout_28" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="211.4027403094528" y="556.5921285796901"/>
                    <End x="265.204561128" y="628.8044484649134"/>
                    <BasePoint1 x="229.0169675673316" y="553.4138430374155"/>
                    <BasePoint2 x="251.5143211621355" y="590.3145743655958"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_46" name="curve60" metaboliteGlyph="Layout_85" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="193.7885130515739" y="559.7704141219647"/>
                    <End x="160.0208229156336" y="566.6918474406065"/>
                    <BasePoint1 x="176.1742857936951" y="562.9486996642393"/>
                    <BasePoint2 x="163.6939975401947" y="565.6148449379915"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_42" name="rGlyph_7" reaction="Reaction_4">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="155.6545879272855" y="620.9906844751805"/>
                <End x="167.655045794581" y="618.8110614792564"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_53" name="curve70" metaboliteGlyph="Layout_85" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="155.6545879272855" y="620.9906844751805"/>
                    <End x="111.0581881695647" y="601.6918474406065"/>
                    <BasePoint1 x="143.65413005999" y="623.1703074711046"/>
                    <BasePoint2 x="124.3560446479535" y="612.9759832048366"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_50" name="curve70" metaboliteGlyph="Layout_10" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="167.655045794581" y="618.8110614792564"/>
                    <End x="141.0102276044009" y="495.986786497818"/>
                    <BasePoint1 x="179.6555036618765" y="616.6314384833323"/>
                    <BasePoint2 x="163.3329800999626" y="555.7642067415942"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_47" name="curve71" metaboliteGlyph="Layout_28" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="167.655045794581" y="618.8110614792564"/>
                    <End x="218.1970303193191" y="628.8044484649134"/>
                    <BasePoint1 x="179.6555036618765" y="616.6314384833323"/>
                    <BasePoint2 x="201.9263814574217" y="622.1730377251419"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_51" name="rGlyph_8" reaction="Reaction_3">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="323.6029481526172" y="395.8061890698089"/>
                <End x="335.4157452905786" y="403.3859833466973"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_54" name="curve80" metaboliteGlyph="Layout_12" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="323.6029481526172" y="395.8061890698089"/>
                    <End x="263.6420312588405" y="441.0135355708081"/>
                    <BasePoint1 x="311.7901510146559" y="388.2263947929204"/>
                    <BasePoint2 x="284.7628918522578" y="412.7250166126421"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_55" name="curve81" metaboliteGlyph="Layout_8" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="323.6029481526172" y="395.8061890698089"/>
                    <End x="329.5841865019753" y="316.9616708655706"/>
                    <BasePoint1 x="311.7901510146559" y="388.2263947929204"/>
                    <BasePoint2 x="317.7339694738253" y="350.6990842600233"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_60" name="curve80" metaboliteGlyph="Layout_49" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="335.4157452905786" y="403.3859833466973"/>
                    <End x="384.2976173903103" y="437.2855459870744"/>
                    <BasePoint1 x="347.22854242854" y="410.9657776235858"/>
                    <BasePoint2 x="368.7162791939155" y="426.0206103745524"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_58" name="rGlyph_9" reaction="Reaction_2">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="453.4604758662262" y="389.1308472290932"/>
                <End x="455.5271039735873" y="384.7539912098704"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_59" name="curve90" metaboliteGlyph="Layout_49" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="453.4604758662262" y="389.1308472290932"/>
                    <End x="421.0676069537659" y="437.2855459870744"/>
                    <BasePoint1 x="451.3938477588652" y="393.507703248316"/>
                    <BasePoint2 x="435.7140703294753" y="416.490838622501"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_63" name="curve90" metaboliteGlyph="Layout_14" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="455.5271039735873" y="384.7539912098704"/>
                    <End x="516.9397161500777" y="505.0723007241212"/>
                    <BasePoint1 x="457.5937320809484" y="380.3771351906474"/>
                    <BasePoint2 x="487.7833811423533" y="441.6305039525786"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_56" name="curve91" metaboliteGlyph="Layout_8" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="455.5271039735873" y="384.7539912098704"/>
                    <End x="360.6939980085425" y="316.9616708655706"/>
                    <BasePoint1 x="457.5937320809484" y="380.3771351906474"/>
                    <BasePoint2 x="409.6605220715857" y="347.5751890233033"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_62" name="rGlyph_10" reaction="Reaction_1">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="410.3524554768237" y="624.1484489778526"/>
                <End x="410.5453204713121" y="619.4063094203237"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_66" name="curve100" metaboliteGlyph="Layout_14" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="410.3524554768237" y="624.1484489778526"/>
                    <End x="506.3215336470396" y="540.0723007241212"/>
                    <BasePoint1 x="410.1595904823352" y="628.8905885353813"/>
                    <BasePoint2 x="458.1923458160653" y="585.6669795191334"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_61" name="curve101" metaboliteGlyph="Layout_28" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="410.3524554768237" y="624.1484489778526"/>
                    <End x="331.1045850264778" y="638.97189450539"/>
                    <BasePoint1 x="410.1595904823352" y="628.8905885353813"/>
                    <BasePoint2 x="370.5838715057844" y="635.1167764097678"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_65" name="curve100" metaboliteGlyph="Layout_78" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="410.5453204713121" y="619.4063094203237"/>
                    <End x="403.4776491279103" y="554.5169790192297"/>
                    <BasePoint1 x="410.7381854658005" y="614.664169862795"/>
                    <BasePoint2 x="407.1561335454775" y="583.4050395516301"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_69" name="rGlyph_11" reaction="Reaction_0">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="312.8098452782629" y="548.7468644687774"/>
                <End x="298.7375550384519" y="550.2860657686406"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_64" name="curve110" metaboliteGlyph="Layout_78" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="312.8098452782629" y="548.7468644687774"/>
                    <End x="307.8651749768973" y="549.8095419291022"/>
                    <BasePoint1 x="326.8821355180738" y="547.2076631689143"/>
                    <BasePoint2 x="320.8917278074383" y="548.1238022240425"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_68" name="curve110" metaboliteGlyph="Layout_12" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="298.7375550384519" y="550.2860657686406"/>
                    <End x="254.6163101622624" y="476.0135355708081"/>
                    <BasePoint1 x="284.665264798641" y="551.8252670685037"/>
                    <BasePoint2 x="266.1227149204989" y="514.3042016446217"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_72" name="curve111" metaboliteGlyph="Layout_28" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="298.7375550384519" y="550.2860657686406"/>
                    <End x="275.653310398057" y="628.8044484649134"/>
                    <BasePoint1 x="284.665264798641" y="551.8252670685037"/>
                    <BasePoint2 x="276.6412150383962" y="590.6996580916743"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_67" name="rGlyph_12" reaction="Reaction_12">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="567.4628301523653" y="641.7248936804648"/>
                <End x="563.7984731969452" y="653.82778744272"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_71" name="curve120" metaboliteGlyph="Layout_16" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="567.4628301523653" y="641.7248936804648"/>
                    <End x="676.7200427387072" y="672.6119775547921"/>
                    <BasePoint1 x="571.1271871077854" y="629.6219999182096"/>
                    <BasePoint2 x="624.8397041621013" y="648.091265295937"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_75" name="curve121" metaboliteGlyph="Layout_14" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="567.4628301523653" y="641.7248936804648"/>
                    <End x="532.7652412290819" y="540.0723007241212"/>
                    <BasePoint1 x="571.1271871077854" y="629.6219999182096"/>
                    <BasePoint2 x="552.8623034072887" y="581.8214268806015"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_70" name="curve120" metaboliteGlyph="Layout_52" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="563.7984731969452" y="653.82778744272"/>
                    <End x="574.9350638778444" y="707.9404976509535"/>
                    <BasePoint1 x="560.1341162415251" y="665.9306812049753"/>
                    <BasePoint2 x="566.6185008208297" y="689.9613128685282"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_74" name="rGlyph_13" reaction="Reaction_13">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="608.4544778659215" y="615.8988243878376"/>
                <End x="612.0659308197712" y="598.4429046321353"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_79" name="curve130" metaboliteGlyph="Layout_52" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="608.4544778659215" y="615.8988243878376"/>
                    <End x="585.6126847714764" y="707.9404976509535"/>
                    <BasePoint1 x="604.8430249120718" y="633.35474414354"/>
                    <BasePoint2 x="594.3249916033117" y="675.0116008361723"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_73" name="curve130" metaboliteGlyph="Layout_18" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="612.0659308197712" y="598.4429046321353"/>
                    <End x="667.6619627073005" y="579.9878903121681"/>
                    <BasePoint1 x="615.6773837736209" y="580.986984876433"/>
                    <BasePoint2 x="642.5725364789232" y="576.1234576553749"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_77" name="curve131" metaboliteGlyph="Layout_14" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="612.0659308197712" y="598.4429046321353"/>
                    <End x="552.3533684456688" y="540.0723007241212"/>
                    <BasePoint1 x="615.6773837736209" y="580.986984876433"/>
                    <BasePoint2 x="584.9182393481074" y="556.1656628613515"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_82" name="rGlyph_14" reaction="Reaction_14">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="800.2421449846121" y="602.8715386623337"/>
                <End x="804.5581282247318" y="620.1828444647083"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_76" name="curve140" metaboliteGlyph="Layout_18" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="800.2421449846121" y="602.8715386623337"/>
                    <End x="750.6619627073005" y="582.2370887947831"/>
                    <BasePoint1 x="795.9261617444925" y="585.5602328599591"/>
                    <BasePoint2 x="772.2150664158665" y="579.5708343767775"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_81" name="curve141" metaboliteGlyph="Layout_24" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="800.2421449846121" y="602.8715386623337"/>
                    <End x="850.9121258935102" y="550.0930352556493"/>
                    <BasePoint1 x="795.9261617444925" y="585.5602328599591"/>
                    <BasePoint2 x="822.3401480089714" y="563.4988076072106"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_86" name="curve140" metaboliteGlyph="Layout_96" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="804.5581282247318" y="620.1828444647083"/>
                    <End x="831.4291015692157" y="711.5047253834395"/>
                    <BasePoint1 x="808.8741114648515" y="637.4941502670829"/>
                    <BasePoint2 x="821.2306023270635" y="678.8272642758549"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_80" name="rGlyph_15" reaction="Reaction_15">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="857.9090850208559" y="655.5020888131076"/>
                <End x="853.6460057823065" y="643.5438090041801"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_84" name="curve150" metaboliteGlyph="Layout_96" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="857.9090850208559" y="655.5020888131076"/>
                    <End x="843.9875306773625" y="711.5047253834395"/>
                    <BasePoint1 x="862.1721642594051" y="667.4603686220351"/>
                    <BasePoint2 x="854.1456172780212" y="692.4721169549691"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_89" name="curve150" metaboliteGlyph="Layout_16" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="853.6460057823065" y="643.5438090041801"/>
                    <End x="743.7200427387072" y="673.0915115522433"/>
                    <BasePoint1 x="849.3829265437572" y="631.5855291952526"/>
                    <BasePoint2 x="795.4857148315948" y="649.3489504215161"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_83" name="curve151" metaboliteGlyph="Layout_24" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="853.6460057823065" y="643.5438090041801"/>
                    <End x="872.9764017888605" y="550.0930352556493"/>
                    <BasePoint1 x="849.3829265437572" y="631.5855291952526"/>
                    <BasePoint2 x="860.1138943566715" y="587.8497122732191"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_88" name="rGlyph_16" reaction="Reaction_16">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="617.5708893955695" y="530.5793931328043"/>
                <End x="620.219589466849" y="520.2114230709509"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_93" name="curve160" metaboliteGlyph="Layout_18" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="617.5708893955695" y="530.5793931328043"/>
                    <End x="667.6619627073005" y="562.3494073627289"/>
                    <BasePoint1 x="614.9221893242899" y="540.9473631946577"/>
                    <BasePoint2 x="640.6299009979753" y="554.2403777941566"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_87" name="curve161" metaboliteGlyph="Layout_14" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="617.5708893955695" y="530.5793931328043"/>
                    <End x="574.7684650375475" y="532.7176192764489"/>
                    <BasePoint1 x="614.9221893242899" y="540.9473631946577"/>
                    <BasePoint2 x="594.1831521630988" y="539.4244837510166"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_91" name="curve160" metaboliteGlyph="Layout_57" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="620.219589466849" y="520.2114230709509"/>
                    <End x="637.8819256289238" y="464.7015994753957"/>
                    <BasePoint1 x="622.8682895381286" y="509.8434530090975"/>
                    <BasePoint2 x="631.0372826013461" y="484.6805337267833"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_97" name="rGlyph_17" reaction="Reaction_17">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="603.2785351157932" y="379.6464975299589"/>
                <End x="601.73838097199" y="376.1882862650451"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_90" name="curve170" metaboliteGlyph="Layout_57" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="603.2785351157932" y="379.6464975299589"/>
                    <End x="633.0860725856016" y="429.7015994753957"/>
                    <BasePoint1 x="604.8186892595962" y="383.1047087948726"/>
                    <BasePoint2 x="619.3374194585497" y="407.2677069513626"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_95" name="curve170" metaboliteGlyph="Layout_14" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="601.73838097199" y="376.1882862650451"/>
                    <End x="534.019475141679" y="505.0723007241212"/>
                    <BasePoint1 x="600.1982268281869" y="372.7300750001314"/>
                    <BasePoint2 x="566.7238124489821" y="438.0366350458978"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_101" name="curve171" metaboliteGlyph="Layout_20" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="601.73838097199" y="376.1882862650451"/>
                    <End x="698.5788843819474" y="320.166672928395"/>
                    <BasePoint1 x="600.1982268281869" y="372.7300750001314"/>
                    <BasePoint2 x="649.0035170691164" y="345.5838211480348"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_94" name="rGlyph_18" reaction="Reaction_18">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="839.7120563595134" y="396.3002466055332"/>
                <End x="834.0316690124026" y="396.0907675110331"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_99" name="curve180" metaboliteGlyph="Layout_20" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="839.7120563595134" y="396.3002466055332"/>
                    <End x="752.6028877615053" y="320.166672928395"/>
                    <BasePoint1 x="845.3924437066243" y="396.5097257000333"/>
                    <BasePoint2 x="800.4177625708425" y="358.3905690878391"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_105" name="curve181" metaboliteGlyph="Layout_24" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="839.7120563595134" y="396.3002466055332"/>
                    <End x="873.8441719249274" y="515.0930352556493"/>
                    <BasePoint1 x="845.3924437066243" y="396.5097257000333"/>
                    <BasePoint2 x="861.0384046525535" y="455.8537502514663"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_98" name="curve180" metaboliteGlyph="Layout_92" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="834.0316690124026" y="396.0907675110331"/>
                    <End x="819.5332145382945" y="398.0350631470209"/>
                    <BasePoint1 x="828.3512816652918" y="395.8812884165329"/>
                    <BasePoint2 x="822.5221512650155" y="396.9058060081519"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
        <ReactionGlyph key="Layout_103" name="rGlyph_19" reaction="Reaction_19">
          <Curve>
            <ListOfCurveSegments>
              <CurveSegment xsi:type="LineSegment">
                <Start x="781.4950585424741" y="496.1508011865695"/>
                <End x="786.0668999621086" y="510.1864616078368"/>
              </CurveSegment>
            </ListOfCurveSegments>
          </Curve>
          <ListOfMetaboliteReferenceGlyphs>
            <MetaboliteReferenceGlyph key="Layout_106" name="curve190" metaboliteGlyph="Layout_92" role="substrate">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="781.4950585424741" y="496.1508011865695"/>
                    <End x="755.5167399624885" y="433.0350631470209"/>
                    <BasePoint1 x="776.9232171228398" y="482.1151407653023"/>
                    <BasePoint2 x="765.0770181877556" y="454.0661868508447"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_102" name="curve190" metaboliteGlyph="Layout_18" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="786.0668999621086" y="510.1864616078368"/>
                    <End x="735.1014006393349" y="561.6902994637381"/>
                    <BasePoint1 x="790.6387413817429" y="524.2221220291041"/>
                    <BasePoint2 x="764.0130313654474" y="546.465125851738"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
            <MetaboliteReferenceGlyph key="Layout_107" name="curve191" metaboliteGlyph="Layout_24" role="product">
              <Curve>
                <ListOfCurveSegments>
                  <CurveSegment xsi:type="CubicBezier">
                    <Start x="786.0668999621086" y="510.1864616078368"/>
                    <End x="824.5429520541562" y="527.4692105088226"/>
                    <BasePoint1 x="790.6387413817429" y="524.2221220291041"/>
                    <BasePoint2 x="808.7338070728581" y="529.3545813742802"/>
                  </CurveSegment>
                </ListOfCurveSegments>
              </Curve>
            </MetaboliteReferenceGlyph>
          </ListOfMetaboliteReferenceGlyphs>
        </ReactionGlyph>
      </ListOfReactionGlyphs>
      <ListOfTextGlyphs>
        <TextGlyph key="Layout_109" name="tGlyph_0" graphicalObject="Layout_2" originOfText="Metabolite_33">
          <BoundingBox>
            <Position x="296.2970630279131" y="88.34966316248098"/>
            <Dimensions width="41" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_115" name="tGlyph_1" graphicalObject="Layout_4" originOfText="Metabolite_29">
          <BoundingBox>
            <Position x="373.3214208477608" y="155.9030708831204"/>
            <Dimensions width="41" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_111" name="tGlyph_2" graphicalObject="Layout_6" text="MAPKKK">
          <BoundingBox>
            <Position x="334.8806978727152" y="0"/>
            <Dimensions width="73" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_113" name="tGlyph_3" graphicalObject="Layout_8" text="P-MAPKKK">
          <BoundingBox>
            <Position x="289.4537483815041" y="286.9616708655706"/>
            <Dimensions width="89" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_110" name="tGlyph_4" graphicalObject="Layout_10" text="MAPKK">
          <BoundingBox>
            <Position x="102.9045723194321" y="465.986786497818"/>
            <Dimensions width="65" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_118" name="tGlyph_5" graphicalObject="Layout_12" text="P-MAPKK">
          <BoundingBox>
            <Position x="207.1799601310985" y="446.0135355708081"/>
            <Dimensions width="81" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_116" name="tGlyph_6" graphicalObject="Layout_14" text="PP-MAPKK">
          <BoundingBox>
            <Position x="480.7684650375474" y="510.0723007241212"/>
            <Dimensions width="89" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_114" name="tGlyph_7" graphicalObject="Layout_16" text="MAPK">
          <BoundingBox>
            <Position x="681.7200427387072" y="673.7508193326802"/>
            <Dimensions width="57" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_123" name="tGlyph_8" graphicalObject="Layout_18" text="P-MAPK">
          <BoundingBox>
            <Position x="672.6619627073005" y="566.6902994637381"/>
            <Dimensions width="73" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_120" name="tGlyph_9" graphicalObject="Layout_20" text="PP-MAPK">
          <BoundingBox>
            <Position x="690.8328812568292" y="290.166672928395"/>
            <Dimensions width="81" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_117" name="tGlyph_10" graphicalObject="Layout_24" text="MAPK-Pase">
          <BoundingBox>
            <Position x="829.5429520541562" y="520.0930352556493"/>
            <Dimensions width="97" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_122" name="tGlyph_11" graphicalObject="Layout_28" text="MAPKK-Pase">
          <BoundingBox>
            <Position x="221.1045850264778" y="633.8044484649134"/>
            <Dimensions width="105" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_126" name="tGlyph_12" graphicalObject="Layout_31" text="MAPKKK_E1">
          <BoundingBox>
            <Position x="141.0196229998448" y="88.71491496538314"/>
            <Dimensions width="97" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_124" name="tGlyph_13" graphicalObject="Layout_37" text="P-MAPKKK_E2">
          <BoundingBox>
            <Position x="465.2483264022186" y="182.1359716170413"/>
            <Dimensions width="113" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_121" name="tGlyph_14" graphicalObject="Layout_43" text="P-MAPKKK_MAPKK">
          <BoundingBox>
            <Position x="66.07729152763226" y="297.3201612924149"/>
            <Dimensions width="137" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_129" name="tGlyph_15" graphicalObject="Layout_49" text="P-MAPKKK_P-MAPKK">
          <BoundingBox>
            <Position x="332.444825635915" y="442.2855459870744"/>
            <Dimensions width="153" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_127" name="tGlyph_16" graphicalObject="Layout_52" text="PP-MAPKK_MAPK">
          <BoundingBox>
            <Position x="516.6006843339268" y="712.9404976509535"/>
            <Dimensions width="129" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_125" name="tGlyph_17" graphicalObject="Layout_57" text="PP-MAPKK_P-MAPK">
          <BoundingBox>
            <Position x="571.2022145852193" y="434.7015994753957"/>
            <Dimensions width="145" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_134" name="tGlyph_18" graphicalObject="Layout_78" text="MAPKK-Pase_PP-MAPKK">
          <BoundingBox>
            <Position x="312.8651749768973" y="524.5169790192297"/>
            <Dimensions width="177" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_131" name="tGlyph_19" graphicalObject="Layout_85" text="MAPKK-Pase_P-MAPKK">
          <BoundingBox>
            <Position x="0" y="571.6918474406065"/>
            <Dimensions width="169" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_128" name="tGlyph_20" graphicalObject="Layout_92" text="MAPK-Pase_PP-MAPK">
          <BoundingBox>
            <Position x="667.3840431843846" y="403.0350631470209"/>
            <Dimensions width="161" height="25"/>
          </BoundingBox>
        </TextGlyph>
        <TextGlyph key="Layout_133" name="tGlyph_21" graphicalObject="Layout_96" text="MAPK-Pase_P-MAPK">
          <BoundingBox>
            <Position x="760.2622897819249" y="716.5047253834395"/>
            <Dimensions width="153" height="25"/>
          </BoundingBox>
        </TextGlyph>
      </ListOfTextGlyphs>
    </Layout>
  </ListOfLayouts>
  <SBMLReference file="MAPK-HF96-layout.xml">
    <SBMLMap SBMLid="E1" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="E1_KKK" COPASIkey="Metabolite_63"/>
    <SBMLMap SBMLid="E2" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="E2_P_KKK" COPASIkey="Metabolite_65"/>
    <SBMLMap SBMLid="K" COPASIkey="Metabolite_53"/>
    <SBMLMap SBMLid="KK" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="KKK" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="KKPase" COPASIkey="Metabolite_61"/>
    <SBMLMap SBMLid="KKPase_PP_KK" COPASIkey="Metabolite_75"/>
    <SBMLMap SBMLid="KKPase_P_KK" COPASIkey="Metabolite_77"/>
    <SBMLMap SBMLid="KPase" COPASIkey="Metabolite_59"/>
    <SBMLMap SBMLid="KPase_PP_K" COPASIkey="Metabolite_79"/>
    <SBMLMap SBMLid="KPase_P_K" COPASIkey="Metabolite_81"/>
    <SBMLMap SBMLid="PP_K" COPASIkey="Metabolite_57"/>
    <SBMLMap SBMLid="PP_KK" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="PP_KK_K" COPASIkey="Metabolite_71"/>
    <SBMLMap SBMLid="PP_KK_P_K" COPASIkey="Metabolite_73"/>
    <SBMLMap SBMLid="P_K" COPASIkey="Metabolite_55"/>
    <SBMLMap SBMLid="P_KK" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="P_KKK" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="P_KKK_KK" COPASIkey="Metabolite_67"/>
    <SBMLMap SBMLid="P_KKK_P_KK" COPASIkey="Metabolite_69"/>
    <SBMLMap SBMLid="compartment" COPASIkey="Compartment_6"/>
    <SBMLMap SBMLid="parameter_1" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="r10a" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="r10b" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="r1a" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="r1b" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="r2a" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="r2b" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="r3a" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="r3b" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="r4a" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="r4b" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="r5a" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="r5b" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="r6a" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="r6b" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="r7a" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="r7b" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="r8a" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="r8b" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="r9a" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="r9b" COPASIkey="Reaction_17"/>
  </SBMLReference>
</COPASI>
