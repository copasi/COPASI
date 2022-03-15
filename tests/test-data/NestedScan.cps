<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.16 (Build 104) (http://www.copasi.org) at 2016-10-22 19:29:45 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="16" versionDevel="104" copasiSourcesModified="0">
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
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:56:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
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
  <Model key="Model_3" name="Bush2016-Simplified-Carrousel-model-of-GPCR" simulationType="time" timeUnit="s" volumeUnit="fl" areaUnit="m²" lengthUnit="m" quantityUnit="#" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:29:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Description>
        <vCard:EMAIL>abush84@gmail.com</vCard:EMAIL>
        <vCard:N>
          <rdf:Description>
            <vCard:Family>Bush</vCard:Family>
            <vCard:Given>Alan</vCard:Given>
          </rdf:Description>
        </vCard:N>
        <vCard:ORG>
          <rdf:Description>
            <vCard:Orgname>IFIBYNE-UBA-CONICET</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      Carrousel model of G protein activation. 

See model definition in the Appendix to Bush, Vasen et al 2016. The rates used are the ones defined by the symmetry assumptions and the reference parameters. 

The concentration units used in the model are #/fl. To transform units we used the equivalence 1.66 nM = #/fl. The factor 1.66 appears in second order rates, and dividing K_d values.  

The ligand L is not explicitly modeled as a specie. It is introduced in the model as a modulator of the effective k_on_R·L rates ( k_on_R·L = [L] * k_off_L·R / K_d_L·R). Note that this allows us to express the fixed extracelular ligand concentration in nM (assuming no ligand depletion), and there is therefore no need to transform the units of K_d_L·R to #/fl.

All parameters are defined as global quantities. See references for each paramter in the correspondent comment sections.

Parameter scan of total amount of receptors and k_orr_R·G for figure 3 of Bush, Vasen et al 2016.

# internal version 039
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="PM" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:39:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Plasma membrane volume. Defined as the volume contained in h=50nm spanning the membrane, in a spherical cell of Rc=2.5um of radius. 
V_PM=4*pi*h*Rc^2=3.92 fl
        </Comment>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_1" name="R" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:43:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Free, unoccupied receptor, uncoupled from G protein
        </Comment>
        <InitialExpression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Rtot],Reference=InitialValue&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Reference=InitialVolume&gt;
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="LR" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:44:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Ligand bound receptor, uncoupled from G protein
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="G" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:45:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Heterotrimeric G protein, uncoupled from receptor
        </Comment>
        <InitialExpression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Gtot],Reference=InitialValue&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Reference=InitialVolume&gt;
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="Gt" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:47:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          free GalphaGTP
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="Gd" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:47:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          free GalphaGDP
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="RG" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:47:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          unoccupied receptor - heterotirmeric G protein complex
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="Gbg" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:48:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          free G_beta_gamma heterodimer
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="LRG" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:48:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Ligand bound receptor, coupled to heterotrimeric G protein
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="LRGt" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:49:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Ligand bound receptor, coupled to GalphaGTP
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="RGd" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:49:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          unoccupied receptor - GalphaGDP complex
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="RGt" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:51:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          unoccupied receptor - GalphaGTP complex
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="LRGd" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T12:52:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Ligand bound receptor, coupled to GalphaGDP
        </Comment>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="L" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:44:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Extracelular ligand (alpha-factor) concentrarion in nM.
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="K_d_L·R" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:45:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Kd of alpha-factor with Ste2, expressed in nM.
Average of the values in the follwing publications. PMID 15491163, PMID 2839507, PMID 3023832, PMID 9819407, PMID 9182592, PMID 10866688, PMID 8524302, PMID 11495900, PMID 8385135
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="lambda" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:47:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Adimensional parameter used to code the micro-reversibility restrictions. 
lambda=K_d_L.RG/K_d_L.R
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_3" name="lambda_t" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:49:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Adimensional parameter used to code the micro-reversibility restrictions. 
lambda_t=K_d_L.RGt/K_d_L.R
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="lambda_d" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:50:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Adimensional parameter used to code the micro-reversibility restrictions. 
lambda_d=K_d_L.RGd/K_d_L.R
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="K_d_R·G" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:52:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Dissociation constant (Kd) between Galpha and Ste2, expressed in nM. Geometrical average of values reported in Alves et al. 2005 for transducin (Gt) and rhodopsin, and values reported in Alves et al. 2003 for the human delta-opioid receptor and Galpha_0, Galpha_i1, Galpha_i2, Galpha_i3.
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="eta" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:53:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Ratio of Kds of receptor binding to GαGTP over heterotrimeric G protein.
Assumed to be 1 by symmetry assumptions. 

