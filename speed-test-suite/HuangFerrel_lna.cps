<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2021-01-02T20:27:20Z -->
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
      <Compartment key="Compartment_2" name="compartment" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_2">
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
      <Metabolite key="Metabolite_32" name="E1" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:20:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="KKK" simulationType="reactions" compartment="Compartment_2" addNoise="false">
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
      <Metabolite key="Metabolite_34" name="KKK.E1" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_35" name="KKK*" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_35">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_36" name="E2" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:20:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="KKK.E2" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_37">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="KK" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_38">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="KK.KKK*" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_39">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="KK-P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="KK-P.KKPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_42" name="KKPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="KK-P.KKK*" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_44" name="KK-PP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_45" name="KK-PP+KKPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_46" name="KK-PP.KPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_47" name="K" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_48" name="KK-PP.K" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_49" name="K-P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_50" name="KK-P.K" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_51" name="KK-P.KPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_52" name="KPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_52">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="K-P.KPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_54" name="K-P.KK-PP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_55" name="K-PP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T01:46:22Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_56" name="K-PP.KPase" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_56">
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
      <ModelValue key="ModelValue_7" name="a" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:28:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="d" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:28:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="k" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
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
      <Reaction key="Reaction_107" name="reaction_2" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:03:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4374" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_2],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_106" name="reaction_4" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4372" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_4],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_105" name="reaction_6" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4371" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_6],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_104" name="reaction_8" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_104">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4375" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_8],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_103" name="reaction_10" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_103">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4373" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_10],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_102" name="reaction_12" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_102">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4376" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_12],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_101" name="reaction_14" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_101">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:12:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4377" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_14],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_100" name="reaction_16" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_100">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:29:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4381" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_16],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_99" name="reaction_18" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_99">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:29:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4383" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_18],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_98" name="reaction_20" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_98">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-26T12:30:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4384" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_20],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_97" name="reaction_1 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_97">
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
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4378" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_96" name="reaction_1 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_96">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4380" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_1 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_95" name="reaction_3 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_95">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4379" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_35"/>
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_94" name="reaction_3 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_94">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4382" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_3 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_93" name="reaction_5 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4385" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_38"/>
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_92" name="reaction_5 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4386" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_5 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_91" name="reaction_7 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_91">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6868" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_40"/>
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_90" name="reaction_7 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_90">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6897" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_7 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_89" name="reaction_9 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_89">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6899" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_40"/>
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_88" name="reaction_9 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_88">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6879" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_9 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_87" name="reaction_11 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_87">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6910" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_44"/>
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_86" name="reaction_11 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6898" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_11 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_85" name="reaction_13 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6916" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_44"/>
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_84" name="reaction_13 (backward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_84">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6912" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_13 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_83" name="reaction_15 (forward)" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T01:50:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6878" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_49"/>
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_0" name="reaction_15 (backward)" reversible="false" fast="false" addNoise="true">
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
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6905" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_15 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_1" name="reaction_17 (forward)" reversible="false" fast="false" addNoise="true">
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
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6900" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_49"/>
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_2" name="reaction_17 (backward)" reversible="false" fast="false" addNoise="true">
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
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6896" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_17 (backward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_3" name="reaction_19 (forward)" reversible="false" fast="false" addNoise="true">
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
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6911" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_55"/>
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Huang-Ferrel MAPK,Vector=Reactions[reaction_19 (forward)],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_4" name="reaction_19 (backward)" reversible="false" fast="false" addNoise="true">
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
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6915" name="k1" value="150"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_56"/>
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
<dcterms:W3CDTF>2021-01-02T20:22:12Z</dcterms:W3CDTF>
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
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[E1]" value="1791.6138293568874" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK]" value="151547.7390232661" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK.E1]" value="15.028707643113135" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK*]" value="15041.219808107728" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[E2]" value="18051.396662356878" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKK.E2]" value="15.028707643113135" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK]" value="3558728.6427591587" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK.KKK*]" value="2962.8229523497262" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P]" value="13311394.757599577" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KKPase]" value="2962.8229523497257" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KKPase]" value="4021.1879166599033" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KKK*]" value="11082.414500990359" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP]" value="49791160.88358672" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP+KKPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP.KPase]" value="11082.414500990362" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K]" value="64908.771044191795" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-PP.K]" value="178888.90555980761" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P]" value="1958428.0774759529" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.K]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KK-P.KPase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[KPase]" value="1650243.4268520763" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P.KPase]" value="178888.90555980746" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-P.KK-PP]" value="5397437.8155881222" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-PP]" value="59089711.189184077" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Huang-Ferrel MAPK,Vector=Compartments[compartment],Vector=Metabolites[K-PP.KPase]" value="5397437.8155881194" type="Species" simulationType="reactions"/>
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
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_54"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_56"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 15041.219808107728 49791160.88358672 1650243.4268520763 4021.1879166599033 1958428.0774759529 13311394.757599577 151547.7390232661 15.028707643113135 64908.771044191795 2962.8229523497262 5397437.8155881222 11082.414500990362 178888.90555980746 15.028707643113135 3558728.6427591587 59089711.189184077 11082.414500990359 5397437.8155881194 178888.90555980761 2962.8229523497257 18051.396662356878 1791.6138293568874 0 0 0 1e-10 1000 150 150 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_0" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_12" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_22" target="" append="1" confirmOverwrite="0"/>
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
      <Method name="Hybrid (LSODA)" type="Hybrid (LSODA)">
        <Parameter name="Max Internal Steps" type="integer" value="1000000"/>
        <Parameter name="Lower Limit" type="float" value="800"/>
        <Parameter name="Upper Limit" type="float" value="1000"/>
        <Parameter name="Partitioning Interval" type="unsignedInteger" value="1"/>
        <Parameter name="Use Random Seed" type="bool" value="0"/>
        <Parameter name="Random Seed" type="unsignedInteger" value="1"/>
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_11" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_10" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_9" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_8" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_7" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_0"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
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
    <Task key="Task_5" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_4" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_3" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_2" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
    <Task key="Task_1" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="true" updateModel="false">
      <Report reference="Report_22" target="HuangFerrel_lna.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_0"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_13" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
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
    <Report key="Report_10" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_8" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_7" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_6" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_4" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_1" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_0" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_22" name="Speed test" taskType="timeCourse" separator="&#x09;" precision="8">
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T20:12:17Z</dcterms:W3CDTF>
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
