<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2021-01-02T20:17:20Z -->
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
    <Function key="Function_105" name="Prot synth" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_105">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*mRNA/(K+mRNA)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1729" name="mRNA" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1728" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1727" name="K" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_106" name="mRNA synthesis w/ repressor &amp; inducer" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_106">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V/(1+(Repressor/Kr)^hr +(Ki/Inducer)^hi)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1724" name="Repressor" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1725" name="Inducer" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1726" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1723" name="Kr" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1730" name="hr" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1731" name="Ki" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1732" name="hi" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_107" name="MM(expl. enzyme) (forward part)" type="Function" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_107">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*E*S/(S+Kms*(1+P/Kmp))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1715" name="S" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1714" name="P" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1713" name="E" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1712" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1710" name="Kms" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1709" name="Kmp" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_108" name="MM(expl. enzyme) (backward part)" type="Function" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_108">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*E*(P/Keq)/(S+Kms*(1+P/Kmp))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1703" name="S" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1704" name="P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1705" name="E" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1706" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1707" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1708" name="Kms" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1711" name="Kmp" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="3-enzyme linear pathway with gene expression" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_1">
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:isbn:9780262277204"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T15:47:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Description>
        <vCard:EMAIL>pmendes@uchc.edu</vCard:EMAIL>
        <vCard:N>
          <rdf:Description>
            <vCard:Family>Pedro</vCard:Family>
            <vCard:Given>Mendes</vCard:Given>
          </rdf:Description>
        </vCard:N>
        <vCard:ORG>
          <rdf:Description>
            <vCard:Orgname>University of Connecticut School of Medicine</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      We attempt to fit 36 parameters of this model against 1 trajectory. This is the problem first proposed in Mendes (2001) "Modeling large scale biological systems from functional genomic data: parameter estimation" in Foundations of Systems Biology (Kitano ed.) MIT Press, 
