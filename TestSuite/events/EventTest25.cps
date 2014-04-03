<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.12.78+ (Debug) (http://www.copasi.org) at 2014-04-03 18:41:28 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="12" versionDevel="77" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_40" name="mass action arrheinius [1] [1]" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-06-15T14:13:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v*exp((65000+E_diff*a)/8.31447*(T2-T1)/(T1*T2))*S
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="v" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_258" name="a" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="T2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_268" name="T1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_270" name="S" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_254" name="E_diff" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="translation arrhenius" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-06-15T14:14:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v*exp((65000+a*E_diff)/8.31447*(T2-T1)/(T1*T2))*M
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_271" name="v" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="a" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_272" name="T2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_274" name="T1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_276" name="M" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_246" name="E_diff" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="compartment mass action arrhenius" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:14:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Compartment*v*exp((65000+E_diff*a)/8.31447*(T2-T1)/(T1*T2))*S
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_277" name="Compartment" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_273" name="v" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_265" name="E_diff" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_278" name="a" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_280" name="T2" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_282" name="T1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="S" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="complex formation arrhenius" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:22:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k2b*exp((65000+E_diff*a)/8.31447*(T2-T1)/(T1*T2))*y1^q
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_285" name="k2b" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_289" name="y1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_291" name="q" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_281" name="E_diff" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_269" name="a" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_275" name="T2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_287" name="T1" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="trans_per2" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:45:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v1b*exp((65000+E_diff*a)/8.31447*(T2-T1)/(T1*T2))*(ActiveBmal1+c)/(k1b*(1+(PerCrycomplexnucleus/k1i)^n)+ActiveBmal1+c)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_292" name="v1b" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_296" name="ActiveBmal1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_298" name="c" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_300" name="k1b" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_302" name="PerCrycomplexnucleus" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_304" name="k1i" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_306" name="n" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_288" name="E_diff" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_262" name="a" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_283" name="T2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_294" name="T1" order="10" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="Bmal transcription arrhenius" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:55:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v4b*exp((65000+a*E_diff)/8.31447*(T2-T1)/(T1*T2))*M^r/(k4b^r+M^r)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_307" name="v4b" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="a" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_299" name="E_diff" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_295" name="T2" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_279" name="T1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_290" name="M" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_309" name="r" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_311" name="k4b" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_4" name="Weimann2004_CircadianOscillator" simulationType="time" timeUnit="h" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="nmol" type="deterministic" avogadroConstant="6.02214179e+23">
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
            <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:15347590"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2008-04-16T11:56:13Z</dcterms:W3CDTF>
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
        <dcterms:W3CDTF>2008-08-20T18:28:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:BIOMD0000000170"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:MODEL8378813456"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007623"/>
        <rdf:li rdf:resource="urn:miriam:taxonomy:40674"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isPartOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:hsa04710"/>
      </rdf:Bag>
    </CopasiMT:isPartOf>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
    <p>This model was automatically converted from model BIOMD0000000170 by using <a href="http://sbml.org/Software/libSBML" target="_blank">libSBML</a>.</p>
    <p>According to the <a href="http://www.ebi.ac.uk/biomodels//legal.html">BioModels Database terms of use</a>, this generated model is not related with model <a href="http://www.ebi.ac.uk/biomodels/models-main/publ/BIOMD0000000170/BIOMD0000000170.xml">BIOMD0000000170</a> any more.</p>
  </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="Nucleus" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:13:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_3" name="Cytoplasm" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:13:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_1" name="PER2_CRY_complex_nucleus" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:O15055" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q16526" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="BMAL1_nucleus" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:Q8IUT4" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="Active BMAL1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:Q8IUT4" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="Per2 or Cry mRNA" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <CopasiMT:encodes>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:O15055" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q16526" />
      </rdf:Bag>
    </CopasiMT:encodes>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00046" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A33699" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="PER2_CRY_complex_cytoplasm" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:O15055" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q16526" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="Bmal1 mRNA" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <CopasiMT:encodes>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:Q8IUT4" />
      </rdf:Bag>
    </CopasiMT:encodes>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00046" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A33699" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="BMAL1_cytoplasm" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:Q8IUT4" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="trans_per2_cry" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:25:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[v1b],Reference=Value&gt;*(&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1],Reference=Concentration&gt;+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[c],Reference=Value&gt;)/(&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1b],Reference=Value&gt;*(1+(&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[PER2_CRY_complex_nucleus],Reference=Concentration&gt;/&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1i],Reference=Value&gt;)^&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[hill_coeff],Reference=Value&gt;)+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1],Reference=Concentration&gt;+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[c],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="v1b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_2" name="c" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_3" name="k1b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_4" name="k1i" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_5" name="hill_coeff" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_6" name="v4b" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:16:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="r" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="k4b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_9" name="y5_y6_y7" simulationType="assignment">
        <Expression>
          &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[BMAL1_cytoplasm],Reference=Concentration&gt;+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[BMAL1_nucleus],Reference=Concentration&gt;+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="k1d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_11" name="k2b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_12" name="q" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_13" name="k2d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_14" name="k2t" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_15" name="k3t" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_16" name="k3d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_17" name="k4d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_18" name="k5b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_19" name="k5d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="k5t" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_21" name="k6t" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="k6d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="k6a" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:04:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="k7a" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_25" name="k7d" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="a" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:59:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="T2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:59:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="T1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:59:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="periodBmalcytoplasm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:01:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="periodBmalcytoplasm2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:01:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="peaktimeBmalcytoplasm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:01:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="entryn" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:03:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          if(abs(&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value&gt;-&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entrperiod],Reference=Value&gt;) lt 0.02,1,if(abs(&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value&gt;+&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm2],Reference=Value&gt;-2*&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entrperiod],Reference=Value&gt;) lt 0.06,2,3))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="amplitude" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:04:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="entrperiod" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:04:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="q10" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-27T11:12:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          23.88/&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="Tempchanged" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-02T12:13:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="per2_cry_transcription" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:12:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006350" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4067" name="v1b" value="9"/>
          <Constant key="Parameter_4068" name="c" value="0.1"/>
          <Constant key="Parameter_4069" name="k1b" value="1"/>
          <Constant key="Parameter_4070" name="k1i" value="0.56"/>
          <Constant key="Parameter_4071" name="n" value="8"/>
          <Constant key="Parameter_4072" name="E_diff" value="76601"/>
          <Constant key="Parameter_4073" name="a" value="1"/>
          <Constant key="Parameter_4074" name="T2" value="288"/>
          <Constant key="Parameter_4075" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_44">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Parameter_4068"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Parameter_4072"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="per2_cry_mRNA_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:12:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006402" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4076" name="v" value="0.12"/>
          <Constant key="Parameter_4077" name="a" value="1"/>
          <Constant key="Parameter_4078" name="T2" value="288"/>
          <Constant key="Parameter_4079" name="T1" value="288"/>
          <Constant key="Parameter_4080" name="E_diff" value="-60000"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4080"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="per2_cry_complex_formation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:12:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0046982" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4081" name="k2b" value="0.3"/>
          <Constant key="Parameter_4082" name="q" value="2"/>
          <Constant key="Parameter_4083" name="E_diff" value="-54973"/>
          <Constant key="Parameter_4084" name="a" value="1"/>
          <Constant key="Parameter_4085" name="T2" value="288"/>
          <Constant key="Parameter_4086" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_43">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Parameter_4083"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="cytoplasmic_per2_cry_complex_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:09:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4087" name="v" value="0.05"/>
          <Constant key="Parameter_4088" name="a" value="1"/>
          <Constant key="Parameter_4089" name="T2" value="288"/>
          <Constant key="Parameter_4090" name="T1" value="288"/>
          <Constant key="Parameter_4091" name="E_diff" value="-60000"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4091"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="per2_cry_nuclear_import" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:12:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051170" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4092" name="v" value="0.24"/>
          <Constant key="Parameter_4093" name="E_diff" value="-60000"/>
          <Constant key="Parameter_4094" name="a" value="1"/>
          <Constant key="Parameter_4097" name="T2" value="288"/>
          <Constant key="Parameter_4096" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_4093"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="per2_cry_nuclear_export" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:12:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051168" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4098" name="v" value="0.02"/>
          <Constant key="Parameter_4095" name="E_diff" value="-59999"/>
          <Constant key="Parameter_4099" name="a" value="1"/>
          <Constant key="Parameter_4100" name="T2" value="288"/>
          <Constant key="Parameter_4101" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_4095"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="nuclear_per2_cry_complex_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:11:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4102" name="v" value="0.12"/>
          <Constant key="Parameter_4103" name="a" value="1"/>
          <Constant key="Parameter_4104" name="T2" value="288"/>
          <Constant key="Parameter_4105" name="T1" value="288"/>
          <Constant key="Parameter_4106" name="E_diff" value="-60000"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="Bmal1_transcription" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006350" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4107" name="v4b" value="3.6"/>
          <Constant key="Parameter_4108" name="a" value="1"/>
          <Constant key="Parameter_4109" name="E_diff" value="35954"/>
          <Constant key="Parameter_4110" name="T2" value="288"/>
          <Constant key="Parameter_4111" name="T1" value="288"/>
          <Constant key="Parameter_4112" name="r" value="3"/>
          <Constant key="Parameter_4113" name="k4b" value="2.16"/>
        </ListOfConstants>
        <KineticLaw function="Function_45">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Parameter_4109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="Bmal1_mRNA_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006402" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4114" name="v" value="0.75"/>
          <Constant key="Parameter_4119" name="a" value="1"/>
          <Constant key="Parameter_4118" name="T2" value="288"/>
          <Constant key="Parameter_4117" name="T1" value="288"/>
          <Constant key="Parameter_4115" name="E_diff" value="-59500"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4115"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="BMAL1_translation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:08:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4116" name="v" value="0.24"/>
          <Constant key="Parameter_4120" name="a" value="1"/>
          <Constant key="Parameter_4121" name="T2" value="288"/>
          <Constant key="Parameter_4124" name="T1" value="288"/>
          <Constant key="Parameter_4123" name="E_diff" value="30721"/>
        </ListOfConstants>
        <KineticLaw function="Function_41">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="Parameter_4123"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="cytoplasmic_BMAL1_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:08:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4122" name="v" value="0.06"/>
          <Constant key="Parameter_4125" name="a" value="1"/>
          <Constant key="Parameter_4126" name="T2" value="288"/>
          <Constant key="Parameter_4127" name="T1" value="288"/>
          <Constant key="Parameter_4128" name="E_diff" value="-51846"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4128"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="BMAL1_nuclear_import" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051170" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4129" name="v" value="0.45"/>
          <Constant key="Parameter_4130" name="E_diff" value="-59672"/>
          <Constant key="Parameter_4131" name="a" value="1"/>
          <Constant key="Parameter_4132" name="T2" value="288"/>
          <Constant key="Parameter_4133" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_4130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="BMAL1_nuclear_export" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:07:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051168" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4134" name="v" value="0.06"/>
          <Constant key="Parameter_4135" name="E_diff" value="18466"/>
          <Constant key="Parameter_4136" name="a" value="1"/>
          <Constant key="Parameter_4137" name="T2" value="288"/>
          <Constant key="Parameter_4138" name="T1" value="288"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_4135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="nuclear_BMAL1_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T12:10:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4139" name="v" value="0.12"/>
          <Constant key="Parameter_4140" name="a" value="1"/>
          <Constant key="Parameter_4141" name="T2" value="288"/>
          <Constant key="Parameter_4142" name="T1" value="288"/>
          <Constant key="Parameter_4143" name="E_diff" value="-58029"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4143"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="BMAL1_activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051091" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4144" name="v" value="0.09"/>
          <Constant key="Parameter_4145" name="a" value="0.24"/>
          <Constant key="Parameter_4146" name="T2" value="288"/>
          <Constant key="Parameter_4147" name="T1" value="288"/>
          <Constant key="Parameter_4148" name="E_diff" value="-57837"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4148"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="BMAL1_deactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043433" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4149" name="v" value="0.003"/>
          <Constant key="Parameter_4172" name="a" value="1"/>
          <Constant key="Parameter_4173" name="T2" value="288"/>
          <Constant key="Parameter_4174" name="T1" value="288"/>
          <Constant key="Parameter_4175" name="E_diff" value="-16478"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4175"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="Active_BMAL1_degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T11:50:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0044257" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4176" name="v" value="0.09"/>
          <Constant key="Parameter_4177" name="a" value="1"/>
          <Constant key="Parameter_4055" name="T2" value="288"/>
          <Constant key="Parameter_4056" name="T1" value="288"/>
          <Constant key="Parameter_4057" name="E_diff" value="-57534"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_4057"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_0" name="peak Bmalcytoplasm" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-10-14T13:01:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[BMAL1_cytoplasm],Reference=Rate&gt; lt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_29">
            <Expression>
              &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time&gt;-&lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[peaktimeBmalcytoplasm],Reference=Value&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_30">
            <Expression>
              &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_31">
            <Expression>
              &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_1" name="TempChange" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-02T12:13:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time&gt; gt 400
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_27">
            <Expression>
              &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[Tempchanged],Reference=Value&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus]" value="1" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[PER2_CRY_complex_nucleus]" value="662435596900000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[BMAL1_nucleus]" value="602214179000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1]" value="632324887950000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Per2 or Cry mRNA]" value="120442835800000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[PER2_CRY_complex_cytoplasm]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Bmal1 mRNA]" value="481771343200000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[BMAL1_cytoplasm]" value="602214179000000" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[trans_per2_cry]" value="0.04264745962528374" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[v1b]" value="9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[c]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1b]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1i]" value="0.5600000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[hill_coeff]" value="8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[v4b]" value="3.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[r]" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k4b]" value="2.16" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[y5_y6_y7]" value="3.05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1d]" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2b]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[q]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2d]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2t]" value="0.24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k3t]" value="0.02" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k3d]" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k4d]" value="0.75" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5b]" value="0.24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5d]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5t]" value="0.45" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6t]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6d]" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6a]" value="0.09" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k7a]" value="0.003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k7d]" value="0.09" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2]" value="288" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1]" value="288" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm2]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[peaktimeBmalcytoplasm]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entryn]" value="3" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[amplitude]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entrperiod]" value="24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[q10]" value="INF" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[Tempchanged]" value="272.548" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=v1b" value="9" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[v1b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=c" value="0.1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=k1b" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=k1i" value="0.5600000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1i],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=n" value="8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[hill_coeff],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=E_diff" value="76601" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_transcription],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation],ParameterGroup=Parameters,Parameter=v" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k1d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_mRNA_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-60000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=k2b" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=q" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[q],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=E_diff" value="-54973" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_complex_formation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=v" value="0.05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-60000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import],ParameterGroup=Parameters,Parameter=v" value="0.24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k2t],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import],ParameterGroup=Parameters,Parameter=E_diff" value="-60000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_import],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export],ParameterGroup=Parameters,Parameter=v" value="0.02" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k3t],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export],ParameterGroup=Parameters,Parameter=E_diff" value="-59999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[per2_cry_nuclear_export],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=v" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k3d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_per2_cry_complex_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-60000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=v4b" value="3.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[v4b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=E_diff" value="35954" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=r" value="3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[r],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_transcription],ParameterGroup=Parameters,Parameter=k4b" value="2.16" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k4b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation],ParameterGroup=Parameters,Parameter=v" value="0.75" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k4d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Bmal1_mRNA_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-59500" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation],ParameterGroup=Parameters,Parameter=v" value="0.24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_translation],ParameterGroup=Parameters,Parameter=E_diff" value="30721" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation],ParameterGroup=Parameters,Parameter=v" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[cytoplasmic_BMAL1_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-51846" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import],ParameterGroup=Parameters,Parameter=v" value="0.45" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5t],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import],ParameterGroup=Parameters,Parameter=E_diff" value="-59672" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_import],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export],ParameterGroup=Parameters,Parameter=v" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6t],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export],ParameterGroup=Parameters,Parameter=E_diff" value="18466" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_nuclear_export],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation],ParameterGroup=Parameters,Parameter=v" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[nuclear_BMAL1_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-58029" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation],ParameterGroup=Parameters,Parameter=v" value="0.09" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k6a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation],ParameterGroup=Parameters,Parameter=a" value="0.24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k5b],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_activation],ParameterGroup=Parameters,Parameter=E_diff" value="-57837" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation],ParameterGroup=Parameters,Parameter=v" value="0.003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k7a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[BMAL1_deactivation],ParameterGroup=Parameters,Parameter=E_diff" value="-16478" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation],ParameterGroup=Parameters,Parameter=v" value="0.09" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[k7d],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation],ParameterGroup=Parameters,Parameter=a" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T2" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation],ParameterGroup=Parameters,Parameter=T1" value="288" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Reactions[Active_BMAL1_degradation],ParameterGroup=Parameters,Parameter=E_diff" value="-57534" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_4"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_32"/>
      <StateTemplateVariable objectReference="ModelValue_35"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
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
      <StateTemplateVariable objectReference="ModelValue_33"/>
      <StateTemplateVariable objectReference="ModelValue_34"/>
      <StateTemplateVariable objectReference="ModelValue_36"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 602214179000000 0 602214179000000 120442835800000 481771343200000 632324887950000 662435596900000 0.04264745962528374 3.05 3 INF 1 1 9 0.01 1 0.5600000000000001 8 3.6 3 2.16 0.12 0.3 2 0.05 0.24 0.02 0.12 0.75 0.24 0.06 0.45 0.06 0.12 0.09 0.003 0.09 1 288 288 0 0 0 0 24 272.548 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_12" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_17" target="EventTest25.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100000"/>
        <Parameter name="StepSize" type="float" value="0.02"/>
        <Parameter name="Duration" type="float" value="2000"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
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
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="1"/>
            <Parameter name="Minimum" type="float" value="0"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="100"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[a],Reference=InitialValue"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="log" type="bool" value="0"/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_9" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_8" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_5" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_5" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
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
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_13" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="1"/>
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
    <Report key="Report_0" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_17" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="7">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[PER2_CRY_complex_nucleus],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[BMAL1_nucleus],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Per2 or Cry mRNA],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[PER2_CRY_complex_cytoplasm],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Bmal1 mRNA],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[BMAL1_cytoplasm],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[trans_per2_cry],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[y5_y6_y7],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm2],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[peaktimeBmalcytoplasm],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entryn],Reference=Value"/>
        <Object cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[q10],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[PER2_CRY_complex_nucleus]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[PER2_CRY_complex_nucleus],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BMAL1_nucleus]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[BMAL1_nucleus],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Active BMAL1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Nucleus],Vector=Metabolites[Active BMAL1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Per2 or Cry mRNA]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Per2 or Cry mRNA],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PER2_CRY_complex_cytoplasm]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[PER2_CRY_complex_cytoplasm],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Bmal1 mRNA]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[Bmal1 mRNA],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BMAL1_cytoplasm]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Compartments[Cytoplasm],Vector=Metabolites[BMAL1_cytoplasm],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[trans_per2_cry]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[trans_per2_cry],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[y5_y6_y7]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[y5_y6_y7],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[T2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[T2],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[periodBmalcytoplasm]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[periodBmalcytoplasm2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[periodBmalcytoplasm2],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[peaktimeBmalcytoplasm]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[peaktimeBmalcytoplasm],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[entryn]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[entryn],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[q10]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[q10],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
    <ListOfSliders>
      <Slider key="Slider_0" associatedEntityKey="Task_11" objectCN="CN=Root,Model=Weimann2004_CircadianOscillator,Vector=Values[Tempchanged],Reference=InitialValue" objectType="float" objectValue="272.548" minValue="270" maxValue="298" tickNumber="1000" tickFactor="100" scaling="linear"/>
    </ListOfSliders>
  </GUI>
  <SBMLReference file="BIOMD0000000170_SBML-L2V4.xml">
    <SBMLMap SBMLid="Active_BMAL1_degradation" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="BMAL1_activation" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="BMAL1_deactivation" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="BMAL1_nuclear_export" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="BMAL1_nuclear_import" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="BMAL1_translation" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="Bmal1_mRNA_degradation" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="Bmal1_transcription" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="Cytoplasm" COPASIkey="Compartment_3"/>
    <SBMLMap SBMLid="Nucleus" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="c" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="cytoplasmic_BMAL1_degradation" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="cytoplasmic_per2_cry_complex_degradation" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="hill_coeff" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="k1b" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="k1d" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="k1i" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="k2b" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="k2d" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="k2t" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="k3d" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="k3t" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="k4b" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="k4d" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="k5b" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="k5d" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="k5t" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="k6a" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="k6d" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="k6t" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="k7a" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="k7d" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="nuclear_BMAL1_degradation" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="nuclear_per2_cry_complex_degradation" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="per2_cry_complex_formation" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="per2_cry_mRNA_degradation" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="per2_cry_nuclear_export" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="per2_cry_nuclear_import" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="per2_cry_transcription" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="q" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="r" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="trans_per2_cry" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="v1b" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="v4b" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="y1" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="y2" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="y3" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="y4" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="y5" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="y5_y6_y7" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="y6" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="y7" COPASIkey="Metabolite_5"/>
  </SBMLReference>
</COPASI>