Adimensional parameter used to code the micro-reversibility restrictions. 
eta=K_d_R.Gt/K_d_R.G
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="rho" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T14:55:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Adimensional parameter used to code the micro-reversibility restrictions. 
rho=K_d_R.Gd/K_d_R.G
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="k_Ef_G" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:03:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Exchange reaction rate for uncoupled heterotrimeric G protein
set to k_Ef_Gd by symmetry assumptions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_Gd],Reference=InitialValue&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_9" name="k_Hf_Gt" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:05:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Hydrolysis rate of GTP in GaGTP uncoupled from receptor. 
Average of rates reported in Yi et al. 2003 and Apanovitch en el. 1998.
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="k_Af_Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:06:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          reassociation rate of uncoupled GαGDP (uncoupled) to Gβγ 
Estimated in this work such that Gtot * k_Af_Gd = 1000 * k_Hf_RGt. This ensures that the hydrolysis of GTP and not the reassociation with Gbg is the limiting step in the inactivation of the system. 
Estimated to be k_Af_Gd=1000*(0.11s-1)/(860nM)= 0.13 nM-1 s-1
        </Comment>
        <Expression>
          1.66*0.13
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="k_Ef_RG" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:08:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Nucleotide exchange reaction rate for heterotrimeric G protein coupled to unoccupied receptor.
Set to k_Ef_RGd by symmetry assumption.
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="k_Ef_LRG" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:08:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Nucleotide exchange reaction rate for heterotrimeric G protein coupled to ligand-occupied receptor.
from Biddlecome et al. 1996 and Mukhopadhyay and Ross 1999 (PMID 8626481, PMID 10449728)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="k_Hf_LRGt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:08:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Hydrolysis rate of GTP in GaGTP coupled to occupied receptor.
Set to k_Hf_RGt by symmetry assumptions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_RGt],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="k_Af_LRGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:09:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          reassociation rate of GαGDP (coupled to occupied R) to Gβγ, 
assumed in this work equal to k_Af_Gd by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_Gd],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="k_Hf_RGt" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:10:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Hydrolysis rate of GTP in GaGTP coupled to unoccupied receptor
Rates reported in Yi et al. 2003 for Sst2 (GAP) stimulated hydrolysis of GTP in Gpa1. 
(Note that Sst2 interacts with Ste2, see main text).
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="k_Af_RGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:11:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          reassociation rate of GαGDP (coupled to unoccupied R) to Gβγ
assumed in this work equal to k_Af_Gd by symmetry assumption.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_Gd],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="Rtot" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:12:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          total amount of receptor molecules
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="Gtot" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:12:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          total amount of heterotrimeric G protein
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="k_on_L·R" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:22:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between ligand and uncoupled receptor.
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off), the extracelular ligand concentration [L] and adimensional parameters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R],Reference=Value&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_L·R],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="k_off_L·R" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:23:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the ligand (alpha-factor mating pheromone) and uncoupled receptor (Ste2). Set to k_off_L.R=0.001 s-1. 
Reference: Bajaj et al., 2004a; Jenness et al., 1983 (PMID 6360378, PMID 15491163).
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="k_on_L·RG" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:23:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between ligand and receptor coupled to heterotrimeric G protein.
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off), the extracelular ligand concentration [L] and adimensional parameters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RG],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_L·R],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="k_off_L·RG" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:25:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the ligand (alpha-factor mating pheromone) and receptor (Ste2) coupled to heterotrimeric G protein. 
Set to k_off_L.R by symmetry assumptions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="k_on_L·RGt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:26:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between ligand and receptor coupled to GalphaGTP.
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off), the extracelular ligand concentration [L] and adimensional parameters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGt],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_t],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_L·R],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="k_off_L·RGt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:27:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the ligand (alpha-factor mating pheromone) and receptor (Ste2) coupled to GalphaGTP. 
Set to k_off_L.R by symmetry assumptions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="k_on_L·RGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:29:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between ligand and receptor coupled to GalphaGDP.
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off), the extracelular ligand concentration [L] and adimensional parameters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGd],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_d],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_L·R],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="k_off_L·RGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:30:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the ligand (alpha-factor mating pheromone) and receptor (Ste2) coupled to GalphaGDP. 
Set to k_off_L.R by symmetry assumptions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="k_on_R·G" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:31:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between the heterotrimeric G protein and unoccupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="k_off_R·G" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:32:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate of receptor-heterotrimeric G protein interaction. 	
k_off_R.G=0.09 s-1, calculated from the time constants (tau) reported for the A_A2-adenosin and beta1-adrenergic receptors disociation from Galpha_s (Hein et al. 2006).
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="k_on_LR·G" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:33:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between the heterotrimeric G protein and ligand-occupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·G],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="k_off_LR·G" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:34:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the heterotrimeric G protein and ligand-occupied receptor
set to k_off_R.G by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="k_on_R·Gt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:35:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between GalphaGTP and unoccupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gt],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[eta],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="k_off_R·Gt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:36:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the GalphaGTP and unoccupied receptor
set to k_off_R.G by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="k_on_LR·Gt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:37:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between GalphaGTP and ligand-occupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gt],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_t],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[eta],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="k_off_LR·Gt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:38:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the GalphaGTP and ligand-occupied receptor
set to k_off_R.G by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="k_on_R·Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:39:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between GalphaGDP and unoccupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gd],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[rho],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="k_off_R·Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:40:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the GalphaGDP and unoccupied receptor
set to k_off_R.G by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="k_on_LR·Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:41:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          on-rate between GalphaGDP and ligand-occupied receptor
Value calculated from the correspondent dissociacion constant (K_d), off-rate (k_off) and adimensional paramters denoted by greek letters, used to code the micro-reversibility restrictions.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gd],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_d],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[rho],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G],Reference=Value&gt;/1.66))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="k_off_LR·Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:43:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          off-rate between the GalphaGDP and ligand-occupied receptor
set to k_off_R.G by symmetry assumption
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="k_Ar_Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:47:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          dissociation rate of uncoupled GαGDP (uncoupled) from Gβγ.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_Gd],Reference=Value&gt;/1.66*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_Gd·Gbg],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="k_Ar_RGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:49:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          dissociation rate of uncoupled GαGDP (coupled to unoccupied receptor) from Gβγ.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_RGd],Reference=Value&gt;/1.66*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_Gd·Gbg],Reference=Value&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[rho],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="k_Ar_LRGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T15:51:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          dissociation rate of uncoupled GαGDP (coupled to occupied receptor) from Gβγ.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda],Reference=Value&gt;*(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_LRGd],Reference=Value&gt;/1.66)*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_Gd·Gbg],Reference=Value&gt;/(&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_d],Reference=Value&gt;*&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[rho],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="tot_LR" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T11:11:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          variable representing total amount occupied receptor at a given time.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRG],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGd],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGt],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LR],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="tot_RG" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T11:13:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          variable representing total amount of receptor-Galpha complex
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RG],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGd],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGt],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRG],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGd],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGt],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="tot_G" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T11:16:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          variable representing total amount of heteromtrimeric G protein at a given time.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[G],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRG],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RG],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="tot_Gd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T11:16:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          variable representing total amount of  GaGDP at a given time.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gd],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGd],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGd],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="tot_Gt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T11:17:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          variable representing total amount of  GaGTP at a given time.
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gt],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGt],Reference=Concentration&gt;+&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGt],Reference=Concentration&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="k_Ef_Gd" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:28:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          exchange reaction rate for GaGDP (Gpa1) uncoupled from receptor
k_Ef_G=0.00062 s-1
reference: Apanovitch et al. 1998 (PMID 9537998)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="k_Ef_RGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:29:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Nucleotide exchange reaction rate for GalphaGDP coupled to unoccupied receptor.
Estimated as k_Ef_Gd by in this work (See supplementary materials).
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_RG],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="k_Ef_LRGd" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Nucleotide exchange reaction rate for GaGDP coupled to ligand-occupied receptor.
set to k_Ef_LRG by symmetry assumptions
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_LRG],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="K_d_Gd·Gbg" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-12-16T12:10:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Dissociation constante between GaGDP and Gbg, expressed in nM.
Estimated based on boundaries defined by the Ste5 - Gbg dissociation constant (Bush and Colman-Lerner 2013) and the lower limit for Kd values of protein-protein interactions (Chen et al 2013). See supplementary materials for details.
        </Comment>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="binding_R·G" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:16:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1032" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1031" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_1"/>
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="binding_L·R" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:40:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1030" name="k1" value="0"/>
          <Constant key="Parameter_1029" name="k2" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="binding_R·Gt" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:44:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1028" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1027" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_1"/>
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="binding_R·Gd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:44:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1026" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1025" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_1"/>
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="binding_LR·G" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:46:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1024" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1023" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_3"/>
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="binding_LR·Gt" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:46:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1022" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1021" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_3"/>
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="binding_LR·Gd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:48:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1020" name="k1" value="0.00461111"/>
          <Constant key="Parameter_1019" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_3"/>
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="binding_L·RG" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:49:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1018" name="k1" value="0"/>
          <Constant key="Parameter_1017" name="k2" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="binding_L·RGt" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:53:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1016" name="k1" value="0"/>
          <Constant key="Parameter_1015" name="k2" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="exchange_G" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:55:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1014" name="k1" value="0.00062"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="hydrolysis_Gt" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:56:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1013" name="k1" value="0.002"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="association_Gd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:59:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1012" name="k1" value="0.2158"/>
          <Constant key="Parameter_1011" name="k2" value="0.0013"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="exchange_RG" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:01:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1010" name="k1" value="0.00062"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="exchange_LRG" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:02:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1009" name="k1" value="1.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="hydrolysis_RGt" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:03:31Z</dcterms:W3CDTF>
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
          <Constant key="Parameter_1008" name="k1" value="0.11"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="hydrolysis_LRGt" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:04:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1007" name="k1" value="0.11"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="association_RGd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:06:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1006" name="k1" value="0.2158"/>
          <Constant key="Parameter_1005" name="k2" value="0.0013"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_19"/>
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="association_LRGd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T14:07:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1004" name="k1" value="0.2158"/>
          <Constant key="Parameter_1003" name="k2" value="0.0013"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_23"/>
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="binding_L·RGd" reversible="true" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-01T11:14:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1002" name="k1" value="0"/>
          <Constant key="Parameter_1001" name="k2" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="exchange_Gd" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:26:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1000" name="k1" value="0.00062"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="exchange_RGd" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:31:49Z</dcterms:W3CDTF>
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
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_999" name="k1" value="0.00062"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="exchange_LRGd" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:32:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_998" name="k1" value="1.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM]" value="3.92" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[R]" value="3308" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Rtot],Reference=InitialValue&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Reference=InitialVolume&gt;
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[G]" value="2042" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Gtot],Reference=InitialValue&gt;/&lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Reference=InitialVolume&gt;
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gt]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gd]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RG]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gbg]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRG]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGt]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGd]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[RGt]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[LRGd]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_L·R]" value="5.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_t]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[lambda_d]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_R·G]" value="36" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[eta]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[rho]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_G]" value="0.00062" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_Gt]" value="0.002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_Gd]" value="0.2158" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_RG]" value="0.00062" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_LRG]" value="1.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_LRGt]" value="0.11" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_LRGd]" value="0.2158" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_RGt]" value="0.11" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_RGd]" value="0.2158" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Rtot]" value="3308" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Gtot]" value="2042" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·R]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RG]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RG]" value="0.001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RGt]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGt]" value="0.001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RGd]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGd]" value="0.001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·G]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·G]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·G]" value="0.1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·Gt]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gt]" value="0.1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·Gt]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gt]" value="0.1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·Gd]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gd]" value="0.1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·Gd]" value="0.004611111111111112" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gd]" value="0.1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_Gd]" value="0.0013" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_RGd]" value="0.0013" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_LRGd]" value="0.0013" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_LR]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_RG]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_G]" value="520.9183673469388" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_Gd]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_Gt]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_Gd]" value="0.00062" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_RGd]" value="0.00062" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_LRGd]" value="1.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[K_d_Gd·Gbg]" value="0.01" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·G]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·G],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·G],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·G],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·R]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·R],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·R],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·R],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·R],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gt],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·Gt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gt],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gd],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_R·Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_R·Gd],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·G]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·G],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·G],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·G],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·G],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gt],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·Gt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gt],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gd],ParameterGroup=Parameters,Parameter=k1" value="0.004611111111111112" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_LR·Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_LR·Gd],ParameterGroup=Parameters,Parameter=k2" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_LR·Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RG]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RG],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RG],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RG],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RG],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGt],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RGt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGt],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_G]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_G],ParameterGroup=Parameters,Parameter=k1" value="0.00062" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_G],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_Gt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_Gt],ParameterGroup=Parameters,Parameter=k1" value="0.002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_Gt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_Gd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_Gd],ParameterGroup=Parameters,Parameter=k1" value="0.2158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_Gd],ParameterGroup=Parameters,Parameter=k2" value="0.0013" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_RG]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_RG],ParameterGroup=Parameters,Parameter=k1" value="0.00062" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_RG],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_LRG]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_LRG],ParameterGroup=Parameters,Parameter=k1" value="1.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_LRG],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_RGt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_RGt],ParameterGroup=Parameters,Parameter=k1" value="0.11" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_RGt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_LRGt]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[hydrolysis_LRGt],ParameterGroup=Parameters,Parameter=k1" value="0.11" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Hf_LRGt],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_RGd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_RGd],ParameterGroup=Parameters,Parameter=k1" value="0.2158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_RGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_RGd],ParameterGroup=Parameters,Parameter=k2" value="0.0013" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_RGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_LRGd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_LRGd],ParameterGroup=Parameters,Parameter=k1" value="0.2158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Af_LRGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[association_LRGd],ParameterGroup=Parameters,Parameter=k2" value="0.0013" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ar_LRGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGd],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_on_L·RGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[binding_L·RGd],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_L·RGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_Gd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_Gd],ParameterGroup=Parameters,Parameter=k1" value="0.00062" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_Gd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_RGd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_RGd],ParameterGroup=Parameters,Parameter=k1" value="0.00062" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_RGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_LRGd]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Reactions[exchange_LRGd],ParameterGroup=Parameters,Parameter=k1" value="1.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_Ef_LRGd],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_3"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
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
      <StateTemplateVariable objectReference="ModelValue_48"/>
      <StateTemplateVariable objectReference="ModelValue_49"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
      <StateTemplateVariable objectReference="ModelValue_50"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 0 0 0 3308 0 0 0 0 0 2042 0.00062 0.2158 0.11 0.2158 0.2158 0 0 0.001 0 0.001 0 0.001 0.004611111111111112 0.004611111111111112 0.1 0.004611111111111112 0.1 0.004611111111111112 0.1 0.004611111111111112 0.1 0.004611111111111112 0.1 0.0013 0.0013 0.0013 0.00062 1.5 0 0 520.9183673469388 0 0 3.92 0 5.6 1 1 1 36 1 1 0.002 0.00062 1.5 0.11 3308 2042 0.001 0.1 0.00062 0.01 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_14" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_15" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.1"/>
        <Parameter name="Duration" type="float" value="10"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="0"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="Carrousel_v39.txt" append="0" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="0"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="10"/>
            <Parameter name="Minimum" type="float" value="0.001"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="2"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=InitialValue"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="log" type="bool" value="1"/>
          </ParameterGroup>
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="33000"/>
            <Parameter name="Minimum" type="float" value="330"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="2"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Rtot],Reference=InitialValue"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="log" type="bool" value="1"/>
          </ParameterGroup>
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="1000"/>
            <Parameter name="Minimum" type="float" value="0.01"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="50"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=InitialValue"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="log" type="bool" value="1"/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_17" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_12" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_13" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Use Reeder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_22" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_23" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_26" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_9" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Body>
        <Object cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[k_off_R·G],Reference=InitialValue"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[Rtot],Reference=InitialValue"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=InitialValue"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gbg],Reference=ParticleNumber"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[tot_LR],Reference=Value"/>
      </Body>
    </Report>
    <Report key="Report_10" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_11" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_12" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_14" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
  <ListOfPlots>
    <PlotSpecification name="DoR" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="1"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[Gbg]|Values[L].InitialValue" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Values[L],Reference=InitialValue"/>
            <ChannelSpec cn="CN=Root,Model=Bush2016-Simplified-Carrousel-model-of-GPCR,Vector=Compartments[PM],Vector=Metabolites[Gbg],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="Bush2016-Simplified-Carrousel-model-of-GPCR.xml">
    <SBMLMap SBMLid="G" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="Gbg" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="Gd" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="Gt" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="Gtot" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="K_d_Gd_Gbg" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="K_d_L_R" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="K_d_R_G" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="L" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="LR" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="LRG" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="LRGd" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="LRGt" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="PM" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="R" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="RG" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="RGd" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="RGt" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="Rtot" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="association_Gd" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="association_LRGd" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="association_RGd" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="binding_LR_G" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="binding_LR_Gd" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="binding_LR_Gt" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="binding_L_R" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="binding_L_RG" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="binding_L_RGd" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="binding_L_RGt" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="binding_R_G" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="binding_R_Gd" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="binding_R_Gt" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="eta" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="exchange_G" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="exchange_Gd" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="exchange_LRG" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="exchange_LRGd" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="exchange_RG" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="exchange_RGd" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="hydrolysis_Gt" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="hydrolysis_LRGt" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="hydrolysis_RGt" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="k_Af_Gd" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="k_Af_LRGd" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="k_Af_RGd" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="k_Ar_Gd" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="k_Ar_LRGd" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="k_Ar_RGd" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="k_Ef_G" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="k_Ef_Gd" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="k_Ef_LRG" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="k_Ef_LRGd" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="k_Ef_RG" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="k_Ef_RGd" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="k_Hf_Gt" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="k_Hf_LRGt" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="k_Hf_RGt" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="k_off_LR_G" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="k_off_LR_Gd" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="k_off_LR_Gt" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="k_off_L_R" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="k_off_L_RG" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="k_off_L_RGd" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="k_off_L_RGt" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="k_off_R_G" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="k_off_R_Gd" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="k_off_R_Gt" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="k_on_LR_G" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="k_on_LR_Gd" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="k_on_LR_Gt" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="k_on_L_R" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="k_on_L_RG" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="k_on_L_RGd" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="k_on_L_RGt" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="k_on_R_G" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="k_on_R_Gd" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="k_on_R_Gt" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="lambda" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="lambda_d" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="lambda_t" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="rho" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="tot_G" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="tot_Gd" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="tot_Gt" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="tot_LR" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="tot_RG" COPASIkey="ModelValue_43"/>
  </SBMLReference>
</COPASI>
