<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.23.172+ (Debug) (http://www.copasi.org) at 2018-02-14 21:56:20 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="23" versionDevel="172" copasiSourcesModified="1">
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
        k1*PRODUCT&lt;substrate_i>-k2*PRODUCT&lt;product_j>
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_69" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_68" name="substrate" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_78" name="k2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="product" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_40" name="vGLYS" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T17:00:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v_max * (G6P/(G6P+K_m_G6P))*(1-(1/(1+exp(-20*(GLY-4.2)))))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="v_max" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_263" name="G6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_262" name="K_m_G6P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="GLY" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="vdHb_in" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T11:34:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        F_in * (O2_a - (2 * O2_c - O2_a))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_267" name="F_in" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="O2_a" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_265" name="O2_c" order="2" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="vdHb_out" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T11:41:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        F_out * dHb/V_v
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_269" name="F_out" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_268" name="dHb" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_250" name="V_v" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="vATPase" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:03:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        VmaxATPase * (ATP/(ATP+Km_ATP))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_272" name="VmaxATPase" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_271" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_270" name="Km_ATP" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="vPK" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:07:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k_PK*PEP*ADP
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_275" name="k_PK" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_274" name="PEP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_273" name="ADP" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="vPGK" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:10:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k_PGK*GAP*ADP*(NAD/NADH)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_278" name="k_PGK" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="GAP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_276" name="ADP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_279" name="NAD" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_280" name="NADH" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="vPFK" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-30T14:36:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k_PFK*ATP*(1+(ATP/K_I_ATP)^nH)^(-1)*(F6P/(F6P+K_m_F6P))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_285" name="k_PFK" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_283" name="K_I_ATP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_282" name="nH" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_281" name="F6P" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_286" name="K_m_F6P" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="vMITO (inkl. Volumes)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-30T14:32:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v_max_mito*(PYR/(PYR+K_m_PYR))*(ADP/(ADP+K_m_ADP))*(O2/(O2+K_m_O2))*(1-1/(1+exp(-5*(ATP/ADP-20)))) * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_292" name="v_max_mito" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_291" name="PYR" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_290" name="K_m_PYR" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_289" name="ADP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_288" name="K_m_ADP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_287" name="O2" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_293" name="K_m_O2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_294" name="ATP" order="7" role="product"/>
        <ParameterDescription key="FunctionParameter_295" name="Volume" order="8" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="vGLU_eg (inkl. Volumes)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:04:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax_GLU * (GLU_e/(GLU_e + K_m_GLU)) * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_304" name="Vmax_GLU" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="GLU_e" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_302" name="K_m_GLU" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_301" name="Volume" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="vGLU_gn (inkl. Volume)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:12:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax_GLU * (GLU_g/(GLU_g+K_m_GLU))*(ATP_g/(ATP_g+K_m_ATP)) * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_297" name="Vmax_GLU" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_298" name="GLU_g" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_299" name="K_m_GLU" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_300" name="ATP_g" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_296" name="K_m_ATP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_305" name="Volume" order="5" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="vGLU_ne (inkl. Volume)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T08:57:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        vSTIM * ratio_Na_GLU * (GLU_n/(GLU_n + Km_GLU)) * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_311" name="vSTIM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_310" name="ratio_Na_GLU" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_309" name="GLU_n" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_308" name="Km_GLU" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_307" name="Volume" order="4" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="vStim (with volume)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-26T11:59:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        vstim * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_315" name="vstim" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_314" name="Volume" order="1" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="modular rate law for two substrates, two products" type="UserDefined" reversible="unspecified">
      <Expression>
        Vmax * (1/(K_S1 * K_S2)) * ((S1 * S2 - (P1 * P2)/Keq)/((1+S1/K_S1)*(1+S2/K_S2)+(1+P1/K_P1)*(1+P2/K_P2) -1 ))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_312" name="Vmax" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_313" name="K_S1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_306" name="K_S2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_316" name="S1" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_317" name="S2" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_318" name="P1" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_319" name="P2" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_320" name="Keq" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_321" name="K_P1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_322" name="K_P2" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="modular rate law for one substrate, one product" type="UserDefined" reversible="unspecified">
      <Expression>
        Vmax * (1/(K_S1)) *( (S1 - P1/Keq)/((1+S1/K_S1)+(1+P1/K_P1)-1))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_332" name="Vmax" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_331" name="K_S1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_330" name="S1" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_329" name="P1" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_328" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_327" name="K_P1" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="Blood flow contribution inkl. volume" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T11:24:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        ((2*F_in)/V_c)*(Substrate - Product) * Volume
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_334" name="F_in" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_333" name="V_c" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_323" name="Volume" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_324" name="Substrate" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_325" name="Product" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="O2 transport function inkl. volume" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:43:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (PScap/Volume) *((KO2*(HbOP/O2_source -1)^(-1/nh))-O2_destination) * Volume1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_338" name="PScap" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_337" name="Volume" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_336" name="KO2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_335" name="HbOP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_326" name="O2_source" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_339" name="nh" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_340" name="O2_destination" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_341" name="Volume1" order="7" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="vLEAK_Na inkl. Volume" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:13:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (Sm* gNA )/(Volume * F)*((RT/F)*log(Na_e/Na) - Vm) * Volume1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_349" name="Sm" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_348" name="gNA" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_347" name="Volume" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_346" name="F" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_345" name="RT" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_344" name="Na_e" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_343" name="Na" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_342" name="Vm" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_350" name="Volume1" order="8" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="vPUMP volume dependent" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:37:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Sm/Volume * k_pump * ATP * Na * (1+ATP/Km_pump)^-1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_359" name="Sm" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_358" name="Volume" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_357" name="k_pump" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_356" name="ATP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_355" name="Na" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_354" name="Km_pump" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="vGlyp_SS" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T17:19:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        v_max*(GLY/(GLY+Km_GLY))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_362" name="v_max" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_361" name="GLY" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_360" name="Km_GLY" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="vHK (HS)" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-30T14:02:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k_HK*ATP * (1+G6P/K_I_G6P)^-1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_353" name="k_HK" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_352" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_351" name="G6P" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_363" name="K_I_G6P" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Brain Energy Metabolism with PPP" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-30T11:50:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Description>
        <vCard:EMAIL>felix.winter@asd-online.com</vCard:EMAIL>
        <vCard:N>
          <rdf:Description>
            <vCard:Family>Winter</vCard:Family>
            <vCard:Given>Felix</vCard:Given>
          </rdf:Description>
        </vCard:N>
        <vCard:ORG>
          <rdf:Description>
            <vCard:Orgname>ASD GmbH</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T09:29:38</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      Based on the model by Cloutier et al. (2009)

arteries have been modelled as additional compartments. Same size as capillaries to keep equations for transport between both compartments intact. 20140520

v_CO2_cg = 3*v_mito_g
v_CO2_cn = 3*v_mito_n

Parameter values were corrected according to the values from the SBML-File

Some rate laws depend on the volume information! Have to be adjusted (vPUMP, vLEAK, O2 transport ...)

Changes to the original model: dHb (desoxyhemoglobin) has been included in the capillaries. Initial values according to steady state value

The reactions for the PPP have all their reaction rates set to zero so that they do not influence the other reactions (yet).

2015-01-21: corrected rate laws for GLU cycling
2015-09-28: linked volumes to respective compartment
2015-10-01: renaming of reactions to common system
2016-01-07: correction rate laws for PPP

2016-10-12: worked on having the correct steady state values

2016-10-29:
	changed PGI to reversible, checked steady state to be the same
	changed AK to reversible, checked steady state to be the same
	changed CK to reversible, checked steady state to be the same
	changed LDH to reversible, checked steady state to be the same

	fixed reactions of PPP
	fixed species concentrations of species only relevant in PPP
	changed reaction rates of PGI and PFK to their values in the Cloutier model
2016-10-30
	changed reaction rates of ATPase to their values in the Cloutier model
	steady state only changed slightly for astrocytes
2016-11-08
	changed HK astrocytes to use the version of Heinrich/Schuster, applied K_I suggested by the reviewer. (works great!!!)
	changed HK neurons to use the version of Heinrich/Schuster, applied K_I suggested by the reviewer. (works )

2016-11-20
	set GLU concentration to 0 to allow time course simulation
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="capillary" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-11-07T12:05:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_1" name="neurons" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-11-07T12:05:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_2" name="astrocytes" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-11-07T12:33:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_3" name="extracellular_space" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-11-07T12:05:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:go:0005576" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_4" name="venous balloon" simulationType="ode" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T10:51:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=Value>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_out],Reference=Value>
        </Expression>
      </Compartment>
      <Compartment key="Compartment_5" name="artery" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T11:39:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="O2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-18T08:56:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="CO2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-18T08:56:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="dHb" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T12:01:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="GLC" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:17:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="G6P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:16:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="ATP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:14:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="F6P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:16:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="GAP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:17:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="NADH" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:00:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="PEP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:14:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_10" name="PYR" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:06:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="LAC" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:16:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="O2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:39:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="PCr" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:26:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Phosphocreatine</pre>
  </body>
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_14" name="Na+" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:06:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="GLU" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T11:15:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="ADP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:12:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="AMP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:53:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[ANP],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=InitialConcentration>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="Cr" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T09:53:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="NAD" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T11:00:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_neurons],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADH],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="G6L" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:08:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="P6G" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:08:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="Ru5P" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:10:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="X5P" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:10:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="R5P" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:11:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="S7P" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:12:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="E4P" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:13:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="NADPH" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-07-27T14:16:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="NADP" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-07-27T14:16:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="GLC" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:47:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="ATP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:46:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="G6P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:47:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="F6P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-07-31T13:55:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="GAP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:02:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_34" name="NADH" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:00:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_35" name="PEP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:14:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_36" name="PYR" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:06:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="LAC" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:16:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="O2" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:39:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="PCr" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:26:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Phosphocreatine</pre>
  </body>
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="Na+" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:44:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="GLY" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:55:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_42" name="GLU" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T11:13:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="ADP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:14:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_44" name="AMP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:53:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[ANP],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=InitialConcentration>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_45" name="Cr" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T09:50:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_46" name="NAD" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T11:00:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <InitialExpression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_astrocytes],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADH],Reference=InitialConcentration>
        </InitialExpression>
      </Metabolite>
      <Metabolite key="Metabolite_47" name="G6L" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:08:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_48" name="P6G" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:09:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_49" name="Ru5P" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:10:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_50" name="X5P" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:10:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_51" name="R5P" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:11:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_52" name="S7P" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:12:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="E4P" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-21T13:13:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_54" name="NADP" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-07-27T14:16:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_55" name="NADPH" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-07-27T14:15:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_56" name="GLU" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T09:58:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_57" name="Na+" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T09:56:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_58" name="O2" simulationType="fixed" compartment="Compartment_5" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-28T14:20:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_59" name="CO2" simulationType="fixed" compartment="Compartment_5" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T11:47:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="K_m_GLC" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-09T12:39:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Affinity constant for GLC</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="K_m_G6P" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-09T12:47:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Affinity constant for G6P</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="K_m_F6P_PGI" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-09T12:49:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_3" name="K_m_F6P_PFK" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T08:45:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="K_I_ATP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:23:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Inhibition constant for ATP</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="nH" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:06:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.sbo:0000190" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Hill coefficient for ATP</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="NADH_total_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:05:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="NADH_total_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:05:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="NAD_neurons" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:03:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_neurons],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADH],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_9" name="NAD_astrocytes" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:04:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_astrocytes],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADH],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="ANP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:32:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="q_AK" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:26:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="K_m_ATP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:35:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="K_m_ADP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:54:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="K_m_O2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:54:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="K_m_PYR" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:56:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="PCr_total" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:24:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="Cr_neurons" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:27:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="Cr_astrocytes" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:28:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="Vmax_ATPase_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:21:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="Vmax_ATPase_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:21:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="Vmax_en_GLC (wrt neurons)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:31:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>maximum transport rate of GLC from extracellular space to neurons</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="Vmax_eg_GLC (wrt astrocytes)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:33:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="K_T_GLC_ce" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:37:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="K_T_GLC_cg" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:38:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="K_T_GLC_en" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:39:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>affinity constant for transport of GLC from extracellular space to neurons</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="K_T_GLC_eg" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:41:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>affinity constant for transport of GLC from extracellular space to astrocytes</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="Vmax_ne_LAC (wrt neurons)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:31:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="Vmax_ge_LAC (wrt astrocytes)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:29:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="Vmax_gc_LAC (wrt astrocytes)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:28:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="Vmax_ec_LAC (wrt extracellular space)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:26:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="K_T_LAC_ec" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:24:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="K_T_LAC_gc" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:24:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="K_T_LAC_ne" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:03:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="K_T_LAC_ge" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:02:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="F_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-16T16:08:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          cerebral blood flow in resting condition
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="delta_F" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T10:54:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="f_CBF" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-16T16:14:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="t_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:10:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="t_end" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T11:28:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="t_1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:33:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="F_in" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T10:45:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_0],Reference=Value>*&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[f_CBF_dyn],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="F_out" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T10:47:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_0],Reference=Value>*(((&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)^(1/0.5)+(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)^(-1/2)*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[tau_v],Reference=Value>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)*&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=Value>)/(1+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_0],Reference=Value>*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)^(-1/2)*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[tau_v],Reference=Value>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="tau_v" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:09:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="K_O2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:29:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 transport constant
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="Hb.OP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:31:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 concentration with hemoglobin
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="nh_O2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:42:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 reaction order constant
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="Sm_g" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:33:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          characteristic length for Na (astrocytes)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="Sm_n" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:34:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          characteristic length for Na (neurons)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="k_pump" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:35:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          transport rate constant
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="K_m,Na-pump" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T11:23:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="Vmax_GLYS" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:31:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_52" name="K_m_G6P_GLYS" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T11:46:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_53" name="delta_GLY" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T11:01:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_54" name="t_0_GLY" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:11:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="t_end_GLY" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:34:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end],Reference=Value>+100
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_56" name="vmax_GLYP" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_57" name="K_m_GLY" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T17:31:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          affinity constant for GLY
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_58" name="g_Na_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:07:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          surface resistance neurons
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_59" name="g_Na_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:08:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          surface resistance astrocytes
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_60" name="Vm" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_60">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:09:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          surface potential
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_61" name="RT" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_61">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:09:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          perfect gas constant and temperature kPa
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_62" name="F" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_62">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:11:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          molecular charge
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_63" name="vn_1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:56:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          base sodium transport rate during stimulation (tail pinch)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_64" name="vn_2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_64">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:57:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          early stimulation of sodium transport rate (tail pinch)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="t_stim_tp" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_65">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T11:28:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          time constant of stimulation (tail pinch)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_66" name="stimulus_0" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_66">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T11:29:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_67" name="is_stimulated" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_67">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T11:22:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          if(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time> le 200 or &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time> ge &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0],Reference=Value>+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end],Reference=Value>,0,1)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_68" name="v_stim" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_68">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T11:35:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[is_stimulated],Reference=Value>*&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[stimulus],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_69" name="R_Na_GLU" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_69">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T08:55:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Glutamate / Na ratio for release of GLU by neurons during stimulation
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_70" name="V_eg_max_GLU" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_70">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T08:59:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          maximum uptake rate of GLU in astrocytes
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_71" name="K_m_GLU" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_71">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-09T12:39:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>Affinity constant for GLU</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_72" name="V_gn_max_GLU" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_72">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:09:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          reaction rate constant for glutamine synthase
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_73" name="delta_HK" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_73">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-09-28T10:55:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_74" name="BOLD signal" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_74">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T12:03:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>*(7*(1-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=Concentration>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=InitialConcentration>))+2*((1-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=Concentration>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=InitialConcentration>)/(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>))+(2*&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[E0],Reference=InitialValue>-0.2)*(1-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=InitialVolume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_75" name="E0" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_75">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T12:11:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          1-(2*&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[O2],Reference=InitialConcentration>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[artery],Vector=Metabolites[O2],Reference=InitialConcentration>)/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[artery],Vector=Metabolites[O2],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="K_m_ATP(ATPase)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_76">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:10:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_77" name="k_PK_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_77">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T12:59:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_78" name="k_PK_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_78">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T13:00:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="k_CK_forward_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_79">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T09:59:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_80" name="k_CK_reverse_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_80">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T10:01:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="k_CK_forward_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_81">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T10:02:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="k_CK_reverse_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-17T10:03:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_83" name="v_max_f_PGI" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-19T12:12:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_84" name="v_max_r_PGI" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_84">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-19T12:12:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_85" name="k_LDH_forward_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-20T15:03:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_86" name="k_LDH_reverse_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-20T15:03:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_87" name="k_LDH_forward_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_87">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-20T15:03:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="k_LDH_reverse_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_88">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-20T15:04:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_89" name="NULL" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_89">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:37:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_90" name="Vmax_cg_GLC (wrt capillaries)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_90">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:34:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>maximum transport rate of GLC from capillaries to the astrocytes</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_91" name="Vmax_ce_GLC (wrt capillaries)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_91">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:35:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <body xmlns="http://www.w3.org/1999/xhtml">
    <pre>maximum transport rate of GLC from capillaries to extracellular space</pre>
  </body>
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_92" name="Vmax_ne_LAC (wrt extracellular space)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:31:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_93" name="PS_cap_astrocytes (wrt capillaries)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:33:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 mass transfer constant between capillaries and astrocytes
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_94" name="PS_cap_neuron (wrt capillaries)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_94">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:32:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 mass transfer constant between capillary and neuron
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_95" name="Vmax_eg_GLU (wrt extracellular space)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_95">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:09:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          reaction rate constant for glutamine synthase
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_96" name="K_T_GLC_ce (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_96">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:37:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_97" name="Vmax_ce_GLC (wrt capillaries) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_97">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:35:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          0.118 from Aubert 2005 model
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (Aubert)],Reference=InitialValue>*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_98" name="Vmax_eg_GLC (wrt astrocytes) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_98">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:33:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Comment>
          1020 from model Aubert 2005
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (Aubert)],Reference=Value>*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_99" name="K_T_GLC_eg (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_99">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:41:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_100" name="K_T_GLC_en (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_100">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:39:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_101" name="Vmax_en_GLC (wrt neurons) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_101">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-11T13:24:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC  (Aubert)],Reference=InitialValue>*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_102" name="K_T_GLC_cg (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_102">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:38:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_103" name="Vmax_cg_GLC (wrt capillaries) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_103">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:34:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          0.0093 from Aubert 2005 model
        </Comment>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC  (Aubert)],Reference=InitialValue>*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_104" name="Vmax_ec_LAC (wrt extracellular space) (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_104">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:26:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_105" name="Vmax_gc_LAC (wrt astrocytes) (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:28:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_106" name="Vmax_ge_LAC (wrt astrocytes) (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:29:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_107" name="Vmax_ne_LAC (wrt neurons) (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-11T10:31:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_108" name="K_T_LAC_ne (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_108">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:03:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_109" name="K_T_LAC_ge (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_109">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-10T12:02:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_110" name="K_T_LAC_gc (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_110">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:24:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_111" name="K_T_LAC_ec (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_111">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:24:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_112" name="PS_cap_astrocytes (wrt capillaries) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_112">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:33:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          0.414 from Aubert 2005
0.25 is the astrocytic volume considered in Aubert 2005
        </Comment>
        <Expression>
          0.414*0.25*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_113" name="PS_cap_neuron (wrt capillaries) (Aubert)" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_113">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:32:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          1.73 from model Aubert 2005
0.45 is the neuronal volume considered in Aubert 2005
        </Comment>
        <Expression>
          1.73*0.45*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Reference=Volume>/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=Volume>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_114" name="K_O2 (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_114">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:29:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          0.0361 taken from model Aubert 2005
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_115" name="nh_O2 (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:42:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          2.73 taken from Aubert 2005
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_116" name="k_PFK_astrocytes" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_116">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-29T13:49:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          from Cloutier 2009 (kg_PFK)
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_117" name="k_PFK_neurons" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_117">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-29T13:49:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_118" name="Vmax_f_PGI (Cloutier)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_118">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-29T13:54:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          from Model Cloutier 2009
        </Comment>
      </ModelValue>
      <ModelValue key="ModelValue_119" name="Vmax_r_PGI (Cloutier)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-29T13:54:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_120" name="Vmax_ce_GLC (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_120">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:35:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_121" name="Vmax_cg_GLC  (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:34:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_122" name="Vmax_eg_GLC (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_122">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-22T10:33:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_123" name="Vmax_en_GLC  (Aubert)" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_123">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-10-11T13:24:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_124" name="f_CBF_dyn" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_124">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2016-11-21T10:50:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          1+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[delta_F],Reference=Value>*(1/(1+exp(-4.59186*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time>-(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0],Reference=Value>+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_1],Reference=Value>-3))))-1/(1+exp(-4.59186*(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time>-(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0],Reference=Value>+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_1],Reference=Value>+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end],Reference=Value>+3)))))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_125" name="stimulus" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_125">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-31T12:34:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vn_1],Reference=InitialValue>+&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vn_2],Reference=Value>*((&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0],Reference=Value>)/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_stim_tp],Reference=Value>)*exp(-(&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0],Reference=Value>)/&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_stim_tp],Reference=Value>)
        </Expression>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="HK_astrocytes (R01786)  (HeinrichSchuster)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:12:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5144" name="k_HK" value="0.0154276"/>
          <Constant key="Parameter_5146" name="ATP" value="3.18137e+20"/>
          <Constant key="Parameter_5147" name="K_I_G6P" value="0.02"/>
        </ListOfConstants>
        <KineticLaw function="Function_59" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Parameter_5144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Parameter_5147"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="PFK_neurons (R04779, R01070, R01015)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T12:15:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="2"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5141" name="k_PFK" value="0.383639"/>
          <Constant key="Parameter_5143" name="ATP" value="6.12398e+20"/>
          <Constant key="Parameter_5142" name="K_I_ATP" value="1"/>
          <Constant key="Parameter_5145" name="nH" value="4"/>
          <Constant key="Parameter_5148" name="K_m_F6P" value="0.18"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Parameter_5141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="PFK_astrocytes (R04779, R01070, R01015)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T12:14:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="2"/>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5139" name="k_PFK" value="0.280786"/>
          <Constant key="Parameter_5137" name="ATP" value="3.18137e+20"/>
          <Constant key="Parameter_5136" name="K_I_ATP" value="1"/>
          <Constant key="Parameter_5140" name="nH" value="4"/>
          <Constant key="Parameter_5138" name="K_m_F6P" value="0.18"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Parameter_5139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="PGK_neurons (R01061, R01512, R01518, R00658)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:12:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5113" name="k_PGK" value="6.13613"/>
          <Constant key="Parameter_5111" name="ADP" value="3.06364e+19"/>
          <Constant key="Parameter_5110" name="NAD" value="4.51608e+19"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Parameter_5113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="PGK_astrocytes (R01061, R01512, R01518, R00658)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-12T10:20:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5114" name="k_PGK" value="4.3855"/>
          <Constant key="Parameter_5112" name="ADP" value="3.56799e+19"/>
          <Constant key="Parameter_5116" name="NAD" value="2.13499e+19"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Parameter_5114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="PK_neurons (R00200)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:08:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5131" name="k_PK" value="28.6"/>
          <Constant key="Parameter_5119" name="ADP" value="3.06364e+19"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="PK_astrocytes (R00200)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:09:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5133" name="k_PK" value="2.73"/>
          <Constant key="Parameter_5134" name="ADP" value="3.56799e+19"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="mitochondrial_respiration_neurons (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T12:46:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_12" stoichiometry="3"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="15"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="15"/>
          <Product metabolite="Metabolite_1" stoichiometry="3"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5128" name="v_max_mito" value="0.0556"/>
          <Constant key="Parameter_5115" name="K_m_PYR" value="0.0632"/>
          <Constant key="Parameter_5123" name="ADP" value="3.06364e+19"/>
          <Constant key="Parameter_5130" name="K_m_ADP" value="0.00107"/>
          <Constant key="Parameter_5117" name="K_m_O2" value="0.0029658"/>
          <Constant key="Parameter_5129" name="ATP" value="6.12398e+20"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Parameter_5128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="mitochondrial_respiration_astrocytes (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:03:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_43" stoichiometry="15"/>
          <Substrate metabolite="Metabolite_38" stoichiometry="3"/>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="15"/>
          <Product metabolite="Metabolite_1" stoichiometry="3"/>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5122" name="v_max_mito" value="0.008454"/>
          <Constant key="Parameter_5126" name="K_m_PYR" value="0.0632"/>
          <Constant key="Parameter_5121" name="ADP" value="3.56799e+19"/>
          <Constant key="Parameter_5125" name="K_m_ADP" value="0.00107"/>
          <Constant key="Parameter_5124" name="K_m_O2" value="0.0029658"/>
          <Constant key="Parameter_5127" name="ATP" value="3.18137e+20"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Parameter_5122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="O2_exchange_capillary_neurons" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-19T11:47:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          O2 exchange between capillary and neurons
        </Comment>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5132" name="PScap" value="63.6955"/>
          <Constant key="Parameter_5118" name="Volume" value="0.45"/>
          <Constant key="Parameter_5120" name="KO2" value="0.0361"/>
          <Constant key="Parameter_5135" name="HbOP" value="8.6"/>
          <Constant key="Parameter_5149" name="nh" value="2.73"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="ModelValue_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="O2_exchange_capillary_astrocytes" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T11:17:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5150" name="PScap" value="4.70455"/>
          <Constant key="Parameter_5156" name="Volume" value="0.25"/>
          <Constant key="Parameter_5155" name="KO2" value="0.0361"/>
          <Constant key="Parameter_5157" name="HbOP" value="8.6"/>
          <Constant key="Parameter_5154" name="nh" value="2.73"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="ModelValue_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="O2_exchange_artery_capillary" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T11:42:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5153" name="F_in" value="0.012"/>
          <Constant key="Parameter_5152" name="V_c" value="0.0055"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="Compartment_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="CO2_exchange_capillary_artery" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-20T12:43:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5151" name="F_in" value="0.012"/>
          <Constant key="Parameter_5158" name="V_c" value="0.0055"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="Na+_exchange_neurons_extracellular_space (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:39:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_14" stoichiometry="3"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5162" name="Sm" value="40500"/>
          <Constant key="Parameter_5160" name="k_pump" value="3.17e-07"/>
          <Constant key="Parameter_5159" name="Km_pump" value="0.4243"/>
          <Constant key="Parameter_5163" name="Volume" value="0.45"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="Na+_exchange_astrocytes_extracellular_space (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T16:39:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_40" stoichiometry="3"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5161" name="Sm" value="10500"/>
          <Constant key="Parameter_5165" name="k_pump" value="3.17e-07"/>
          <Constant key="Parameter_5167" name="Km_pump" value="0.4243"/>
          <Constant key="Parameter_5168" name="Volume" value="0.25"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="GLY_production_astrocytes (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T17:09:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5164" name="v_max" value="0.0001528"/>
          <Constant key="Parameter_5166" name="K_m_G6P" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="GLY_degradation_astrocytes (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-21T17:33:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5171" name="v_max" value="4.922e-05"/>
          <Constant key="Parameter_5172" name="Km_GLY" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_58" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="ModelValue_57"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="LEAK_Na_neurons (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:28:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5173" name="Sm" value="40500"/>
          <Constant key="Parameter_5169" name="gNA" value="0.0039"/>
          <Constant key="Parameter_5170" name="F" value="96500"/>
          <Constant key="Parameter_5174" name="RT" value="2.57734e+06"/>
          <Constant key="Parameter_5176" name="Vm" value="-70"/>
          <Constant key="Parameter_5175" name="Volume" value="0.45"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="ModelValue_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="LEAK_Na_astrocytes (n.a)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T10:28:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5177" name="Sm" value="10500"/>
          <Constant key="Parameter_5178" name="gNA" value="0.00325"/>
          <Constant key="Parameter_5179" name="F" value="96500"/>
          <Constant key="Parameter_5180" name="RT" value="2.57734e+06"/>
          <Constant key="Parameter_5185" name="Vm" value="-70"/>
          <Constant key="Parameter_5188" name="Volume" value="0.25"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="ModelValue_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="Na+_exchange_extracellular_space_neurons  (stimulation)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-26T11:38:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5187" name="vstim" value="-0"/>
        </ListOfConstants>
        <KineticLaw function="Function_51" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="GLU_exchange_neurons_extracellular_space" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T08:56:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          Glutamate release by neurons to extracellular space
        </Comment>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5186" name="vSTIM" value="-0"/>
          <Constant key="Parameter_5181" name="ratio_Na_GLU" value="0.075"/>
          <Constant key="Parameter_5183" name="Km_GLU" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_50" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="GLU_exchange_extracellular_space_astrocytes" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:05:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5182" name="Vmax_GLU" value="0.026"/>
          <Constant key="Parameter_5193" name="K_m_GLU" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_48" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="GLU_exchange_astrocytes_neurons" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-05-27T09:14:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5190" name="Vmax_GLU" value="0.3"/>
          <Constant key="Parameter_5191" name="K_m_GLU" value="0.05"/>
          <Constant key="Parameter_5192" name="K_m_ATP" value="0.01532"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="inflow of dHb" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T11:35:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_58" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5184" name="F_in" value="0.012"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="ConcentrationPerTime" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="outflow of dHb" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-24T11:42:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5189" name="F_out" value="0.012"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Compartment_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="ATPase_neurons (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:11:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5195" name="VmaxATPase" value="0.0490284"/>
          <Constant key="Parameter_5222" name="Km_ATP" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Parameter_5195"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="ATPase_astrocytes (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:13:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5265" name="VmaxATPase" value="0.0357804"/>
          <Constant key="Parameter_5194" name="Km_ATP" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Parameter_5265"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="AK_neurons (R00127)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:48:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5196" name="k1" value="1000"/>
          <Constant key="Parameter_5260" name="k2" value="920"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_5196"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_16"/>
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_5260"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="AK_astrocytes (R00127)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-10-22T11:48:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5261" name="k1" value="1000"/>
          <Constant key="Parameter_5259" name="k2" value="920"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_5261"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_43"/>
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_5259"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_30"/>
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="CK_astrocytes (R01881)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:57:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5262" name="k1" value="0.0243"/>
          <Constant key="Parameter_5199" name="k2" value="0.02073"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_43"/>
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_30"/>
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="CK_neurons (R01881)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-16T13:54:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5198" name="k1" value="0.0524681"/>
          <Constant key="Parameter_5197" name="k2" value="0.015"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_13"/>
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="LDH_astrocytes (R00703)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:22:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5203" name="k1" value="6.26"/>
          <Constant key="Parameter_5201" name="k2" value="0.547"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_36"/>
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_37"/>
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="LDH_neurons (R00703)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-08-13T11:19:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5200" name="k1" value="5.3"/>
          <Constant key="Parameter_5204" name="k2" value="0.1046"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_87"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_10"/>
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="ZWF_astrocytes (R02736)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T12:54:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5202" name="Vmax" value="0.29057"/>
          <Constant key="Parameter_5208" name="K_S1" value="6.91392e-05"/>
          <Constant key="Parameter_5210" name="K_S2" value="1.31616e-05"/>
          <Constant key="Parameter_5211" name="Keq" value="22906.4"/>
          <Constant key="Parameter_5205" name="K_P1" value="0.0180932"/>
          <Constant key="Parameter_5207" name="K_P2" value="0.00050314"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_5202"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_5208"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_5210"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_5211"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_5205"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_5207"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="ZWF_neurons (R02736)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T12:54:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5206" name="Vmax" value="0.586458"/>
          <Constant key="Parameter_5209" name="K_S1" value="6.91392e-05"/>
          <Constant key="Parameter_5212" name="K_S2" value="1.31616e-05"/>
          <Constant key="Parameter_5221" name="Keq" value="22906.4"/>
          <Constant key="Parameter_5218" name="K_P1" value="0.0180932"/>
          <Constant key="Parameter_5217" name="K_P2" value="0.00050314"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_5206"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_5209"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_5212"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_5221"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_5218"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_5217"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="SOL_neurons (R02035)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T12:58:22Z</dcterms:W3CDTF>
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
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5219" name="Vmax" value="0.372782"/>
          <Constant key="Parameter_5214" name="K_S1" value="0.0180932"/>
          <Constant key="Parameter_5213" name="Keq" value="531174"/>
          <Constant key="Parameter_5215" name="K_P1" value="2.28618"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_5219"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_5214"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_5213"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_5215"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="SOL_astrocytes (R02035)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T12:58:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5220" name="Vmax" value="0.184701"/>
          <Constant key="Parameter_5216" name="K_S1" value="0.0180932"/>
          <Constant key="Parameter_5104" name="Keq" value="531174"/>
          <Constant key="Parameter_5100" name="K_P1" value="2.28618"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_5220"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_5216"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_5104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_5100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="GND_neurons  (R01528)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T13:01:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5099" name="Vmax" value="2.65764"/>
          <Constant key="Parameter_5107" name="K_S1" value="3.23421e-05"/>
          <Constant key="Parameter_5106" name="K_S2" value="3.11043e-06"/>
          <Constant key="Parameter_5102" name="Keq" value="4.0852e+07"/>
          <Constant key="Parameter_5108" name="K_P1" value="0.0537179"/>
          <Constant key="Parameter_5105" name="K_P2" value="0.00050314"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_5099"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_5107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_5106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_5102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_5108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_5105"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="GND_astrocytes (R01528)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T13:01:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5097" name="Vmax" value="1.31677"/>
          <Constant key="Parameter_5098" name="K_S1" value="3.23421e-05"/>
          <Constant key="Parameter_5096" name="K_S2" value="3.11043e-06"/>
          <Constant key="Parameter_5101" name="Keq" value="4.0852e+07"/>
          <Constant key="Parameter_5103" name="K_P1" value="0.00050314"/>
          <Constant key="Parameter_5257" name="K_P2" value="0.0537179"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_5097"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_5098"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_5096"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_5101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_5103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_5257"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="RPE_neurons (R01529)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T13:04:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5258" name="Vmax" value="0.0156605"/>
          <Constant key="Parameter_4961" name="K_S1" value="0.0537179"/>
          <Constant key="Parameter_4960" name="Keq" value="39.2574"/>
          <Constant key="Parameter_4959" name="K_P1" value="0.603002"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_5258"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_4961"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_4960"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_4959"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="RPE_astrocytes (R01529)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-24T13:04:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4958" name="Vmax" value="0.00775925"/>
          <Constant key="Parameter_4957" name="K_S1" value="0.0537179"/>
          <Constant key="Parameter_4956" name="Keq" value="39.2574"/>
          <Constant key="Parameter_4955" name="K_P1" value="0.603002"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_4958"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_4957"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_4956"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_4955"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="RKI_astrocytes (R01056)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:32:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4954" name="Vmax" value="0.000821984"/>
          <Constant key="Parameter_4953" name="K_S1" value="0.0537179"/>
          <Constant key="Parameter_4952" name="Keq" value="35.4534"/>
          <Constant key="Parameter_4951" name="K_P1" value="0.778461"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_4954"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_4953"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_4952"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_4951"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="RKI_neurons (R01056)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:32:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4950" name="Vmax" value="0.00165901"/>
          <Constant key="Parameter_4949" name="K_S1" value="0.0537179"/>
          <Constant key="Parameter_4948" name="Keq" value="35.4534"/>
          <Constant key="Parameter_4947" name="K_P1" value="0.778461"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Parameter_4950"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Parameter_4949"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Parameter_4948"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Parameter_4947"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="TKL-1_astrocytes (R01641)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:36:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4946" name="Vmax" value="0.000244278"/>
          <Constant key="Parameter_4945" name="K_S1" value="0.000173625"/>
          <Constant key="Parameter_4944" name="K_S2" value="0.000585387"/>
          <Constant key="Parameter_4943" name="Keq" value="1.65287e+06"/>
          <Constant key="Parameter_4942" name="K_P1" value="0.168333"/>
          <Constant key="Parameter_4941" name="K_P2" value="0.192807"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4946"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4945"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4944"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4943"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4942"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4941"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="TKL-1_neurons (R01641)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:36:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4940" name="Vmax" value="0.000493027"/>
          <Constant key="Parameter_4939" name="K_S1" value="0.000173625"/>
          <Constant key="Parameter_4938" name="K_S2" value="0.000585387"/>
          <Constant key="Parameter_4937" name="Keq" value="1.65287e+06"/>
          <Constant key="Parameter_4936" name="K_P1" value="0.168333"/>
          <Constant key="Parameter_4935" name="K_P2" value="0.192807"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4940"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4939"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4938"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4937"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4936"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4935"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="TAL_astrocytes (R01827)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:59:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4934" name="Vmax" value="0.0080394"/>
          <Constant key="Parameter_4933" name="K_S1" value="0.168333"/>
          <Constant key="Parameter_4932" name="K_S2" value="0.192807"/>
          <Constant key="Parameter_4931" name="Keq" value="0.323922"/>
          <Constant key="Parameter_4930" name="K_P1" value="0.0799745"/>
          <Constant key="Parameter_4929" name="K_P2" value="0.109681"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4934"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4933"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4932"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4931"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4930"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4929"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="TAL_neurons (R01827)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T16:59:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4928" name="Vmax" value="0.0162259"/>
          <Constant key="Parameter_4927" name="K_S1" value="0.168333"/>
          <Constant key="Parameter_4926" name="Keq" value="0.323922"/>
          <Constant key="Parameter_4925" name="K_P1" value="0.0799745"/>
          <Constant key="Parameter_4924" name="K_S2" value="0.192807"/>
          <Constant key="Parameter_4923" name="K_P2" value="0.109681"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4928"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4927"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4924"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4926"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4925"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4923"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="TKL-2_astrocytes (R01830)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T17:05:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4922" name="Vmax" value="0.000137124"/>
          <Constant key="Parameter_4921" name="K_S1" value="0.0799745"/>
          <Constant key="Parameter_4920" name="K_S2" value="0.168333"/>
          <Constant key="Parameter_4919" name="Keq" value="0.0777764"/>
          <Constant key="Parameter_4918" name="K_P1" value="0.603002"/>
          <Constant key="Parameter_4917" name="K_P2" value="0.109681"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4922"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4921"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4920"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4919"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4918"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4917"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="TKL-2_neurons (R01830)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-26T17:05:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4916" name="Vmax" value="0.000276758"/>
          <Constant key="Parameter_4915" name="K_S1" value="0.0799745"/>
          <Constant key="Parameter_4914" name="K_S2" value="0.168333"/>
          <Constant key="Parameter_4913" name="Keq" value="0.0777764"/>
          <Constant key="Parameter_4912" name="K_P1" value="0.603002"/>
          <Constant key="Parameter_4911" name="K_P2" value="0.109681"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4916"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4915"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4914"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Parameter_4913"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Parameter_4912"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Parameter_4911"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="NADPH oxidase neurons (R07172)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-28T09:25:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4910" name="k1" value="0.000423283"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4910"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="NADPH oxidase astrocytes (R07172)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-28T09:25:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4909" name="k1" value="0.000209722"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4909"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="R5P sink_astrocytes (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-28T09:28:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4908" name="k1" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="R5P sink_neurons (n.a.)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-28T09:28:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4907" name="k1" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4907"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="PGI_astrocytes (R02740) (HS)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-18T16:03:18Z</dcterms:W3CDTF>
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
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4906" name="k1" value="931.69"/>
          <Constant key="Parameter_4905" name="k2" value="2273.32"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_4906"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_4905"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="HK_neurons (R01786) (HeinrichSchuster)" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-04-09T16:12:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4904" name="k_HK" value="0.016132"/>
          <Constant key="Parameter_4903" name="K_I_G6P" value="0.02"/>
        </ListOfConstants>
        <KineticLaw function="Function_59" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Parameter_4904"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Parameter_4903"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="PGI_neurons (R02740) (HS)" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-20T13:08:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4902" name="k1" value="931.69"/>
          <Constant key="Parameter_4901" name="k2" value="2273.32"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_4902"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_4901"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary]" value="0.0054999999999999997" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons]" value="0.45000000000000001" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes]" value="0.25" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space]" value="0.20000000000000001" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon]" value="0.023699999999999999" type="Compartment" simulationType="ode"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[artery]" value="0.0054999999999999997" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[O2]" value="2.4593489666072855e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[CO2]" value="7.0046883060573071e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb]" value="1.4362554194875469e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GLC]" value="3.2519951898424148e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[G6P]" value="2.7085763639200514e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP]" value="6.1239808749382192e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[F6P]" value="1.110002005499752e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GAP]" value="1.5229654907008059e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADH]" value="1.4458431701165263e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PEP]" value="1.0206074901425231e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PYR]" value="1.6310385846277562e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[LAC]" value="2.7735201300299111e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[O2]" value="1.311293410424304e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr]" value="1.1531880621694239e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Na+]" value="4.2092649037732774e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GLU]" value="8.1298914165000516e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP]" value="3.0636384767729893e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[AMP]" value="1.6659170668981862e+18" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[ANP],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=InitialConcentration>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Cr]" value="2.0179384058057625e+20" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NAD]" value="4.5160772019834741e+19" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_neurons],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADH],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[G6L]" value="818496508518207.12" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[P6G]" value="2.4041756873336448e+18" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Ru5P]" value="4.320386223277241e+17" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[X5P]" value="1.5276567365779483e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[R5P]" value="6950085347313792" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[S7P]" value="2.4878687495292514e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[E4P]" value="2.95373673802447e+18" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADPH]" value="7.892119239539037e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NADP]" value="409271566336.00006" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLC]" value="1.8066723209904121e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP]" value="3.1813743487212028e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[G6P]" value="1.5117457284749619e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[F6P]" value="6.1953316022025411e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GAP]" value="8.6407414172139123e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADH]" value="1.17719023923967e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PEP]" value="2.517423088583274e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PYR]" value="3.2138618099791852e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[LAC]" value="1.9321060850376462e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[O2]" value="4.2654900441065672e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr]" value="6.6530258577245064e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Na+]" value="2.027604186273903e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLY]" value="1.6256618994333159e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLU]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP]" value="3.5679895829847679e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[AMP]" value="4.3495522582820413e+18" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[ANP],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=InitialConcentration>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Cr]" value="8.7465137977549406e+19" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NAD]" value="2.1349877452603302e+19" type="Species" simulationType="reactions">
            <InitialExpression>
              &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_astrocytes],Reference=InitialValue>-&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADH],Reference=InitialConcentration>
            </InitialExpression>
          </ModelParameter>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[G6L]" value="454285251450454.81" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[P6G]" value="1.1995116698785229e+18" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Ru5P]" value="2.4027153821971299e+17" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[X5P]" value="8.4966819080110049e+18" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[R5P]" value="3868134360429810" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[S7P]" value="1.2498175832677249e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[E4P]" value="2.6335200997563192e+18" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADP]" value="227030480008.80591" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NADPH]" value="4.3845106874728227e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Vector=Metabolites[GLU]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Vector=Metabolites[Na+]" value="1.806642537e+22" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[artery],Vector=Metabolites[O2]" value="2.7623564390730047e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[artery],Vector=Metabolites[CO2]" value="3.9746135814000246e+18" type="Species" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLC]" value="0.105" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_G6P]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_F6P_PGI]" value="0.059999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_F6P_PFK]" value="0.17999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_I_ATP]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nH]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_neurons]" value="0.22" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NADH_total_astrocytes]" value="0.22" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_neurons]" value="0.16664714092556812" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_astrocytes]" value="0.1418091981032768" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[ANP]" value="2.379" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[q_AK]" value="0.92000000000000004" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ATP]" value="0.01532" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ADP]" value="0.00107" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_O2]" value="0.0029658000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_PYR]" value="0.063200000000000006" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PCr_total]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_neurons]" value="0.74463666330534029" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_astrocytes]" value="0.58095701514559916" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ATPase_neurons]" value="0.048890000000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ATPase_astrocytes]" value="0.035657000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC (wrt neurons)]" value="1.1343825000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (wrt astrocytes)]" value="0.047611250000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_ce]" value="8.4567999999999994" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_cg]" value="9.9199999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_en]" value="5.3200000000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_eg]" value="3.52" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ne_LAC (wrt neurons)]" value="0.1978" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ge_LAC (wrt astrocytes)]" value="0.086124000000000006" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_gc_LAC (wrt astrocytes)]" value="0.00021855999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ec_LAC (wrt extracellular space)]" value="0.032500000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ec]" value="0.764818" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_gc]" value="0.12862000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ne]" value="0.093140000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ge]" value="0.22162999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_0]" value="0.012" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[delta_F]" value="0.41999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[f_CBF]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0]" value="200" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end]" value="40" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_1]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in]" value="0.012" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_out]" value="0.012" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[tau_v]" value="35" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_O2]" value="0.089732999999999993" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Hb.OP]" value="8.5999999999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nh_O2]" value="2.7000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_g]" value="10500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_n]" value="40500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_pump]" value="3.1699999999999999e-07" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m\,Na-pump]" value="0.42430000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_GLYS]" value="0.0001528" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_G6P_GLYS]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[delta_GLY]" value="62" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_0_GLY]" value="83" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end_GLY]" value="140" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vmax_GLYP]" value="4.922e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLY]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[g_Na_neurons]" value="0.0038999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[g_Na_astrocytes]" value="0.0032499999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vm]" value="-70" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[RT]" value="2577340" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F]" value="96500" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vn_1]" value="0.041000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vn_2]" value="1.4399999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_stim_tp]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[stimulus_0]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[is_stimulated]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_stim]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[R_Na_GLU]" value="0.074999999999999997" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[V_eg_max_GLU]" value="0.020799999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLU]" value="0.050000000000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[V_gn_max_GLU]" value="0.29999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[delta_HK]" value="0.59999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[BOLD signal]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[E0]" value="0.21938332662630811" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ATP(ATPase)]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PK_neurons]" value="28.600000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PK_astrocytes]" value="2.73" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_forward_neurons]" value="0.052468099999999997" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_reverse_neurons]" value="0.014999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_forward_astrocytes]" value="0.024299999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_reverse_astrocytes]" value="0.020729999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_max_f_PGI]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_max_r_PGI]" value="0.45000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_forward_astrocytes]" value="6.2599999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_reverse_astrocytes]" value="0.54700000000000004" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_forward_neurons]" value="5.2999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_reverse_neurons]" value="0.1046" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NULL]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC (wrt capillaries)]" value="0.44724540000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (wrt capillaries)]" value="1.778181" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ne_LAC (wrt extracellular space)]" value="0.44505" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_astrocytes (wrt capillaries)]" value="11.161818179999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_neuron (wrt capillaries)]" value="18.016363630000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLU (wrt extracellular space)]" value="0.025999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_ce (Aubert)]" value="9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (wrt capillaries) (Aubert)]" value="3.2523966726908893" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (wrt astrocytes) (Aubert)]" value="9040.0407685196769" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_eg (Aubert)]" value="9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_en (Aubert)]" value="9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC (wrt neurons) (Aubert)]" value="11767.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_GLC_cg (Aubert)]" value="9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC (wrt capillaries) (Aubert)]" value="0.096127950054900241" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ec_LAC (wrt extracellular space) (Aubert)]" value="0.0078300000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_gc_LAC (wrt astrocytes) (Aubert)]" value="0.0058000000000000013" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ge_LAC (wrt astrocytes) (Aubert)]" value="0.075999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ne_LAC (wrt neurons) (Aubert)]" value="0.28999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ne (Aubert)]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ge (Aubert)]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_gc (Aubert)]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_T_LAC_ec (Aubert)]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_astrocytes (wrt capillaries) (Aubert)]" value="4.704545454545455" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_neuron (wrt capillaries) (Aubert)]" value="63.695454545454552" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_O2 (Aubert)]" value="0.0361" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nh_O2 (Aubert)]" value="2.73" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PFK_astrocytes]" value="0.40300000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PFK_neurons]" value="0.55783000000000005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_f_PGI (Cloutier)]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_r_PGI (Cloutier)]" value="0.45000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (Aubert)]" value="0.089440908498999452" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC  (Aubert)]" value="0.002114814901207805" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (Aubert)]" value="7232.032614815741" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC  (Aubert)]" value="5230" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[f_CBF_dyn]" value="1" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[stimulus]" value="-3.8708886842152355e+45" type="ModelValue" simulationType="assignment"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_astrocytes (R01786)  (HeinrichSchuster)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_astrocytes (R01786)  (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=k_HK" value="0.0154276" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_astrocytes (R01786)  (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=ATP" value="3.1813743487212028e+20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_astrocytes (R01786)  (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=K_I_G6P" value="0.02" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=k_PFK" value="0.38363900000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=ATP" value="6.1239808749382192e+20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=K_I_ATP" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_I_ATP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=nH" value="4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nH],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_neurons (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=K_m_F6P" value="0.17999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_F6P_PFK],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=k_PFK" value="0.28078599999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=ATP" value="3.1813743487212028e+20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=K_I_ATP" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_I_ATP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=nH" value="4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nH],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PFK_astrocytes (R04779\, R01070\, R01015)],ParameterGroup=Parameters,Parameter=K_m_F6P" value="0.17999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_F6P_PFK],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_neurons (R01061\, R01512\, R01518\, R00658)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_neurons (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=k_PGK" value="6.1361299999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_neurons (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=ADP" value="3.0636384767729893e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_neurons (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=NAD" value="4.5160772019834741e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NAD],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_astrocytes (R01061\, R01512\, R01518\, R00658)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_astrocytes (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=k_PGK" value="4.3855000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_astrocytes (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=ADP" value="3.5679895829847679e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_astrocytes (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=NAD" value="2.1349877452603302e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NAD],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_neurons (R00200)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_neurons (R00200)],ParameterGroup=Parameters,Parameter=k_PK" value="28.600000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PK_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_neurons (R00200)],ParameterGroup=Parameters,Parameter=ADP" value="3.0636384767729893e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_astrocytes (R00200)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_astrocytes (R00200)],ParameterGroup=Parameters,Parameter=k_PK" value="2.73" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_PK_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PK_astrocytes (R00200)],ParameterGroup=Parameters,Parameter=ADP" value="3.5679895829847679e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=v_max_mito" value="0.055599999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=K_m_PYR" value="0.063200000000000006" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_PYR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=ADP" value="3.0636384767729893e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=K_m_ADP" value="0.00107" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ADP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=K_m_O2" value="0.0029658000000000002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_O2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_neurons (n.a.)],ParameterGroup=Parameters,Parameter=ATP" value="6.1239808749382192e+20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=v_max_mito" value="0.0084539999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=K_m_PYR" value="0.063200000000000006" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_PYR],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=ADP" value="3.5679895829847679e+19" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=K_m_ADP" value="0.00107" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ADP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=K_m_O2" value="0.0029658000000000002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_O2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[mitochondrial_respiration_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=ATP" value="3.1813743487212028e+20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=InitialParticleNumber>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons],ParameterGroup=Parameters,Parameter=PScap" value="63.695454545454552" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_neuron (wrt capillaries) (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons],ParameterGroup=Parameters,Parameter=Volume" value="0.45000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons],ParameterGroup=Parameters,Parameter=KO2" value="0.0361" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_O2 (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons],ParameterGroup=Parameters,Parameter=HbOP" value="8.5999999999999996" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Hb.OP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_neurons],ParameterGroup=Parameters,Parameter=nh" value="2.73" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nh_O2 (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes],ParameterGroup=Parameters,Parameter=PScap" value="4.704545454545455" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_astrocytes (wrt capillaries) (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes],ParameterGroup=Parameters,Parameter=Volume" value="0.25" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes],ParameterGroup=Parameters,Parameter=KO2" value="0.0361" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_O2 (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes],ParameterGroup=Parameters,Parameter=HbOP" value="8.5999999999999996" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Hb.OP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_capillary_astrocytes],ParameterGroup=Parameters,Parameter=nh" value="2.73" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[nh_O2 (Aubert)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_artery_capillary]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_artery_capillary],ParameterGroup=Parameters,Parameter=F_in" value="0.012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[O2_exchange_artery_capillary],ParameterGroup=Parameters,Parameter=V_c" value="0.0054999999999999997" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CO2_exchange_capillary_artery]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CO2_exchange_capillary_artery],ParameterGroup=Parameters,Parameter=F_in" value="0.012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CO2_exchange_capillary_artery],ParameterGroup=Parameters,Parameter=V_c" value="0.0054999999999999997" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_neurons_extracellular_space (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_neurons_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Sm" value="40500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_n],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_neurons_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=k_pump" value="3.1699999999999999e-07" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_pump],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_neurons_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Km_pump" value="0.42430000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m\,Na-pump],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_neurons_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Volume" value="0.45000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_astrocytes_extracellular_space (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_astrocytes_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Sm" value="10500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_g],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_astrocytes_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=k_pump" value="3.1699999999999999e-07" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_pump],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_astrocytes_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Km_pump" value="0.42430000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m\,Na-pump],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_astrocytes_extracellular_space (n.a.)],ParameterGroup=Parameters,Parameter=Volume" value="0.25" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_production_astrocytes (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_production_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=v_max" value="0.0001528" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_GLYS],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_production_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=K_m_G6P" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_G6P_GLYS],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_degradation_astrocytes (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_degradation_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=v_max" value="4.922e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[vmax_GLYP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLY_degradation_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=Km_GLY" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLY],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=Sm" value="40500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_n],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=gNA" value="0.0038999999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[g_Na_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=F" value="96500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=RT" value="2577340" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[RT],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=Vm" value="-70" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vm],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_neurons (n.a.)],ParameterGroup=Parameters,Parameter=Volume" value="0.45000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=Sm" value="10500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Sm_g],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=gNA" value="0.0032499999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[g_Na_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=F" value="96500" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=RT" value="2577340" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[RT],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=Vm" value="-70" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vm],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LEAK_Na_astrocytes (n.a)],ParameterGroup=Parameters,Parameter=Volume" value="0.25" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Reference=InitialVolume>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_extracellular_space_neurons  (stimulation)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[Na+_exchange_extracellular_space_neurons  (stimulation)],ParameterGroup=Parameters,Parameter=vstim" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_stim],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_neurons_extracellular_space]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_neurons_extracellular_space],ParameterGroup=Parameters,Parameter=vSTIM" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_stim],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_neurons_extracellular_space],ParameterGroup=Parameters,Parameter=ratio_Na_GLU" value="0.074999999999999997" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[R_Na_GLU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_neurons_extracellular_space],ParameterGroup=Parameters,Parameter=Km_GLU" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_extracellular_space_astrocytes]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_extracellular_space_astrocytes],ParameterGroup=Parameters,Parameter=Vmax_GLU" value="0.025999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLU (wrt extracellular space)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_extracellular_space_astrocytes],ParameterGroup=Parameters,Parameter=K_m_GLU" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_astrocytes_neurons]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_astrocytes_neurons],ParameterGroup=Parameters,Parameter=Vmax_GLU" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[V_gn_max_GLU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_astrocytes_neurons],ParameterGroup=Parameters,Parameter=K_m_GLU" value="0.050000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_GLU],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GLU_exchange_astrocytes_neurons],ParameterGroup=Parameters,Parameter=K_m_ATP" value="0.01532" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ATP],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[inflow of dHb]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[inflow of dHb],ParameterGroup=Parameters,Parameter=F_in" value="0.012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[outflow of dHb]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[outflow of dHb],ParameterGroup=Parameters,Parameter=F_out" value="0.012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_out],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_neurons (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_neurons (n.a.)],ParameterGroup=Parameters,Parameter=VmaxATPase" value="0.0490284" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_neurons (n.a.)],ParameterGroup=Parameters,Parameter=Km_ATP" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ATP(ATPase)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_astrocytes (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=VmaxATPase" value="0.035780399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ATPase_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=Km_ATP" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[K_m_ATP(ATPase)],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_neurons (R00127)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_neurons (R00127)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_neurons (R00127)],ParameterGroup=Parameters,Parameter=k2" value="920" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_astrocytes (R00127)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_astrocytes (R00127)],ParameterGroup=Parameters,Parameter=k1" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[AK_astrocytes (R00127)],ParameterGroup=Parameters,Parameter=k2" value="920" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_astrocytes (R01881)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_astrocytes (R01881)],ParameterGroup=Parameters,Parameter=k1" value="0.024299999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_forward_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_astrocytes (R01881)],ParameterGroup=Parameters,Parameter=k2" value="0.020729999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_reverse_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_neurons (R01881)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_neurons (R01881)],ParameterGroup=Parameters,Parameter=k1" value="0.052468099999999997" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_forward_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[CK_neurons (R01881)],ParameterGroup=Parameters,Parameter=k2" value="0.014999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_CK_reverse_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_astrocytes (R00703)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_astrocytes (R00703)],ParameterGroup=Parameters,Parameter=k1" value="6.2599999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_forward_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_astrocytes (R00703)],ParameterGroup=Parameters,Parameter=k2" value="0.54700000000000004" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_reverse_astrocytes],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_neurons (R00703)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_neurons (R00703)],ParameterGroup=Parameters,Parameter=k1" value="5.2999999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_forward_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[LDH_neurons (R00703)],ParameterGroup=Parameters,Parameter=k2" value="0.1046" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[k_LDH_reverse_neurons],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=Vmax" value="0.29056999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=K_S1" value="6.9139200000000004e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=K_S2" value="1.3161599999999999e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=Keq" value="22906.400000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=K_P1" value="0.0180932" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_astrocytes (R02736)],ParameterGroup=Parameters,Parameter=K_P2" value="0.00050314000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=Vmax" value="0.58645800000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=K_S1" value="6.9139200000000004e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=K_S2" value="1.3161599999999999e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=Keq" value="22906.400000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=K_P1" value="0.0180932" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[ZWF_neurons (R02736)],ParameterGroup=Parameters,Parameter=K_P2" value="0.00050314000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_neurons (R02035)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_neurons (R02035)],ParameterGroup=Parameters,Parameter=Vmax" value="0.372782" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_neurons (R02035)],ParameterGroup=Parameters,Parameter=K_S1" value="0.0180932" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_neurons (R02035)],ParameterGroup=Parameters,Parameter=Keq" value="531174" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_neurons (R02035)],ParameterGroup=Parameters,Parameter=K_P1" value="2.2861799999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_astrocytes (R02035)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_astrocytes (R02035)],ParameterGroup=Parameters,Parameter=Vmax" value="0.184701" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_astrocytes (R02035)],ParameterGroup=Parameters,Parameter=K_S1" value="0.0180932" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_astrocytes (R02035)],ParameterGroup=Parameters,Parameter=Keq" value="531174" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[SOL_astrocytes (R02035)],ParameterGroup=Parameters,Parameter=K_P1" value="2.2861799999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=Vmax" value="2.6576399999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=K_S1" value="3.2342100000000003e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=K_S2" value="3.1104299999999999e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=Keq" value="40852000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=K_P1" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_neurons  (R01528)],ParameterGroup=Parameters,Parameter=K_P2" value="0.00050314000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=Vmax" value="1.31677" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=K_S1" value="3.2342100000000003e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=K_S2" value="3.1104299999999999e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=Keq" value="40852000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=K_P1" value="0.00050314000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[GND_astrocytes (R01528)],ParameterGroup=Parameters,Parameter=K_P2" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_neurons (R01529)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_neurons (R01529)],ParameterGroup=Parameters,Parameter=Vmax" value="0.015660500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_neurons (R01529)],ParameterGroup=Parameters,Parameter=K_S1" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_neurons (R01529)],ParameterGroup=Parameters,Parameter=Keq" value="39.257399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_neurons (R01529)],ParameterGroup=Parameters,Parameter=K_P1" value="0.60300200000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_astrocytes (R01529)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_astrocytes (R01529)],ParameterGroup=Parameters,Parameter=Vmax" value="0.0077592499999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_astrocytes (R01529)],ParameterGroup=Parameters,Parameter=K_S1" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_astrocytes (R01529)],ParameterGroup=Parameters,Parameter=Keq" value="39.257399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RPE_astrocytes (R01529)],ParameterGroup=Parameters,Parameter=K_P1" value="0.60300200000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_astrocytes (R01056)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_astrocytes (R01056)],ParameterGroup=Parameters,Parameter=Vmax" value="0.000821984" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_astrocytes (R01056)],ParameterGroup=Parameters,Parameter=K_S1" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_astrocytes (R01056)],ParameterGroup=Parameters,Parameter=Keq" value="35.453400000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_astrocytes (R01056)],ParameterGroup=Parameters,Parameter=K_P1" value="0.77846099999999996" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_neurons (R01056)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_neurons (R01056)],ParameterGroup=Parameters,Parameter=Vmax" value="0.00165901" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_neurons (R01056)],ParameterGroup=Parameters,Parameter=K_S1" value="0.053717899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_neurons (R01056)],ParameterGroup=Parameters,Parameter=Keq" value="35.453400000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[RKI_neurons (R01056)],ParameterGroup=Parameters,Parameter=K_P1" value="0.77846099999999996" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=Vmax" value="0.00024427800000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=K_S1" value="0.00017362500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=K_S2" value="0.00058538700000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=Keq" value="1652870" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=K_P1" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_astrocytes (R01641)],ParameterGroup=Parameters,Parameter=K_P2" value="0.19280700000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=Vmax" value="0.00049302700000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=K_S1" value="0.00017362500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=K_S2" value="0.00058538700000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=Keq" value="1652870" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=K_P1" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-1_neurons (R01641)],ParameterGroup=Parameters,Parameter=K_P2" value="0.19280700000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=Vmax" value="0.0080394000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=K_S1" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=K_S2" value="0.19280700000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=Keq" value="0.32392199999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=K_P1" value="0.079974500000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_astrocytes (R01827)],ParameterGroup=Parameters,Parameter=K_P2" value="0.109681" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=Vmax" value="0.016225900000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=K_S1" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=Keq" value="0.32392199999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=K_P1" value="0.079974500000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=K_S2" value="0.19280700000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TAL_neurons (R01827)],ParameterGroup=Parameters,Parameter=K_P2" value="0.109681" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=Vmax" value="0.000137124" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=K_S1" value="0.079974500000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=K_S2" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=Keq" value="0.077776399999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=K_P1" value="0.60300200000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_astrocytes (R01830)],ParameterGroup=Parameters,Parameter=K_P2" value="0.109681" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=Vmax" value="0.000276758" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=K_S1" value="0.079974500000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=K_S2" value="0.16833300000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=Keq" value="0.077776399999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=K_P1" value="0.60300200000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[TKL-2_neurons (R01830)],ParameterGroup=Parameters,Parameter=K_P2" value="0.109681" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[NADPH oxidase neurons (R07172)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[NADPH oxidase neurons (R07172)],ParameterGroup=Parameters,Parameter=k1" value="0.00042328299999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[NADPH oxidase astrocytes (R07172)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[NADPH oxidase astrocytes (R07172)],ParameterGroup=Parameters,Parameter=k1" value="0.000209722" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[R5P sink_astrocytes (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[R5P sink_astrocytes (n.a.)],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NULL],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[R5P sink_neurons (n.a.)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[R5P sink_neurons (n.a.)],ParameterGroup=Parameters,Parameter=k1" value="0" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_astrocytes (R02740) (HS)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_astrocytes (R02740) (HS)],ParameterGroup=Parameters,Parameter=k1" value="931.69000000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_astrocytes (R02740) (HS)],ParameterGroup=Parameters,Parameter=k2" value="2273.3200000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_neurons (R01786) (HeinrichSchuster)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_neurons (R01786) (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=k_HK" value="0.016132000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_neurons (R01786) (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=K_I_G6P" value="0.02" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_neurons (R02740) (HS)]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_neurons (R02740) (HS)],ParameterGroup=Parameters,Parameter=k1" value="931.69000000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGI_neurons (R02740) (HS)],ParameterGroup=Parameters,Parameter=k2" value="2273.3200000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="Compartment_4"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_56"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_55"/>
      <StateTemplateVariable objectReference="ModelValue_67"/>
      <StateTemplateVariable objectReference="ModelValue_68"/>
      <StateTemplateVariable objectReference="ModelValue_74"/>
      <StateTemplateVariable objectReference="ModelValue_75"/>
      <StateTemplateVariable objectReference="ModelValue_97"/>
      <StateTemplateVariable objectReference="ModelValue_98"/>
      <StateTemplateVariable objectReference="ModelValue_101"/>
      <StateTemplateVariable objectReference="ModelValue_103"/>
      <StateTemplateVariable objectReference="ModelValue_112"/>
      <StateTemplateVariable objectReference="ModelValue_113"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_54"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_57"/>
      <StateTemplateVariable objectReference="Metabolite_58"/>
      <StateTemplateVariable objectReference="Metabolite_59"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
      <StateTemplateVariable objectReference="Compartment_5"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
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
      <StateTemplateVariable objectReference="ModelValue_69"/>
      <StateTemplateVariable objectReference="ModelValue_70"/>
      <StateTemplateVariable objectReference="ModelValue_71"/>
      <StateTemplateVariable objectReference="ModelValue_72"/>
      <StateTemplateVariable objectReference="ModelValue_73"/>
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
      <StateTemplateVariable objectReference="ModelValue_90"/>
      <StateTemplateVariable objectReference="ModelValue_91"/>
      <StateTemplateVariable objectReference="ModelValue_92"/>
      <StateTemplateVariable objectReference="ModelValue_93"/>
      <StateTemplateVariable objectReference="ModelValue_94"/>
      <StateTemplateVariable objectReference="ModelValue_95"/>
      <StateTemplateVariable objectReference="ModelValue_96"/>
      <StateTemplateVariable objectReference="ModelValue_99"/>
      <StateTemplateVariable objectReference="ModelValue_100"/>
      <StateTemplateVariable objectReference="ModelValue_102"/>
      <StateTemplateVariable objectReference="ModelValue_104"/>
      <StateTemplateVariable objectReference="ModelValue_105"/>
      <StateTemplateVariable objectReference="ModelValue_106"/>
      <StateTemplateVariable objectReference="ModelValue_107"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
      <StateTemplateVariable objectReference="ModelValue_114"/>
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0.023699999999999999 3.5679895829847679e+19 3.0636384767729893e+19 2.027604186273903e+21 4.2092649037732774e+21 8.6407414172139123e+17 1.5229654907008059e+18 1.5117457284749619e+19 1.110002005499752e+19 6.1953316022025411e+18 2.4593489666072855e+19 2.7085763639200514e+19 1.4362554194875469e+17 8.1298914165000516e+20 2.1349877452603302e+19 4.5160772019834741e+19 7.0046883060573071e+18 1.0206074901425231e+18 2.517423088583274e+18 0 1.6256618994333159e+20 6.6530258577245064e+20 2.0179384058057625e+20 4.2654900441065672e+18 6.1239808749382192e+20 3.1813743487212028e+20 1.311293410424304e+19 4.3495522582820413e+18 1.6659170668981862e+18 1.1531880621694239e+21 0 8.7465137977549406e+19 0.16664714092556812 0.1418091981032768 0.74463666330534029 0.58095701514559916 0.012 0.012 140 0 0 0 0.21938332662630811 3.2523966726908893 9040.0407685196769 11767.5 0.096127950054900241 4.704545454545455 63.695454545454552 1 -3.8708886842152355e+45 3.2519951898424148e+20 1.4458431701165263e+19 1.6310385846277562e+19 2.7735201300299111e+20 818496508518207.12 2.4041756873336448e+18 4.320386223277241e+17 1.5276567365779483e+19 6950085347313792 2.4878687495292514e+19 2.95373673802447e+18 7.892119239539037e+19 409271566336.00006 1.8066723209904121e+20 1.17719023923967e+19 3.2138618099791852e+19 1.9321060850376462e+20 454285251450454.81 1.1995116698785229e+18 2.4027153821971299e+17 8.4966819080110049e+18 3868134360429810 1.2498175832677249e+19 2.6335200997563192e+18 227030480008.80591 4.3845106874728227e+19 1.806642537e+22 2.7623564390730047e+19 3.9746135814000246e+18 0.0054999999999999997 0.45000000000000001 0.25 0.20000000000000001 0.0054999999999999997 0.105 0.5 0.059999999999999998 0.17999999999999999 1 4 0.22 0.22 2.379 0.92000000000000004 0.01532 0.00107 0.0029658000000000002 0.063200000000000006 5 0.048890000000000003 0.035657000000000001 1.1343825000000001 0.047611250000000001 8.4567999999999994 9.9199999999999999 5.3200000000000003 3.52 0.1978 0.086124000000000006 0.00021855999999999999 0.032500000000000001 0.764818 0.12862000000000001 0.093140000000000001 0.22162999999999999 0.012 0.41999999999999998 1 200 40 2 35 0.089732999999999993 8.5999999999999996 2.7000000000000002 10500 40500 3.1699999999999999e-07 0.42430000000000001 0.0001528 0.5 62 83 4.922e-05 1 0.0038999999999999998 0.0032499999999999999 -70 2577340 96500 0.041000000000000002 1.4399999999999999 2 0 0.074999999999999997 0.020799999999999999 0.050000000000000003 0.29999999999999999 0.59999999999999998 0.001 28.600000000000001 2.73 0.052468099999999997 0.014999999999999999 0.024299999999999999 0.020729999999999998 0.5 0.45000000000000001 6.2599999999999998 0.54700000000000004 5.2999999999999998 0.1046 0 0.44724540000000002 1.778181 0.44505 11.161818179999999 18.016363630000001 0.025999999999999999 9 9 9 9 0.0078300000000000002 0.0058000000000000013 0.075999999999999998 0.28999999999999998 0.5 0.5 0.5 0.5 0.0361 2.73 0.40300000000000002 0.55783000000000005 0.5 0.45000000000000001 0.089440908498999452 0.002114814901207805 7232.032614815741 5230 
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
      <Report reference="Report_18" target="EventTest29.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="300"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="300"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="195"/>
        <Parameter name="Output Event" type="bool" value="1"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
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
    <Task key="Task_10" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="0"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="0.10000000000000001"/>
            <Parameter name="Minimum" type="float" value="0.025000000000000001"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="10"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[HK_astrocytes (R01786)  (HeinrichSchuster)],ParameterGroup=Parameters,Parameter=k_HK,Reference=Value"/>
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
          ((&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GAP],Reference=Concentration>-0.0056)/0.0056)^2+((&lt;CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GAP],Reference=Concentration>-0.0056)/0.0056)^2
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="0.1"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_astrocytes (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=k_PGK,Reference=Value"/>
            <Parameter name="StartValue" type="float" value="4.3854981370354933"/>
            <Parameter name="UpperBound" type="cn" value="10.0"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="0.1"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Reactions[PGK_neurons (R01061\, R01512\, R01518\, R00658)],ParameterGroup=Parameters,Parameter=k_PGK,Reference=Value"/>
            <Parameter name="StartValue" type="float" value="6.136131770216819"/>
            <Parameter name="UpperBound" type="cn" value="10.0"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
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
        <Parameter name="Create Parameter Sets" type="bool" value="0"/>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
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
            <Parameter name="ObjectListType" type="unsignedInteger" value="0"/>
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
    <Report key="Report_18" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[O2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[CO2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[G6P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[F6P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GAP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PEP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[O2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Na+],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GLU],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[AMP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Cr],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NAD],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[G6P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[F6P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GAP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PEP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[O2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Na+],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLY],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLU],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[AMP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Cr],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NAD],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Vector=Metabolites[GLU],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_neurons],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_astrocytes],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_neurons],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_astrocytes],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_out],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end_GLY],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[is_stimulated],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_stim],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[BOLD signal],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[E0],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (wrt capillaries) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (wrt astrocytes) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC (wrt neurons) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC (wrt capillaries) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_astrocytes (wrt capillaries) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_neuron (wrt capillaries) (Aubert)],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[f_CBF_dyn],Reference=Value"/>
        <Object cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[stimulus],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Compartments[venous balloon].Volume" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[venous balloon],Reference=Volume"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[BOLD signal]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[BOLD signal],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Cr_astrocytes]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_astrocytes],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Cr_neurons]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Cr_neurons],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[E0]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[E0],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F_in]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_in],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F_out]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[F_out],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[NAD_astrocytes]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_astrocytes],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[NAD_neurons]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[NAD_neurons],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[PS_cap_astrocytes (wrt capillaries) (Aubert)]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_astrocytes (wrt capillaries) (Aubert)],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[PS_cap_neuron (wrt capillaries) (Aubert)]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[PS_cap_neuron (wrt capillaries) (Aubert)],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vmax_ce_GLC (wrt capillaries) (Aubert)]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_ce_GLC (wrt capillaries) (Aubert)],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vmax_cg_GLC (wrt capillaries) (Aubert)]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_cg_GLC (wrt capillaries) (Aubert)],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vmax_eg_GLC (wrt astrocytes) (Aubert) ]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_eg_GLC (wrt astrocytes) (Aubert) ],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vmax_en_GLC (wrt neurons) (Aubert)]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[Vmax_en_GLC (wrt neurons) (Aubert)],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[f_CBF_dyn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[f_CBF_dyn],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[is_stimulated]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[is_stimulated],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[stimulus]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[stimulus],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[t_end_GLY]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[t_end_GLY],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[v_stim]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Values[v_stim],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ADP{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ADP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ADP{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ADP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[AMP{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[AMP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[AMP{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[AMP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ATP{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[ATP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ATP{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[ATP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CO2{capillary}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[CO2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Cr{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Cr],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Cr{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Cr],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F6P{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[F6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F6P{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[F6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[G6P{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[G6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[G6P{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[G6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GAP{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GAP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GAP{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GAP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GLU{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLU],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GLU{extracellular_space}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[extracellular_space],Vector=Metabolites[GLU],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GLU{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[GLU],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[GLY]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[GLY],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NAD{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[NAD],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NAD{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[NAD],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Na+{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[Na+],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Na+{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[Na+],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[O2{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[O2{capillary}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[O2{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PCr{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PCr],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PCr{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PCr],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PEP{astrocytes}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[astrocytes],Vector=Metabolites[PEP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PEP{neurons}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[neurons],Vector=Metabolites[PEP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[dHb]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Brain Energy Metabolism with PPP,Vector=Compartments[capillary],Vector=Metabolites[dHb],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="model2.xml">
    <SBMLMap SBMLid="ADP_astrocytes" COPASIkey="Metabolite_43"/>
    <SBMLMap SBMLid="ADP_neurons" COPASIkey="Metabolite_16"/>
    <SBMLMap SBMLid="AK_astrocytes" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="AK_neurons" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="AMP_astrocytes" COPASIkey="Metabolite_44"/>
    <SBMLMap SBMLid="AMP_neurons" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="ATPase_astrocytes" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="ATPase_neurons" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="BOLD_signal" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="Blood_flow_contribution_inkl__volume" COPASIkey="Function_54"/>
    <SBMLMap SBMLid="Blood_flow_contribution_to_capillary_O2" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="CK_astrocytes_forward__R01881" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="CK_neurons_forward__R01881" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="CO2_artery" COPASIkey="Metabolite_59"/>
    <SBMLMap SBMLid="Cr_astrocytes" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="Cr_neurons" COPASIkey="Metabolite_18"/>
    <SBMLMap SBMLid="E0" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="E4P_astrocytes" COPASIkey="Metabolite_53"/>
    <SBMLMap SBMLid="E4P_neurons" COPASIkey="Metabolite_26"/>
    <SBMLMap SBMLid="F" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="F_0" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="F_in" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="F_out" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="Flow_of_CO2_between_capillary_and_vessel__artery_" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="G6L_astrocytes" COPASIkey="Metabolite_47"/>
    <SBMLMap SBMLid="G6L_neurons" COPASIkey="Metabolite_20"/>
    <SBMLMap SBMLid="GLU_astrocytes" COPASIkey="Metabolite_42"/>
    <SBMLMap SBMLid="GLU_extracellular_space" COPASIkey="Metabolite_56"/>
    <SBMLMap SBMLid="GLU_neurons" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="GLY" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="GND_astrocytes__R01528" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="GND_neurons___R01528" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="HK_neurons__R01786___HeinrichSchuster" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="Hb_OP" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="K_O2" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="K_O2__Aubert" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="K_T_GLC_ce__Aubert" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="K_T_GLC_cg__Aubert" COPASIkey="ModelValue_102"/>
    <SBMLMap SBMLid="K_T_GLC_eg__Aubert" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="K_T_GLC_en__Aubert" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="K_T_LAC_ec__Aubert" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="K_T_LAC_gc__Aubert" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="K_T_LAC_ge__Aubert" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="K_T_LAC_ne__Aubert" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="K_m_ATP_ATPase" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="K_m_G6P_GLYS" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="K_m_GLU" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="K_m_GLY" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="K_m_Na_pump" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="LDH_astrocytes_forward__R00703" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="LDH_neurons_forward__R00703" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="NADPH_astrocytes" COPASIkey="Metabolite_55"/>
    <SBMLMap SBMLid="NADPH_neurons" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="NADPH_oxidase_astrocytes__R07172" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="NADPH_oxidase_neurons__R07172" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="NADP_astrocytes" COPASIkey="Metabolite_54"/>
    <SBMLMap SBMLid="NADP_neurons" COPASIkey="Metabolite_28"/>
    <SBMLMap SBMLid="NAD_astrocytes" COPASIkey="Metabolite_46"/>
    <SBMLMap SBMLid="NAD_neurons" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="NULL" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="Na__astrocytes" COPASIkey="Metabolite_40"/>
    <SBMLMap SBMLid="Na__extracellular_space" COPASIkey="Metabolite_57"/>
    <SBMLMap SBMLid="Na__neurons" COPASIkey="Metabolite_14"/>
    <SBMLMap SBMLid="O2_artery" COPASIkey="Metabolite_58"/>
    <SBMLMap SBMLid="O2_exchange_capillary_astrocytes" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="O2_exchange_capillary_neurons" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="O2_transport_function_inkl__volume" COPASIkey="Function_55"/>
    <SBMLMap SBMLid="P6G_astrocytes" COPASIkey="Metabolite_48"/>
    <SBMLMap SBMLid="P6G_neurons" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="PGI_astrocytes__R02740___HS" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="PGI_neurons__R02740___HS" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="PS_cap_astrocytes__wrt_capillaries" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="PS_cap_astrocytes__wrt_capillaries___Aubert" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="PS_cap_neuron__wrt_capillaries" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="PS_cap_neuron__wrt_capillaries___Aubert" COPASIkey="ModelValue_113"/>
    <SBMLMap SBMLid="R5P_astrocytes" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="R5P_neurons" COPASIkey="Metabolite_24"/>
    <SBMLMap SBMLid="R5P_sink_astrocytes__n_a_" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="R5P_sink_neurons__n_a_" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="RKI_astrocytes__R01056" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="RKI_neurons__R01056" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="RPE_astrocytes__R01529" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="RPE_neurons__R01529" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="RT" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="R_Na_GLU" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="Ru5P_astrocytes" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="Ru5P_neurons" COPASIkey="Metabolite_22"/>
    <SBMLMap SBMLid="S7P_astrocytes" COPASIkey="Metabolite_52"/>
    <SBMLMap SBMLid="S7P_neurons" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="SOL_astrocytes__R02035" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="SOL_neurons__R02035" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="Sm_g" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="Sm_n" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="TAL_astrocytes__R01827" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="TAL_neurons__R01827" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="TKL_1_astrocytes__R01641" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="TKL_1_neurons__R01641" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="TKL_2_astrocytes__R01830" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="TKL_2_neurons__R01830" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="V_eg_max_GLU" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="V_gn_max_GLU" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="Vm" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="Vmax_GLYS" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="Vmax_ce_GLC__Aubert" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="Vmax_ce_GLC__wrt_capillaries" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="Vmax_ce_GLC__wrt_capillaries___Aubert" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="Vmax_cg_GLC___Aubert" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="Vmax_cg_GLC__wrt_capillaries" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="Vmax_cg_GLC__wrt_capillaries___Aubert" COPASIkey="ModelValue_103"/>
    <SBMLMap SBMLid="Vmax_ec_LAC__wrt_extracellular_space___Aubert" COPASIkey="ModelValue_104"/>
    <SBMLMap SBMLid="Vmax_eg_GLC__Aubert_" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="Vmax_eg_GLC__wrt_astrocytes___Aubert_" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="Vmax_eg_GLU__wrt_extracellular_space" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="Vmax_en_GLC___Aubert" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="Vmax_en_GLC__wrt_neurons___Aubert" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="Vmax_f_PGI__Cloutier" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="Vmax_gc_LAC__wrt_astrocytes___Aubert" COPASIkey="ModelValue_105"/>
    <SBMLMap SBMLid="Vmax_ge_LAC__wrt_astrocytes___Aubert" COPASIkey="ModelValue_106"/>
    <SBMLMap SBMLid="Vmax_ne_LAC__wrt_extracellular_space" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="Vmax_ne_LAC__wrt_neurons___Aubert" COPASIkey="ModelValue_107"/>
    <SBMLMap SBMLid="Vmax_r_PGI__Cloutier" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="X5P_astrocytes" COPASIkey="Metabolite_50"/>
    <SBMLMap SBMLid="X5P_neurons" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="ZWF_astrocytes__R02736" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="ZWF_neurons__R02736" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="artery" COPASIkey="Compartment_5"/>
    <SBMLMap SBMLid="compartment_1" COPASIkey="Compartment_0"/>
    <SBMLMap SBMLid="compartment_2" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="compartment_3" COPASIkey="Compartment_2"/>
    <SBMLMap SBMLid="compartment_4" COPASIkey="Compartment_3"/>
    <SBMLMap SBMLid="dHb" COPASIkey="Metabolite_2"/>
    <SBMLMap SBMLid="delta_F" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="delta_GLY" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="delta_HK" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="f_CBF" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="f_CBF_dyn" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="g_Na_astrocytes" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="g_Na_neurons" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="inflow_of_dHb" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="is_stimulated" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="k_CK_backward_astrocytes" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="k_CK_backward_neurons" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="k_CK_forward_astrocytes" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="k_CK_forward_neurons" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="k_LDH_forward_astrocytes" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="k_LDH_forward_neurons" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="k_LDH_reverse_astrocytes" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="k_LDH_reverse_neurons" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="k_PFK_astrocytes" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="k_PFK_neurons" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="k_PK_astrocytes" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="k_PK_neurons" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="k_pump" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="modular_rate_law_for_one_substrate__one_product" COPASIkey="Function_53"/>
    <SBMLMap SBMLid="modular_rate_law_for_two_substrates__two_products" COPASIkey="Function_52"/>
    <SBMLMap SBMLid="nh_O2" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="nh_O2__Aubert" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="outflow_of_dHb" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="parameter_1" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="parameter_10" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="parameter_11" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="parameter_12" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="parameter_14" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="parameter_16" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="parameter_17" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="parameter_18" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="parameter_19" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="parameter_2" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="parameter_20" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="parameter_21" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="parameter_25" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="parameter_26" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="parameter_3" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="parameter_32" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="parameter_33" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="parameter_36" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="parameter_37" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="parameter_38" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="parameter_39" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="parameter_4" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="parameter_40" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="parameter_41" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="parameter_42" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="parameter_43" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="parameter_44" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="parameter_45" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="parameter_46" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="parameter_47" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="parameter_5" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="parameter_6" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="parameter_7" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="parameter_8" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="parameter_9" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="reaction_10" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="reaction_13" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="reaction_14" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="reaction_2" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="reaction_5" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="reaction_6" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="reaction_7" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="reaction_8" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="reaction_9" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="species_1" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="species_10" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="species_11" COPASIkey="Metabolite_8"/>
    <SBMLMap SBMLid="species_12" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="species_13" COPASIkey="Metabolite_34"/>
    <SBMLMap SBMLid="species_14" COPASIkey="Metabolite_35"/>
    <SBMLMap SBMLid="species_15" COPASIkey="Metabolite_10"/>
    <SBMLMap SBMLid="species_16" COPASIkey="Metabolite_12"/>
    <SBMLMap SBMLid="species_17" COPASIkey="Metabolite_36"/>
    <SBMLMap SBMLid="species_18" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="species_19" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="species_2" COPASIkey="Metabolite_4"/>
    <SBMLMap SBMLid="species_20" COPASIkey="Metabolite_38"/>
    <SBMLMap SBMLid="species_21" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="species_22" COPASIkey="Metabolite_39"/>
    <SBMLMap SBMLid="species_23" COPASIkey="Metabolite_0"/>
    <SBMLMap SBMLid="species_24" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="species_3" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="species_4" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="species_5" COPASIkey="Metabolite_30"/>
    <SBMLMap SBMLid="species_6" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="species_7" COPASIkey="Metabolite_6"/>
    <SBMLMap SBMLid="species_8" COPASIkey="Metabolite_32"/>
    <SBMLMap SBMLid="species_9" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="stimulus" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="stimulus_tail_pinch" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="t_0" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="t_0_GLY" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="t_1" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="t_end" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="t_end_GLY" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="t_stim_tp" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="tau_v" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="vATPase" COPASIkey="Function_43"/>
    <SBMLMap SBMLid="vGLU_eg" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="vGLU_eg__inkl__Volumes" COPASIkey="Function_48"/>
    <SBMLMap SBMLid="vGLU_gn" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="vGLU_gn__inkl__Volume" COPASIkey="Function_49"/>
    <SBMLMap SBMLid="vGLU_ne" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="vGLU_ne__inkl__Volume" COPASIkey="Function_50"/>
    <SBMLMap SBMLid="vGLYP" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="vGLYS" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="vGLYS_0" COPASIkey="Function_40"/>
    <SBMLMap SBMLid="vGlyp_SS" COPASIkey="Function_58"/>
    <SBMLMap SBMLid="vHK__HS" COPASIkey="Function_59"/>
    <SBMLMap SBMLid="vLEAK_Na_astrocytes" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="vLEAK_Na_inkl__Volume" COPASIkey="Function_56"/>
    <SBMLMap SBMLid="vLEAK_Na_neurons" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="vMITO__inkl__Volumes" COPASIkey="Function_47"/>
    <SBMLMap SBMLid="vPFK" COPASIkey="Function_46"/>
    <SBMLMap SBMLid="vPGK" COPASIkey="Function_45"/>
    <SBMLMap SBMLid="vPK" COPASIkey="Function_44"/>
    <SBMLMap SBMLid="vPUMP_astrocytes" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="vPUMP_neurons" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="vPUMP_volume_dependent" COPASIkey="Function_57"/>
    <SBMLMap SBMLid="vSTIM" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="vStim__with_volume" COPASIkey="Function_51"/>
    <SBMLMap SBMLid="v_max_f_PGI" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="v_max_r_PGI" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="v_stim" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="vdHb_in" COPASIkey="Function_41"/>
    <SBMLMap SBMLid="vdHb_out" COPASIkey="Function_42"/>
    <SBMLMap SBMLid="venous_balloon" COPASIkey="Compartment_4"/>
    <SBMLMap SBMLid="vmax_GLYP" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="vn_1_tp" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="vn_2_tp" COPASIkey="ModelValue_64"/>
  </SBMLReference>
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
  </ListOfUnitDefinitions>
</COPASI>
