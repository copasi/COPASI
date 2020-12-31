<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2020-12-31T14:59:23Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="30" versionDevel="237" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
   <rdf:Description rdf:about="#Function_13">
   <CopasiMT:is rdf:resource="urn:miriam:obo.sbo:SBO:0000163" />
   </rdf:Description>
   </rdf:RDF>
      </MiriamAnnotation>
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
<b>Mass action rate law for irreversible reactions</b>
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
  <Model key="Model_0" name="Vilar2002_Oscillator" simulationType="time" timeUnit="h" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="#" type="deterministic" avogadroConstant="6.0221408570000002e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_0">
    <bqbiol:hasTaxon>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/taxonomy/131567"/>
      </rdf:Bag>
    </bqbiol:hasTaxon>
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:doi:10.1073/pnas.092133899"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:11972055"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2005-06-30T10:20:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Description>
        <vCard:EMAIL>pmendes@uchc.edu</vCard:EMAIL>
        <vCard:N>
          <rdf:Description>
            <vCard:Family>Mendes</vCard:Family>
            <vCard:Given>Pedro</vCard:Given>
          </rdf:Description>
        </vCard:N>
        <vCard:ORG>
          <rdf:Description>
            <vCard:Orgname>University of Connecticut</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>bshapiro@caltech.edu</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Shapiro</vCard:Family>
                <vCard:Given>Bruce</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>Jet Propulsion Laboratory</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>lenov@ebi.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Le Novère</vCard:Family>
                <vCard:Given>Nicolas</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>EMBL-EBI</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:creator>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-03T13:58:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-30T19:49:56</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/biomodels.db/MODEL6619651140"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/biomodels.db/BIOMD0000000035"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0042752"/>
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
    <h1>
      <h1>Minimal Model for Circadian Oscillations</h1>
    </h1>
    <table cellspacing="0" cellpadding="2" border="0">
      <thead>
        <tr>
          <th valign="middle" bgcolor="#eeeeee" align="left">Citation</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>Vilar JMG, Kueh HY, Barkai N, Leibler S,
							 (2002)
							. Mechanisms of noise resistance in genetic oscillators,
							  <a href="https://doi.org/10.1073/pnas.092133899">PNAS, 99(9):5988-5992</a>.</td>
        </tr>
      </tbody>
    </table>
    <table cellspacing="0" cellpadding="2" border="0">
      <thead>
        <tr>
          <th valign="middle" bgcolor="#eeeeee" align="left">Description</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>A minimal model of genomically based oscillation,
							 based on two mutually interacting genes,
							 an activator and a repressor. Postive feedback is provided by the activator protein,
							 which binds to the promotors of both the activator and the repressor genes. Negative feedback is provided by the repressor protein which binds to the activator protein.</td>
        </tr>
      </tbody>
    </table>
    <p>Based on a model  created by B.E. Shapiro and available as BIOMD0000000035 in the  BioModels Database. Further adapted to better fit the original publication by Pedro Mendes.</p>