Cambidge, MA, pp. 163-186.
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_3" name="compartment" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Compartment_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_77" name="S" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_77">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_78" name="M1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_78">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:03:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_79" name="M2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_79">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_80" name="P" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_80">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_81" name="E1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_81">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_82" name="E2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_83" name="E3" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:04:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_84" name="G1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_84">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:05:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_85" name="G2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:05:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_86" name="G3" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:05:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_71" name="R4" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_84" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4864" name="V" value="0.001"/>
          <Constant key="Parameter_4867" name="K" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_105" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1729">
              <SourceParameter reference="Metabolite_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1728">
              <SourceParameter reference="Parameter_4864"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1727">
              <SourceParameter reference="Parameter_4867"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_72" name="E1d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_72">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-05-23T21:20:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4870" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4870"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_73" name="E2s" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4871" name="V" value="0.001"/>
          <Constant key="Parameter_4905" name="K" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_105" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1729">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1728">
              <SourceParameter reference="Parameter_4871"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1727">
              <SourceParameter reference="Parameter_4905"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_74" name="E2d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4906" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4906"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_75" name="E3s" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4910" name="V" value="0.001"/>
          <Constant key="Parameter_4912" name="K" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_105" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1729">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1728">
              <SourceParameter reference="Parameter_4910"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1727">
              <SourceParameter reference="Parameter_4912"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_76" name="E3d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4913" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4913"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_77" name="G1s" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_84" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_80" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4907" name="V" value="0.001"/>
          <Constant key="Parameter_4909" name="Kr" value="0.001"/>
          <Constant key="Parameter_4908" name="hr" value="1"/>
          <Constant key="Parameter_4911" name="Ki" value="0.001"/>
          <Constant key="Parameter_4914" name="hi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1724">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1725">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1726">
              <SourceParameter reference="Parameter_4907"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1723">
              <SourceParameter reference="Parameter_4909"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1730">
              <SourceParameter reference="Parameter_4908"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1731">
              <SourceParameter reference="Parameter_4911"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1732">
              <SourceParameter reference="Parameter_4914"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_78" name="G1d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_84" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4903" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4903"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_84"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_79" name="G2s" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_80" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4901" name="V" value="0.001"/>
          <Constant key="Parameter_4900" name="Kr" value="0.001"/>
          <Constant key="Parameter_4904" name="hr" value="1"/>
          <Constant key="Parameter_4902" name="Ki" value="0.001"/>
          <Constant key="Parameter_4875" name="hi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1724">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1725">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1726">
              <SourceParameter reference="Parameter_4901"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1723">
              <SourceParameter reference="Parameter_4900"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1730">
              <SourceParameter reference="Parameter_4904"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1731">
              <SourceParameter reference="Parameter_4902"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1732">
              <SourceParameter reference="Parameter_4875"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_80" name="G2d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4873" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4873"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_81" name="G3s" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_80" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4872" name="V" value="0.001"/>
          <Constant key="Parameter_4876" name="Kr" value="0.001"/>
          <Constant key="Parameter_4874" name="hr" value="1"/>
          <Constant key="Parameter_4890" name="Ki" value="0.001"/>
          <Constant key="Parameter_4891" name="hi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1724">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1725">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1726">
              <SourceParameter reference="Parameter_4872"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1723">
              <SourceParameter reference="Parameter_4876"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1730">
              <SourceParameter reference="Parameter_4874"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1731">
              <SourceParameter reference="Parameter_4890"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1732">
              <SourceParameter reference="Parameter_4891"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_82" name="G3d" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-22T20:36:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4878" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4878"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_67" name="R1 (forward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_78" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4601" name="kcat" value="0.001"/>
          <Constant key="Parameter_4597" name="Kms" value="0.001"/>
          <Constant key="Parameter_4594" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_107" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1715">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1714">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1713">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1712">
              <SourceParameter reference="Parameter_4601"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1710">
              <SourceParameter reference="Parameter_4597"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1709">
              <SourceParameter reference="Parameter_4594"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_66" name="R1 (backward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_77" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4595" name="kcat" value="0.001"/>
          <Constant key="Parameter_4600" name="Keq" value="1"/>
          <Constant key="Parameter_4620" name="Kms" value="0.001"/>
          <Constant key="Parameter_4598" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_108" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1703">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1704">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1705">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1706">
              <SourceParameter reference="Parameter_4595"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1707">
              <SourceParameter reference="Parameter_4600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1708">
              <SourceParameter reference="Parameter_4620"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1711">
              <SourceParameter reference="Parameter_4598"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_65" name="R2 (forward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_79" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4638" name="kcat" value="0.001"/>
          <Constant key="Parameter_4621" name="Kms" value="0.001"/>
          <Constant key="Parameter_4639" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_107" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1715">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1714">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1713">
              <SourceParameter reference="Metabolite_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1712">
              <SourceParameter reference="Parameter_4638"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1710">
              <SourceParameter reference="Parameter_4621"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1709">
              <SourceParameter reference="Parameter_4639"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_64" name="R2 (backward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_78" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4623" name="kcat" value="0.001"/>
          <Constant key="Parameter_4622" name="Keq" value="1"/>
          <Constant key="Parameter_4625" name="Kms" value="0.001"/>
          <Constant key="Parameter_4624" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_108" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1703">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1704">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1705">
              <SourceParameter reference="Metabolite_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1706">
              <SourceParameter reference="Parameter_4623"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1707">
              <SourceParameter reference="Parameter_4622"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1708">
              <SourceParameter reference="Parameter_4625"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1711">
              <SourceParameter reference="Parameter_4624"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="R3 (forward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_80" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_80" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4627" name="kcat" value="0.001"/>
          <Constant key="Parameter_4626" name="Kms" value="0.001"/>
          <Constant key="Parameter_4629" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_107" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1715">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1714">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1713">
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1712">
              <SourceParameter reference="Parameter_4627"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1710">
              <SourceParameter reference="Parameter_4626"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1709">
              <SourceParameter reference="Parameter_4629"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="R3 (backward)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:15:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_80" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_79" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4628" name="kcat" value="0.001"/>
          <Constant key="Parameter_4632" name="Keq" value="1"/>
          <Constant key="Parameter_4630" name="Kms" value="0.001"/>
          <Constant key="Parameter_4631" name="Kmp" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_108" unitType="Default" scalingCompartment="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1703">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1704">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1705">
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1706">
              <SourceParameter reference="Parameter_4628"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1707">
              <SourceParameter reference="Parameter_4632"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1708">
              <SourceParameter reference="Parameter_4630"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1711">
              <SourceParameter reference="Parameter_4631"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T20:12:53Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[S]" value="6.0221417900000003e+21" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[M1]" value="7.0870695083104259e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[M2]" value="7.0865349528161616e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[P]" value="6.0221417900000005e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[E1]" value="22958.38940507374" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[E2]" value="402.46337476016924" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[E3]" value="2.7279104015323996e+32" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[G1]" value="630236741142.9967" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[G2]" value="124.54333272455122" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Compartments[compartment],Vector=Metabolites[G3]" value="9.4808166436095119e+20" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R4],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R4],ParameterGroup=Parameters,Parameter=K" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E1d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E1d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E2s]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E2s],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E2s],ParameterGroup=Parameters,Parameter=K" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E2d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E2d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E3s]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E3s],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E3s],ParameterGroup=Parameters,Parameter=K" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E3d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[E3d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s],ParameterGroup=Parameters,Parameter=Kr" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s],ParameterGroup=Parameters,Parameter=hr" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s],ParameterGroup=Parameters,Parameter=Ki" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1s],ParameterGroup=Parameters,Parameter=hi" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G1d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s],ParameterGroup=Parameters,Parameter=Kr" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s],ParameterGroup=Parameters,Parameter=hr" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s],ParameterGroup=Parameters,Parameter=Ki" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2s],ParameterGroup=Parameters,Parameter=hi" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G2d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s],ParameterGroup=Parameters,Parameter=V" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s],ParameterGroup=Parameters,Parameter=Kr" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s],ParameterGroup=Parameters,Parameter=hr" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s],ParameterGroup=Parameters,Parameter=Ki" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3s],ParameterGroup=Parameters,Parameter=hi" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3d]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[G3d],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (forward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (forward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (forward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (backward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (backward)],ParameterGroup=Parameters,Parameter=Keq" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (backward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R1 (backward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (forward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (forward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (forward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (backward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (backward)],ParameterGroup=Parameters,Parameter=Keq" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (backward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R2 (backward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (forward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (forward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (forward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (forward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (backward)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (backward)],ParameterGroup=Parameters,Parameter=kcat" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (backward)],ParameterGroup=Parameters,Parameter=Keq" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (backward)],ParameterGroup=Parameters,Parameter=Kms" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=3-enzyme linear pathway with gene expression,Vector=Reactions[R3 (backward)],ParameterGroup=Parameters,Parameter=Kmp" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_78"/>
      <StateTemplateVariable objectReference="Metabolite_79"/>
      <StateTemplateVariable objectReference="Metabolite_81"/>
      <StateTemplateVariable objectReference="Metabolite_82"/>
      <StateTemplateVariable objectReference="Metabolite_83"/>
      <StateTemplateVariable objectReference="Metabolite_84"/>
      <StateTemplateVariable objectReference="Metabolite_85"/>
      <StateTemplateVariable objectReference="Metabolite_86"/>
      <StateTemplateVariable objectReference="Metabolite_77"/>
      <StateTemplateVariable objectReference="Metabolite_80"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 7.0870695083104259e+20 7.0865349528161616e+20 22958.38940507374 402.46337476016924 2.7279104015323996e+32 630236741142.9967 124.54333272455122 9.4808166436095119e+20 6.0221417900000003e+21 6.0221417900000005e+20 1 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_28" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_21" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="0"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="0"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Maximum duration for forward integration" type="unsignedFloat" value="1000000000"/>
        <Parameter name="Maximum duration for backward integration" type="unsignedFloat" value="1000000"/>
        <Parameter name="Target Criterion" type="string" value="Distance and Rate"/>
      </Method>
    </Task>
    <Task key="Task_27" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="1"/>
        <Parameter name="StepSize" type="float" value="120"/>
        <Parameter name="Duration" type="float" value="120"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_26" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Report reference="Report_23" target="3enzyme_tn.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="5"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
        <Parameter name="Continue on Error" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_25" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_24" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_23" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="0"/>
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
      <Method name="Truncated Newton" type="TruncatedNewton">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_22" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_28"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_20" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_19" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_18" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_17" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="true" updateModel="false">
      <Report reference="Report_23" target="3enzyme_lna.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_28"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_16" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_29" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
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
    <Report key="Report_21" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_20" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_19" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_18" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_17" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_15" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_14" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_13" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_12" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_11" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_23" name="Speed test" taskType="linearNoiseApproximation" separator="&#x09;" precision="8">
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
