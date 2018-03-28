<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.23.178+ (Debug) (http://www.copasi.org) at 2018-03-28 21:08:09 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="23" versionDevel="178" copasiSourcesModified="1">
  <ListOfFunctions>
    <Function key="Function_6" name="Constant flux (irreversible)" type="PreDefined" reversible="false">
      <Expression>
        v
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_49" name="v" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_7" name="Constant flux (reversible)" type="PreDefined" reversible="true">
      <Expression>
        v
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_48" name="v" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-10T16:15:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
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
    <Function key="Function_40" name="Mass Action (irreversible, two substrates)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-10T16:14:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k1*substrate1*substrate2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_263" name="substrate1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_262" name="substrate2" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="06F_IP3 [1]" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:41:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*modifier
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_265" name="k" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_250" name="modifier" order="1" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="5F_PLC activation [1]" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:42:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k_e2 * Gaq* PLC / (PLC + k_Ee)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_266" name="k_e2" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="Gaq" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_267" name="PLC" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_268" name="k_Ee" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="actN special [1]" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:43:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*substrate*(1-actN)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_272" name="k" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_271" name="substrate" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_270" name="actN" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="Nuclear Import [1]" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T18:01:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        substrate*k*v_beginning
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_274" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_273" name="k" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_269" name="v_beginning" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="17" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:43:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*modifier/(kd+modifier)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_277" name="kcat" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_276" name="modifier" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_275" name="kd" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="16" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:43:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*modifier^2/(kd^2+modifier^2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_280" name="kcat" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_279" name="modifier" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_278" name="kd" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Pratap2016" simulationType="time" timeUnit="min" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="µmol" type="deterministic" avogadroConstant="6.0221408570000002e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T13:52:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      Mathematical modeling of gonadotropin-releasing hormone signaling

Amitesh Pratapc, 1, Kathryn L. Garnerc, 1, Margaritis Voliotisb, 1, Krasimira Tsaneva-Atanasovaa, b, Craig A. McArdlec, , 

http://dx.doi.org/10.1016/j.mce.2016.08.022
http://www.sciencedirect.com/science/article/pii/S0303720716303161

ABSTRACT
Gonadotropin-releasing hormone (GnRH) acts via G-protein coupled receptors on pituitary gonadotropes to control reproduction. These are Gq-coupled receptors that mediate acute effects of GnRH on the exocytotic secretion of luteinizing hormone (LH) and follicle-stimulating hormone (FSH), as well as the chronic regulation of their synthesis. GnRH is secreted in short pulses and GnRH effects on its target cells are dependent upon the dynamics of these pulses. Here we overview GnRH receptors and their signaling network, placing emphasis on pulsatile signaling, and how mechanistic mathematical models and an information theoretic approach have helped further this field.
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cytosol" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-31T10:55:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_1" name="nucleus" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-31T10:55:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Reference=InitialVolume>/&lt;CN=Root,Model=Pratap2016,Vector=Values[C_cn],Reference=InitialValue>
        </InitialExpression>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="GnRH" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-03T15:39:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          0.1
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="R_free" simulationType="assignment" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T14:00:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[R_0],Reference=Value>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_fin],Reference=Concentration>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11_act],Reference=Concentration>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="HR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-08T15:34:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="PLC" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T19:58:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[PLC_0],Reference=InitialValue>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="G_aq11" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-08T15:38:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="G_aq11_act" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-08T15:38:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="PLC_act" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-08T15:38:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          1*10^(-7)
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="act_N" simulationType="assignment" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T15:59:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[k_mn],Reference=Value>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>*(1+&lt;CN=Root,Model=Pratap2016,Vector=Values[k_d1],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[M],Reference=Value>))
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="N_active" simulationType="assignment" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T21:58:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[N_tot],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[act_N],Reference=Concentration>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="Ca2+_cytosol" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T20:09:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Die Konzentration bezieht sich nicht auf das Volumen des Zytosols, sondern auf die ganze Zelle
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_10" name="IP3" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-15T17:26:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="MEK_act" simulationType="assignment" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T15:51:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[MEK_t],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_MEK],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_de],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=Concentration>)
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="E_c" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:00:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="Epp_c" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:00:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_14" name="E_n" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:00:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="Epp_n" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:00:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="Ep_c" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T15:57:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="EGR1" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-05-01T18:54:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          1e-3
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="TF2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:09:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="NFAT_c" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:03:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="NFAT_n" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:03:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="NFATp_c" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:01:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="NFATp_n" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:03:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="Ca2+_total" simulationType="assignment" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T20:28:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_ER],Reference=Concentration>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="Ca2+_ER" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:47:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Die Konzentration bezieht sich nicht auf das Volumen des ER, sondern auf die ganze Zelle
        </Comment>
        <InitialExpression>
          1.29533*10^(+2)-0.322
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="R_mid" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:41:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="R_fin" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:40:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="h" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-12T10:21:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="GSU_par_OR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_29" name="GSU_par_AND" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_30" name="GSU_par_COOP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_31" name="GSU_seq_OR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_32" name="GSU_seq_AND" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_33" name="GSU_seq_COOP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_34" name="GSU_seq_OR_copy" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="R_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T14:51:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="k_1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:50:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="k_(-1)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T15:02:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_3" name="k_2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T15:02:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="k_(-2)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T15:02:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="k_3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T15:02:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="k_(-3)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T15:02:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="epsilon" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T20:33:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="sigma" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T17:22:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_9" name="V_p" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-30T16:26:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="K_p" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_11" name="V_e" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T14:55:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="K_e" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T20:56:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="J_in" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-14T15:58:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="L" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:03:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="P" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T21:16:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="A" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-30T12:54:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="K_i" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:09:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="K_a" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:09:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="K_d" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="k_d1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_21" name="k_f1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="k_r1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="k_f2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-19T14:40:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="k_f3" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_25" name="k_f4" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="k_mn" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_27" name="M" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T21:13:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="n" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T15:18:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="N_tot" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-07T13:49:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="C_cn" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-07T13:50:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="k_1cat" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T15:51:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="k_2cat" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-14T16:35:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="h1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_34" name="h2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:07:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="h3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T15:58:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="h4" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T15:58:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="h5" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T15:58:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="h6" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T15:58:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="k_catMKPn" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-19T15:58:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="k_dppEn" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_41" name="MEK_t" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:24:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="MKP_n" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T15:18:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="K_de" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_44" name="MKP_3t" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T15:18:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="M_tot" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:12:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="K_impE" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-19T15:58:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="k_expE" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T22:30:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="G_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T14:49:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="k_catTF1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T15:04:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="k_catTF2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-20T22:14:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="K_dppETF1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_52" name="K_dTF1TF2" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_53" name="k_11" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_54" name="kk_2" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_55" name="kk_3" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_56" name="k_33" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_57" name="k_3intmid" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_58" name="Km_1intmid" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_59" name="k_4int" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_60" name="k_4intmid" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_61" name="k_e2" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_62" name="k_(-e2)" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_63" name="PLC_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T17:52:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_64" name="l_base" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_64">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-02T16:21:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="d_TF2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_65">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-07T13:50:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_66" name="d_GSU" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_66">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:51:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_67" name="K_comp" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_67">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-07T14:21:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_68" name="K_dTF1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_69" name="K_dTF2" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_70" name="kk_1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_70">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:12:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_71" name="h_11" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="h_33" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_73" name="h_44" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_74" name="h_66" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_75" name="fi/Vi" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_75">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-07T13:50:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          6e-5
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="k_3int" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_76">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T20:47:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_77" name="Km_1int" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_78" name="Km_2intmid" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_79" name="n_int" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_79">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T21:15:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_80" name="l_dp" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_80">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-02T16:21:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="l_exp" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_81">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T21:13:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="l_imp" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-06T10:32:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Unit>
          1/min
        </Unit>
      </ModelValue>
      <ModelValue key="ModelValue_83" name="K_Ee" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_84" name="k_(-4)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_84">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-31T11:56:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-3)],Reference=InitialValue>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_85" name="k_MEK" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T16:46:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_86" name="k_4cat" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T00:44:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[h6],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h_33],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Values[h_44],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>)/(&lt;CN=Root,Model=Pratap2016,Vector=Values[h3],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[h4],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_87" name="k_m1" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_87">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T00:50:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Values[k_11],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[kk_2],Reference=Value>)/&lt;CN=Root,Model=Pratap2016,Vector=Values[kk_1],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="k_m2" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_88">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T00:53:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Values[k_33],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[kk_4],Reference=Value>)/&lt;CN=Root,Model=Pratap2016,Vector=Values[kk_3],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_89" name="kk_4" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_90" name="k_m3" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_90">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T00:58:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Values[h_11],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h2],Reference=Value>)/(&lt;CN=Root,Model=Pratap2016,Vector=Values[h1],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h2],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[h1],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[h3],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_91" name="k_m4" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_91">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T01:01:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h_44],Reference=Value>)/(&lt;CN=Root,Model=Pratap2016,Vector=Values[h4],Reference=Value>*(1+&lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[h6],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h_33],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Values[h_44],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[h5],Reference=Value>)/(&lt;CN=Root,Model=Pratap2016,Vector=Values[h4],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[h3],Reference=Value>)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_92" name="k_m5" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T01:09:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[h6],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[h_66],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_93" name="k3cat" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-29T15:03:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[h2],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Values[h2],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[h3],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_94" name="d_TF1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_94">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-03T00:00:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_95" name="k_r3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_95">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-02T16:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_96" name="dh/dt" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_96">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T20:39:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[A],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_d],Reference=Value>-(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_d],Reference=Value>)*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[h],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_97" name="act_N" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[k_mn],Reference=Value>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n],Reference=Value>*(1+&lt;CN=Root,Model=Pratap2016,Vector=Values[k_d1],Reference=Value>/&lt;CN=Root,Model=Pratap2016,Vector=Values[M],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_98" name="v_2" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_98">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:54:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_2cat],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m1],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_99" name="v_4" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_99">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:53:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_4cat],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[MKP_3t],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m4],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m5],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m3],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m4],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_100" name="v_3" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_100">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:54:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k3cat],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[MKP_3t],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m3],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m5],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m4],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m3],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_101" name="v_1" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_101">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:53:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_1cat],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m1],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m1],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_102" name="J_impE" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_2cat],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value>/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[k_m1],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_103" name="J_expE" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_103">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:41:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[E_n],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_expE],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_104" name="v_5" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_104">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:54:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_catMKPn],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[MKP_n],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Values[k_dppEn],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_105" name="spike_period" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:49:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_106" name="spike_length" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:49:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_107" name="v_07F" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:02:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[J_in],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Values[fi/Vi],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Values[epsilon],Reference=InitialValue>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_108" name="v_07B" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_108">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:02:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[epsilon],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Values[fi/Vi],Reference=InitialValue>*(&lt;CN=Root,Model=Pratap2016,Vector=Values[V_p],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^2/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_p],Reference=InitialValue>^2+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^2))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_109" name="v_08F" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_109">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:02:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[fi/Vi],Reference=InitialValue>*((&lt;CN=Root,Model=Pratap2016,Vector=Values[L],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[P],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[IP3],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[h],Reference=Concentration>/((&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[IP3],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_i],Reference=Value>)*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_a],Reference=Value>)))^3)*((&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_total],Reference=Concentration>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>)/&lt;CN=Root,Model=Pratap2016,Vector=Values[sigma],Reference=InitialValue>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_110" name="v_08B" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_110">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:02:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[fi/Vi],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^2*&lt;CN=Root,Model=Pratap2016,Vector=Values[V_e],Reference=InitialValue>/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_e],Reference=InitialValue>^2+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration>^2)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_111" name="spike_amplitude" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_111">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:12:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_112" name="NFAT(N:C)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_112">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-18T18:12:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>)/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFATp_c],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_113" name="ERK(N:C)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_113">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-18T18:14:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[E_n],Reference=Concentration>)/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_114" name="quantity" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_114">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T02:14:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_115" name="v_03F" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:35:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_3intmid],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration>*(&lt;CN=Root,Model=Pratap2016,Vector=Values[R_0mid],Reference=Value>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration>)/(&lt;CN=Root,Model=Pratap2016,Vector=Values[R_0mid],Reference=Value>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[Km_1intmid],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_116" name="R_0mid" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_116">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:37:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_117" name="v_03B" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_117">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:55:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_4intmid],Reference=Value>/(&lt;CN=Root,Model=Pratap2016,Vector=Values[Km_2intmid],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_118" name="v_04F" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_118">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:44:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_3int],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n_int],Reference=Value>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n_int],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Values[Km_1int],Reference=Value>^&lt;CN=Root,Model=Pratap2016,Vector=Values[n_int],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_119" name="v_04B" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:48:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_4int],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_fin],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_120" name="constGnRH" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_120">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-15T00:04:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_121" name="v_16F" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-02T23:51:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_catTF1],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration>^2/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dppETF1],Reference=Value>^2+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration>^2)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_122" name="J1" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_122">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-05T10:20:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f1],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[N_tot],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFATp_c],Reference=Concentration>-&lt;CN=Root,Model=Pratap2016,Vector=Values[k_r1],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c],Reference=Concentration>*(1-&lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_123" name="J2" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_123">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-05T10:24:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_f2],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_124" name="J3" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_124">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-05T10:24:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f3],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>*(1-&lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=Value>)-&lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[N_tot],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_r3],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_125" name="J4" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_125">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-05T10:27:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[k_f4],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_126" name="k_r3*N_active" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_126">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-05T11:35:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[k_r3],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[N_active],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_127" name="spike_offset_total" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_127">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T18:49:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          spike_Amplitude larger than period was not tolerated and is indirectly impemented
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_128" name="GSU_par_COOP" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_128">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[DNA_tot],Reference=Value>^2/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>)/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_129" name="GSU_par_AND" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_129">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>/((&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>)*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_130" name="GSU_par_OR" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_130">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>)+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_131" name="gamma" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_131">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:10:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_132" name="DNA_tot" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_132">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:19:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_133" name="GSU_seq_OR" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_133">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>)+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>/(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_134" name="GSU_seq_COOP" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_134">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Values[DNA_tot],Reference=Value>^2/(&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>*&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>)/(1+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>+&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>/&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_135" name="quantity_1" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_135">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>/((&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>)*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_136" name="GSU_seq_AND" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_136">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T16:43:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[gamma],Reference=Value>*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>*&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>/((&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1],Reference=Value>)*(&lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>+&lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF2],Reference=Value>)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_137" name="Total_EGR" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_137">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:45:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_138" name="Total_TF2" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_138">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:50:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_139" name="Total_NFAT_n" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_139">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:49:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_140" name="Total_GSU_par_COOP" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_140">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:47:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_COOP],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_COOP],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_141" name="Total_GSU_par_AND" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_141">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:46:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_AND],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_AND],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_142" name="Total_GSU_par_OR" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_142">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:47:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_OR],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_OR],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_143" name="Total_GSU_seq_AND" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_143">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:48:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_AND],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_AND],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_144" name="Total_GSU_seq_COOP" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_144">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:48:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_COOP],Reference=Value>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_COOP],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_145" name="Total_GSU_seq_OR" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_145">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:49:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
      <ModelValue key="ModelValue_146" name="Total_HR" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_146">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-23T14:37:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration>
        </Expression>
        <InitialExpression>
          &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=InitialConcentration>
        </InitialExpression>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="01F_Hormon-receptor binding" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T14:02:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5144" name="k1" value="2500"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="01B_Hormon-receptor binding" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-01-27T14:51:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5146" name="k1" value="5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="02F_G-protein activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:40:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          HR + G_aq11 -> G_aq11_act
        </Comment>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5147" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="02B G-protein activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:40:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5141" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="05F_PLC activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-08T15:37:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5143" name="k_e2" value="20"/>
          <Constant key="Parameter_5142" name="k_Ee" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="05B_PLC activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:40:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5145" name="k1" value="5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="11F_Unbinding+Phosphorylation of NFAT_n" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:23:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5148" name="k" value="0.0732"/>
          <Constant key="Parameter_5139" name="actN" value="0.981921"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="06F_IP3 production" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:51:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5137" name="k" value="36"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="11B_Unbinding+Phosphorylation of NFAT_n" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:55:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5136" name="k1" value="3.46795"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="09B_Binding+Dephosphorylation of NFATp_c" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:51:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5140" name="k" value="0.3605"/>
          <Constant key="Parameter_5138" name="actN" value="0.981921"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="ConcentrationPerTime" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="09F_Binding+Dephosphorylation of NFATp_c" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:52:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5113" name="k1" value="25.3452"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="06B_IP3 production" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:44:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5111" name="k1" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="10_NFAT_c import" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T17:52:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5110" name="k" value="0.0104"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="09F_ Basal dephosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:27:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5114" name="k1" value="8.6772"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="12_ NFATp_n export" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:26:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5112" name="k" value="94.8693"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="18F_EGR1 activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:51:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
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
          <Constant key="Parameter_5116" name="kcat" value="0.018"/>
          <Constant key="Parameter_5131" name="kd" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="18F_TF2 activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-04T01:52:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5119" name="kcat" value="0.045"/>
          <Constant key="Parameter_5133" name="kd" value="0.26"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="18B_EGR1 activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:48:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5134" name="k1" value="0.011"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="19B_TF2 activation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:51:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5128" name="k1" value="0.023"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="13B_ppERK nuclear import" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:50:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5115" name="k" value="2.6665"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="13F_ppERK nuclear import" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T17:21:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5123" name="k" value="1.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="17_ppERK dephosphorylation (nucleus)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-17T21:50:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5130" name="v" value="0.0371578"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="14F_ERK nuclear import" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-19T19:31:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5117" name="k" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="14B_ERK nuclear import" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-19T19:31:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5129" name="k" value="0.45"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="16F_pERK phosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T17:21:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5122" name="v" value="1.32234e-08"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="16B_pERK phosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T17:21:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5126" name="v" value="0.569915"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="15B_ERK phosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-19T19:33:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5121" name="v" value="0.0350156"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="15F_ ERK phosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T15:58:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5125" name="v" value="3.60944e-06"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="16F_basal ppERK dephosphorylation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-21T16:15:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5124" name="k1" value="0.17"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="07F_Ca2+_extracellular cytosol" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T20:55:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5127" name="v" value="6e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_107"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="07B_Ca2+_cytosol extracellular" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:38:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5132" name="v" value="6e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="08F_Ca2+ ER cytsol" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:39:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5118" name="v" value="3.0929"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="08B_Ca2+ cytosol  ER" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-14T21:39:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5120" name="v" value="2.93926"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_110"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="03F_Rfree2Rmid" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:33:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5135" name="v" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="03B_Rfree2Rmid" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:41:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5149" name="v" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="04F_Rmid2Rfin" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:43:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5150" name="v" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_118"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="04B_Rmid2Rfin" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-14T23:44:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5156" name="k1" value="5.8109"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="00_GnRH" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-01-15T00:03:29Z</dcterms:W3CDTF>
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
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5155" name="v" value="0.002"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_120"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="h" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-12T10:22:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5157" name="v" value="-0.023628"/>
        </ListOfConstants>
        <KineticLaw function="Function_7" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_48">
              <SourceParameter reference="ModelValue_96"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="20F_GSU_par_OR" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:49:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5154" name="v" value="0.000765163"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_130"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="20B_GSU_par_OR" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:50:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5153" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="21F_GSU_par_AND" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:59:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5152" name="v" value="1.42768e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_129"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="21B_GSU_par_AND" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:54:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5151" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="22F_GSU_par_COOP" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:55:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5158" name="v" value="1.42972e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_128"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="22B_GSU_par_COOP" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:55:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5162" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="23B_GSU_seq_OR" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:56:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5160" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="24B_GSU_seq_AND" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:56:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5159" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="25B_GSU_seq_COOP" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:56:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5163" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="23F_GSU_seq_OR" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-16T15:56:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5161" name="v" value="0.000953211"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="24F_GSU_seq_AND" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:22:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5165" name="v" value="2.03429e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_136"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="25F_GSU_seq_COOP" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-21T17:23:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5167" name="v" value="2.03844e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_6" unitType="Default" scalingCompartment="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_134"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_0" name="spike_on" fireAtInitialTime="0" persistentTrigger="1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-18T17:58:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          abs(&lt;CN=Root,Model=Pratap2016,Reference=Time>-&lt;CN=Root,Model=Pratap2016,Vector=Values[spike_offset_total],Reference=Value>)%&lt;CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=Value> == 0 AND &lt;CN=Root,Model=Pratap2016,Reference=Time> > &lt;CN=Root,Model=Pratap2016,Vector=Values[spike_offset_total],Reference=Value>
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_0">
            <Expression>
              &lt;CN=Root,Model=Pratap2016,Vector=Values[spike_amplitude],Reference=Value>
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_1" name="spike_off" fireAtInitialTime="0" persistentTrigger="1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-18T18:01:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          abs(&lt;CN=Root,Model=Pratap2016,Reference=Time>-&lt;CN=Root,Model=Pratap2016,Vector=Values[spike_offset_total],Reference=Value>-&lt;CN=Root,Model=Pratap2016,Vector=Values[spike_length],Reference=Value>)%&lt;CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=Value> == 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_0">
            <Expression>
              0
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Pratap2016" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol]" value="9.3999999999999997e-15" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus]" value="3.1333333333333331e-15" type="Compartment" simulationType="fixed">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Reference=InitialVolume>/&lt;CN=Root,Model=Pratap2016,Vector=Values[C_cn],Reference=InitialValue>
            </InitialExpression>
          </ModelParameter>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GnRH]" value="0" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_free]" value="101.89462330043985" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC]" value="566.08067447675944" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Values[PLC_0],Reference=InitialValue>-&lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11]" value="2264.3249622320004" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11_act]" value="566.0812405580001" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act]" value="0.00056608124055799991" type="Species" simulationType="reactions">
            <InitialExpression>
              1*10^(-7)
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[act_N]" value="5558.4690695330846" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[N_active]" value="5558.4690695330846" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol]" value="1822.78159459676" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[IP3]" value="88.308673527047986" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act]" value="0.024484760139120498" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c]" value="2088.83977765902" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c]" value="1409.5422889894198" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[E_n]" value="467.9604921946131" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n]" value="31.323161977542664" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c]" value="98.498135857092961" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1]" value="1.8869374685266667" type="Species" simulationType="reactions">
            <InitialExpression>
              1e-3
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2]" value="66.042811398433329" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c]" value="60.570692739705983" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n]" value="45.437454242122136" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFATp_c]" value="4189.0011801291994" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n]" value="2.7171899546784002" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_total]" value="733262.01333199418" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_ER]" value="731439.23173739738" type="Species" simulationType="reactions">
            <InitialExpression>
              1.29533*10^(+2)-0.322
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_fin]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[h]" value="3079.48194863552" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_OR]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_AND]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_COOP]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_AND]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_COOP]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR_copy]" value="5660.8124055799999" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[R_0]" value="0.11799999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_1]" value="2500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_(-1)]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_2]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_(-2)]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_3]" value="36" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_(-3)]" value="30" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[epsilon]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[sigma]" value="0.81899999999999995" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[V_p]" value="10000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_p]" value="5.0000000000000004e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[V_e]" value="131500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_e]" value="0.41789999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J_in]" value="10000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[L]" value="32" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[P]" value="1598400" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[A]" value="16.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_i]" value="0.00079000000000000012" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_a]" value="2.605" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_d]" value="0.38100000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_d1]" value="5.7672999999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_f1]" value="25.345199999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_r1]" value="0.36049999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_f2]" value="0.0104" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_f3]" value="0.073200000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_f4]" value="94.869299999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_mn]" value="0.1115" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[M]" value="53.492899999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[n]" value="3.8633000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[N_tot]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[C_cn]" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_1cat]" value="0.95267199999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_2cat]" value="0.73283100000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h1]" value="2700" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h2]" value="5.5199999999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h3]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h4]" value="600" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h5]" value="30" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h6]" value="5.1600000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_catMKPn]" value="2.8999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_dppEn]" value="0.10000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[MEK_t]" value="0.40000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[MKP_n]" value="0.089999999999999997" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_de]" value="0.41510000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[MKP_3t]" value="0.17999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[M_tot]" value="0.90000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_impE]" value="1.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_expE]" value="0.45000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[G_0]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_catTF1]" value="0.017999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_catTF2]" value="0.044999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_dppETF1]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_dTF1TF2]" value="0.26000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_11]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[kk_2]" value="0.59999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[kk_3]" value="1920" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_33]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_3intmid]" value="0.058999999999999997" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Km_1intmid]" value="1.8775999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_4int]" value="5.8109000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_4intmid]" value="0.24399999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_e2]" value="20" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_(-e2)]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[PLC_0]" value="0.10000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[l_base]" value="0.17000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[d_TF2]" value="0.023" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[d_GSU]" value="0.050000000000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_comp]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_dTF1]" value="0.029999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_dTF2]" value="0.52000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[kk_1]" value="1200" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h_11]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h_33]" value="600" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h_44]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[h_66]" value="66" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[fi/Vi]" value="6.0000000000000002e-05" type="ModelValue" simulationType="fixed">
            <InitialExpression>
              6e-5
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_3int]" value="18.832699999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Km_1int]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Km_2intmid]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[n_int]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[l_dp]" value="8.6771999999999991" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[l_exp]" value="2.6665000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[l_imp]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[K_Ee]" value="0.10000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_(-4)]" value="30" type="ModelValue" simulationType="fixed">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-3)],Reference=InitialValue>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_MEK]" value="44.885899999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_4cat]" value="3.6083916083916083" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_m1]" value="0.050500000000000003" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_m2]" value="0.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[kk_4]" value="900" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_m3]" value="0.02222222222222222" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_m4]" value="0.018041958041958042" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_m5]" value="0.078181818181818186" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k3cat]" value="5.0549450549450539" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[d_TF1]" value="0.010999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_r3]" value="3.5318000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[dh/dt]" value="-0.023628000000000732" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[act_N]" value="0.98192073350707887" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_2]" value="1.3223426403462283e-08" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_4]" value="0.035015567414379549" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_3]" value="0.56991517975222528" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_1]" value="3.609435746811488e-06" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J_impE]" value="1.3223426403462283e-08" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J_expE]" value="0.11159999999999995" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_5]" value="0.037157804459691246" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[spike_period]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[spike_length]" value="22.460000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_07F]" value="6.0000000000000002e-05" type="ModelValue" simulationType="fixed">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Values[J_in],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Values[fi/Vi],Reference=InitialValue>*&lt;CN=Root,Model=Pratap2016,Vector=Values[epsilon],Reference=InitialValue>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_07B]" value="5.9999999985532977e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_08F]" value="3.092897227717089" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_08B]" value="2.9392562441792296" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[spike_amplitude]" value="0.10000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[NFAT(N:C)]" value="0.033994938057812715" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[ERK(N:C)]" value="0.41643059490084955" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[quantity]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_03F]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[R_0mid]" value="0.10000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_03B]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_04F]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_04B]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[constGnRH]" value="0.002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[v_16F]" value="1.9818475283803178e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J1]" value="18.416293519355264" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J2]" value="0.00011127999999999996" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J3]" value="-0.0049619770835450877" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[J4]" value="0.13661179200000001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[k_r3*N_active]" value="3.4679476466003014" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[spike_offset_total]" value="100" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_COOP]" value="1.4297249798128531e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_AND]" value="1.4276837846426758e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_OR]" value="0.00076516261840051981" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[gamma]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[DNA_tot]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_OR]" value="0.00095321127579192091" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_COOP]" value="2.03843913803145e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[quantity_1]" value="2.0342923568730017e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_AND]" value="2.0342923568730017e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_EGR]" value="0.001" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_TF2]" value="0.034999999999999996" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_NFAT_n]" value="0.024080000000000001" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_COOP]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_COOP],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_AND]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_AND],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_OR]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_OR],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_AND]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_AND],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_COOP]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_COOP],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_OR]" value="1" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Values[Total_HR]" value="0" type="ModelValue" simulationType="ode">
            <InitialExpression>
              &lt;CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[01F_Hormon-receptor binding]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[01F_Hormon-receptor binding],ParameterGroup=Parameters,Parameter=k1" value="2500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[01B_Hormon-receptor binding]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[01B_Hormon-receptor binding],ParameterGroup=Parameters,Parameter=k1" value="5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-1)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[02F_G-protein activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[02F_G-protein activation],ParameterGroup=Parameters,Parameter=k1" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[02B G-protein activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[02B G-protein activation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-2)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[05F_PLC activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[05F_PLC activation],ParameterGroup=Parameters,Parameter=k_e2" value="20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_e2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[05F_PLC activation],ParameterGroup=Parameters,Parameter=k_Ee" value="0.10000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[K_Ee],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[05B_PLC activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[05B_PLC activation],ParameterGroup=Parameters,Parameter=k1" value="5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-e2)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[11F_Unbinding+Phosphorylation of NFAT_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[11F_Unbinding+Phosphorylation of NFAT_n],ParameterGroup=Parameters,Parameter=k" value="0.073200000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[11F_Unbinding+Phosphorylation of NFAT_n],ParameterGroup=Parameters,Parameter=actN" value="0.98192073350707887" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[06F_IP3 production]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[06F_IP3 production],ParameterGroup=Parameters,Parameter=k" value="36" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[11B_Unbinding+Phosphorylation of NFAT_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[11B_Unbinding+Phosphorylation of NFAT_n],ParameterGroup=Parameters,Parameter=k1" value="3.4679476466003014" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_r3*N_active],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[09B_Binding+Dephosphorylation of NFATp_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[09B_Binding+Dephosphorylation of NFATp_c],ParameterGroup=Parameters,Parameter=k" value="0.36049999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_r1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[09B_Binding+Dephosphorylation of NFATp_c],ParameterGroup=Parameters,Parameter=actN" value="0.98192073350707887" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[09F_Binding+Dephosphorylation of NFATp_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[09F_Binding+Dephosphorylation of NFATp_c],ParameterGroup=Parameters,Parameter=k1" value="25.345199999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[06B_IP3 production]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[06B_IP3 production],ParameterGroup=Parameters,Parameter=k1" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_(-3)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[10_NFAT_c import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[10_NFAT_c import],ParameterGroup=Parameters,Parameter=k" value="0.0104" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[09F_ Basal dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[09F_ Basal dephosphorylation],ParameterGroup=Parameters,Parameter=k1" value="8.6771999999999991" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[l_dp],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[12_ NFATp_n export]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[12_ NFATp_n export],ParameterGroup=Parameters,Parameter=k" value="94.869299999999996" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_f4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_EGR1 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_EGR1 activation],ParameterGroup=Parameters,Parameter=kcat" value="0.017999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_catTF1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_EGR1 activation],ParameterGroup=Parameters,Parameter=kd" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[K_dppETF1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_TF2 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_TF2 activation],ParameterGroup=Parameters,Parameter=kcat" value="0.044999999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_catTF2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[18F_TF2 activation],ParameterGroup=Parameters,Parameter=kd" value="0.26000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[K_dTF1TF2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[18B_EGR1 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[18B_EGR1 activation],ParameterGroup=Parameters,Parameter=k1" value="0.010999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_TF1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[19B_TF2 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[19B_TF2 activation],ParameterGroup=Parameters,Parameter=k1" value="0.023" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_TF2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[13B_ppERK nuclear import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[13B_ppERK nuclear import],ParameterGroup=Parameters,Parameter=k" value="2.6665000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[l_exp],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[13F_ppERK nuclear import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[13F_ppERK nuclear import],ParameterGroup=Parameters,Parameter=k" value="1.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[K_impE],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[17_ppERK dephosphorylation (nucleus)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[17_ppERK dephosphorylation (nucleus)],ParameterGroup=Parameters,Parameter=v" value="0.037157804459691246" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[14F_ERK nuclear import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[14F_ERK nuclear import],ParameterGroup=Parameters,Parameter=k" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[l_imp],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[14B_ERK nuclear import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[14B_ERK nuclear import],ParameterGroup=Parameters,Parameter=k" value="0.45000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_expE],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[16F_pERK phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[16F_pERK phosphorylation],ParameterGroup=Parameters,Parameter=v" value="1.3223426403462283e-08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[16B_pERK phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[16B_pERK phosphorylation],ParameterGroup=Parameters,Parameter=v" value="0.56991517975222528" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[15B_ERK phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[15B_ERK phosphorylation],ParameterGroup=Parameters,Parameter=v" value="0.035015567414379549" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[15F_ ERK phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[15F_ ERK phosphorylation],ParameterGroup=Parameters,Parameter=v" value="3.609435746811488e-06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[16F_basal ppERK dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[16F_basal ppERK dephosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.17000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[l_base],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[07F_Ca2+_extracellular cytosol]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[07F_Ca2+_extracellular cytosol],ParameterGroup=Parameters,Parameter=v" value="6.0000000000000002e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_07F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[07B_Ca2+_cytosol extracellular]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[07B_Ca2+_cytosol extracellular],ParameterGroup=Parameters,Parameter=v" value="5.9999999985532977e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_07B],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[08F_Ca2+ ER cytsol]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[08F_Ca2+ ER cytsol],ParameterGroup=Parameters,Parameter=v" value="3.092897227717089" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_08F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[08B_Ca2+ cytosol  ER]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[08B_Ca2+ cytosol  ER],ParameterGroup=Parameters,Parameter=v" value="2.9392562441792296" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_08B],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[03F_Rfree2Rmid]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[03F_Rfree2Rmid],ParameterGroup=Parameters,Parameter=v" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_03F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[03B_Rfree2Rmid]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[03B_Rfree2Rmid],ParameterGroup=Parameters,Parameter=v" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_03B],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[04F_Rmid2Rfin]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[04F_Rmid2Rfin],ParameterGroup=Parameters,Parameter=v" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[v_04F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[04B_Rmid2Rfin]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[04B_Rmid2Rfin],ParameterGroup=Parameters,Parameter=k1" value="5.8109000000000002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[k_4int],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[00_GnRH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[00_GnRH],ParameterGroup=Parameters,Parameter=v" value="0.002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[constGnRH],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[h]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[h],ParameterGroup=Parameters,Parameter=v" value="-0.023628000000000732" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[dh/dt],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[20F_GSU_par_OR]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[20F_GSU_par_OR],ParameterGroup=Parameters,Parameter=v" value="0.00076516261840051981" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_par_OR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[20B_GSU_par_OR]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[20B_GSU_par_OR],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[21F_GSU_par_AND]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[21F_GSU_par_AND],ParameterGroup=Parameters,Parameter=v" value="1.4276837846426758e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_par_AND],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[21B_GSU_par_AND]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[21B_GSU_par_AND],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[22F_GSU_par_COOP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[22F_GSU_par_COOP],ParameterGroup=Parameters,Parameter=v" value="1.4297249798128531e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_par_COOP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[22B_GSU_par_COOP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[22B_GSU_par_COOP],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[23B_GSU_seq_OR]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[23B_GSU_seq_OR],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[24B_GSU_seq_AND]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[24B_GSU_seq_AND],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[25B_GSU_seq_COOP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[25B_GSU_seq_COOP],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[d_GSU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[23F_GSU_seq_OR]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[23F_GSU_seq_OR],ParameterGroup=Parameters,Parameter=v" value="0.00095321127579192091" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_OR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[24F_GSU_seq_AND]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[24F_GSU_seq_AND],ParameterGroup=Parameters,Parameter=v" value="2.0342923568730017e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_AND],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Pratap2016,Vector=Reactions[25F_GSU_seq_COOP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Pratap2016,Vector=Reactions[25F_GSU_seq_COOP],ParameterGroup=Parameters,Parameter=v" value="2.03843913803145e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_COOP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="ModelValue_137"/>
      <StateTemplateVariable objectReference="ModelValue_138"/>
      <StateTemplateVariable objectReference="ModelValue_139"/>
      <StateTemplateVariable objectReference="ModelValue_140"/>
      <StateTemplateVariable objectReference="ModelValue_141"/>
      <StateTemplateVariable objectReference="ModelValue_142"/>
      <StateTemplateVariable objectReference="ModelValue_143"/>
      <StateTemplateVariable objectReference="ModelValue_144"/>
      <StateTemplateVariable objectReference="ModelValue_145"/>
      <StateTemplateVariable objectReference="ModelValue_146"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="ModelValue_86"/>
      <StateTemplateVariable objectReference="ModelValue_87"/>
      <StateTemplateVariable objectReference="ModelValue_88"/>
      <StateTemplateVariable objectReference="ModelValue_90"/>
      <StateTemplateVariable objectReference="ModelValue_91"/>
      <StateTemplateVariable objectReference="ModelValue_92"/>
      <StateTemplateVariable objectReference="ModelValue_93"/>
      <StateTemplateVariable objectReference="ModelValue_96"/>
      <StateTemplateVariable objectReference="ModelValue_97"/>
      <StateTemplateVariable objectReference="ModelValue_98"/>
      <StateTemplateVariable objectReference="ModelValue_99"/>
      <StateTemplateVariable objectReference="ModelValue_100"/>
      <StateTemplateVariable objectReference="ModelValue_101"/>
      <StateTemplateVariable objectReference="ModelValue_102"/>
      <StateTemplateVariable objectReference="ModelValue_103"/>
      <StateTemplateVariable objectReference="ModelValue_104"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_112"/>
      <StateTemplateVariable objectReference="ModelValue_113"/>
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="ModelValue_126"/>
      <StateTemplateVariable objectReference="ModelValue_128"/>
      <StateTemplateVariable objectReference="ModelValue_129"/>
      <StateTemplateVariable objectReference="ModelValue_130"/>
      <StateTemplateVariable objectReference="ModelValue_133"/>
      <StateTemplateVariable objectReference="ModelValue_134"/>
      <StateTemplateVariable objectReference="ModelValue_135"/>
      <StateTemplateVariable objectReference="ModelValue_136"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
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
      <StateTemplateVariable objectReference="ModelValue_53"/>
      <StateTemplateVariable objectReference="ModelValue_54"/>
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
      <StateTemplateVariable objectReference="ModelValue_89"/>
      <StateTemplateVariable objectReference="ModelValue_94"/>
      <StateTemplateVariable objectReference="ModelValue_95"/>
      <StateTemplateVariable objectReference="ModelValue_105"/>
      <StateTemplateVariable objectReference="ModelValue_106"/>
      <StateTemplateVariable objectReference="ModelValue_107"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
      <StateTemplateVariable objectReference="ModelValue_114"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="ModelValue_127"/>
      <StateTemplateVariable objectReference="ModelValue_131"/>
      <StateTemplateVariable objectReference="ModelValue_132"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0.001 0.034999999999999996 0.024080000000000001 1 1 1 1 1 1 0 0 1409.5422889894198 1822.78159459676 2088.83977765902 60.570692739705983 2.7171899546784002 98.498135857092961 566.08067447675944 88.308673527047986 0 0 5660.8124055799999 5660.8124055799999 5660.8124055799999 5660.8124055799999 5660.8124055799999 5660.8124055799999 1.8869374685266667 66.042811398433329 467.9604921946131 4189.0011801291994 566.0812405580001 731439.23173739738 3079.48194863552 31.323161977542664 2264.3249622320004 45.437454242122136 0.00056608124055799991 101.89462330043985 5558.4690695330846 5558.4690695330846 0.024484760139120498 733262.01333199418 3.6083916083916083 0.050500000000000003 0.5 0.02222222222222222 0.018041958041958042 0.078181818181818186 5.0549450549450539 -0.023628000000000732 0.98192073350707887 1.3223426403462283e-08 0.035015567414379549 0.56991517975222528 3.609435746811488e-06 1.3223426403462283e-08 0.11159999999999995 0.037157804459691246 5.9999999985532977e-05 3.092897227717089 2.9392562441792296 0.033994938057812715 0.41643059490084955 0 0 0 0 1.9818475283803178e-05 18.416293519355264 0.00011127999999999996 -0.0049619770835450877 0.13661179200000001 3.4679476466003014 1.4297249798128531e-05 1.4276837846426758e-05 0.00076516261840051981 0.00095321127579192091 2.03843913803145e-05 2.0342923568730017e-05 2.0342923568730017e-05 0 5660.8124055799999 9.3999999999999997e-15 3.1333333333333331e-15 0.11799999999999999 2500 5 0.5 1 36 30 0.0001 0.81899999999999995 10000 5.0000000000000004e-06 131500 0.41789999999999999 10000 32 1598400 16.5 0.00079000000000000012 2.605 0.38100000000000001 5.7672999999999996 25.345199999999998 0.36049999999999999 0.0104 0.073200000000000001 94.869299999999996 0.1115 53.492899999999999 3.8633000000000002 1 3 0.95267199999999996 0.73283100000000001 2700 5.5199999999999996 60 600 30 5.1600000000000001 2.8999999999999999 0.10000000000000001 0.40000000000000002 0.089999999999999997 0.41510000000000002 0.17999999999999999 0.90000000000000002 1.5 0.45000000000000001 0.5 0.017999999999999999 0.044999999999999998 0.5 0.26000000000000001 60 0.59999999999999998 1920 60 0.058999999999999997 1.8775999999999999 5.8109000000000002 0.24399999999999999 20 5 0.10000000000000001 0.17000000000000001 0.023 0.050000000000000003 0.01 0.029999999999999999 0.52000000000000002 1200 60 600 60 66 6.0000000000000002e-05 18.832699999999999 0.0001 50 4 8.6771999999999991 2.6665000000000001 0.01 0.10000000000000001 30 44.885899999999999 900 0.010999999999999999 3.5318000000000001 60 22.460000000000001 6.0000000000000002e-05 0.10000000000000001 60 0.10000000000000001 0.002 100 0.01 1 
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
        <Parameter name="Resolution" type="unsignedFloat" value="1.0000000000000001e-09"/>
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
      <Report reference="Report_17" target="EventTest31.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="200"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="200"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="totalScan_P2" append="0" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="180"/>
            <Parameter name="Minimum" type="float" value="30"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="500"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=InitialValue"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="log" type="bool" value="0"/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
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
        <Parameter name="#LogVerbosity" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="fitdataGQERK" append="0" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
          <ParameterGroup name="FitItem">
            <ParameterGroup name="Affected Cross Validation Experiments">
            </ParameterGroup>
            <ParameterGroup name="Affected Experiments">
            </ParameterGroup>
            <Parameter name="LowerBound" type="cn" value="1e-06"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[K_impE],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="1.5"/>
            <Parameter name="UpperBound" type="cn" value="1e+06"/>
          </ParameterGroup>
          <ParameterGroup name="FitItem">
            <ParameterGroup name="Affected Cross Validation Experiments">
            </ParameterGroup>
            <ParameterGroup name="Affected Experiments">
            </ParameterGroup>
            <Parameter name="LowerBound" type="cn" value="1e-06"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[k_2cat],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.73283100000000001"/>
            <Parameter name="UpperBound" type="cn" value="1e+06"/>
          </ParameterGroup>
          <ParameterGroup name="FitItem">
            <ParameterGroup name="Affected Cross Validation Experiments">
            </ParameterGroup>
            <ParameterGroup name="Affected Experiments">
            </ParameterGroup>
            <Parameter name="LowerBound" type="cn" value="1e-06"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[k_catMKPn],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="2.8999999999999999"/>
            <Parameter name="UpperBound" type="cn" value="1e+06"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <Parameter name="Time-Course" type="cn" value="CN=Root,Vector=TaskList[Time-Course]"/>
        <Parameter name="Create Parameter Sets" type="bool" value="0"/>
        <ParameterGroup name="Experiment Set">
          <ParameterGroup name="Experiment_1">
            <Parameter name="Data is Row Oriented" type="bool" value="1"/>
            <Parameter name="Experiment Type" type="unsignedInteger" value="1"/>
            <Parameter name="File Name" type="file" value="../../../../Documents/COPASI/Files/Bugs/Scan/ppERK30.csv"/>
            <Parameter name="First Row" type="unsignedInteger" value="1"/>
            <Parameter name="Key" type="key" value="Experiment_0"/>
            <Parameter name="Last Row" type="unsignedInteger" value="3150"/>
            <Parameter name="Normalize Weights per Experiment" type="bool" value="1"/>
            <Parameter name="Number of Columns" type="unsignedInteger" value="3"/>
            <ParameterGroup name="Object Map">
              <ParameterGroup name="0">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=InitialValue"/>
                <Parameter name="Role" type="unsignedInteger" value="1"/>
              </ParameterGroup>
              <ParameterGroup name="1">
                <Parameter name="Role" type="unsignedInteger" value="3"/>
              </ParameterGroup>
              <ParameterGroup name="2">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration"/>
                <Parameter name="Role" type="unsignedInteger" value="2"/>
              </ParameterGroup>
            </ParameterGroup>
            <Parameter name="Row containing Names" type="unsignedInteger" value="1"/>
            <Parameter name="Separator" type="string" value=","/>
            <Parameter name="Weight Method" type="unsignedInteger" value="1"/>
          </ParameterGroup>
          <ParameterGroup name="Experiment_2">
            <Parameter name="Data is Row Oriented" type="bool" value="1"/>
            <Parameter name="Experiment Type" type="unsignedInteger" value="1"/>
            <Parameter name="File Name" type="file" value="ppERK60.csv"/>
            <Parameter name="First Row" type="unsignedInteger" value="1"/>
            <Parameter name="Key" type="key" value="Experiment_1"/>
            <Parameter name="Last Row" type="unsignedInteger" value="2777"/>
            <Parameter name="Normalize Weights per Experiment" type="bool" value="1"/>
            <Parameter name="Number of Columns" type="unsignedInteger" value="3"/>
            <ParameterGroup name="Object Map">
              <ParameterGroup name="0">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=InitialValue"/>
                <Parameter name="Role" type="unsignedInteger" value="1"/>
              </ParameterGroup>
              <ParameterGroup name="1">
                <Parameter name="Role" type="unsignedInteger" value="3"/>
              </ParameterGroup>
              <ParameterGroup name="2">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration"/>
                <Parameter name="Role" type="unsignedInteger" value="2"/>
              </ParameterGroup>
            </ParameterGroup>
            <Parameter name="Row containing Names" type="unsignedInteger" value="1"/>
            <Parameter name="Separator" type="string" value=","/>
            <Parameter name="Weight Method" type="unsignedInteger" value="1"/>
          </ParameterGroup>
          <ParameterGroup name="Experiment">
            <Parameter name="Data is Row Oriented" type="bool" value="1"/>
            <Parameter name="Experiment Type" type="unsignedInteger" value="1"/>
            <Parameter name="File Name" type="file" value="ppERK_const.csv"/>
            <Parameter name="First Row" type="unsignedInteger" value="1"/>
            <Parameter name="Key" type="key" value="Experiment_2"/>
            <Parameter name="Last Row" type="unsignedInteger" value="190"/>
            <Parameter name="Normalize Weights per Experiment" type="bool" value="1"/>
            <Parameter name="Number of Columns" type="unsignedInteger" value="3"/>
            <ParameterGroup name="Object Map">
              <ParameterGroup name="0">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=InitialValue"/>
                <Parameter name="Role" type="unsignedInteger" value="1"/>
              </ParameterGroup>
              <ParameterGroup name="1">
                <Parameter name="Role" type="unsignedInteger" value="3"/>
              </ParameterGroup>
              <ParameterGroup name="2">
                <Parameter name="Object CN" type="cn" value="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration"/>
                <Parameter name="Role" type="unsignedInteger" value="2"/>
              </ParameterGroup>
            </ParameterGroup>
            <Parameter name="Row containing Names" type="unsignedInteger" value="1"/>
            <Parameter name="Separator" type="string" value=","/>
            <Parameter name="Weight Method" type="unsignedInteger" value="1"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
        </ParameterGroup>
      </Problem>
      <Method name="Particle Swarm" type="ParticleSwarm">
        <Parameter name="Iteration Limit" type="unsignedInteger" value="2000"/>
        <Parameter name="Swarm Size" type="unsignedInteger" value="50"/>
        <Parameter name="Std. Deviation" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="#LogVerbosity" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
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
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
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
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
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
    <Task key="Task_2" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_1" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
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
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
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
    <Report key="Report_18" name="conc" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Pratap2016,Reference=Time"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_amplitude],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_length],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_offset],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_ER],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_total],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[E_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GnRH],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[IP3],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFATp_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[N_active],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_fin],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_free],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[act_N],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[h],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_EGR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_NFAT_n],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_TF2],Reference=Value"/>
      </Table>
    </Report>
    <Report key="Report_19" name="total_conc" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Pratap2016,Reference=Time"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_amplitude],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_length],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_offset],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[spike_period],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_EGR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_NFAT_n],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_TF2],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_HR],Reference=Value"/>
      </Table>
    </Report>
    <Report key="Report_17" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Pratap2016,Reference=Time"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GnRH],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_free],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[HR],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[G_aq11_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[PLC_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[act_N],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[N_active],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_cytosol],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[IP3],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[MEK_act],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[E_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Epp_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[E_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[Epp_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ep_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[EGR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[TF2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFAT_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFAT_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[NFATp_c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[nucleus],Vector=Metabolites[NFATp_n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_total],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[Ca2+_ER],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_mid],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[R_fin],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[h],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_OR],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_AND],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_par_COOP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_AND],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_COOP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GSU_seq_OR_copy],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_4cat],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_m1],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_m2],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_m3],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_m4],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_m5],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k3cat],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[dh/dt],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[act_N],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_2],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_4],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_3],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_1],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J_impE],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J_expE],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_5],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_07B],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_08F],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_08B],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[NFAT(N:C)],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[ERK(N:C)],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_03F],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_03B],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_04F],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_04B],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[v_16F],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J1],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J2],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J3],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[J4],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[k_r3*N_active],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_par_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[quantity_1],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[GSU_seq_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_EGR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_TF2],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_NFAT_n],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_par_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_AND],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_COOP],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_GSU_seq_OR],Reference=Value"/>
        <Object cn="CN=Root,Model=Pratap2016,Vector=Values[Total_HR],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="plot" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[GnRH]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Pratap2016,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Pratap2016,Vector=Compartments[cytosol],Vector=Metabolites[GnRH],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
    <ListOfSliders>
      <Slider key="Slider_0" associatedEntityKey="Task_11" objectCN="CN=Root,Model=Pratap2016,Vector=Values[k_catTF1],Reference=InitialValue" objectType="float" objectValue="0.018" minValue="0.01" maxValue="0.02" tickNumber="1000" tickFactor="100" scaling="linear"/>
      <Slider key="Slider_1" associatedEntityKey="Task_11" objectCN="CN=Root,Model=Pratap2016,Vector=Values[d_TF1],Reference=InitialValue" objectType="float" objectValue="0.011" minValue="0.0055" maxValue="0.022" tickNumber="1000" tickFactor="100" scaling="linear"/>
    </ListOfSliders>
  </GUI>
  <ListOfUnitDefinitions>
    <UnitDefinition key="Unit_0" name="meter" symbol="m">
      <Expression>
        m
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_2" name="second" symbol="s">
      <Expression>
        s
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_6" name="Avogadro" symbol="Avogadro">
      <Expression>
        Avogadro
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_7" name="dimensionless" symbol="1">
      <Expression>
        1
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_8" name="item" symbol="#">
      <Expression>
        #
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_17" name="liter" symbol="l">
      <Expression>
        0.001*m^3
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_20" name="mole" symbol="mol">
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_32" name="minute" symbol="min">
      <Expression>
        60*s
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