<p>Copyright (c) 2005-2009 The BioModels Team. </p>
  </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cell" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-30T21:31:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_33" name="A" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:36080" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="C" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:36080" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="DA" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-30T21:31:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="DAp" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-30T21:31:35Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="DR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-30T21:31:35Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="DRp" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-30T21:31:35Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="MA" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:33699" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="MR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:33699" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="R" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:36080" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_12" name="theta_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_12">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:23:57Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="gamma_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_13">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:06Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="theta_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_14">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:11Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="gamma_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:16Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="alphap_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:43Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="alpha_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:49Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="delta_MA" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:24:58Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="beta_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="gamma_C" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:17Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="delta_A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="alphap_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:34Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="alpha_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:39Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="delta_MR" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:47Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="beta_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:25:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="delta_R" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:27:58Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_45" name="Reaction1" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006461" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4469" name="k1" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_44" name="Reaction2" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0030163" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7174" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_43" name="Reaction3" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0030163" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4491" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_42" name="Reaction4" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0030163" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4490" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_41" name="Reaction5" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0016563" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4498" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_40" name="Reaction6" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0032986" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4499" name="k1" value="50"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
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
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_39" name="Reaction7" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006351" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4495" name="k1" value="50"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_38" name="Reaction8" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006351" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4487" name="k1" value="500"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_37" name="Reaction9" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006402" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4493" name="k1" value="1000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_36" name="Reaction10" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006412" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4494" name="k1" value="5000"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_35" name="Reaction11" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0010843" />
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0016563" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4500" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_34" name="Reaction12" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0032986" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4540" name="k1" value="100"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_33" name="Reaction13" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006351" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4496" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_32" name="Reaction14" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006351" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4492" name="k1" value="50"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_0" name="Reaction15" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006402" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4539" name="k1" value="50"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15],Reference=ParticleFlux>))
        </NoiseExpression>
      </Reaction>
      <Reaction key="Reaction_1" name="Reaction16" reversible="false" fast="false" addNoise="true">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/obo.go/GO:0006412" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4535" name="k1" value="500"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
        <NoiseExpression>
          sqrt(abs(&lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16],Reference=ParticleFlux>))
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
<dcterms:W3CDTF>2020-12-31T14:58:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[A]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[C]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DA]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DAp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DR]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DRp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MA]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[R]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R]" value="100" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA]" value="1000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A]" value="5000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R]" value="0.20000000000000001" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1],ParameterGroup=Parameters,Parameter=k1" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4],ParameterGroup=Parameters,Parameter=k1" value="0.20000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10],ParameterGroup=Parameters,Parameter=k1" value="5000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12],ParameterGroup=Parameters,Parameter=k1" value="100" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13],ParameterGroup=Parameters,Parameter=k1" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
      <ModelParameterSet key="ModelParameterSet_7" name="Fig.1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelParameterSet_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T00:54:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[A]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[C]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DA]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DAp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DR]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DRp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MA]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[R]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R]" value="100" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA]" value="10" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R]" value="0.20000000000000001" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1],ParameterGroup=Parameters,Parameter=k1" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4],ParameterGroup=Parameters,Parameter=k1" value="0.20000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9],ParameterGroup=Parameters,Parameter=k1" value="10" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12],ParameterGroup=Parameters,Parameter=k1" value="100" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13],ParameterGroup=Parameters,Parameter=k1" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15],ParameterGroup=Parameters,Parameter=k1" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16],ParameterGroup=Parameters,Parameter=k1" value="5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
      <ModelParameterSet key="ModelParameterSet_6" name="Fig.5">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_6">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T00:54:07Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[A]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[C]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DA]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DAp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DR]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DRp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MA]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[R]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R]" value="100" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA]" value="10" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R]" value="0.050000000000000003" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1],ParameterGroup=Parameters,Parameter=k1" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9],ParameterGroup=Parameters,Parameter=k1" value="10" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12],ParameterGroup=Parameters,Parameter=k1" value="100" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13],ParameterGroup=Parameters,Parameter=k1" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15],ParameterGroup=Parameters,Parameter=k1" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16],ParameterGroup=Parameters,Parameter=k1" value="5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
      <ModelParameterSet key="ModelParameterSet_5" name="Fig.7">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelParameterSet_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T00:54:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[A]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[C]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DA]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DAp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DR]" value="1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[DRp]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MA]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[MR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Compartments[cell],Vector=Metabolites[R]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R]" value="100" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA]" value="1000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A]" value="5000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R]" value="500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R]" value="0.20000000000000001" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction1],ParameterGroup=Parameters,Parameter=k1" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_C],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction2],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction3],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction4],ParameterGroup=Parameters,Parameter=k1" value="0.20000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction5],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction6],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction7],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction8],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction9],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MA],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction10],ParameterGroup=Parameters,Parameter=k1" value="5000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_A],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction11],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[gamma_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction12],ParameterGroup=Parameters,Parameter=k1" value="100" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[theta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction13],ParameterGroup=Parameters,Parameter=k1" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alpha_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction14],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[alphap_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction15],ParameterGroup=Parameters,Parameter=k1" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[delta_MR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Vilar2002_Oscillator,Vector=Reactions[Reaction16],ParameterGroup=Parameters,Parameter=k1" value="500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Vilar2002_Oscillator,Vector=Values[beta_R],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 0 0 1 1 0 0 0 1 50 1 100 1 500 50 1000 5000 2 1 50 0.01 50 500 0.20000000000000001 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_0" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_23" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1.0000000000000001e-09"/>
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
    <Task key="Task_12" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_0" target="Vilar2002_adaptivetauleap.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="10000"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="10000"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="0"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
      </Problem>
      <Method name="Stochastic (Adaptive SSA/τ-Leap)" type="AdaptiveSA">
        <Parameter name="Epsilon" type="float" value="0.029999999999999999"/>
        <Parameter name="Max Internal Steps" type="integer" value="1000000"/>
        <Parameter name="Use Random Seed" type="bool" value="0"/>
        <Parameter name="Random Seed" type="unsignedInteger" value="1"/>
      </Method>
    </Task>
    <Task key="Task_11" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="Vilar2002_tauleap.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Number of steps" type="unsignedInteger" value="10"/>
            <Parameter name="Type" type="unsignedInteger" value="0"/>
            <Parameter name="Object" type="cn" value=""/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
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
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="0.0001"/>
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
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
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
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_1" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
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
    <Report key="Report_23" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_1" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_0" name="Speed test" taskType="timeCourse" separator="&#x09;" precision="8">
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
  <SBMLReference file="BIOMD0000000035_url.xml">
    <SBMLMap SBMLid="A" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="C" COPASIkey="Metabolite_32"/>
    <SBMLMap SBMLid="DA" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="DAp" COPASIkey="Metabolite_30"/>
    <SBMLMap SBMLid="DR" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="DRp" COPASIkey="Metabolite_28"/>
    <SBMLMap SBMLid="MA" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="MR" COPASIkey="Metabolite_26"/>
    <SBMLMap SBMLid="R" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="Reaction1" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="Reaction10" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="Reaction11" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="Reaction12" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="Reaction13" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="Reaction14" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="Reaction15" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="Reaction16" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="Reaction2" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="Reaction3" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="Reaction4" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="Reaction5" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="Reaction6" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="Reaction7" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="Reaction8" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="Reaction9" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="deterministicOscillator" COPASIkey="Compartment_0"/>
  </SBMLReference>
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
    <UnitDefinition key="Unit_67" name="hour" symbol="h">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        3600*s
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
