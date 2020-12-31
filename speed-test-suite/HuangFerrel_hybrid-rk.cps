<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2020-12-31T14:34:30Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="30" versionDevel="237" copasiSourcesModified="0">
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
        k1*PRODUCT&lt;substrate_i>
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_80" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_81" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Huang-Ferrel MAPK" simulationType="time" timeUnit="s" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="µmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <dcterms:description>Huang and Ferrel (1996) Ultrasensitivity in the mitogen-activated protein kinase cascade PNAS 93:10078-83</dcterms:description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:8816754"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:01:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      From Huang and Ferrel 1996, PNAS 93:10078-83
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_8" name="E1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:20:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="KKK" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_7">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="KKK.E1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_6">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="KKK*" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_5">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="E2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:20:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="KKK.E2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="KK" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_2">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="KK.KKK*" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_0" name="KK-P" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="KK-P.KKPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="KKPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="KK-P.KKK*" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="KK-PP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="KK-PP+KKPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="KK-PP.KPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="K" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="KK-PP.K" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="K-P" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="KK-P.K" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="KK-P.KPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="KPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="K-P.KPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="K-P.KK-PP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="K-PP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="K-PP.KPase" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_14" name="a" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:28:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="d" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:28:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="k" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:29:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_15" name="reaction_2" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:03:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4106" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_2],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_14" name="reaction_4" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4104" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_4],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_13" name="reaction_6" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4103" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_6],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_12" name="reaction_8" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4107" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_8],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_11" name="reaction_10" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4105" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_10],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_10" name="reaction_12" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4108" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_12],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_9" name="reaction_14" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4109" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_14],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_8" name="reaction_16" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:29:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4110" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_16],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_7" name="reaction_18" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:29:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4111" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_18],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_6" name="reaction_20" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4112" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_20],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_5" name="reaction_1 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4113" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_7"/>
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_4" name="reaction_1 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4114" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_3" name="reaction_3 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4115" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_5"/>
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_2" name="reaction_3 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4116" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_1" name="reaction_5 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4117" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_2"/>
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_0" name="reaction_5 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4118" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_32" name="reaction_7 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4119" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_33" name="reaction_7 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4147" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_34" name="reaction_9 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4148" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_35" name="reaction_9 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4146" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_36" name="reaction_11 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4150" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_21"/>
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_37" name="reaction_11 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4149" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_38" name="reaction_13 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4158" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_21"/>
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_39" name="reaction_13 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4159" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_40" name="reaction_15 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4160" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_41" name="reaction_15 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4213" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_42" name="reaction_17 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4215" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_43" name="reaction_17 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4161" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_44" name="reaction_19 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4162" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_45" name="reaction_19 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4163" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T14:31:43Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]" value="1e-10" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[E1]" value="1806.6425370000006" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK]" value="180664.25370000006" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK.E1]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[E2]" value="18066.42536999999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK.E2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK]" value="72265701.480000049" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK.KKK*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KKPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKPase]" value="18066.42536999999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KKK*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP+KKPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP.KPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K]" value="72265701.480000049" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP.K]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.K]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KPase]" value="7226570.148000001" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P.KPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P.KK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-PP.KPase]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a]" value="1000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d]" value="150" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k]" value="150" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_2],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_4],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_6],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_8],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_10],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_12],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_14],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_16],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_18]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_18],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_20],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (forward)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (backward)],ParameterGroup=Parameters,Parameter=k1" value="150" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 7226570.148000001 18066.42536999999 0 0 180664.25370000006 0 72265701.480000049 0 0 0 0 0 72265701.480000049 0 0 0 0 0 18066.42536999999 1806.6425370000006 0 0 0 1e-10 1000 150 150 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_14" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="1"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Maximum duration for forward integration" type="unsignedFloat" value="1000000000"/>
        <Parameter name="Maximum duration for backward integration" type="unsignedFloat" value="1000000"/>
        <Parameter name="Target Criterion" type="string" value="Distance and Rate"/>
      </Method>
    </Task>
    <Task key="Task_1" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_23" target="HuangFerrel_hybrid-rk.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="1000"/>
        <Parameter name="StepSize" type="float" value="0.10000000000000001"/>
        <Parameter name="Duration" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="0"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Hybrid (Runge-Kutta)" type="Hybrid">
        <Parameter name="Max Internal Steps" type="integer" value="1000000"/>
        <Parameter name="Lower Limit" type="float" value="800"/>
        <Parameter name="Upper Limit" type="float" value="1000"/>
        <Parameter name="Partitioning Interval" type="unsignedInteger" value="1"/>
        <Parameter name="Use Random Seed" type="bool" value="0"/>
        <Parameter name="Random Seed" type="unsignedInteger" value="1"/>
        <Parameter name="Runge Kutta Stepsize" type="float" value="0.001"/>
      </Method>
    </Task>
    <Task key="Task_2" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
        <Parameter name="Continue on Error" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_3" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_4" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Iterations" type="unsignedInteger" value="100000"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_5" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Create Parameter Sets" type="bool" value="0"/>
        <Parameter name="Use Time Sens" type="bool" value="0"/>
        <Parameter name="Time-Sens" type="cn" value=""/>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Stop after # Stalled Generations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
      </Method>
    </Task>
    <Task key="Task_9" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
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
          <ParameterGroup name="Variables">
            <Parameter name="SingleObject" type="cn" value=""/>
            <Parameter name="ObjectListType" type="unsignedInteger" value="0"/>
          </ParameterGroup>
        </ParameterGroup>
      </Problem>
      <Method name="Sensitivities Method" type="SensitivitiesMethod">
        <Parameter name="Delta factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Delta minimum" type="unsignedFloat" value="9.9999999999999998e-13"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_11" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
        <Parameter name="LimitCrossings" type="bool" value="0"/>
        <Parameter name="NumCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitOutTime" type="bool" value="0"/>
        <Parameter name="LimitOutCrossings" type="bool" value="0"/>
        <Parameter name="PositiveDirection" type="bool" value="1"/>
        <Parameter name="NumOutCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitUntilConvergence" type="bool" value="0"/>
        <Parameter name="ConvergenceTolerance" type="float" value="0"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="0"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_12" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_0" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
        <ParameterGroup name="ListOfParameters">
        </ParameterGroup>
        <ParameterGroup name="ListOfTargets">
        </ParameterGroup>
      </Problem>
      <Method name="LSODA Sensitivities" type="Sensitivities(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_0" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_1" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_2" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_5" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_6" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_7" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_8" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_9" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Time-Course],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Time-Course],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Moieties],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Moieties],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_23" name="Speed test" taskType="timeCourse" separator="&#x09;" precision="8">
      <Comment>
      </Comment>
      <Header>
        <Object cn="CN=Root,CN=Information,String=COPASI Version"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,CN=Information,Timer=Current Date/Time"/>
      </Header>
      <Footer>
        <Object cn="CN=Root,Timer=CPU Time"/>
      </Footer>
    </Report>
  </ListOfReports>
  <GUI>
  </GUI>
  <ListOfUnitDefinitions>
    <UnitDefinition key="Unit_1" name="meter" symbol="m">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        m
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_5" name="second" symbol="s">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_4">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        s
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_13" name="Avogadro" symbol="Avogadro">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_12">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_17" name="item" symbol="#">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_16">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        #
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_35" name="liter" symbol="l">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        0.001*m^3
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_41" name="mole" symbol="mol">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
