<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.29 (Build 228) (http://www.copasi.org) at 2021-01-04T13:53:39Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="29" versionDevel="228" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_40" name="Function for Glucose transport" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv0/KMoutv0*(Glcout-Glcin/Keqv0)/(1+Glcout/KMoutv0+Glcin/KMinv0+alfav0*Glcout*Glcin/KMoutv0/KMinv0)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="Glcin" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_263" name="Glcout" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_262" name="KMinv0" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="KMoutv0" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_250" name="Keqv0" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_265" name="Vmaxv0" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="alfav0" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="Function for Hexokinase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Inhibv1*Glcin/(Glcin+KMGlcv1)*(Vmax1v1/KMgATPv1)*(MgATP+Vmax2v1/Vmax1v1*MgATP*Mgf/KMgATPMgv1-Glc6P*MgADP/Keqv1)/(1+MgATP/KMgATPv1*(1+Mgf/KMgATPMgv1)+Mgf/KMgv1+(1.55+Glc6P/KGlc6Pv1)*(1+Mgf/KMgv1)+(Gri23P2f+MgGri23P2)/K23P2Gv1+Mgf*(Gri23P2f+MgGri23P2)/(KMgv1*KMg23P2Gv1))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_273" name="Glc6P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_272" name="Glcin" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_271" name="Gri23P2f" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_270" name="Inhibv1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_269" name="K23P2Gv1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_268" name="KGlc6Pv1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="KMGlcv1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_274" name="KMg23P2Gv1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_275" name="KMgATPMgv1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_276" name="KMgATPv1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="KMgv1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_278" name="Keqv1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_279" name="MgADP" order="12" role="product"/>
        <ParameterDescription key="FunctionParameter_280" name="MgATP" order="13" role="substrate"/>
        <ParameterDescription key="FunctionParameter_281" name="MgGri23P2" order="14" role="modifier"/>
        <ParameterDescription key="FunctionParameter_282" name="Mgf" order="15" role="modifier"/>
        <ParameterDescription key="FunctionParameter_283" name="Vmax1v1" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="Vmax2v1" order="17" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="Function for Glucosephosphate isomerase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv2*(Glc6P-Fru6P/Keqv2)/(Glc6P+KGlc6Pv2*(1+Fru6P/KFru6Pv2))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_302" name="Fru6P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_301" name="Glc6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_300" name="KFru6Pv2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_299" name="KGlc6Pv2" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_298" name="Keqv2" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_297" name="Vmaxv2" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="Function for Phosphofructokinase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv3*(Fru6P*MgATP-Fru16P2*MgADP/Keqv3)/((Fru6P+KFru6Pv3)*(MgATP+KMgATPv3)*(1+L0v3*((1+ATPf/KATPv3)*(1+Mgf/KMgv3)/((1+(AMPf+MgAMP)/KAMPv3)*(1+Fru6P/KFru6Pv3)))^4))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_291" name="AMPf" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_292" name="ATPf" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_293" name="Fru16P2" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_294" name="Fru6P" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_295" name="KAMPv3" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_296" name="KATPv3" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_290" name="KFru6Pv3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_289" name="KMgATPv3" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_288" name="KMgv3" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_287" name="Keqv3" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_286" name="L0v3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_285" name="MgADP" order="11" role="product"/>
        <ParameterDescription key="FunctionParameter_303" name="MgAMP" order="12" role="modifier"/>
        <ParameterDescription key="FunctionParameter_304" name="MgATP" order="13" role="substrate"/>
        <ParameterDescription key="FunctionParameter_305" name="Mgf" order="14" role="modifier"/>
        <ParameterDescription key="FunctionParameter_306" name="Vmaxv3" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="Function for Aldolase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv4/KFru16P2v4*(Fru16P2-GraP*DHAP/Keqv4)/(1+Fru16P2/KFru16P2v4+GraP/KiGraPv4+DHAP*(GraP+KGraPv4)/(KDHAPv4*KiGraPv4)+Fru16P2*GraP/(KFru16P2v4*KiiGraPv4))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_322" name="DHAP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_321" name="Fru16P2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_320" name="GraP" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_319" name="KDHAPv4" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_318" name="KFru16P2v4" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_317" name="KGraPv4" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_316" name="Keqv4" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_315" name="KiGraPv4" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_314" name="KiiGraPv4" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_313" name="Vmaxv4" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="Function for Triosephosphate isomerase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv5*(DHAP-GraP/Keqv5)/(DHAP+KDHAPv5*(1+GraP/KGraPv5))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_326" name="DHAP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_325" name="GraP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_324" name="KDHAPv5" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_323" name="KGraPv5" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_307" name="Keqv5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_308" name="Vmaxv5" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="Function for Glyceraldehyde 3-phosphate dehydrogenase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv6/(KNADv6*KGraPv6*KPv6)*(NAD*GraP*Phi-Gri13P2*NADH/Keqv6)/((1+NAD/KNADv6)*(1+GraP/KGraPv6)*(1+Phi/KPv6)+(1+NADH/KNADHv6)*(1+Gri13P2/K13P2Gv6)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_328" name="GraP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_327" name="Gri13P2" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_312" name="K13P2Gv6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_311" name="KGraPv6" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_310" name="KNADHv6" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_309" name="KNADv6" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_329" name="KPv6" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_330" name="Keqv6" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_331" name="NAD" order="8" role="substrate"/>
        <ParameterDescription key="FunctionParameter_332" name="NADH" order="9" role="product"/>
        <ParameterDescription key="FunctionParameter_333" name="Phi" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_334" name="Vmaxv6" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="Function for Phosphoglycerate kinase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv7/(KMgADPv7*K13P2Gv7)*(MgADP*Gri13P2-MgATP*Gri3P/Keqv7)/((1+MgADP/KMgADPv7)*(1+Gri13P2/K13P2Gv7)+(1+MgATP/KMgATPv7)*(1+Gri3P/K3PGv7)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_346" name="Gri13P2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_345" name="Gri3P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_344" name="K13P2Gv7" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_343" name="K3PGv7" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_342" name="KMgADPv7" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_341" name="KMgATPv7" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_340" name="Keqv7" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_339" name="MgADP" order="7" role="substrate"/>
        <ParameterDescription key="FunctionParameter_338" name="MgATP" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_337" name="Vmaxv7" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="Function for Bisphosphoglycerate mutase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kDPGMv8*(Gri13P2-(Gri23P2f+MgGri23P2)/Keqv8)/(1+(Gri23P2f+MgGri23P2)/K23P2Gv8)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_354" name="Gri13P2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_353" name="Gri23P2f" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_352" name="K23P2Gv8" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_351" name="Keqv8" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_350" name="MgGri23P2" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_349" name="kDPGMv8" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="Function for Bisphosphoglycerate phosphatase" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv9*(Gri23P2f+MgGri23P2-Gri3P/Keqv9)/(Gri23P2f+MgGri23P2+K23P2Gv9)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_356" name="Gri23P2f" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_355" name="Gri3P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_336" name="K23P2Gv9" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_335" name="Keqv9" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_347" name="MgGri23P2" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_348" name="Vmaxv9" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="Function for Phosphoglycerate mutase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv10*(Gri3P-Gri2P/Keqv10)/(Gri3P+K3PGv10*(1+Gri2P/K2PGv10))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_362" name="Gri2P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_361" name="Gri3P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_360" name="K2PGv10" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_359" name="K3PGv10" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_358" name="Keqv10" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_357" name="Vmaxv10" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="Function for Enolase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv11*(Gri2P-PEP/Keqv11)/(Gri2P+K2PGv11*(1+PEP/KPEPv11))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_368" name="Gri2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_367" name="K2PGv11" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_366" name="KPEPv11" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_365" name="Keqv11" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_364" name="PEP" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_363" name="Vmaxv11" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="Function for Pyruvate kinase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_52">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv12*(PEP*MgADP-Pyr*MgATP/Keqv12)/((PEP+KPEPv12)*(MgADP+KMgADPv12)*(1+L0v12*(1+(ATPf+MgATP)/KATPv12)^4/((1+PEP/KPEPv12)^4*(1+Fru16P2/KFru16P2v12)^4)))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_374" name="ATPf" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_373" name="Fru16P2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_372" name="KATPv12" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="KFru16P2v12" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_370" name="KMgADPv12" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_369" name="KPEPv12" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_375" name="Keqv12" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_376" name="L0v12" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_377" name="MgADP" order="8" role="substrate"/>
        <ParameterDescription key="FunctionParameter_378" name="MgATP" order="9" role="product"/>
        <ParameterDescription key="FunctionParameter_379" name="PEP" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_380" name="Pyr" order="11" role="product"/>
        <ParameterDescription key="FunctionParameter_381" name="Vmaxv12" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="Function for Lactate dehydrogenase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv13*(Pyr*NADH-Lac*NAD/Keqv13)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_394" name="Keqv13" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_393" name="Lac" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_392" name="NAD" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_391" name="NADH" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_390" name="Pyr" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_389" name="Vmaxv13" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="Function for Lactate dehydrogenase_2" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kLDHv14*(Pyr*NADPHf-Lac*NADPf/Keqv14)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_383" name="Keqv14" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_384" name="Lac" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_385" name="NADPHf" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_386" name="NADPf" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_387" name="Pyr" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_388" name="kLDHv14" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="Function for ATPase" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kATPasev15*MgATP
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_399" name="MgATP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_398" name="kATPasev15" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="Function for Adenylate kinase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_56">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv16/(KATPv16*KAMPv16)*(MgATP*AMPf-MgADP*ADPf/Keqv16)/((1+MgATP/KATPv16)*(1+AMPf/KAMPv16)+(MgADP+ADPf)/KADPv16+MgADP*ADPf/KADPv16^2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_396" name="ADPf" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_397" name="AMPf" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_395" name="KADPv16" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_382" name="KAMPv16" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_400" name="KATPv16" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_401" name="Keqv16" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_402" name="MgADP" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_403" name="MgATP" order="7" role="substrate"/>
        <ParameterDescription key="FunctionParameter_404" name="Vmaxv16" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="Function for Glucose 6-phosphate dehydrogenase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_57">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv17/KG6Pv17/KNADPv17*(Glc6P*NADPf-GlcA6P*NADPHf/Keqv17)/(1+NADPf*(1+Glc6P/KG6Pv17)/KNADPv17+(ATPf+MgATP)/KATPv17+NADPHf/KNADPHv17+(Gri23P2f+MgGri23P2)/KPGA23v17)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_413" name="ATPf" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_412" name="Glc6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_411" name="GlcA6P" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_410" name="Gri23P2f" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_409" name="KATPv17" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_408" name="KG6Pv17" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_407" name="KNADPHv17" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_406" name="KNADPv17" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_405" name="KPGA23v17" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_414" name="Keqv17" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_415" name="MgATP" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_416" name="MgGri23P2" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_417" name="NADPHf" order="12" role="product"/>
        <ParameterDescription key="FunctionParameter_418" name="NADPf" order="13" role="substrate"/>
        <ParameterDescription key="FunctionParameter_419" name="Vmaxv17" order="14" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="Function for Phosphogluconate dehydrogenase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_58">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv18/K6PG1v18/KNADPv18*(GlcA6P*NADPf-Rul5P*NADPHf/Keqv18)/((1+NADPf/KNADPv18)*(1+GlcA6P/K6PG1v18+(Gri23P2f+MgGri23P2)/KPGA23v18)+(ATPf+MgATP)/KATPv18+NADPHf*(1+GlcA6P/K6PG2v18)/KNADPHv18)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_434" name="ATPf" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_433" name="GlcA6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_432" name="Gri23P2f" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_431" name="K6PG1v18" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_430" name="K6PG2v18" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_429" name="KATPv18" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_428" name="KNADPHv18" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_427" name="KNADPv18" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_426" name="KPGA23v18" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_425" name="Keqv18" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_424" name="MgATP" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_423" name="MgGri23P2" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_422" name="NADPHf" order="12" role="product"/>
        <ParameterDescription key="FunctionParameter_421" name="NADPf" order="13" role="substrate"/>
        <ParameterDescription key="FunctionParameter_420" name="Rul5P" order="14" role="product"/>
        <ParameterDescription key="FunctionParameter_435" name="Vmaxv18" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="Function for Glutathione reductase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_59">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv19*(GSSG*NADPHf/(KGSSGv19*KNADPHv19)-GSH^2/KGSHv19^2*NADPf/(KNADPv19*Keqv19))/(1+NADPHf*(1+GSSG/KGSSGv19)/KNADPHv19+NADPf/KNADPv19*(1+GSH*(1+GSH/KGSHv19)/KGSHv19))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_451" name="GSH" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_450" name="GSSG" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_449" name="KGSHv19" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_448" name="KGSSGv19" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_447" name="KNADPHv19" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_446" name="KNADPv19" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_445" name="Keqv19" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_444" name="NADPHf" order="7" role="substrate"/>
        <ParameterDescription key="FunctionParameter_443" name="NADPf" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_442" name="Vmaxv19" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="Function for Glutathione oxidation" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_60">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Kv20*GSH
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_455" name="GSH" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_454" name="Kv20" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_61" name="Function for Phosphoribulose epimerase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_61">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv21*(Rul5P-Xul5P/Keqv21)/(Rul5P+KRu5Pv21*(1+Xul5P/KX5Pv21))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_452" name="KRu5Pv21" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_453" name="KX5Pv21" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_436" name="Keqv21" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_437" name="Rul5P" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_438" name="Vmaxv21" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_439" name="Xul5P" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_62" name="Function for Ribose phosphate isomerase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv22*(Rul5P-Rib5P/Keqv22)/(Rul5P+KRu5Pv22*(1+Rib5P/KR5Pv22))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_459" name="KR5Pv22" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_458" name="KRu5Pv22" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_457" name="Keqv22" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_456" name="Rib5P" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_441" name="Rul5P" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_440" name="Vmaxv22" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_63" name="Function for Transketolase 1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv23*(Rib5P*Xul5P-GraP*Sed7P/Keqv23)/((K1v23+Rib5P)*Xul5P+(K2v23+K6v23*Sed7P)*Rib5P+(K3v23+K5v23*Sed7P)*GraP+K4v23*Sed7P+K7v23*Xul5P*GraP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_465" name="GraP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_464" name="K1v23" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_463" name="K2v23" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_462" name="K3v23" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_461" name="K4v23" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_460" name="K5v23" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_466" name="K6v23" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_467" name="K7v23" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_468" name="Keqv23" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_469" name="Rib5P" order="9" role="substrate"/>
        <ParameterDescription key="FunctionParameter_470" name="Sed7P" order="10" role="product"/>
        <ParameterDescription key="FunctionParameter_471" name="Vmaxv23" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_472" name="Xul5P" order="12" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_64" name="Function for Transaldolase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv24*(Sed7P*GraP-E4P*Fru6P/Keqv24)/((K1v24+GraP)*Sed7P+(K2v24+K6v24*Fru6P)*GraP+(K3v24+K5v24*Fru6P)*E4P+K4v24*Fru6P+K7v24*Sed7P*E4P)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_485" name="E4P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_484" name="Fru6P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_483" name="GraP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_482" name="K1v24" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_481" name="K2v24" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_480" name="K3v24" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_479" name="K4v24" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_478" name="K5v24" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_477" name="K6v24" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_476" name="K7v24" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_475" name="Keqv24" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_474" name="Sed7P" order="11" role="substrate"/>
        <ParameterDescription key="FunctionParameter_473" name="Vmaxv24" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_65" name="Function for Phosphoribosylpyrophosphate synthetase" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv25*(Rib5P*MgATP-PRPP*MgAMP/Keqv25)/((KATPv25+MgATP)*(KR5Pv25+Rib5P))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_498" name="KATPv25" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_497" name="KR5Pv25" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_496" name="Keqv25" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_495" name="MgAMP" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_494" name="MgATP" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_493" name="PRPP" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_492" name="Rib5P" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_491" name="Vmaxv25" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_66" name="Function for Transketolase 2" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv26*(E4P*Xul5P-GraP*Fru6P/Keqv26)/((K1v26+E4P)*Xul5P+(K2v26+K6v26*Fru6P)*E4P+(K3v26+K5v26*Fru6P)*GraP+K4v26*Fru6P+K7v26*Xul5P*GraP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_501" name="E4P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_500" name="Fru6P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_499" name="GraP" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_486" name="K1v26" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_487" name="K2v26" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_488" name="K3v26" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_489" name="K4v26" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_490" name="K5v26" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_502" name="K6v26" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_503" name="K7v26" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_504" name="Keqv26" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_505" name="Vmaxv26" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_506" name="Xul5P" order="12" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_67" name="Function for Phosphate exchange" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv27*(Phiex-Phi/Keqv27)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_519" name="Keqv27" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_518" name="Phi" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_517" name="Phiex" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_516" name="Vmaxv27" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_68" name="Function for Lactate exchange" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_68">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv28*(Lacex-Lac/Keqv28)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_512" name="Keqv28" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_513" name="Lac" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_514" name="Lacex" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_515" name="Vmaxv28" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_69" name="Function for Pyruvate exchange" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_69">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmaxv29*(Pyrex-Pyr/Keqv29)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_508" name="Keqv29" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_509" name="Pyr" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_510" name="Pyrex" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_511" name="Vmaxv29" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_70" name="Function for MgATP dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_70">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(MgATP-Mgf*ATPf/KdATP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_522" name="ATPf" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_521" name="EqMult" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_520" name="KdATP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_507" name="MgATP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_523" name="Mgf" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="Function for MgADP dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(MgADP-Mgf*ADPf/KdADP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_528" name="ADPf" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_527" name="EqMult" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_526" name="KdADP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_525" name="MgADP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_524" name="Mgf" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="Function for MgAMP dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_72">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(MgAMP-Mgf*AMPf/KdAMP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_533" name="AMPf" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_532" name="EqMult" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_531" name="KdAMP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_530" name="MgAMP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_529" name="Mgf" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="Function for MgGri23P2 dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(MgGri23P2-Mgf*Gri23P2f/Kd23P2G)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_538" name="EqMult" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_537" name="Gri23P2f" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_536" name="Kd23P2G" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_535" name="MgGri23P2" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_534" name="Mgf" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="Function for P1NADP dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(P1NADP-P1f*NADPf/Kd1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_543" name="EqMult" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_542" name="Kd1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_541" name="NADPf" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_540" name="P1NADP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_539" name="P1f" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="Function for P1NADPH dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(P1NADPH-P1f*NADPHf/Kd3)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_548" name="EqMult" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_547" name="Kd3" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_546" name="NADPHf" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_545" name="P1NADPH" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_544" name="P1f" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="Function for P2NADP dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(P2NADP-P2f*NADPf/Kd2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_553" name="EqMult" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_552" name="Kd2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_551" name="NADPf" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_550" name="P2NADP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_549" name="P2f" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="Function for P2NADPH dissociation" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        EqMult*(P2NADPH-P2f*NADPHf/Kd4)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_558" name="EqMult" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_557" name="Kd4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_556" name="NADPHf" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_555" name="P2NADPH" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_554" name="P2f" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Holzhutter2004_Erythrocyte_Metabolism" simulationType="time" timeUnit="h" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221408570000002e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_1">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:15233787"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2006-09-07T15:04:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>jls@sun.ac.za</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Snoep</vCard:Family>
                <vCard:Given>Jacky L</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>Stellenbosh University</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
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
        <dcterms:W3CDTF>2010-02-02T17:20:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006096"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006098"/>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006749"/>
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:hsa00010"/>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:hsa00030"/>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:hsa00480"/>
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1383"/>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1859"/>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2220"/>
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:BIOMD0000000070"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:MODEL6624180840"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:taxonomy:9606"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
    <p align="right">
      <font color="#FFFFFF">.</font>
    </p>
    <p align="right">
      <font color="#FFFFFF">.</font>
    </p>
    <p align="right">
      <font color="#FFFFFF">.</font>
    </p>
    <p align="left">
      <font face="Arial, Helvetica, sans-serif">
        <b>
          <a href="http://www.sbml.org/">SBML</a> level 2 code generated for the JWS Online project by Jacky Snoep using <a href="http://pysces.sourceforge.net/">PySCeS</a>
          <br />
Run this model online at <a href="http://jjj.biochem.sun.ac.za/">http://jjj.biochem.sun.ac.za</a>
          <br />
To cite JWS Online please refer to: Olivier, B.G. and Snoep, J.L. (2004) <a href="http://bioinformatics.oupjournals.org/cgi/content/abstract/20/13/2143">Web-based 
modelling using JWS Online</a>, Bioinformatics, 20:2143-2144
 </b>
        </font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p align="right">
        <font color="#FFFFFF">.</font>
      </p>
      <p>
        <u>Biomodels Curation</u>
The model simulates the flux values as given for "kinetic model" in Table 1 of the paper. The model was successfully tested on Jarnac.
</p>
        <p>This model originates from BioModels Database: A Database of Annotated Published Models (http://www.ebi.ac.uk/biomodels/). It is copyright (c) 2005-2011 The BioModels.net Team.<br />
For more information see the <a href="http://www.ebi.ac.uk/biomodels/legal.html" target="_blank">terms of use</a>.<br />
To cite BioModels Database, please use: <a href="http://www.ncbi.nlm.nih.gov/pubmed/20587024" target="_blank">Li C, Donizelli M, Rodriguez N, Dharuri H, Endler L, Chelliah V, Li L, He E, Henry A, Stefan MI, Snoep JL, Hucka M, Le Novère N, Laibe C (2010) BioModels Database: An enhanced, curated and annotated resource for published quantitative kinetic models. BMC Syst Biol., 4:92.</a></p>
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cytoplasm" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005737" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="Glucose in" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_0">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00293" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17234" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="MgATP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A15422" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A25107" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00002" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00305" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="Glucose 6-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00668" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17665" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="MgADP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16761" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A25107" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00008" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00305" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="Fructose 6-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C05345" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16084" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="Fructose 1,6-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C05378" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A28013" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="Glyceraldehyde 3-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00118" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A29052" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="Dihydroxyacetone phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00111" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16108" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="Phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A35780" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="NAD" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00003" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A15846" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_10" name="1,3-Bisphospho-D-glycerate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_10">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00236" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16001" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="NADH" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00004" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16908" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="3-Phospho-D-glycerate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00197" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17794" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="2,3-Bisphospho-D-glycerate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C01159" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17720" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_14" name="2-Phospho-D-glycerate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_14">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00631" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17835" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="Phosphoenolpyruvate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00074" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A18021" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="Pyruvate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_16">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A15361" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00022" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="Lactate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00256" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="NADPH" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00005" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16474" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="NADP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00006" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A18009" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="AMP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00020" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16027" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="ADP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00008" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16761" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="Phospho-D-glucono-1,5-lactone" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C01236" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16938" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="Ribulose 5-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00199" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17363" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="Oxidized Glutathione" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_24">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00127" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17858" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="Reduced Glutathione" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00051" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16856" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="Xylulose 5-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00231" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16332" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="Ribose 5-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00117" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17797" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="Sedoheptulose 7-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C05382" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="Erythrose 4-phosphate" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00279" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16897" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="MgAMP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_30">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16027" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A25107" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00020" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00305" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="ATP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00002" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A15422" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="Mg" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00305" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A25107" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="MgGri23P2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17720" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A25107" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00305" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C01159" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_34" name="Protein1 bound NADP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_34">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A18009" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00006" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_35" name="Protein1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_35">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_36" name="Protein1 bound NADPH" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16474" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00005" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="Protein2 bound NADP" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A18009" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00006" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="Protein2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="Protein2 bound NADPH" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_39">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A16474" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A36080" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00005" />
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00017" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="PRPP" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_40">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00119" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17111" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="External Lactate" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00256" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_42" name="External Pyruvate" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_42">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00022" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A32816" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="Glucose outside" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_43">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.compound:C00293" />
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A17234" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_44" name="Phosphate external" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.chebi:CHEBI%3A35780" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="Glucose transport" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2092" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0046323" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5001" name="Vmaxv0" value="33.6"/>
          <Constant key="Parameter_5000" name="KMoutv0" value="1.7"/>
          <Constant key="Parameter_4999" name="Keqv0" value="1"/>
          <Constant key="Parameter_4998" name="KMinv0" value="6.9"/>
          <Constant key="Parameter_4997" name="alfav0" value="0.54"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Parameter_4998"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Parameter_5000"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Parameter_4999"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_5001"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Parameter_4997"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Hexokinase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00299" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1318" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.1.2" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4996" name="Inhibv1" value="1"/>
          <Constant key="Parameter_4995" name="KMGlcv1" value="0.1"/>
          <Constant key="Parameter_4994" name="Vmax1v1" value="15.8"/>
          <Constant key="Parameter_4993" name="KMgATPv1" value="1.44"/>
          <Constant key="Parameter_4992" name="Vmax2v1" value="33.2"/>
          <Constant key="Parameter_4991" name="KMgATPMgv1" value="1.14"/>
          <Constant key="Parameter_4990" name="Keqv1" value="3900"/>
          <Constant key="Parameter_4989" name="KMgv1" value="1.03"/>
          <Constant key="Parameter_4988" name="KGlc6Pv1" value="0.0045"/>
          <Constant key="Parameter_4987" name="K23P2Gv1" value="2.7"/>
          <Constant key="Parameter_4986" name="KMg23P2Gv1" value="3.44"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Parameter_4996"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Parameter_4987"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Parameter_4988"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Parameter_4995"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Parameter_4986"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Parameter_4991"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Parameter_4993"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Parameter_4989"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Parameter_4990"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Parameter_4994"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Parameter_4992"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="Glucosephosphate isomerase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00771" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1164" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.3.1.9" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4985" name="Vmaxv2" value="935"/>
          <Constant key="Parameter_4984" name="Keqv2" value="0.3925"/>
          <Constant key="Parameter_4983" name="KGlc6Pv2" value="0.182"/>
          <Constant key="Parameter_4982" name="KFru6Pv2" value="0.071"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Parameter_4982"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Parameter_4983"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Parameter_4984"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Parameter_4985"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="Phosphofructokinase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00756" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_736" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.1.11" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_20" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4981" name="Vmaxv3" value="239"/>
          <Constant key="Parameter_4980" name="Keqv3" value="100000"/>
          <Constant key="Parameter_4979" name="KFru6Pv3" value="0.1"/>
          <Constant key="Parameter_4978" name="KMgATPv3" value="0.068"/>
          <Constant key="Parameter_4977" name="L0v3" value="0.001072"/>
          <Constant key="Parameter_4976" name="KATPv3" value="0.01"/>
          <Constant key="Parameter_4975" name="KMgv3" value="0.44"/>
          <Constant key="Parameter_4974" name="KAMPv3" value="0.033"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Parameter_4974"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="Parameter_4976"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Parameter_4979"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Parameter_4978"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Parameter_4975"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Parameter_4980"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="Parameter_4977"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Parameter_4981"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="Aldolase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01070" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1602" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:4.1.2.13" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4973" name="Vmaxv4" value="98.91"/>
          <Constant key="Parameter_4972" name="KFru16P2v4" value="0.0071"/>
          <Constant key="Parameter_4971" name="Keqv4" value="0.114"/>
          <Constant key="Parameter_4970" name="KiGraPv4" value="0.0572"/>
          <Constant key="Parameter_4969" name="KGraPv4" value="0.1906"/>
          <Constant key="Parameter_4968" name="KDHAPv4" value="0.0364"/>
          <Constant key="Parameter_4967" name="KiiGraPv4" value="0.176"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Parameter_4968"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Parameter_4972"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Parameter_4969"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Parameter_4971"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="Parameter_4970"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Parameter_4967"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Parameter_4973"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="Triosephosphate isomerase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01015" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_775" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.3.1.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4966" name="Vmaxv5" value="5456.6"/>
          <Constant key="Parameter_4965" name="Keqv5" value="0.0407"/>
          <Constant key="Parameter_4964" name="KDHAPv5" value="0.838"/>
          <Constant key="Parameter_4963" name="KGraPv5" value="0.428"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Parameter_4964"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="Parameter_4963"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Parameter_4965"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="Parameter_4966"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="Glyceraldehyde 3-phosphate dehydrogenase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01061" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1847" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.2.1.12" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4962" name="Vmaxv6" value="4300"/>
          <Constant key="Parameter_4961" name="KNADv6" value="0.05"/>
          <Constant key="Parameter_4960" name="KGraPv6" value="0.005"/>
          <Constant key="Parameter_4959" name="KPv6" value="3.9"/>
          <Constant key="Parameter_4958" name="Keqv6" value="0.000192"/>
          <Constant key="Parameter_4957" name="KNADHv6" value="0.0083"/>
          <Constant key="Parameter_4956" name="K13P2Gv6" value="0.0035"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Parameter_4956"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="Parameter_4960"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="Parameter_4957"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="Parameter_4961"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Parameter_4959"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Parameter_4958"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="Parameter_4962"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="Phosphoglycerate kinase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01512" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1186" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.2.3" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4955" name="Vmaxv7" value="5000"/>
          <Constant key="Parameter_4954" name="KMgADPv7" value="0.35"/>
          <Constant key="Parameter_4953" name="K13P2Gv7" value="0.002"/>
          <Constant key="Parameter_4952" name="Keqv7" value="1455"/>
          <Constant key="Parameter_4951" name="KMgATPv7" value="0.48"/>
          <Constant key="Parameter_4950" name="K3PGv7" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="Parameter_4953"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="Parameter_4950"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="Parameter_4954"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="Parameter_4951"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Parameter_4952"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Parameter_4955"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="Bisphosphoglycerate mutase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01662" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.4.2.4" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4949" name="kDPGMv8" value="76000"/>
          <Constant key="Parameter_4948" name="Keqv8" value="100000"/>
          <Constant key="Parameter_4947" name="K23P2Gv8" value="0.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_48" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Parameter_4947"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="Parameter_4948"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="Parameter_4949"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="Bisphosphoglycerate phosphatase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01516" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.13" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4946" name="Vmaxv9" value="0.53"/>
          <Constant key="Parameter_4945" name="Keqv9" value="100000"/>
          <Constant key="Parameter_4944" name="K23P2Gv9" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="Parameter_4944"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="Parameter_4945"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="Parameter_4946"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="Phosphoglycerate mutase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01518" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_576" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.4.2.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
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
          <Constant key="Parameter_4943" name="Vmaxv10" value="2000"/>
          <Constant key="Parameter_4942" name="Keqv10" value="0.145"/>
          <Constant key="Parameter_4941" name="K3PGv10" value="5"/>
          <Constant key="Parameter_4940" name="K2PGv10" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_50" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="Parameter_4940"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="Parameter_4941"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Parameter_4942"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="Parameter_4943"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="Enolase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00658" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1400" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:4.2.1.11" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4939" name="Vmaxv11" value="1500"/>
          <Constant key="Parameter_4938" name="Keqv11" value="1.7"/>
          <Constant key="Parameter_4937" name="K2PGv11" value="1"/>
          <Constant key="Parameter_4936" name="KPEPv11" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="Parameter_4937"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="Parameter_4936"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Parameter_4938"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Parameter_4939"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="Pyruvate kinase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00200" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1911" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.1.40" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4935" name="Vmaxv12" value="570"/>
          <Constant key="Parameter_4934" name="Keqv12" value="13790"/>
          <Constant key="Parameter_4933" name="KPEPv12" value="0.225"/>
          <Constant key="Parameter_4932" name="KMgADPv12" value="0.474"/>
          <Constant key="Parameter_4931" name="L0v12" value="19"/>
          <Constant key="Parameter_4930" name="KATPv12" value="3.39"/>
          <Constant key="Parameter_4929" name="KFru16P2v12" value="0.005"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="Parameter_4930"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="Parameter_4929"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="Parameter_4932"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Parameter_4933"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Parameter_4934"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="Parameter_4931"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="Parameter_4935"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="Lactate dehydrogenase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00703" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_178" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.1.1.27" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4928" name="Vmaxv13" value="2.8e+06"/>
          <Constant key="Parameter_4927" name="Keqv13" value="9090"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_394">
              <SourceParameter reference="Parameter_4927"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_393">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_392">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_391">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_390">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_389">
              <SourceParameter reference="Parameter_4928"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="Lactate dehydrogenase_2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.1.1.27" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4926" name="kLDHv14" value="243.4"/>
          <Constant key="Parameter_4925" name="Keqv14" value="14181.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="Parameter_4925"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="Parameter_4926"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="ATPase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00086" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.6.1.3" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4924" name="kATPasev15" value="1.68"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_399">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_398">
              <SourceParameter reference="Parameter_4924"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="Adenylate kinase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00127" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.4.3" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4923" name="Vmaxv16" value="1380"/>
          <Constant key="Parameter_4922" name="KATPv16" value="0.09"/>
          <Constant key="Parameter_4921" name="KAMPv16" value="0.08"/>
          <Constant key="Parameter_4920" name="Keqv16" value="0.25"/>
          <Constant key="Parameter_4919" name="KADPv16" value="0.11"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_396">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_397">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_395">
              <SourceParameter reference="Parameter_4919"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="Parameter_4921"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_400">
              <SourceParameter reference="Parameter_4922"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_401">
              <SourceParameter reference="Parameter_4920"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_402">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_403">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_404">
              <SourceParameter reference="Parameter_4923"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="Glucose 6-phosphate dehydrogenase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1125" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1868" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00835" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.1.1.49" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4918" name="Vmaxv17" value="162"/>
          <Constant key="Parameter_4917" name="KG6Pv17" value="0.0667"/>
          <Constant key="Parameter_4916" name="KNADPv17" value="0.00367"/>
          <Constant key="Parameter_4915" name="Keqv17" value="2000"/>
          <Constant key="Parameter_4914" name="KATPv17" value="0.749"/>
          <Constant key="Parameter_4913" name="KNADPHv17" value="0.00312"/>
          <Constant key="Parameter_4912" name="KPGA23v17" value="2.289"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_413">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_412">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_411">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_410">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_409">
              <SourceParameter reference="Parameter_4914"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_408">
              <SourceParameter reference="Parameter_4917"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_407">
              <SourceParameter reference="Parameter_4913"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_406">
              <SourceParameter reference="Parameter_4916"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_405">
              <SourceParameter reference="Parameter_4912"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_414">
              <SourceParameter reference="Parameter_4915"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_415">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_416">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_417">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_418">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="Parameter_4918"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="Phosphogluconate dehydrogenase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01528" />
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R02035" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2072" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_611" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.1.1.44" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4911" name="Vmaxv18" value="1575"/>
          <Constant key="Parameter_4910" name="K6PG1v18" value="0.01"/>
          <Constant key="Parameter_4909" name="KNADPv18" value="0.018"/>
          <Constant key="Parameter_4908" name="Keqv18" value="141.7"/>
          <Constant key="Parameter_4907" name="KPGA23v18" value="0.12"/>
          <Constant key="Parameter_4906" name="KATPv18" value="0.154"/>
          <Constant key="Parameter_4905" name="K6PG2v18" value="0.058"/>
          <Constant key="Parameter_4904" name="KNADPHv18" value="0.0045"/>
        </ListOfConstants>
        <KineticLaw function="Function_58" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="Parameter_4910"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="Parameter_4905"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="Parameter_4906"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="Parameter_4904"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="Parameter_4909"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="Parameter_4907"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="Parameter_4908"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="Parameter_4911"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="Glutathione reductase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R00094" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2220" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.8.1.7" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="2"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4903" name="Vmaxv19" value="90"/>
          <Constant key="Parameter_4902" name="KGSSGv19" value="0.0652"/>
          <Constant key="Parameter_4901" name="KNADPHv19" value="0.00852"/>
          <Constant key="Parameter_4900" name="KGSHv19" value="20"/>
          <Constant key="Parameter_4899" name="KNADPv19" value="0.07"/>
          <Constant key="Parameter_4898" name="Keqv19" value="1.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_59" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="Parameter_4900"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="Parameter_4902"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Parameter_4901"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Parameter_4899"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="Parameter_4898"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Parameter_4903"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="Glutathione oxidation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2037" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:1.8.1.7" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4897" name="Kv20" value="0.03"/>
        </ListOfConstants>
        <KineticLaw function="Function_60" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="Parameter_4897"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="Phosphoribulose epimerase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01529" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1522" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.1.3.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4896" name="Vmaxv21" value="4634"/>
          <Constant key="Parameter_4895" name="Keqv21" value="2.7"/>
          <Constant key="Parameter_4894" name="KRu5Pv21" value="0.19"/>
          <Constant key="Parameter_4893" name="KX5Pv21" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_61" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="Parameter_4894"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Parameter_4893"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="Parameter_4895"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Parameter_4896"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="Ribose phosphate isomerase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_22">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:5.3.1.6" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01056" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2033" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4892" name="Vmaxv22" value="730"/>
          <Constant key="Parameter_4891" name="Keqv22" value="3"/>
          <Constant key="Parameter_4890" name="KRu5Pv22" value="0.78"/>
          <Constant key="Parameter_4889" name="KR5Pv22" value="2.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_62" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="Parameter_4889"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="Parameter_4890"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Parameter_4891"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="Parameter_4892"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="Transketolase 1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01641" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1629" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.2.1.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4888" name="Vmaxv23" value="23.5"/>
          <Constant key="Parameter_4887" name="Keqv23" value="1.05"/>
          <Constant key="Parameter_4886" name="K1v23" value="0.4177"/>
          <Constant key="Parameter_4885" name="K2v23" value="0.3055"/>
          <Constant key="Parameter_4884" name="K6v23" value="0.00774"/>
          <Constant key="Parameter_4883" name="K3v23" value="12.432"/>
          <Constant key="Parameter_4882" name="K5v23" value="0.41139"/>
          <Constant key="Parameter_4881" name="K4v23" value="0.00496"/>
          <Constant key="Parameter_4880" name="K7v23" value="48.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_63" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Parameter_4886"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="Parameter_4885"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Parameter_4883"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Parameter_4881"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="Parameter_4882"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="Parameter_4884"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="Parameter_4880"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="Parameter_4887"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="Parameter_4888"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="Transaldolase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01827" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_479" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.2.1.2" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4879" name="Vmaxv24" value="27.2"/>
          <Constant key="Parameter_4878" name="Keqv24" value="1.05"/>
          <Constant key="Parameter_4877" name="K1v24" value="0.00823"/>
          <Constant key="Parameter_4876" name="K2v24" value="0.04765"/>
          <Constant key="Parameter_4875" name="K6v24" value="0.4653"/>
          <Constant key="Parameter_4874" name="K3v24" value="0.1733"/>
          <Constant key="Parameter_4873" name="K5v24" value="0.8683"/>
          <Constant key="Parameter_4872" name="K4v24" value="0.006095"/>
          <Constant key="Parameter_4871" name="K7v24" value="2.524"/>
        </ListOfConstants>
        <KineticLaw function="Function_64" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Parameter_4877"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="Parameter_4876"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Parameter_4874"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="Parameter_4872"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Parameter_4873"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Parameter_4875"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="Parameter_4871"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="Parameter_4878"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="Parameter_4879"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="Phosphoribosylpyrophosphate synthetase" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01049" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_2023" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.6.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4870" name="Vmaxv25" value="1.1"/>
          <Constant key="Parameter_4869" name="Keqv25" value="100000"/>
          <Constant key="Parameter_4868" name="KATPv25" value="0.03"/>
          <Constant key="Parameter_4867" name="KR5Pv25" value="0.57"/>
        </ListOfConstants>
        <KineticLaw function="Function_65" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_498">
              <SourceParameter reference="Parameter_4868"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_497">
              <SourceParameter reference="Parameter_4867"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_496">
              <SourceParameter reference="Parameter_4869"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_495">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_494">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_493">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_492">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_491">
              <SourceParameter reference="Parameter_4870"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="Transketolase 2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.reaction:R01830" />
        <rdf:li rdf:resource="urn:miriam:reactome:REACT_1811" />
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.2.1.1" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4866" name="Vmaxv26" value="23.5"/>
          <Constant key="Parameter_4865" name="Keqv26" value="1.2"/>
          <Constant key="Parameter_4864" name="K1v26" value="0.00184"/>
          <Constant key="Parameter_4863" name="K2v26" value="0.3055"/>
          <Constant key="Parameter_4862" name="K6v26" value="0.122"/>
          <Constant key="Parameter_4861" name="K3v26" value="0.0548"/>
          <Constant key="Parameter_4860" name="K5v26" value="0.0287"/>
          <Constant key="Parameter_4859" name="K4v26" value="0.0003"/>
          <Constant key="Parameter_4858" name="K7v26" value="0.215"/>
        </ListOfConstants>
        <KineticLaw function="Function_66" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_501">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_500">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_499">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="Parameter_4864"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Parameter_4863"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="Parameter_4861"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_489">
              <SourceParameter reference="Parameter_4859"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Parameter_4860"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_502">
              <SourceParameter reference="Parameter_4862"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_503">
              <SourceParameter reference="Parameter_4858"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_504">
              <SourceParameter reference="Parameter_4865"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_505">
              <SourceParameter reference="Parameter_4866"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_506">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="Phosphate exchange" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0009935" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4857" name="Vmaxv27" value="100"/>
          <Constant key="Parameter_4856" name="Keqv27" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_67" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_519">
              <SourceParameter reference="Parameter_4856"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_518">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_517">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_516">
              <SourceParameter reference="Parameter_4857"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="Lactate exchange" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0009935" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4855" name="Vmaxv28" value="10000"/>
          <Constant key="Parameter_4854" name="Keqv28" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_68" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_512">
              <SourceParameter reference="Parameter_4854"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_513">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_514">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_515">
              <SourceParameter reference="Parameter_4855"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="Pyruvate exchange" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0009935" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4853" name="Vmaxv29" value="10000"/>
          <Constant key="Parameter_4852" name="Keqv29" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_69" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_508">
              <SourceParameter reference="Parameter_4852"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_509">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_510">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_511">
              <SourceParameter reference="Parameter_4853"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="MgATP dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006759" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4851" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4850" name="KdATP" value="0.072"/>
        </ListOfConstants>
        <KineticLaw function="Function_70" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_522">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_521">
              <SourceParameter reference="Parameter_4851"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_520">
              <SourceParameter reference="Parameter_4850"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_507">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_523">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="MgADP dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4849" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4848" name="KdADP" value="0.76"/>
        </ListOfConstants>
        <KineticLaw function="Function_71" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_528">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_527">
              <SourceParameter reference="Parameter_4849"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="Parameter_4848"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="MgAMP dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4847" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4846" name="KdAMP" value="16.64"/>
        </ListOfConstants>
        <KineticLaw function="Function_72" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_533">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_532">
              <SourceParameter reference="Parameter_4847"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_531">
              <SourceParameter reference="Parameter_4846"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_530">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_529">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="MgGri23P2 dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
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
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4845" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4844" name="Kd23P2G" value="1.667"/>
        </ListOfConstants>
        <KineticLaw function="Function_73" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_538">
              <SourceParameter reference="Parameter_4845"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_537">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_536">
              <SourceParameter reference="Parameter_4844"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_535">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_534">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="P1NADP dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
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
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4843" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4842" name="Kd1" value="0.0002"/>
        </ListOfConstants>
        <KineticLaw function="Function_74" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_543">
              <SourceParameter reference="Parameter_4843"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_542">
              <SourceParameter reference="Parameter_4842"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_541">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_540">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_539">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="P1NADPH dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006740" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4841" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4840" name="Kd3" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_75" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_548">
              <SourceParameter reference="Parameter_4841"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_547">
              <SourceParameter reference="Parameter_4840"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_546">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_545">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_544">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="P2NADP dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_36">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T18:34:21Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4839" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4838" name="Kd2" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_76" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_553">
              <SourceParameter reference="Parameter_4839"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_552">
              <SourceParameter reference="Parameter_4838"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_551">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_550">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_549">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="P2NADPH dissociation" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006735" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4837" name="EqMult" value="1e+07"/>
          <Constant key="Parameter_4836" name="Kd4" value="0.0002"/>
        </ListOfConstants>
        <KineticLaw function="Function_77" unitType="Default" scalingCompartment="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_558">
              <SourceParameter reference="Parameter_4837"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_557">
              <SourceParameter reference="Parameter_4836"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_556">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_555">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_554">
              <SourceParameter reference="Metabolite_38"/>
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
<dcterms:W3CDTF>2021-01-04T13:53:18Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Glucose in]" value="2.7498901795319102e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[MgATP]" value="8.4309971997999995e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Glucose 6-phosphate]" value="2.3727234976580002e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[MgADP]" value="6.0221408570000007e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Fructose 6-phosphate]" value="9.2138755112100014e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Fructose 1\,6-phosphate]" value="5.8414766312900004e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Glyceraldehyde 3-phosphate]" value="3.6735059227699999e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Dihydroxyacetone phosphate]" value="8.9850341586439995e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphate]" value="6.0173231443144003e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[NAD]" value="3.932457979621e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[1\,3-Bisphospho-D-glycerate]" value="3.0110704285e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[NADH]" value="1.2044281714e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[3-Phospho-D-glycerate]" value="3.9625686839059997e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[2\,3-Bisphospho-D-glycerate]" value="1.24062123795057e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[2-Phospho-D-glycerate]" value="5.0585983198799995e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphoenolpyruvate]" value="6.5641335341299999e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Pyruvate]" value="5.0585983198800003e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Lactate]" value="1.0119003282017099e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[NADPH]" value="2.4088563428e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[NADP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[AMP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[ADP]" value="1.5055352142500001e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Phospho-D-glucono-1\,5-lactone]" value="1.50553521425e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Ribulose 5-phosphate]" value="2.8304062027900001e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Oxidized Glutathione]" value="2.4088563428e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Reduced Glutathione]" value="1.87505377723552e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Xylulose 5-phosphate]" value="7.6481188883899996e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Ribose 5-phosphate]" value="8.4309971998000005e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Sedoheptulose 7-phosphate]" value="9.2740969197799997e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Erythrose 4-phosphate]" value="3.7939487399100001e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[MgAMP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[ATP]" value="1.5055352142500001e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Mg]" value="4.8177126856000012e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[MgGri23P2]" value="3.0110704285000001e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein1 bound NADP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein1]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein1 bound NADPH]" value="1.44531380568e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein2 bound NADP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Protein2 bound NADPH]" value="1.44531380568e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[PRPP]" value="6.0221408570000002e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[External Lactate]" value="1.011719663976e+21" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[External Pyruvate]" value="5.0585983198800003e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Glucose outside]" value="3.0110704285000002e+21" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphate external]" value="6.0221408570000002e+20" type="Species" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport],ParameterGroup=Parameters,Parameter=Vmaxv0" value="33.600000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport],ParameterGroup=Parameters,Parameter=KMoutv0" value="1.7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport],ParameterGroup=Parameters,Parameter=Keqv0" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport],ParameterGroup=Parameters,Parameter=KMinv0" value="6.9000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose transport],ParameterGroup=Parameters,Parameter=alfav0" value="0.54000000000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=Inhibv1" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KMGlcv1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=Vmax1v1" value="15.800000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KMgATPv1" value="1.4399999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=Vmax2v1" value="33.200000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KMgATPMgv1" value="1.1399999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=Keqv1" value="3900" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KMgv1" value="1.03" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KGlc6Pv1" value="0.0044999999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=K23P2Gv1" value="2.7000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Hexokinase],ParameterGroup=Parameters,Parameter=KMg23P2Gv1" value="3.4399999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucosephosphate isomerase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucosephosphate isomerase],ParameterGroup=Parameters,Parameter=Vmaxv2" value="935" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucosephosphate isomerase],ParameterGroup=Parameters,Parameter=Keqv2" value="0.39250000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucosephosphate isomerase],ParameterGroup=Parameters,Parameter=KGlc6Pv2" value="0.182" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucosephosphate isomerase],ParameterGroup=Parameters,Parameter=KFru6Pv2" value="0.070999999999999994" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=Vmaxv3" value="239" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=Keqv3" value="100000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=KFru6Pv3" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=KMgATPv3" value="0.068000000000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=L0v3" value="0.001072" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=KATPv3" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=KMgv3" value="0.44" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphofructokinase],ParameterGroup=Parameters,Parameter=KAMPv3" value="0.033000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=Vmaxv4" value="98.909999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=KFru16P2v4" value="0.0071000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=Keqv4" value="0.114" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=KiGraPv4" value="0.057200000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=KGraPv4" value="0.19059999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=KDHAPv4" value="0.036400000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Aldolase],ParameterGroup=Parameters,Parameter=KiiGraPv4" value="0.17599999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Triosephosphate isomerase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Triosephosphate isomerase],ParameterGroup=Parameters,Parameter=Vmaxv5" value="5456.6000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Triosephosphate isomerase],ParameterGroup=Parameters,Parameter=Keqv5" value="0.0407" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Triosephosphate isomerase],ParameterGroup=Parameters,Parameter=KDHAPv5" value="0.83799999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Triosephosphate isomerase],ParameterGroup=Parameters,Parameter=KGraPv5" value="0.42799999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=Vmaxv6" value="4300" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADv6" value="0.050000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KGraPv6" value="0.0050000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KPv6" value="3.8999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=Keqv6" value="0.000192" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADHv6" value="0.0083000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glyceraldehyde 3-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=K13P2Gv6" value="0.0035000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=Vmaxv7" value="5000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=KMgADPv7" value="0.34999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=K13P2Gv7" value="0.002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=Keqv7" value="1455" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=KMgATPv7" value="0.47999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate kinase],ParameterGroup=Parameters,Parameter=K3PGv7" value="1.2" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate mutase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate mutase],ParameterGroup=Parameters,Parameter=kDPGMv8" value="76000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate mutase],ParameterGroup=Parameters,Parameter=Keqv8" value="100000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate mutase],ParameterGroup=Parameters,Parameter=K23P2Gv8" value="0.040000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate phosphatase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate phosphatase],ParameterGroup=Parameters,Parameter=Vmaxv9" value="0.53000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate phosphatase],ParameterGroup=Parameters,Parameter=Keqv9" value="100000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Bisphosphoglycerate phosphatase],ParameterGroup=Parameters,Parameter=K23P2Gv9" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate mutase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate mutase],ParameterGroup=Parameters,Parameter=Vmaxv10" value="2000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate mutase],ParameterGroup=Parameters,Parameter=Keqv10" value="0.14499999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate mutase],ParameterGroup=Parameters,Parameter=K3PGv10" value="5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoglycerate mutase],ParameterGroup=Parameters,Parameter=K2PGv10" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Enolase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Enolase],ParameterGroup=Parameters,Parameter=Vmaxv11" value="1500" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Enolase],ParameterGroup=Parameters,Parameter=Keqv11" value="1.7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Enolase],ParameterGroup=Parameters,Parameter=K2PGv11" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Enolase],ParameterGroup=Parameters,Parameter=KPEPv11" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=Vmaxv12" value="570" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=Keqv12" value="13790" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=KPEPv12" value="0.22500000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=KMgADPv12" value="0.47399999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=L0v12" value="19" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=KATPv12" value="3.3900000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate kinase],ParameterGroup=Parameters,Parameter=KFru16P2v12" value="0.0050000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase],ParameterGroup=Parameters,Parameter=Vmaxv13" value="2800000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase],ParameterGroup=Parameters,Parameter=Keqv13" value="9090" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase_2],ParameterGroup=Parameters,Parameter=kLDHv14" value="243.40000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate dehydrogenase_2],ParameterGroup=Parameters,Parameter=Keqv14" value="14181.799999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[ATPase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[ATPase],ParameterGroup=Parameters,Parameter=kATPasev15" value="1.6799999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase],ParameterGroup=Parameters,Parameter=Vmaxv16" value="1380" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase],ParameterGroup=Parameters,Parameter=KATPv16" value="0.089999999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase],ParameterGroup=Parameters,Parameter=KAMPv16" value="0.080000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase],ParameterGroup=Parameters,Parameter=Keqv16" value="0.25" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Adenylate kinase],ParameterGroup=Parameters,Parameter=KADPv16" value="0.11" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=Vmaxv17" value="162" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KG6Pv17" value="0.066699999999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADPv17" value="0.0036700000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=Keqv17" value="2000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KATPv17" value="0.749" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADPHv17" value="0.0031199999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glucose 6-phosphate dehydrogenase],ParameterGroup=Parameters,Parameter=KPGA23v17" value="2.2890000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=Vmaxv18" value="1575" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=K6PG1v18" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADPv18" value="0.017999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=Keqv18" value="141.69999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=KPGA23v18" value="0.12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=KATPv18" value="0.154" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=K6PG2v18" value="0.058000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphogluconate dehydrogenase],ParameterGroup=Parameters,Parameter=KNADPHv18" value="0.0044999999999999997" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=Vmaxv19" value="90" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=KGSSGv19" value="0.065199999999999994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=KNADPHv19" value="0.0085199999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=KGSHv19" value="20" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=KNADPv19" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione reductase],ParameterGroup=Parameters,Parameter=Keqv19" value="1.04" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione oxidation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Glutathione oxidation],ParameterGroup=Parameters,Parameter=Kv20" value="0.029999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribulose epimerase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribulose epimerase],ParameterGroup=Parameters,Parameter=Vmaxv21" value="4634" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribulose epimerase],ParameterGroup=Parameters,Parameter=Keqv21" value="2.7000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribulose epimerase],ParameterGroup=Parameters,Parameter=KRu5Pv21" value="0.19" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribulose epimerase],ParameterGroup=Parameters,Parameter=KX5Pv21" value="0.5" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Ribose phosphate isomerase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Ribose phosphate isomerase],ParameterGroup=Parameters,Parameter=Vmaxv22" value="730" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Ribose phosphate isomerase],ParameterGroup=Parameters,Parameter=Keqv22" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Ribose phosphate isomerase],ParameterGroup=Parameters,Parameter=KRu5Pv22" value="0.78000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Ribose phosphate isomerase],ParameterGroup=Parameters,Parameter=KR5Pv22" value="2.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=Vmaxv23" value="23.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=Keqv23" value="1.05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K1v23" value="0.41770000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K2v23" value="0.30549999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K6v23" value="0.0077400000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K3v23" value="12.432" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K5v23" value="0.41138999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K4v23" value="0.00496" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 1],ParameterGroup=Parameters,Parameter=K7v23" value="48.799999999999997" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=Vmaxv24" value="27.199999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=Keqv24" value="1.05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K1v24" value="0.0082299999999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K2v24" value="0.047649999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K6v24" value="0.46529999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K3v24" value="0.17330000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K5v24" value="0.86829999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K4v24" value="0.0060949999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transaldolase],ParameterGroup=Parameters,Parameter=K7v24" value="2.524" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribosylpyrophosphate synthetase]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribosylpyrophosphate synthetase],ParameterGroup=Parameters,Parameter=Vmaxv25" value="1.1000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribosylpyrophosphate synthetase],ParameterGroup=Parameters,Parameter=Keqv25" value="100000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribosylpyrophosphate synthetase],ParameterGroup=Parameters,Parameter=KATPv25" value="0.029999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphoribosylpyrophosphate synthetase],ParameterGroup=Parameters,Parameter=KR5Pv25" value="0.56999999999999995" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=Vmaxv26" value="23.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=Keqv26" value="1.2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K1v26" value="0.0018400000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K2v26" value="0.30549999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K6v26" value="0.122" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K3v26" value="0.054800000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K5v26" value="0.0287" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K4v26" value="0.00029999999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Transketolase 2],ParameterGroup=Parameters,Parameter=K7v26" value="0.215" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphate exchange]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphate exchange],ParameterGroup=Parameters,Parameter=Vmaxv27" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Phosphate exchange],ParameterGroup=Parameters,Parameter=Keqv27" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate exchange]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate exchange],ParameterGroup=Parameters,Parameter=Vmaxv28" value="10000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Lactate exchange],ParameterGroup=Parameters,Parameter=Keqv28" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate exchange]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate exchange],ParameterGroup=Parameters,Parameter=Vmaxv29" value="10000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[Pyruvate exchange],ParameterGroup=Parameters,Parameter=Keqv29" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgATP dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgATP dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgATP dissociation],ParameterGroup=Parameters,Parameter=KdATP" value="0.071999999999999995" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgADP dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgADP dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgADP dissociation],ParameterGroup=Parameters,Parameter=KdADP" value="0.76000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgAMP dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgAMP dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgAMP dissociation],ParameterGroup=Parameters,Parameter=KdAMP" value="16.640000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgGri23P2 dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgGri23P2 dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[MgGri23P2 dissociation],ParameterGroup=Parameters,Parameter=Kd23P2G" value="1.667" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADP dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADP dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADP dissociation],ParameterGroup=Parameters,Parameter=Kd1" value="0.00020000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADPH dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADPH dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P1NADPH dissociation],ParameterGroup=Parameters,Parameter=Kd3" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADP dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADP dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADP dissociation],ParameterGroup=Parameters,Parameter=Kd2" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADPH dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADPH dissociation],ParameterGroup=Parameters,Parameter=EqMult" value="10000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Holzhutter2004_Erythrocyte_Metabolism,Vector=Reactions[P2NADPH dissociation],ParameterGroup=Parameters,Parameter=Kd4" value="0.00020000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 8.4309971997999995e+20 1.87505377723552e+21 3.6735059227699999e+18 2.4088563428e+18 9.2138755112100014e+18 4.8177126856000012e+20 6.0173231443144003e+20 5.0585983198800003e+19 0 2.8304062027900001e+18 3.9625686839059997e+19 2.3727234976580002e+19 3.0110704285e+17 8.4309971998000005e+18 8.9850341586439995e+19 1.0119003282017099e+21 1.5055352142500001e+20 7.6481188883899996e+18 5.0585983198799995e+18 2.7498901795319102e+21 1.24062123795057e+21 3.7939487399100001e+18 0 1.50553521425e+19 0 6.5641335341299999e+18 1.2044281714e+17 5.8414766312900004e+18 0 0 0 9.2740969197799997e+18 6.0221408570000007e+19 0 3.0110704285000001e+20 1.44531380568e+19 1.44531380568e+19 3.932457979621e+19 1.5055352142500001e+20 2.4088563428e+17 6.0221408570000002e+20 1.011719663976e+21 5.0585983198800003e+19 3.0110704285000002e+21 6.0221408570000002e+20 1 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_15" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_16" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_17" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_18" name="Elementary Flux Modes" type="fluxMode" scheduled="true" updateModel="false">
      <Report reference="Report_22" target="BIOMOD70_efm.out" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_19" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_20" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_21" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_15"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_22" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_23" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_24" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_25" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_26" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_27" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_21" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_15"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_28" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
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
    <Report key="Report_11" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
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
    <Report key="Report_13" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_14" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_15" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_17" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_18" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_20" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_21" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_22" name="Speed test" taskType="scan" separator="&#x09;" precision="8">
      <Comment>
      </Comment>
      <Footer>
        <Object cn="CN=Root,CN=Information,String=COPASI Version"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,CN=Information,Timer=Current Date/Time"/>
        <Object cn="String=&#x0a;"/>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro*#
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
<dcterms:W3CDTF>2021-01-04T13:53:17Z</dcterms:W3CDTF>
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
