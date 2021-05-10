<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2020-12-31T20:37:39Z -->
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
    <Function key="Function_121" name="Function for GLC_FEED" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T21:58:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        cell*FEED/extracellular
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_526" name="FEED" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_525" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_524" name="extracellular" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_133" name="Function for FUMA" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_133">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-11T17:11:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(FUM-MAL/Keq)/KmFUM/(1+FUM/KmFUM+MAL/KmMAL)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1139" name="FUM" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1138" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1137" name="KmFUM" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1136" name="KmMAL" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1135" name="MAL" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1134" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_134" name="Function for ACEA" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_134">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T10:00:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ICIT-GLX*SUC/Keq)/KmICIT/(1+ICIT/KmICIT*(1+PEP/KdPEPicit)+SUC/KdSUC*(1+ICIT/KdICITsuc)+KmSUC/KdSUC*(GLX/KmGLX)*(1+PEP/KdPEPglx)+GLX/KmGLX*(SUC/KdSUC)+PEP/KdPEP+PGA3/KdPGA3)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1155" name="GLX" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1154" name="ICIT" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1153" name="KdICITsuc" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1152" name="KdPEP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1151" name="KdPEPglx" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1150" name="KdPEPicit" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1149" name="KdPGA3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1148" name="KdSUC" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1147" name="Keq" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1146" name="KmGLX" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1145" name="KmICIT" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1144" name="KmSUC" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1143" name="PEP" order="12" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1142" name="PGA3" order="13" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1141" name="SUC" order="14" role="product"/>
        <ParameterDescription key="FunctionParameter_1140" name="Vmax" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_135" name="Function for RPI" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_135">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(RU5P-R5P/Keq)/KmRU5P/(1+RU5P/KmRU5P+R5P/KmR5P+E4P/KmE4P)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1163" name="E4P" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1162" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1161" name="KmE4P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1160" name="KmR5P" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1159" name="KmRU5P" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1158" name="R5P" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_1157" name="RU5P" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1156" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_136" name="Function for X5P_GAP_TKT" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_136">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-31T12:39:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*(tkt*X5P-GAP*tktC2/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1169" name="GAP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1168" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1167" name="X5P" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1166" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1165" name="tkt" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1164" name="tktC2" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_137" name="Function for ACS" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_137">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T14:33:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        cell*Vmax*ACEx*ATP*COA/(KmACE*KmATP*KmCOA)/((1+ACEx/KmACE)*(1+ATP/KmATP)*(1+COA/KmCOA))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1177" name="ACEx" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1176" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1175" name="COA" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1174" name="KmACE" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1173" name="KmATP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1172" name="KmCOA" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1171" name="Vmax" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1170" name="cell" order="7" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_138" name="Function for EDD" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_138">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(PGN-KDPG/Keq)/KmPGN/(1+PGN/KmPGN+KDPG/KmKDPG)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1183" name="KDPG" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1182" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1181" name="KmKDPG" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1180" name="KmPGN" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1179" name="PGN" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1178" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_139" name="Function for EDA" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_139">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(KDPG-GAP*PYR/Keq)/KmKDPG/(1+KDPG/KmKDPG+(1+GAP/KmGAP)*(1+PYR/KmPYR)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1191" name="GAP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1190" name="KDPG" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1189" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1188" name="KmGAP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1187" name="KmKDPG" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1186" name="KmPYR" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1185" name="PYR" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_1184" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_140" name="Function for PNT" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_140">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T13:50:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(NAD*NADPH-NADH*NADP/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1197" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1196" name="NAD" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1195" name="NADH" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1194" name="NADP" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1193" name="NADPH" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1192" name="k" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_141" name="Function for ADK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_141">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(AMP*ATP-ADP^2/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1202" name="ADP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1201" name="AMP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1200" name="ATP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1199" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1198" name="k" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_143" name="Function for ACEB" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_143">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T14:32:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACCOA*GLX-COA*MAL/Keq)/(KmACCOA*KmGLX)/((1+ACCOA/KmACCOA)*(1+GLX/KmGLX)+(1+COA/KmCOA)*(1+MAL/KmMAL)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1219" name="ACCOA" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1218" name="COA" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1217" name="GLX" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1216" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1215" name="KmACCOA" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1214" name="KmCOA" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1213" name="KmGLX" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1212" name="KmMAL" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1211" name="MAL" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_1210" name="Vmax" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_144" name="Function for ACEK_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_144">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T13:25:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(ATP*icd-ADP*icdP/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1225" name="ADP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1224" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1223" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1222" name="icd" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1221" name="icdP" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1220" name="k" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_145" name="Function for ACEK_2" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_145">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T14:20:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(icdP-icd*P/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1230" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1229" name="P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1228" name="icd" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1227" name="icdP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1226" name="k" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_146" name="Function for DOS" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_146">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(CAMP-AMP/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1234" name="AMP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1233" name="CAMP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1232" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1231" name="k" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_147" name="Function for ACK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_147">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:42:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        cell*Vmax*(ACP*ADP-ACEx*ATP/Keq)/(KmACP*KmADP)/((1+ACP/KmACP+ACEx/KmACE)*(1+ADP/KmADP+ATP/KmATP))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1245" name="ACEx" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1244" name="ACP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1243" name="ADP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1242" name="ATP" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1241" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1240" name="KmACE" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1239" name="KmACP" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1238" name="KmADP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1237" name="KmATP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1236" name="Vmax" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1235" name="cell" order="10" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_148" name="Function for PTA" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_148">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:44:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACCOA*P-ACP*COA/Keq)/(KiACCOA*KmP)/(1+ACCOA/KiACCOA+P/KiP+ACP/KiACP+COA/KiCOA+ACCOA*P/(KiACCOA*KmP)+ACP*COA/(KmACP*KiCOA))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1257" name="ACCOA" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1256" name="ACP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1255" name="COA" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1254" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1253" name="KiACCOA" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1252" name="KiACP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1251" name="KiCOA" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1250" name="KiP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1249" name="KmACP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1248" name="KmP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1247" name="P" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1246" name="Vmax" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_149" name="Function for PTS_0" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_149">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-22T14:03:00Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kF*ei*PEP^2/(KmPEP^2+PEP^2)-kR*eiP*PYR^2/(KmPYR^2+PYR^2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1265" name="KmPEP" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1264" name="KmPYR" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1263" name="PEP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1262" name="PYR" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1261" name="ei" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1260" name="eiP" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_1259" name="kF" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1258" name="kR" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_151" name="Function for PYK" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_151">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T08:51:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*n*PEP*MgADP/(KirPEP*KmrADPMg)/(1+KmrPEP/KirPEP*(MgADP/KmrADPMg)+MgATP/KirATP+MgADP/KmrADPMg*(PEP/KirPEP)+KmrADPMg/KmrADPMg*(1+(ADP-MgADP)/KirADP)*(PEP/KirPEP)+PYR/KirPYR+MgATP/KirPyrATP*(PYR/KirPYR))/(1+L0*((1+KmtPEP/KitPEP*(MgADP/KmtADPMg)+MgATP/KitATP+MgADP*PEP/(KitPEP*KmtADPMg)+(1+(ADP-MgADP)/KitADP)*(PEP/KitPEP)+PYR/KitPYR+MgATP/KitPyrATP*(PYR/KitPYR))*(1+SUCCOA/KeftSUCCOA+MgATP*SUCCOA/(KeftATP*KeftSUCCOA))/((1+KmrPEP/KirPEP*(MgADP/KmrADPMg)+MgATP/KirATP+MgADP/KmrADPMg*(PEP/KirPEP)+(1+(ADP-MgADP)/KirADP)*(PEP/KirPEP)+PYR/KirPYR+MgATP/KirPyrATP*(PYR/KirPYR))*(1+FDP/KefrFDP+G6P/KefrG6P+GL6P/KefrGL6P+R5P/KefrR5P+RU5P/KefrRU5P+S7P/KefrS7P+X5P/KefrX5P)))^n)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1313" name="ADP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1312" name="FDP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1311" name="G6P" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1310" name="GL6P" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1309" name="KefrFDP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1308" name="KefrG6P" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1307" name="KefrGL6P" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1306" name="KefrR5P" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1305" name="KefrRU5P" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1304" name="KefrS7P" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1303" name="KefrX5P" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1302" name="KeftATP" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1301" name="KeftSUCCOA" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1300" name="KirADP" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1299" name="KirATP" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1298" name="KirPEP" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1297" name="KirPYR" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1296" name="KirPyrATP" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1295" name="KitADP" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1294" name="KitATP" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1293" name="KitPEP" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1292" name="KitPYR" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1291" name="KitPyrATP" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_1290" name="KmrADPMg" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_1289" name="KmrPEP" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_1288" name="KmtADPMg" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_1287" name="KmtPEP" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_1286" name="L0" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_1285" name="MgADP" order="28" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1284" name="MgATP" order="29" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1283" name="PEP" order="30" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1282" name="PYR" order="31" role="product"/>
        <ParameterDescription key="FunctionParameter_1281" name="R5P" order="32" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1280" name="RU5P" order="33" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1279" name="S7P" order="34" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1278" name="SUCCOA" order="35" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1277" name="Vmax" order="36" role="constant"/>
        <ParameterDescription key="FunctionParameter_1276" name="X5P" order="37" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1275" name="n" order="38" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_152" name="Function for GPM" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_152">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-13T10:20:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(PGA3-PGA2/Keq)/KmPGA3/(1+PGA3/KmPGA3+PGA2/KmPGA2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1319" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1318" name="KmPGA2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1317" name="KmPGA3" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1316" name="PGA2" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1315" name="PGA3" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1314" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_153" name="Function for PDH" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_153">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:51:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(COA*NAD*PYR-ACCOA*NADH*HCO3/Keq)/(KmCOA*KmNAD*KmPYR)/(ACCOA/KmACCOA+NADH/KmNADH+ACCOA/KmACCOA*(NADH/KmNADH)+COA/KmCOA*(NADH/KmNADH)+ACCOA/KmACCOA*(COA/KmCOA)*(NADH/KmNADH)+NAD/KmNAD*(NADH/KmNADH)+COA/KmCOA*(NAD/KmNAD)*(NADH/KmNADH)+ACCOA/KmACCOA*(PYR/KmPYR)+ACCOA/KmACCOA*(COA/KmCOA)*(PYR/KmPYR)+COA/KmCOA*(1+NAD/KmNAD)*(PYR/KmPYR)+NAD/KmNAD*(1+COA/KmCOA+PYR/KmPYR))/(1+HCO3/KmHCO3)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1333" name="ACCOA" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1332" name="COA" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1331" name="HCO3" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1330" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1329" name="KmACCOA" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1328" name="KmCOA" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1327" name="KmHCO3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1326" name="KmNAD" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1325" name="KmNADH" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1324" name="KmPYR" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1323" name="NAD" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1322" name="NADH" order="11" role="product"/>
        <ParameterDescription key="FunctionParameter_1321" name="PYR" order="12" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1320" name="Vmax" order="13" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_154" name="Function for GDH" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_154">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:43:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(P*GAP*NAD-BPG*NADH/Keq)/(KmP*KmGAP*KmNAD)/((1+P/KmP)*(1+GAP/KmGAP)*(1+NAD/KmNAD)+(1+BPG/KmBPG)*(1+NADH/KmNADH)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1345" name="BPG" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1344" name="GAP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1343" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1342" name="KmBPG" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1341" name="KmGAP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1340" name="KmNAD" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1339" name="KmNADH" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1338" name="KmP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1337" name="NAD" order="8" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1336" name="NADH" order="9" role="product"/>
        <ParameterDescription key="FunctionParameter_1335" name="P" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1334" name="Vmax" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_155" name="Function for GLT" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_155">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T14:30:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACCOA*OAA-CIT*COA/Keq)/(KdACCOA0*KmOAA0)/(ACCOA/KdACCOA0*(1+AKG/Ki1AKG+NADH/Ki1NADH)+ACCOA/KdACCOA0*(OAA/KmOAA0)*(1+AKG/Ki2AKG+NADH/Ki2NADH)+(1+ATP/KiATP)*(1+KmACCOA0/KdACCOA0*(OAA/KmOAA0))+KmcsCOA/KdcsCOA*(CIT/KmcsCIT)+KmcsCOA/KdcsCOA*(ACCOA/KdACCOA0)*(CIT/KmcsCIT)+COA/KdcsCOA+CIT/KmcsCIT*(OAA/KmOAA0)+ACCOA/KdACCOA0*(CIT/KdcsCIT)*(OAA/KmOAA0)+KmACCOA0/KdACCOA0*(COA/KdcsCOA)*(OAA/KmOAA0)+CIT/KmcsCIT*(COA/KdcsCOA)*(OAA/KdcsOAA))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1367" name="ACCOA" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1366" name="AKG" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1365" name="ATP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1364" name="CIT" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1363" name="COA" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1362" name="KdACCOA0" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1361" name="KdcsCIT" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1360" name="KdcsCOA" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1359" name="KdcsOAA" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1358" name="Keq" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1357" name="Ki1AKG" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1356" name="Ki1NADH" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1355" name="Ki2AKG" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1354" name="Ki2NADH" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1353" name="KiATP" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1352" name="KmACCOA0" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1351" name="KmOAA0" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1350" name="KmcsCIT" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1349" name="KmcsCOA" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1348" name="NADH" order="19" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1347" name="OAA" order="20" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1346" name="Vmax" order="21" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_156" name="Function for FBA" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_156">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T22:00:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(FDP-DAP*GAP/Keq)/KmFDP/(1+FDP/KmFDP+DAP/KmDAP+DAP/KmDAP*(GAP/KmGAP)+PEP/KmPEP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1377" name="DAP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1376" name="FDP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1375" name="GAP" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1374" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1373" name="KmDAP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1372" name="KmFDP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1371" name="KmGAP" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1370" name="KmPEP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1369" name="PEP" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1368" name="Vmax" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_158" name="Function for GND" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_158">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:50:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(NADP*PGN-NADPH*RU5P*HCO3/Keq)/(KdNADP*KmPGN)/(1+NADP/KdNADP+FDP/KefFbP+NADP/KdNADP*(FDP/KefNADPFbP)+KmNADP/KdNADP*(PGN/KmPGN)+NADP/KdNADP*(PGN/KmPGN)+ATP/KefATP+ATP/KefNADPATP*(KmNADP/KdNADP)*(PGN/KmPGN)+HCO3/KdHCO3+NADPH/KdNADPH+RU5P/KdRu5P+HCO3/KdHCO3*(NADPH/KdHCO3NADPH)+HCO3/KdHCO3*(KmNADPH/KdHCO3NADPH)*(RU5P/KmRU5P)+HCO3/KdHCO3*(NADPH/KdHCO3NADPH)*(RU5P/KmRU5P)+KmHCO3/KdHCO3*(NADPH/KdHCO3NADPH)*(RU5P/KmRU5P))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1408" name="ATP" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1407" name="FDP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1406" name="HCO3" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1405" name="KdHCO3" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1404" name="KdHCO3NADPH" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1403" name="KdNADP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1402" name="KdNADPH" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1401" name="KdRu5P" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1400" name="KefATP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1399" name="KefFbP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1398" name="KefNADPATP" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1397" name="KefNADPFbP" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1396" name="Keq" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1395" name="KmHCO3" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1394" name="KmNADP" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1393" name="KmNADPH" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1392" name="KmPGN" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1391" name="KmRU5P" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1390" name="NADP" order="18" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1389" name="NADPH" order="19" role="product"/>
        <ParameterDescription key="FunctionParameter_1388" name="PGN" order="20" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1387" name="RU5P" order="21" role="product"/>
        <ParameterDescription key="FunctionParameter_1386" name="Vmax" order="22" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_159" name="Function for PPC" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_159">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:43:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*n*(PEP*HCO3-OAA*P/Keq)/(KdrPEP*KmrHCO3)/(1+KmrPEP/KdrPEP*(HCO3/KmrHCO3)+KmrOAA/KdrOAA*(P/KmrP)+OAA/KdrOAA+P/KmrP*(OAA/KdrOAA)+HCO3/KmrHCO3*(PEP/KdrPEP)+PEP/KdrPEP)/(1+L0*((1+ACCOA/KeftACCOA+FDP/KeftFDP+FDP/KeftFDP*(ACCOA/KeftFDPACCOA))*(1+KmtPEP/KdtPEP*(HCO3/KmtHCO3)+KmtOAA/KdtOAA*(P/KmtP)+OAA/KdtOAA+P/KmtP*(OAA/KdtOAA)+HCO3/KmtHCO3*(PEP/KdtPEP)+PEP/KdtPEP)*(1+ASP/KeftASP+CYS/KeftCYS+CIT/KeftCIT+FUM/KeftFUM+MAL/KeftMAL+SUC/KeftSUC)/((1+ACCOA/KefrACCOA+FDP/KefrFDP+FDP/KefrFDP*(ACCOA/KefrFDPACCOA))*(1+KmrPEP/KdrPEP*(HCO3/KmrHCO3)+KmrOAA/KdrOAA*(P/KmrP)+OAA/KdrOAA+P/KmrP*(OAA/KdrOAA)+HCO3/KmrHCO3*(PEP/KdrPEP)+PEP/KdrPEP)*(1+ASP/KefrASP+CYS/KefrCYS+CIT/KefrCIT+FUM/KefrFUM+MAL/KefrMAL+SUC/KefrSUC)))^n)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1454" name="ACCOA" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1453" name="ASP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1452" name="CIT" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1451" name="CYS" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1450" name="FDP" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1449" name="FUM" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1448" name="HCO3" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1447" name="KdrOAA" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1446" name="KdrPEP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1445" name="KdtOAA" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1444" name="KdtPEP" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1443" name="KefrACCOA" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1442" name="KefrASP" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1441" name="KefrCIT" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1440" name="KefrCYS" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1439" name="KefrFDP" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1438" name="KefrFDPACCOA" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1437" name="KefrFUM" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1436" name="KefrMAL" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1435" name="KefrSUC" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1434" name="KeftACCOA" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1433" name="KeftASP" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1432" name="KeftCIT" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_1431" name="KeftCYS" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_1430" name="KeftFDP" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_1429" name="KeftFDPACCOA" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_1428" name="KeftFUM" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_1427" name="KeftMAL" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_1426" name="KeftSUC" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_1425" name="Keq" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_1424" name="KmrHCO3" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_1423" name="KmrOAA" order="31" role="constant"/>
        <ParameterDescription key="FunctionParameter_1422" name="KmrP" order="32" role="constant"/>
        <ParameterDescription key="FunctionParameter_1421" name="KmrPEP" order="33" role="constant"/>
        <ParameterDescription key="FunctionParameter_1420" name="KmtHCO3" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_1419" name="KmtOAA" order="35" role="constant"/>
        <ParameterDescription key="FunctionParameter_1418" name="KmtP" order="36" role="constant"/>
        <ParameterDescription key="FunctionParameter_1417" name="KmtPEP" order="37" role="constant"/>
        <ParameterDescription key="FunctionParameter_1416" name="L0" order="38" role="constant"/>
        <ParameterDescription key="FunctionParameter_1415" name="MAL" order="39" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1414" name="OAA" order="40" role="product"/>
        <ParameterDescription key="FunctionParameter_1413" name="P" order="41" role="product"/>
        <ParameterDescription key="FunctionParameter_1412" name="PEP" order="42" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1411" name="SUC" order="43" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1410" name="Vmax" order="44" role="constant"/>
        <ParameterDescription key="FunctionParameter_1409" name="n" order="45" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_160" name="Function for SK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_160">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:44:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ADP*SUCCOA*P-ATP*COA*SUC/Keq)/(KmADP*KmSUCCOA*KmP)/((1+ADP/KmADP)*(1+SUCCOA/KmSUCCOA)*(1+P/KmP)+(1+ATP/KmATP)*(1+COA/KmCOA)*(1+SUC/KmSUC)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1468" name="ADP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1467" name="ATP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1466" name="COA" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1465" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1464" name="KmADP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1463" name="KmATP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1462" name="KmCOA" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1461" name="KmP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1460" name="KmSUC" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1459" name="KmSUCCOA" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1458" name="P" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1457" name="SUC" order="11" role="product"/>
        <ParameterDescription key="FunctionParameter_1456" name="SUCCOA" order="12" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1455" name="Vmax" order="13" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_162" name="Function for ICD" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_162">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T09:24:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        icd*kcat*(ICIT*NADP-AKG*NADPH/Keq)/(KmICIT*KmNADP)/((1+ICIT/KmICIT)*(1+NADP/KmNADP)+(1+AKG/KmAKG)*(1+NADPH/KmNADPH)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1487" name="AKG" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1486" name="ICIT" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1485" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1484" name="KmAKG" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1483" name="KmICIT" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1482" name="KmNADP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1481" name="KmNADPH" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1480" name="NADP" order="7" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1479" name="NADPH" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_1478" name="icd" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1477" name="kcat" order="10" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_163" name="Function for LPD" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_163">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:52:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*COA*AKG*NAD*(1-AKG/KdAKG)/(KmCOA*KmAKG*KmNAD)/(COA/KmCOA*(AKG/KmAKG)+COA/KmCOA*(NAD/KmNAD)+AKG/KmAKG*(NAD/KmNAD)+COA/KmCOA*(AKG/KmAKG)*(NAD/KmNAD)-AKG/KdAKG*(COA/KmCOA*(AKG/KmAKG)+AKG/KmAKG*(NAD/KmNAD)+alpha*(COA/KmCOA)*(AKG/KmAKG)*(NAD/KmNAD)))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1496" name="AKG" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1495" name="COA" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1494" name="KdAKG" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1493" name="KmAKG" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1492" name="KmCOA" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1491" name="KmNAD" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1490" name="NAD" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1489" name="Vmax" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1488" name="alpha" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_164" name="Function for ZWF" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_164">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(G6P*NADP-GL6P*NADPH/Keq)/(KdG6P*KmNADP)/(1+G6P/KdG6P+KmG6P/KdG6P*(NADP/KmNADP)+G6P/KdG6P*(NADP/KmNADP)+KmGL6P/KdGL6P*(NADPH/KmNADPH)+GL6P/KdGL6P*(NADPH/KmNADPH))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1508" name="G6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1507" name="GL6P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1506" name="KdG6P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1505" name="KdGL6P" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1504" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1503" name="KmG6P" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1502" name="KmGL6P" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1501" name="KmNADP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1500" name="KmNADPH" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1499" name="NADP" order="9" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1498" name="NADPH" order="10" role="product"/>
        <ParameterDescription key="FunctionParameter_1497" name="Vmax" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_165" name="Function for F6P_E4P_TKT" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_165">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T22:00:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*(E4P*tktC2-F6P*tkt/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1514" name="E4P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1513" name="F6P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1512" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1511" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1510" name="tkt" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1509" name="tktC2" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_166" name="Function for PFK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_166">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T22:03:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*n*(MgATP*F6P-MgADP*FDP/Keq)/(KirF6P*KmrATPMg)/(1+KmrFDP/KirFDP*(MgADP/KmrADP)+KmrF6P/KirF6P*(MgATP/KmrATPMg)+KmrFDP/KirFDP*(MgADP/KmrADP)*(F6P/KirF6P)+MgATP/KmrATPMg*(F6P/KirF6P)+MgADP/KirADP*(MgATP/KmrATPMg)*(F6P/KirF6P)+(1+(ATP-MgATP)/KirATP)*(F6P/KirF6P)+FDP/KirFDP+MgADP/KmrADP*(FDP/KirFDP)+KmrF6P/KirF6P*(MgATP/KmrATPMg)*(FDP/KirFDP)+Wr*(KmrF6P/KirF6P)*(MgADP/KirADP)*(MgATP/KmrATPMg)*(FDP/KmrFDP))/(1+L0*((1+KmtFDP/KitFDP*(MgADP/KmtADP)+KmtF6P/KitF6P*(MgATP/KmtATPMg)+KmtFDP/KitFDP*(MgADP/KmtADP)*(F6P/KitF6P)+MgATP/KmtATPMg*(F6P/KitF6P)+MgADP/KitADP*(MgATP/KmtATPMg)*(F6P/KitF6P)+(1+(ATP-MgATP)/KitATP)*(F6P/KitF6P)+FDP/KitFDP+MgADP/KmtADP*(FDP/KitFDP)+KmtF6P/KitF6P*(MgATP/KmtATPMg)*(FDP/KitFDP)+Wt*(KmtF6P/KitF6P)*(MgADP/KitADP)*(MgATP/KmtATPMg)*(FDP/KmtFDP))*(1+MgADP/KeftADP+PEP/KeftPEP+MgADP/KeftADP*(PEP/KeftPEP))/((1+KmrFDP/KirFDP*(MgADP/KmrADP)+KmrF6P*MgATP/(KirF6P*KmrATPMg)+KmrFDP/KirFDP*(MgADP/KmrADP)*(F6P/KirF6P)+MgATP/KmrATPMg*(F6P/KirF6P)+MgADP/KirADP*(MgATP/KmrATPMg)*(F6P/KirF6P)+(1+(ATP-MgATP)/KirATP)*(F6P/KirF6P)+FDP/KirFDP+MgADP/KmrADP*(FDP/KirFDP)+KmrF6P/KirF6P*(MgATP/KmrATPMg)*(FDP/KirFDP)+Wr*(KmrF6P/KirF6P)*(MgADP/KirADP)*(MgATP/KmrATPMg)*(FDP/KmrFDP))*(1+MgADP/KefrADP+PEP/KefrPEP+MgADP/KefrADP*(PEP/KefrPEP))))^n)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1546" name="ATP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1545" name="F6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1544" name="FDP" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1543" name="KefrADP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1542" name="KefrPEP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1541" name="KeftADP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1540" name="KeftPEP" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1539" name="Keq" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1538" name="KirADP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1537" name="KirATP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1536" name="KirF6P" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1535" name="KirFDP" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1534" name="KitADP" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1533" name="KitATP" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1532" name="KitF6P" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1531" name="KitFDP" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1530" name="KmrADP" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1529" name="KmrATPMg" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1528" name="KmrF6P" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1527" name="KmrFDP" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1526" name="KmtADP" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1525" name="KmtATPMg" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1524" name="KmtF6P" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_1523" name="KmtFDP" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_1522" name="L0" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_1521" name="MgADP" order="25" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1520" name="MgATP" order="26" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1519" name="PEP" order="27" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1518" name="Vmax" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_1517" name="Wr" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_1516" name="Wt" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_1515" name="n" order="31" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_167" name="Function for TPI" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_167">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(DAP-GAP/Keq)/KmDAP/(1+DAP/KmDAP+GAP/KmGAP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1552" name="DAP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1551" name="GAP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1550" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1549" name="KmDAP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1548" name="KmGAP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1547" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_168" name="Function for PCK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_168">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:54:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(MgATP*OAA-HCO3*MgADP*PEP/Keq)/(KmATP*KmOAA)/(1+HCO3/KmHCO3+HCO3/KmHCO3*(ADP/KmADP)+MgADP/KmADP+MgATP/KmATP+OAA/KmOAA+MgATP/KmATP*(OAA/KmOAA)+HCO3/KmHCO3*(PEP/KmPEP)+PEP/KmPEP+HCO3/KmHCO3*(MgADP/KmADP)*(PEP/KmPEP)+MgADP/KmADP*(PEP/KmPEP))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1565" name="ADP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1564" name="HCO3" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1563" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1562" name="KmADP" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1561" name="KmATP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1560" name="KmHCO3" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1559" name="KmOAA" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1558" name="KmPEP" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1557" name="MgADP" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1556" name="MgATP" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1555" name="OAA" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1554" name="PEP" order="11" role="product"/>
        <ParameterDescription key="FunctionParameter_1553" name="Vmax" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_169" name="Function for PPS" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_169">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:43:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(MgATP*PYR-AMP*PEP*P*MG/Keq)/(KmATPMg*KmPYR)/(MgATP/KmATPMg+alpha*(P/KdP)*(MgATP/KmATPMg)+alpha*(AMP/KdAMP)*(MgATP/KmATPMg)+alpha*(P/KdP)*(AMP/KdAMP)*(MgATP/KmATPMg)+alpha*(MG/KdMg)*(P/KmP)*(AMP/KdAMP)*(MgATP/KdATPMgPPS)/(W*(1+MG/KdMg))+MgATP/KmATPMg*(AKG/KefAKG)+(1+MG/KdMg)*(AKG/KefAKG)*(PEP/KmPEP)/W+MgATP/KmATPMg*(OAA/KefOAA)+(1+MG/KdMg)*(OAA/KefOAA)*(PEP/KmPEP)/W+MG/KdMg*(P/KmP)*(AMP/KdAMP)/W+alpha*(P/KdP)*(AMP/KdAMP)*(PEP/KmPEP)/W+alpha*(MG/KdMg)*(P/KmP)*(AMP/KdAMP)*(PEP/KmPEP)/W+alpha*(1+MG/KdMg)*(KmAMP/KdAMP*(P/KmP)*(PEP/KmPEP)+AMP/KdAMP*(PEP/KmPEP))/W+(1+MG/KdMg)*(PYR/KmPYR)+MgATP/KmATPMg*(PYR/KmPYR)+KdADPMg/KdMg*(P/KmP)*(MgADP/KefADP)*(AMP/KdAMP)/(W*(1+MG/KdMg))+(ADP-MgADP)/KefADP*(PYR/KmPYR)+KdATPMg/KdMg*(P/KmP)*(AMP/KdAMP)*(MgATP/KefATP)/(W*(1+MG/KdMg))+(ATP-MgATP)/KefATP*(PYR/KmPYR)+(1+MG/KdMg)*(PEP/KmPEP)/W+alpha*(1+MG/KdMg)*(PEP/KdPEP)*(PYR/KmPYR)+(1+MG/KdMg)*(PYR/KdPYR)*(PEP/KmPEP)/W)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1597" name="ADP" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1596" name="AKG" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1595" name="AMP" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1594" name="ATP" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1593" name="KdADPMg" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1592" name="KdAMP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1591" name="KdATPMg" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1590" name="KdATPMgPPS" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1589" name="KdMg" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1588" name="KdP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1587" name="KdPEP" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1586" name="KdPYR" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1585" name="KefADP" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1584" name="KefAKG" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1583" name="KefATP" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1582" name="KefOAA" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1581" name="Keq" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1580" name="KmAMP" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1579" name="KmATPMg" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1578" name="KmP" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1577" name="KmPEP" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1576" name="KmPYR" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1575" name="MG" order="22" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1574" name="MgADP" order="23" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1573" name="MgATP" order="24" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1572" name="OAA" order="25" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1571" name="P" order="26" role="product"/>
        <ParameterDescription key="FunctionParameter_1570" name="PEP" order="27" role="product"/>
        <ParameterDescription key="FunctionParameter_1569" name="PYR" order="28" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1568" name="Vmax" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_1567" name="W" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_1566" name="alpha" order="31" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_170" name="Function for PGK" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_170">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T08:49:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(MgADP*BPG-MgATP*PGA3/Keq)/(KmADPMg*KmBPG)/(1+MgADP/KmADPMg+BPG/KmBPG+MgADP/KmADPMg*BPG/KmBPG+MgATP/KmATPMg+PGA3/KmPGA3+MgATP/KmATPMg*PGA3/KmPGA3)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1607" name="BPG" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1606" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1605" name="KmADPMg" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1604" name="KmATPMg" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1603" name="KmBPG" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1602" name="KmPGA3" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1601" name="MgADP" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1600" name="MgATP" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1599" name="PGA3" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_1598" name="Vmax" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_172" name="Function for ENO" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_172">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(PGA2-PEP/Keq)/KmPGA2/(1+PGA2/KmPGA2+PEP/KmPEP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1623" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1622" name="KmPEP" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1621" name="KmPGA2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1620" name="PEP" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1619" name="PGA2" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1618" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_173" name="Function for PGL" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_173">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T22:03:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(GL6P-PGN/Keq)/KmGL6P/(1+GL6P/KmGL6P+PGN/KmPGN+G6P/KiG6P)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1631" name="G6P" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1630" name="GL6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1629" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1628" name="KiG6P" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1627" name="KmGL6P" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1626" name="KmPGN" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1625" name="PGN" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_1624" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_174" name="Function for S7P_R5P_TKT" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_174">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*(R5P*tktC2-S7P*tkt/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1637" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1636" name="R5P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1635" name="S7P" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_1634" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1633" name="tkt" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1632" name="tktC2" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_175" name="Function for F6P_GAP_TAL" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_175">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-12-29T22:00:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*(GAP*talC3-F6P*tal/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1643" name="F6P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1642" name="GAP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1641" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1640" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1639" name="tal" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_1638" name="talC3" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_176" name="Function for S7P_E4P_TAL" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_176">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        kcat*(S7P*tal-E4P*talC3/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1649" name="E4P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1648" name="Keq" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1647" name="S7P" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1646" name="kcat" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1645" name="tal" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1644" name="talC3" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_177" name="Function for FBP" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_177">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:42:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*n*MgFDP/KirFDPMg/(1+KmrFDP/KirFDP*(MG/KmrMg)+P/KirP+P/KirP*(MG/KirPMg)+F6P/KirF6P+F6P/KirF6P*(MG/KirF6PMg)+P/KirP*(F6P/KirPF6P)+P/KirP*(F6P/KirPF6P)*(MG/KirPF6PMg)+(FDP-MgFDP)/KirFDP+KdFDPMg/KmrMg*(MgFDP/KirFDP)+AMP/KirAMP+MgFDP/KirFDPMg+MgFDP/KirFDPMg*(MG/KirFDPMgMg)+AMP/KirAMP*((FDP-MgFDP)/KirAMPFDP))/(1+L0*((1+KmtFDP/KitFDP*(MG/KmtMg)+P/KitP+P/KitP*(MG/KitPMg)+F6P/KitF6P+F6P/KitF6P*(MG/KitF6PMg)+P/KitP*(F6P/KitPF6P)+P/KitP*(F6P/KitPF6P)*(MG/KitPF6PMg)+(FDP-MgFDP)/KitFDP+KdFDPMg/KmtMg*(MgFDP/KitFDP)+AMP/KitAMP+MgFDP/KitFDPMg+MgFDP/KitFDPMg*(MG/KitFDPMgMg)+AMP/KitAMP*((FDP-MgFDP)/KitAMPFDP))/(1+KmrFDP/KirFDP*(MG/KmrMg)+P/KirP+P/KirP*(MG/KirPMg)+F6P/KirF6P+F6P/KirF6P*(MG/KirF6PMg)+P/KirP*(F6P/KirPF6P)+P/KirP*(F6P/KirPF6P)*(MG/KirPF6PMg)+(FDP-MgFDP)/KirFDP+KdFDPMg/KmrMg*(MgFDP/KirFDP)+AMP/KirAMP+MgFDP/KirFDPMg+MgFDP/KirFDPMg*(MG/KirFDPMgMg)+AMP/KirAMP*((FDP-MgFDP)/KirAMPFDP)))^n)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1685" name="AMP" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1684" name="F6P" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_1683" name="FDP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1682" name="KdFDPMg" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1681" name="KirAMP" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1680" name="KirAMPFDP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1679" name="KirF6P" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1678" name="KirF6PMg" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1677" name="KirFDP" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1676" name="KirFDPMg" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1675" name="KirFDPMgMg" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1674" name="KirP" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1673" name="KirPF6P" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1672" name="KirPF6PMg" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1671" name="KirPMg" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1670" name="KitAMP" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1669" name="KitAMPFDP" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1668" name="KitF6P" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1667" name="KitF6PMg" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1666" name="KitFDP" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1665" name="KitFDPMg" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1664" name="KitFDPMgMg" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1663" name="KitP" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_1662" name="KitPF6P" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_1661" name="KitPF6PMg" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_1660" name="KitPMg" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_1659" name="KmrFDP" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_1658" name="KmrMg" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_1657" name="KmtFDP" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_1656" name="KmtMg" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_1655" name="L0" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_1654" name="MG" order="31" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1653" name="MgFDP" order="32" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1652" name="P" order="33" role="product"/>
        <ParameterDescription key="FunctionParameter_1651" name="Vmax" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_1650" name="n" order="35" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_178" name="Function for MQO" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_178">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T17:17:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(MAL*Q-OAA*QH2/Keq)/(KmMAL*KmQ)/((1+MAL/KmMAL)*(1+Q/KmQ)+(1+OAA/KmOAA)*(1+QH2/KmQH2)-1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1695" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1694" name="KmMAL" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1693" name="KmOAA" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1692" name="KmQ" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1691" name="KmQH2" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1690" name="MAL" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1689" name="OAA" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_1688" name="Q" order="7" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1687" name="QH2" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_1686" name="Vmax" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_179" name="Function for MDH" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_179">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:52:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(NADH*OAA-MAL*NAD/Keq)/(KiNADH*KmOAA)/(1+KmNAD/KiNAD*(MAL/KmMAL)+NAD/KiNAD+MAL/KmMAL*(NAD/KiNAD)+NADH/KiNADH+KmNAD/KiNAD*(MAL/KmMAL)*(NADH/KiNADH)+KmNADH/KiNADH*(OAA/KmOAA)+KmNADH/KiNADH*(NAD/KiNAD)*(OAA/KmOAA)+MAL*NAD*OAA/(KiNAD*KiOAA*KmMAL)+NADH/KiNADH*(OAA/KmOAA)+Keq*(KiNADH*KmOAA/(KiNAD*KmMAL))*(KmNAD/KiNAD)*(MAL/KmMAL)*(NADH/KmNADH)*(OAA/KiOAA))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1708" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1707" name="KiNAD" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1706" name="KiNADH" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1705" name="KiOAA" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1704" name="KmMAL" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1703" name="KmNAD" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1702" name="KmNADH" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1701" name="KmOAA" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1700" name="MAL" order="8" role="product"/>
        <ParameterDescription key="FunctionParameter_1699" name="NAD" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1698" name="NADH" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1697" name="OAA" order="11" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1696" name="Vmax" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_180" name="Function for RPE" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_180">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(RU5P-X5P/Keq)/KmRU5P/(1+RU5P/KmRU5P+X5P/KmX5P)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1714" name="Keq" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_1713" name="KmRU5P" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_1712" name="KmX5P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1711" name="RU5P" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1710" name="Vmax" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1709" name="X5P" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_181" name="Function for MAD" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_181">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:46:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*n*MAL*NAD/(KmrMAL*KirNAD)/(1+KmrNAD/KirNAD*(MAL/KmrMAL)+NAD/KirNAD+MAL/KmrMAL*(NAD/KirNAD))*((MG/KmrMg+MN/KmrMn)/(1+MG/KmrMg+MN/KmrMn))/(1+L0*((1+ASP/KeftASP)*(1+MG/KmtMg+MN/KmtMn)*(1+ATP/KeftATP)*(1+ACCOA/KeftACCOA+COA/KeftCOA)*(1+KmtNAD/KitNAD*(MAL/KmtMAL)+NAD/KitNAD+MAL/KmtMAL*(NAD/KitNAD))/((1+ASP/KefrASP)*(1+MG/KmrMg+MN/KmrMn)*(1+ATP/KefrATP)*(1+ACCOA/KefrACCOA+COA/KefrCOA)*(1+KmrNAD/KirNAD*(MAL/KmrMAL)+NAD/KirNAD+MAL/KmrMAL*(NAD/KirNAD))))^n)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1743" name="ACCOA" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1742" name="ASP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1741" name="ATP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1740" name="COA" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1739" name="KefrACCOA" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1738" name="KefrASP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1737" name="KefrATP" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1736" name="KefrCOA" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1735" name="KeftACCOA" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1734" name="KeftASP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1733" name="KeftATP" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1732" name="KeftCOA" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1731" name="KirNAD" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1730" name="KitNAD" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1729" name="KmrMAL" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1728" name="KmrMg" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_1727" name="KmrMn" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_1726" name="KmrNAD" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_1725" name="KmtMAL" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_1724" name="KmtMg" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_1723" name="KmtMn" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_1722" name="KmtNAD" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_1721" name="L0" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_1720" name="MAL" order="23" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1719" name="MG" order="24" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1718" name="MN" order="25" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1717" name="NAD" order="26" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1716" name="Vmax" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_1715" name="n" order="28" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_182" name="Function for PGI_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_182">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(G6P-F6P/Keq)/KmG6P/(1+F6P/KmF6P+G6P/KmG6P+PEP/KmPEP+PGN/KmPGN)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1754" name="F6P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1755" name="G6P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1756" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1757" name="KmF6P" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1758" name="KmG6P" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1759" name="KmPEP" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1760" name="KmPGN" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1761" name="PEP" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1762" name="PGN" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1763" name="Vmax" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_183" name="Function for ACN_1_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_183">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(CIT-ACO/Keq)/KmCIT_ACN/(1+CIT/KmCIT_ACN+ACO/KmACO_ACN+ICIT/KmICIT_ACN)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1923" name="ACO" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1988" name="CIT" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1989" name="ICIT" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1921" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1751" name="KmACO_ACN" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2002" name="KmCIT_ACN" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1991" name="KmICIT_ACN" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1788" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_184" name="Function for ACN_2_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_184">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACO-ICIT/Keq)/KmACO_ACN/(1+ACO/KmACO_ACN+ICIT/KmICIT_ACN+CIT/KmCIT_ACN)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1790" name="ACO" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2018" name="CIT" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2017" name="ICIT" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_2016" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2015" name="KmACO_ACN" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2014" name="KmCIT_ACN" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2013" name="KmICIT_ACN" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2012" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_185" name="Function for SDH_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_185">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(SUC*FAD-FUM*FADH2/Keq)/(KefSUC*KmQ)/(1+FUM/KefFUM+KmSUC/KefSUC*(FAD/KmQ)+KmFUM/KefFUM*(FADH2/KmQH2)+FUM/KefFUM*(FADH2/KmQH2)+SUC/KefSUC+SUC/KefSUC*(FAD/KmQ))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1752" name="FAD" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1992" name="FADH2" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2243" name="FUM" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_2242" name="KefFUM" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2241" name="KefSUC" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2240" name="Keq" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2239" name="KmFUM" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2238" name="KmQ" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2237" name="KmQH2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2236" name="KmSUC" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_2235" name="SUC" order="10" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2234" name="Vmax" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_186" name="Function for NDH1_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_186">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax/(1+(log(Hout/Hin)/log(10))^2)*(NADH*Q-NAD*QH2/KeqNDH)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2341" name="Hin" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2340" name="Hout" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2339" name="KeqNDH" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2338" name="NAD" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_1987" name="NADH" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2311" name="Q" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2312" name="QH2" order="6" role="product"/>
        <ParameterDescription key="FunctionParameter_2214" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_187" name="Function for ATP_SYN_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_187">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(log(Hout/Hin)/log(10))^4/(1+(log(Hout/Hin)/log(10))^4)*(ADP*P-ATP/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2360" name="ADP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2361" name="ATP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2211" name="Hin" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_2371" name="Hout" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2372" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2373" name="P" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2374" name="Vmax" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_188" name="Function for CYA_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_188">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k*(ATP-CAMP*P^2/Keq)*eiiaP/(eiiaP+KaeiiaP)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2382" name="ATP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2383" name="CAMP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2384" name="KaeiiaP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2385" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2386" name="P" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_2387" name="eiiaP" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2388" name="k" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_189" name="Function for PTS_4_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_189">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        cell*(kF*eiicbP*GLCp/(KmGLC+GLCp)-kR*eiicb*G6P/(KmG6P+G6P))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2453" name="G6P" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_2454" name="GLCp" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2455" name="KmG6P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2456" name="KmGLC" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2457" name="cell" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_2458" name="eiicb" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_2459" name="eiicbP" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2460" name="kF" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2461" name="kR" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_190" name="Function for CYTBO_1" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_190">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax/(1+(log(Hout/Hin)/log(10))^2)*(QH2^2*O2-Q^2/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2472" name="Hin" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2473" name="Hout" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2474" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2475" name="O2" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2476" name="Q" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_2477" name="QH2" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2478" name="Vmax" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_191" name="Function for SQR_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_191">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(FADH2*Q-FAD*QH2/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2359" name="FAD" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_2486" name="FADH2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2487" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2488" name="Q" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2489" name="QH2" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_2490" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_192" name="Function for NDH2_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_192">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(NADH*Q-NAD*QH2/KeqNDH)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2497" name="KeqNDH" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_2498" name="NAD" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2499" name="NADH" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2500" name="Q" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2501" name="QH2" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_2502" name="Vmax" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_193" name="Function for GROWTH_1" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_193">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*G6P*E4P*PGA3*OAA*AKG*PYR*R5P*PEP*GAP*F6P*NADPH*ACCOA*NAD*ATP/(KmG6P*KmE4P*KmPGA3*KmOAA*KmAKG*KmPYR*KmR5P*KmPEP*KmGAP*KmF6P*KmNADPH*KmACCOA*KmNAD*KmATP)/((1+G6P/KmG6P)*(1+E4P/KmE4P)*(1+PGA3/KmPGA3)*(1+OAA/KmOAA)*(1+AKG/KmAKG)*(1+PYR/KmPYR)*(1+R5P/KmR5P)*(1+PEP/KmPEP)*(1+GAP/KmGAP)*(1+F6P/KmF6P)*(1+NADPH/KmNADPH)*(1+ACCOA/KmACCOA)*(1+NAD/KmNAD)*(1+ATP/KmATP))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2532" name="ACCOA" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2533" name="AKG" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2534" name="ATP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2535" name="E4P" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2536" name="F6P" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2537" name="G6P" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2538" name="GAP" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2539" name="KmACCOA" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2540" name="KmAKG" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2541" name="KmATP" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_2542" name="KmE4P" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_2543" name="KmF6P" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_2544" name="KmG6P" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_2545" name="KmGAP" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_2546" name="KmNAD" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_2547" name="KmNADPH" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_2548" name="KmOAA" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_2549" name="KmPEP" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_2550" name="KmPGA3" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_2551" name="KmPYR" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_2552" name="KmR5P" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_2553" name="NAD" order="21" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2554" name="NADPH" order="22" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2555" name="OAA" order="23" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2556" name="PEP" order="24" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2557" name="PGA3" order="25" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2558" name="PYR" order="26" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2559" name="R5P" order="27" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2560" name="Vmax" order="28" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_194" name="Function for ATP_MAINTENANCE_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_194">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ATP-ADP*P/Keq)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2449" name="ADP" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_2514" name="ATP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2516" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2524" name="P" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_2523" name="Vmax" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_195" name="Function for XCH_RMM_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_195">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(GLCx/Km-GLCp/Km)/(1+GLCx/Km+GLCp/Km)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2509" name="GLCp" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_2526" name="GLCx" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2518" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2527" name="Vmax" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_196" name="Function for PIT_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_196">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*((log(Hout/Hin)/log(10))^2/(1+(log(Hout/Hin)/log(10))^2)*(Pp/(KmPp+Pp))-Kr/(1+(log(Hout/Hin)/log(10))^2)*(P/(KmP+P)))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2517" name="Hin" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_1873" name="Hout" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2515" name="KmP" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2590" name="KmPp" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2591" name="Kr" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2592" name="P" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_2593" name="Pp" order="6" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2594" name="Vmax" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_197" name="Function for XCH_RMM_2" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_197">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(Px/Km-Pp/Km)/(1+Px/Km+Pp/Km)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2512" name="Km" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_2450" name="Pp" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2511" name="Px" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2471" name="Vmax" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_198" name="Function for XCH_RMM_3" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_198">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACEx/Km-ACEp/Km)/(1+ACEx/Km+ACEp/Km)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2607" name="ACEp" order="0" role="product"/>
        <ParameterDescription key="FunctionParameter_2608" name="ACEx" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2609" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2610" name="Vmax" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_199" name="Function for XCH_RMM_4" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_199">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vmax*(ACEp/Km-ACEx_0/Km)/(1+ACEp/Km+ACEx_0/Km)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2617" name="ACEp" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2618" name="ACEx_0" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_2619" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2620" name="Vmax" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_200" name="Function for GL6P_HYDROLYSIS_1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_200">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        KGl6Phydrol*(GL6P-PGN/KeqGl6Phydrol)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_2625" name="GL6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_2626" name="KGl6Phydrol" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_2627" name="KeqGl6Phydrol" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_2628" name="PGN" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Millard2017 - E. coli central carbon and energy metabolism" simulationType="time" timeUnit="s" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221408570000002e+23">
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
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/doi/10.1371/journal.pcbi.1005396"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-05-10T22:00:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
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
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>millard@insa-toulouse.fr</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Millard</vCard:Family>
                <vCard:Given>Pierre</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>INRA</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>kieran.smallbone@manchester.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Smallbone</vCard:Family>
                <vCard:Given>Kieran</vCard:Given>
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
        <dcterms:W3CDTF>2015-05-10T22:00:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2017-02-22T10:26:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/biomodels.db/MODEL1505110000"/>
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml"><p>This model is described in:</p>
       <p>Millard P, Smallbone K, Mendes P (2017)  <a href="http://identifiers.org/doi/10.1371/journal.pcbi.1005396">Metabolic regulation is
    sufficient for global and robust coordination of glucose
    uptake, catabolism, energy production and growth in <i>Escherichia
    coli</i>.</a> PLOS Computational Biology 13(2):e1005396</p>
</body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_3" name="cell_cytoplasm" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:22:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_2" name="extracellular" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:22:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_0" name="cell_periplasm" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-16T10:08:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_121" name="ACCOA" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-17T08:09:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_120" name="ACO" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_120">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:22:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_119" name="ACP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:22:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_118" name="AKG" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_118">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-17T08:08:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_117" name="BPG" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_117">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T14:57:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_116" name="CIT" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_115" name="DAP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:03:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_114" name="E4P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_114">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-16T11:41:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_113" name="F6P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_113">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:25:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_112" name="FDP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_112">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:49:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_111" name="FUM" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_110" name="G6P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"/>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_109" name="GAP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_109">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:12:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_108" name="GL6P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_108">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:53:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_107" name="GLX" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:53:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_106" name="ICIT" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T14:59:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_105" name="KDPG" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-24T10:12:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_104" name="MAL" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_103" name="NAD" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_103">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:44:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_102" name="NADH" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_102">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T23:44:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_101" name="NADP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_101">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T17:09:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_100" name="NADPH" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_100">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:58:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_99" name="OAA" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_99">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:45:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_98" name="PEP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_98">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-24T16:37:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_97" name="PGA2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_96" name="PGA3" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_95" name="PGN" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_94" name="PYR" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_94">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-31T12:41:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_93" name="Q" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:12:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_92" name="QH2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:12:53Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_91" name="R5P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_90" name="RU5P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" />
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_89" name="S7P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_89">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-24T10:25:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_88" name="SUC" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_88">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:46:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_87" name="SUCCOA" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_87">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T13:47:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_86" name="X5P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-22T20:51:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_85" name="ei" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T14:56:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_84" name="eiP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_83" name="eiia" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-16T09:44:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="eiiaP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="eiicb" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T20:23:19Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="eiicbP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:48:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="hpr" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="hprP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-10T10:15:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_0" name="icd" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:53:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="icdP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:53:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="tal" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T10:37:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="talC3" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T10:37:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="tkt" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T10:37:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="tktC2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T10:37:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="ADP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="AMP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="ATP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_14" name="CAMP" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="COA" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T14:35:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="HCO3" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:47:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="P" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:45:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_10" name="MG" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:50:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="MgADP" simulationType="assignment" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T00:28:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>*&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ADP],Reference=Concentration>/(&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdADPMg],Reference=Value>+&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>)
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="MgATP" simulationType="assignment" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-23T11:39:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>*&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ATP],Reference=Concentration>/(&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdATPMg],Reference=Value>+&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>)
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="MgFDP" simulationType="assignment" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T00:28:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>*&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[FDP],Reference=Concentration>/(&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdFDPMg],Reference=Value>+&lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG],Reference=Concentration>)
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="ASP" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:17:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="CYS" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-16T14:03:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="MN" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-27T11:44:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_34" name="Hin" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:15:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_35" name="H2O" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:15:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_36" name="O2" simulationType="fixed" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:59:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="FAD" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T15:23:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="FADH2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T15:23:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="ACE" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T12:22:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="GLCx" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:49:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="Px" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-24T10:32:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_72" name="ACEx" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_72">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:04:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_73" name="Hout" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_73">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:15:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="GLCp" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-23T16:11:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="Pp" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-31T12:41:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="ACEp" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:12:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_13" name="FEED" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T10:22:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="KdADPMg" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T19:54:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="KdATPMg" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-20T18:47:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="KdFDPMg" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-20T18:47:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="KmICIT_ACN" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-13T02:18:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="KmCIT_ACN" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-13T02:18:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="KmACO_ACN" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-13T02:19:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="KeqNDH" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-25T10:29:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_218" name="PGI" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_218">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:08:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_110" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_113" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_98" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_95" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7101" name="Keq" value="0.36"/>
          <Constant key="Parameter_7094" name="KmF6P" value="0.147"/>
          <Constant key="Parameter_7087" name="KmG6P" value="0.28"/>
          <Constant key="Parameter_7083" name="KmPEP" value="1.999"/>
          <Constant key="Parameter_7106" name="Vmax" value="2.32456"/>
          <Constant key="Parameter_7084" name="KmPGN" value="0.515958"/>
        </ListOfConstants>
        <KineticLaw function="Function_182" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1754">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1755">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1756">
              <SourceParameter reference="Parameter_7101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1757">
              <SourceParameter reference="Parameter_7094"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1758">
              <SourceParameter reference="Parameter_7087"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1759">
              <SourceParameter reference="Parameter_7083"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1760">
              <SourceParameter reference="Parameter_7084"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1761">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1762">
              <SourceParameter reference="Metabolite_95"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1763">
              <SourceParameter reference="Parameter_7106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_219" name="PFK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_219">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-07T10:52:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_113" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_112" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_98" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7111" name="KefrADP" value="0.0735264"/>
          <Constant key="Parameter_7100" name="KefrPEP" value="19.98"/>
          <Constant key="Parameter_7109" name="KeftADP" value="9.009"/>
          <Constant key="Parameter_7090" name="KeftPEP" value="0.26026"/>
          <Constant key="Parameter_7105" name="Keq" value="1998"/>
          <Constant key="Parameter_7088" name="KirADP" value="54.945"/>
          <Constant key="Parameter_7103" name="KirATP" value="2.4975e-05"/>
          <Constant key="Parameter_7092" name="KirF6P" value="1.84615"/>
          <Constant key="Parameter_7089" name="KirFDP" value="0.045954"/>
          <Constant key="Parameter_7098" name="KitADP" value="80.08"/>
          <Constant key="Parameter_7046" name="KitATP" value="0.014014"/>
          <Constant key="Parameter_7047" name="KitF6P" value="0.00856856"/>
          <Constant key="Parameter_7043" name="KitFDP" value="50.5505"/>
          <Constant key="Parameter_7037" name="KmrADP" value="0.690009"/>
          <Constant key="Parameter_7038" name="KmrATPMg" value="8.12187e-05"/>
          <Constant key="Parameter_7048" name="KmrF6P" value="2.05205e-05"/>
          <Constant key="Parameter_7042" name="KmrFDP" value="10.01"/>
          <Constant key="Parameter_7041" name="KmtADP" value="2.002"/>
          <Constant key="Parameter_7044" name="KmtATPMg" value="3.34334"/>
          <Constant key="Parameter_7039" name="KmtF6P" value="32.967"/>
          <Constant key="Parameter_7052" name="KmtFDP" value="9.99"/>
          <Constant key="Parameter_7050" name="L0" value="14.0851"/>
          <Constant key="Parameter_7049" name="Vmax" value="0.185253"/>
          <Constant key="Parameter_7045" name="Wr" value="0.0237041"/>
          <Constant key="Parameter_7051" name="Wt" value="0.146735"/>
          <Constant key="Parameter_7070" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_166" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1546">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1545">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1544">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1543">
              <SourceParameter reference="Parameter_7111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1542">
              <SourceParameter reference="Parameter_7100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1541">
              <SourceParameter reference="Parameter_7109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1540">
              <SourceParameter reference="Parameter_7090"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1539">
              <SourceParameter reference="Parameter_7105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1538">
              <SourceParameter reference="Parameter_7088"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1537">
              <SourceParameter reference="Parameter_7103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1536">
              <SourceParameter reference="Parameter_7092"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1535">
              <SourceParameter reference="Parameter_7089"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1534">
              <SourceParameter reference="Parameter_7098"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1533">
              <SourceParameter reference="Parameter_7046"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1532">
              <SourceParameter reference="Parameter_7047"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1531">
              <SourceParameter reference="Parameter_7043"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1530">
              <SourceParameter reference="Parameter_7037"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1529">
              <SourceParameter reference="Parameter_7038"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1528">
              <SourceParameter reference="Parameter_7048"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1527">
              <SourceParameter reference="Parameter_7042"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1526">
              <SourceParameter reference="Parameter_7041"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1525">
              <SourceParameter reference="Parameter_7044"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1524">
              <SourceParameter reference="Parameter_7039"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1523">
              <SourceParameter reference="Parameter_7052"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1522">
              <SourceParameter reference="Parameter_7050"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1521">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1520">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1519">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1518">
              <SourceParameter reference="Parameter_7049"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1517">
              <SourceParameter reference="Parameter_7045"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1516">
              <SourceParameter reference="Parameter_7051"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1515">
              <SourceParameter reference="Parameter_7070"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_220" name="FBA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_220">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-07T10:49:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_112" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_115" stoichiometry="1"/>
          <Product metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_98" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7110" name="Keq" value="0.18981"/>
          <Constant key="Parameter_7104" name="KmDAP" value="0.13001"/>
          <Constant key="Parameter_7097" name="KmFDP" value="0.12012"/>
          <Constant key="Parameter_7091" name="KmGAP" value="0.13001"/>
          <Constant key="Parameter_7058" name="KmPEP" value="0.5"/>
          <Constant key="Parameter_7066" name="Vmax" value="21.6978"/>
        </ListOfConstants>
        <KineticLaw function="Function_156" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1377">
              <SourceParameter reference="Metabolite_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1376">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1375">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1374">
              <SourceParameter reference="Parameter_7110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1373">
              <SourceParameter reference="Parameter_7104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1372">
              <SourceParameter reference="Parameter_7097"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1371">
              <SourceParameter reference="Parameter_7091"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1370">
              <SourceParameter reference="Parameter_7058"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1369">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1368">
              <SourceParameter reference="Parameter_7066"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_221" name="TPI" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_221">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-07T10:49:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_115" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7073" name="Keq" value="0.270203"/>
          <Constant key="Parameter_7024" name="KmDAP" value="0.01"/>
          <Constant key="Parameter_6809" name="KmGAP" value="1.89301"/>
          <Constant key="Parameter_7054" name="Vmax" value="24.1843"/>
        </ListOfConstants>
        <KineticLaw function="Function_167" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1552">
              <SourceParameter reference="Metabolite_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1551">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1550">
              <SourceParameter reference="Parameter_7073"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1549">
              <SourceParameter reference="Parameter_7024"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1548">
              <SourceParameter reference="Parameter_6809"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1547">
              <SourceParameter reference="Parameter_7054"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_222" name="GDH" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_222">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T17:03:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_109" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_117" stoichiometry="1"/>
          <Product metabolite="Metabolite_102" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7055" name="Keq" value="20"/>
          <Constant key="Parameter_7059" name="KmBPG" value="0.2"/>
          <Constant key="Parameter_7072" name="KmGAP" value="2.47265"/>
          <Constant key="Parameter_7063" name="KmNAD" value="0.0110454"/>
          <Constant key="Parameter_7061" name="KmNADH" value="3.69797"/>
          <Constant key="Parameter_7074" name="KmP" value="0.017"/>
          <Constant key="Parameter_7060" name="Vmax" value="8.66573"/>
        </ListOfConstants>
        <KineticLaw function="Function_154" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1345">
              <SourceParameter reference="Metabolite_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1344">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1343">
              <SourceParameter reference="Parameter_7055"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1342">
              <SourceParameter reference="Parameter_7059"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1341">
              <SourceParameter reference="Parameter_7072"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1340">
              <SourceParameter reference="Parameter_7063"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1339">
              <SourceParameter reference="Parameter_7061"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1338">
              <SourceParameter reference="Parameter_7074"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1337">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1336">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1335">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1334">
              <SourceParameter reference="Parameter_7060"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_223" name="PGK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_223">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-14T17:46:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_117" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_96" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7112" name="Keq" value="99.9925"/>
          <Constant key="Parameter_7062" name="KmADPMg" value="0.085416"/>
          <Constant key="Parameter_7023" name="KmATPMg" value="3.47737"/>
          <Constant key="Parameter_7065" name="KmBPG" value="0.0113296"/>
          <Constant key="Parameter_7064" name="KmPGA3" value="2.45722"/>
          <Constant key="Parameter_7057" name="Vmax" value="16.1089"/>
        </ListOfConstants>
        <KineticLaw function="Function_170" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1607">
              <SourceParameter reference="Metabolite_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1606">
              <SourceParameter reference="Parameter_7112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1605">
              <SourceParameter reference="Parameter_7062"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1604">
              <SourceParameter reference="Parameter_7023"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1603">
              <SourceParameter reference="Parameter_7065"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1602">
              <SourceParameter reference="Parameter_7064"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1601">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1600">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1599">
              <SourceParameter reference="Metabolite_96"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1598">
              <SourceParameter reference="Parameter_7057"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_224" name="GPM" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_224">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-24T12:56:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_96" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_97" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7053" name="Keq" value="0.565818"/>
          <Constant key="Parameter_7071" name="KmPGA2" value="1.9153"/>
          <Constant key="Parameter_7016" name="KmPGA3" value="0.115"/>
          <Constant key="Parameter_7056" name="Vmax" value="10.9934"/>
        </ListOfConstants>
        <KineticLaw function="Function_152" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1319">
              <SourceParameter reference="Parameter_7053"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1318">
              <SourceParameter reference="Parameter_7071"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1317">
              <SourceParameter reference="Parameter_7016"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1316">
              <SourceParameter reference="Metabolite_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1315">
              <SourceParameter reference="Metabolite_96"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1314">
              <SourceParameter reference="Parameter_7056"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_225" name="ENO" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_225">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T20:00:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_97" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_98" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7040" name="Keq" value="3"/>
          <Constant key="Parameter_7022" name="KmPEP" value="0.1"/>
          <Constant key="Parameter_7033" name="KmPGA2" value="0.1"/>
          <Constant key="Parameter_6984" name="Vmax" value="11.7189"/>
        </ListOfConstants>
        <KineticLaw function="Function_172" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1623">
              <SourceParameter reference="Parameter_7040"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1622">
              <SourceParameter reference="Parameter_7022"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1621">
              <SourceParameter reference="Parameter_7033"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1620">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1619">
              <SourceParameter reference="Metabolite_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1618">
              <SourceParameter reference="Parameter_6984"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_226" name="PYK" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_226">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-08T11:11:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_98" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_112" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_110" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_108" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_91" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_90" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_89" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_87" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7034" name="KefrFDP" value="0.449149"/>
          <Constant key="Parameter_6983" name="KefrG6P" value="0.158746"/>
          <Constant key="Parameter_6980" name="KefrGL6P" value="0.150482"/>
          <Constant key="Parameter_6985" name="KefrR5P" value="9.33254"/>
          <Constant key="Parameter_6990" name="KefrRU5P" value="1.53591"/>
          <Constant key="Parameter_7035" name="KefrS7P" value="0.0785955"/>
          <Constant key="Parameter_7031" name="KefrX5P" value="0.677374"/>
          <Constant key="Parameter_7029" name="KeftATP" value="3.69117"/>
          <Constant key="Parameter_7036" name="KeftSUCCOA" value="8.26406"/>
          <Constant key="Parameter_7032" name="KirADP" value="0.517585"/>
          <Constant key="Parameter_7030" name="KirATP" value="96.0333"/>
          <Constant key="Parameter_7026" name="KirPEP" value="0.181056"/>
          <Constant key="Parameter_7028" name="KirPYR" value="15.1403"/>
          <Constant key="Parameter_7017" name="KirPyrATP" value="230.781"/>
          <Constant key="Parameter_7025" name="KitADP" value="0.224911"/>
          <Constant key="Parameter_7027" name="KitATP" value="0.039564"/>
          <Constant key="Parameter_7021" name="KitPEP" value="0.465672"/>
          <Constant key="Parameter_7020" name="KitPYR" value="0.2499"/>
          <Constant key="Parameter_7019" name="KitPyrATP" value="11.3691"/>
          <Constant key="Parameter_7018" name="KmrADPMg" value="0.326144"/>
          <Constant key="Parameter_7003" name="KmrPEP" value="5.56368e-07"/>
          <Constant key="Parameter_6989" name="KmtADPMg" value="0.054678"/>
          <Constant key="Parameter_6932" name="KmtPEP" value="0.11475"/>
          <Constant key="Parameter_6994" name="L0" value="50.4818"/>
          <Constant key="Parameter_7005" name="Vmax" value="0.74716"/>
          <Constant key="Parameter_6964" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_151" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1313">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1312">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1311">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1310">
              <SourceParameter reference="Metabolite_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1309">
              <SourceParameter reference="Parameter_7034"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1308">
              <SourceParameter reference="Parameter_6983"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1307">
              <SourceParameter reference="Parameter_6980"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1306">
              <SourceParameter reference="Parameter_6985"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1305">
              <SourceParameter reference="Parameter_6990"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1304">
              <SourceParameter reference="Parameter_7035"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1303">
              <SourceParameter reference="Parameter_7031"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1302">
              <SourceParameter reference="Parameter_7029"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1301">
              <SourceParameter reference="Parameter_7036"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1300">
              <SourceParameter reference="Parameter_7032"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1299">
              <SourceParameter reference="Parameter_7030"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1298">
              <SourceParameter reference="Parameter_7026"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1297">
              <SourceParameter reference="Parameter_7028"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1296">
              <SourceParameter reference="Parameter_7017"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1295">
              <SourceParameter reference="Parameter_7025"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1294">
              <SourceParameter reference="Parameter_7027"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1293">
              <SourceParameter reference="Parameter_7021"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1292">
              <SourceParameter reference="Parameter_7020"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1291">
              <SourceParameter reference="Parameter_7019"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1290">
              <SourceParameter reference="Parameter_7018"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1289">
              <SourceParameter reference="Parameter_7003"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1288">
              <SourceParameter reference="Parameter_6989"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1287">
              <SourceParameter reference="Parameter_6932"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1286">
              <SourceParameter reference="Parameter_6994"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1285">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1284">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1283">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1282">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1281">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1280">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1279">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1278">
              <SourceParameter reference="Metabolite_87"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1277">
              <SourceParameter reference="Parameter_7005"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1276">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1275">
              <SourceParameter reference="Parameter_6964"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_227" name="ZWF" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_227">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:06:06Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_110" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_108" stoichiometry="1"/>
          <Product metabolite="Metabolite_100" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6981" name="KdG6P" value="0.192"/>
          <Constant key="Parameter_6934" name="KdGL6P" value="0.02"/>
          <Constant key="Parameter_6910" name="Keq" value="6e+10"/>
          <Constant key="Parameter_6914" name="KmG6P" value="0.118525"/>
          <Constant key="Parameter_7004" name="KmGL6P" value="0.328629"/>
          <Constant key="Parameter_6997" name="KmNADP" value="0.0274"/>
          <Constant key="Parameter_6996" name="KmNADPH" value="0.0168"/>
          <Constant key="Parameter_6995" name="Vmax" value="0.2658"/>
        </ListOfConstants>
        <KineticLaw function="Function_164" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1508">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1507">
              <SourceParameter reference="Metabolite_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1506">
              <SourceParameter reference="Parameter_6981"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1505">
              <SourceParameter reference="Parameter_6934"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1504">
              <SourceParameter reference="Parameter_6910"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1503">
              <SourceParameter reference="Parameter_6914"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1502">
              <SourceParameter reference="Parameter_7004"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1501">
              <SourceParameter reference="Parameter_6997"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1500">
              <SourceParameter reference="Parameter_6996"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1499">
              <SourceParameter reference="Metabolite_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1498">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1497">
              <SourceParameter reference="Parameter_6995"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_228" name="PGL" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_228">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-05T14:31:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_108" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_95" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_110" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6922" name="Keq" value="42.7572"/>
          <Constant key="Parameter_6965" name="KiG6P" value="2.0001"/>
          <Constant key="Parameter_6986" name="KmGL6P" value="0.022977"/>
          <Constant key="Parameter_6992" name="KmPGN" value="9.99"/>
          <Constant key="Parameter_6937" name="Vmax" value="11.5967"/>
        </ListOfConstants>
        <KineticLaw function="Function_173" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1631">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1630">
              <SourceParameter reference="Metabolite_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1629">
              <SourceParameter reference="Parameter_6922"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1628">
              <SourceParameter reference="Parameter_6965"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1627">
              <SourceParameter reference="Parameter_6986"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1626">
              <SourceParameter reference="Parameter_6992"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1625">
              <SourceParameter reference="Metabolite_95"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1624">
              <SourceParameter reference="Parameter_6937"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_229" name="GND" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_229">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:44:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_101" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_95" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_100" stoichiometry="1"/>
          <Product metabolite="Metabolite_90" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_112" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7008" name="KdHCO3" value="58.8951"/>
          <Constant key="Parameter_7000" name="KdHCO3NADPH" value="9.7257"/>
          <Constant key="Parameter_7001" name="KdNADP" value="0.116989"/>
          <Constant key="Parameter_6935" name="KdNADPH" value="0.00340034"/>
          <Constant key="Parameter_6987" name="KdRu5P" value="0.0440044"/>
          <Constant key="Parameter_6971" name="KefATP" value="0.0650065"/>
          <Constant key="Parameter_7012" name="KefFbP" value="0.0129987"/>
          <Constant key="Parameter_6957" name="KefNADPATP" value="0.139986"/>
          <Constant key="Parameter_6958" name="KefNADPFbP" value="0.00519948"/>
          <Constant key="Parameter_7006" name="Keq" value="49.962"/>
          <Constant key="Parameter_7002" name="KmHCO3" value="6.41899"/>
          <Constant key="Parameter_6991" name="KmNADP" value="0.049"/>
          <Constant key="Parameter_6979" name="KmNADPH" value="68.3828"/>
          <Constant key="Parameter_7009" name="KmPGN" value="0.093"/>
          <Constant key="Parameter_6999" name="KmRU5P" value="45.1977"/>
          <Constant key="Parameter_6956" name="Vmax" value="4.08105"/>
        </ListOfConstants>
        <KineticLaw function="Function_158" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1408">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1407">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1406">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1405">
              <SourceParameter reference="Parameter_7008"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1404">
              <SourceParameter reference="Parameter_7000"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1403">
              <SourceParameter reference="Parameter_7001"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1402">
              <SourceParameter reference="Parameter_6935"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1401">
              <SourceParameter reference="Parameter_6987"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1400">
              <SourceParameter reference="Parameter_6971"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1399">
              <SourceParameter reference="Parameter_7012"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1398">
              <SourceParameter reference="Parameter_6957"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1397">
              <SourceParameter reference="Parameter_6958"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1396">
              <SourceParameter reference="Parameter_7006"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1395">
              <SourceParameter reference="Parameter_7002"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1394">
              <SourceParameter reference="Parameter_6991"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1393">
              <SourceParameter reference="Parameter_6979"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1392">
              <SourceParameter reference="Parameter_7009"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1391">
              <SourceParameter reference="Parameter_6999"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1390">
              <SourceParameter reference="Metabolite_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1389">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1388">
              <SourceParameter reference="Metabolite_95"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1387">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1386">
              <SourceParameter reference="Parameter_6956"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_230" name="RPE" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_230">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-21T14:42:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_90" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6942" name="Keq" value="1.5015"/>
          <Constant key="Parameter_7015" name="KmRU5P" value="0.872522"/>
          <Constant key="Parameter_6975" name="KmX5P" value="0.893607"/>
          <Constant key="Parameter_6936" name="Vmax" value="6.00103"/>
        </ListOfConstants>
        <KineticLaw function="Function_180" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1714">
              <SourceParameter reference="Parameter_6942"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1713">
              <SourceParameter reference="Parameter_7015"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1712">
              <SourceParameter reference="Parameter_6975"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1711">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1710">
              <SourceParameter reference="Parameter_6936"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1709">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_231" name="RPI" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_231">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-22T20:48:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_90" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_91" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_114" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7013" name="Keq" value="0.330093"/>
          <Constant key="Parameter_6941" name="KmE4P" value="0.67067"/>
          <Constant key="Parameter_6940" name="KmR5P" value="3.09715"/>
          <Constant key="Parameter_6982" name="KmRU5P" value="4.40263"/>
          <Constant key="Parameter_7014" name="Vmax" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_135" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1163">
              <SourceParameter reference="Metabolite_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1162">
              <SourceParameter reference="Parameter_7013"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1161">
              <SourceParameter reference="Parameter_6941"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1160">
              <SourceParameter reference="Parameter_6940"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1159">
              <SourceParameter reference="Parameter_6982"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1158">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1157">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1156">
              <SourceParameter reference="Parameter_7014"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_232" name="X5P_GAP_TKT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_232">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T11:51:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_109" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3582" name="Keq" value="1.001"/>
          <Constant key="Parameter_3584" name="kcat" value="40"/>
        </ListOfConstants>
        <KineticLaw function="Function_136" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1169">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1168">
              <SourceParameter reference="Parameter_3582"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1167">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1166">
              <SourceParameter reference="Parameter_3584"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1165">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1164">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_233" name="F6P_E4P_TKT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_233">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T20:00:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_114" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_113" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3587" name="Keq" value="0.5005"/>
          <Constant key="Parameter_6948" name="kcat" value="40.0002"/>
        </ListOfConstants>
        <KineticLaw function="Function_165" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1514">
              <SourceParameter reference="Metabolite_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1513">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1512">
              <SourceParameter reference="Parameter_3587"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1511">
              <SourceParameter reference="Parameter_6948"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1510">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1509">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_234" name="S7P_R5P_TKT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_234">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T18:41:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_91" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3583" name="Keq" value="0.33033"/>
          <Constant key="Parameter_3585" name="kcat" value="199.979"/>
        </ListOfConstants>
        <KineticLaw function="Function_174" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1637">
              <SourceParameter reference="Parameter_3583"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1636">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1635">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1634">
              <SourceParameter reference="Parameter_3585"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1633">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1632">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_235" name="F6P_GAP_TAL" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_235">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-27T11:53:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_109" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_113" stoichiometry="1"/>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3586" name="Keq" value="0.11011"/>
          <Constant key="Parameter_3588" name="kcat" value="119.992"/>
        </ListOfConstants>
        <KineticLaw function="Function_175" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1643">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1642">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1641">
              <SourceParameter reference="Parameter_3586"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1640">
              <SourceParameter reference="Parameter_3588"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1639">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1638">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_236" name="S7P_E4P_TAL" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_236">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-09T18:41:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_89" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_114" stoichiometry="1"/>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3597" name="Keq" value="26.6266"/>
          <Constant key="Parameter_3593" name="kcat" value="99.9991"/>
        </ListOfConstants>
        <KineticLaw function="Function_176" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1649">
              <SourceParameter reference="Metabolite_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1648">
              <SourceParameter reference="Parameter_3597"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1647">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1646">
              <SourceParameter reference="Parameter_3593"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1645">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1644">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_237" name="FBP" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_237">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T17:07:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_112" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_113" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_16" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_10" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3590" name="KirAMP" value="0.00122122"/>
          <Constant key="Parameter_3592" name="KirAMPFDP" value="0.256256"/>
          <Constant key="Parameter_3632" name="KirF6P" value="1.12112"/>
          <Constant key="Parameter_3595" name="KirF6PMg" value="0.384615"/>
          <Constant key="Parameter_3594" name="KirFDP" value="1.35327"/>
          <Constant key="Parameter_3589" name="KirFDPMg" value="0.75924"/>
          <Constant key="Parameter_3598" name="KirFDPMgMg" value="0.356356"/>
          <Constant key="Parameter_3591" name="KirP" value="3.16316"/>
          <Constant key="Parameter_7099" name="KirPF6P" value="6.60538"/>
          <Constant key="Parameter_7120" name="KirPF6PMg" value="48.4484"/>
          <Constant key="Parameter_7095" name="KirPMg" value="0.856"/>
          <Constant key="Parameter_7114" name="KitAMP" value="0.000255"/>
          <Constant key="Parameter_7102" name="KitAMPFDP" value="690"/>
          <Constant key="Parameter_7113" name="KitF6P" value="0.304"/>
          <Constant key="Parameter_7093" name="KitF6PMg" value="315"/>
          <Constant key="Parameter_7075" name="KitFDP" value="0.043101"/>
          <Constant key="Parameter_7121" name="KitFDPMg" value="0.00642"/>
          <Constant key="Parameter_7108" name="KitFDPMgMg" value="100"/>
          <Constant key="Parameter_7096" name="KitP" value="0.642"/>
          <Constant key="Parameter_7107" name="KitPF6P" value="0.00689"/>
          <Constant key="Parameter_7078" name="KitPF6PMg" value="16.5"/>
          <Constant key="Parameter_7115" name="KitPMg" value="539"/>
          <Constant key="Parameter_7076" name="KmrFDP" value="0.0636141"/>
          <Constant key="Parameter_3633" name="KmrMg" value="0.039039"/>
          <Constant key="Parameter_3637" name="KmtFDP" value="1e-05"/>
          <Constant key="Parameter_3641" name="KmtMg" value="55.055"/>
          <Constant key="Parameter_4107" name="L0" value="0.000815"/>
          <Constant key="Parameter_4104" name="Vmax" value="0.215583"/>
          <Constant key="Parameter_4026" name="n" value="4"/>
          <Constant key="Parameter_4103" name="KdFDPMg" value="5.81"/>
        </ListOfConstants>
        <KineticLaw function="Function_177" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1685">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1684">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1683">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1682">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1681">
              <SourceParameter reference="Parameter_3590"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1680">
              <SourceParameter reference="Parameter_3592"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1679">
              <SourceParameter reference="Parameter_3632"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1678">
              <SourceParameter reference="Parameter_3595"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1677">
              <SourceParameter reference="Parameter_3594"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1676">
              <SourceParameter reference="Parameter_3589"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1675">
              <SourceParameter reference="Parameter_3598"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1674">
              <SourceParameter reference="Parameter_3591"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1673">
              <SourceParameter reference="Parameter_7099"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1672">
              <SourceParameter reference="Parameter_7120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1671">
              <SourceParameter reference="Parameter_7095"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1670">
              <SourceParameter reference="Parameter_7114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1669">
              <SourceParameter reference="Parameter_7102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1668">
              <SourceParameter reference="Parameter_7113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1667">
              <SourceParameter reference="Parameter_7093"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1666">
              <SourceParameter reference="Parameter_7075"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1665">
              <SourceParameter reference="Parameter_7121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1664">
              <SourceParameter reference="Parameter_7108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1663">
              <SourceParameter reference="Parameter_7096"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1662">
              <SourceParameter reference="Parameter_7107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1661">
              <SourceParameter reference="Parameter_7078"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1660">
              <SourceParameter reference="Parameter_7115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1659">
              <SourceParameter reference="Parameter_7076"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1658">
              <SourceParameter reference="Parameter_3633"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1657">
              <SourceParameter reference="Parameter_3637"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1656">
              <SourceParameter reference="Parameter_3641"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1655">
              <SourceParameter reference="Parameter_4107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1654">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1653">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1652">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1651">
              <SourceParameter reference="Parameter_4104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1650">
              <SourceParameter reference="Parameter_4026"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_238" name="PPC" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_238">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:45:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_98" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_116" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_112" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_111" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_104" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_88" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4215" name="KdrOAA" value="4.35404"/>
          <Constant key="Parameter_4105" name="KdrPEP" value="655.591"/>
          <Constant key="Parameter_3566" name="KdtOAA" value="17.9127"/>
          <Constant key="Parameter_4108" name="KdtPEP" value="0.0121991"/>
          <Constant key="Parameter_3574" name="KefrACCOA" value="0.140029"/>
          <Constant key="Parameter_3579" name="KefrASP" value="0.389183"/>
          <Constant key="Parameter_3568" name="KefrCIT" value="34.4277"/>
          <Constant key="Parameter_3576" name="KefrCYS" value="0.000448843"/>
          <Constant key="Parameter_3564" name="KefrFDP" value="9.99126"/>
          <Constant key="Parameter_3580" name="KefrFDPACCOA" value="0.0156251"/>
          <Constant key="Parameter_3639" name="KefrFUM" value="2.7475"/>
          <Constant key="Parameter_3573" name="KefrMAL" value="0.23002"/>
          <Constant key="Parameter_3602" name="KefrSUC" value="22.9834"/>
          <Constant key="Parameter_3635" name="KeftACCOA" value="1.27598"/>
          <Constant key="Parameter_3636" name="KeftASP" value="27.4729"/>
          <Constant key="Parameter_3617" name="KeftCIT" value="0.521945"/>
          <Constant key="Parameter_3640" name="KeftCYS" value="0.977374"/>
          <Constant key="Parameter_3599" name="KeftFDP" value="13.2064"/>
          <Constant key="Parameter_3628" name="KeftFDPACCOA" value="47.7563"/>
          <Constant key="Parameter_3630" name="KeftFUM" value="9.76119"/>
          <Constant key="Parameter_3631" name="KeftMAL" value="0.737283"/>
          <Constant key="Parameter_3618" name="KeftSUC" value="107.18"/>
          <Constant key="Parameter_3638" name="Keq" value="149.705"/>
          <Constant key="Parameter_3601" name="KmrHCO3" value="0.00219811"/>
          <Constant key="Parameter_3634" name="KmrOAA" value="13.0469"/>
          <Constant key="Parameter_3629" name="KmrP" value="0.663356"/>
          <Constant key="Parameter_3627" name="KmrPEP" value="3.20089"/>
          <Constant key="Parameter_3603" name="KmtHCO3" value="0.00220031"/>
          <Constant key="Parameter_3600" name="KmtOAA" value="6.80995"/>
          <Constant key="Parameter_3605" name="KmtP" value="0.285131"/>
          <Constant key="Parameter_3622" name="KmtPEP" value="5.12497"/>
          <Constant key="Parameter_4591" name="L0" value="6.37209e-06"/>
          <Constant key="Parameter_3624" name="Vmax" value="21.439"/>
          <Constant key="Parameter_4584" name="n" value="4.00319"/>
        </ListOfConstants>
        <KineticLaw function="Function_159" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1454">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1453">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1452">
              <SourceParameter reference="Metabolite_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1451">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1450">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1449">
              <SourceParameter reference="Metabolite_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1448">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1447">
              <SourceParameter reference="Parameter_4215"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1446">
              <SourceParameter reference="Parameter_4105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1445">
              <SourceParameter reference="Parameter_3566"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1444">
              <SourceParameter reference="Parameter_4108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1443">
              <SourceParameter reference="Parameter_3574"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1442">
              <SourceParameter reference="Parameter_3579"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1441">
              <SourceParameter reference="Parameter_3568"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1440">
              <SourceParameter reference="Parameter_3576"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1439">
              <SourceParameter reference="Parameter_3564"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1438">
              <SourceParameter reference="Parameter_3580"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1437">
              <SourceParameter reference="Parameter_3639"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1436">
              <SourceParameter reference="Parameter_3573"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1435">
              <SourceParameter reference="Parameter_3602"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1434">
              <SourceParameter reference="Parameter_3635"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1433">
              <SourceParameter reference="Parameter_3636"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1432">
              <SourceParameter reference="Parameter_3617"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1431">
              <SourceParameter reference="Parameter_3640"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1430">
              <SourceParameter reference="Parameter_3599"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1429">
              <SourceParameter reference="Parameter_3628"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1428">
              <SourceParameter reference="Parameter_3630"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1427">
              <SourceParameter reference="Parameter_3631"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1426">
              <SourceParameter reference="Parameter_3618"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1425">
              <SourceParameter reference="Parameter_3638"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1424">
              <SourceParameter reference="Parameter_3601"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1423">
              <SourceParameter reference="Parameter_3634"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1422">
              <SourceParameter reference="Parameter_3629"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1421">
              <SourceParameter reference="Parameter_3627"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1420">
              <SourceParameter reference="Parameter_3603"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1419">
              <SourceParameter reference="Parameter_3600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1418">
              <SourceParameter reference="Parameter_3605"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1417">
              <SourceParameter reference="Parameter_3622"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1416">
              <SourceParameter reference="Parameter_4591"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1415">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1414">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1413">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1412">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1411">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1410">
              <SourceParameter reference="Parameter_3624"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1409">
              <SourceParameter reference="Parameter_4584"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_239" name="PCK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_239">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:46:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_98" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4583" name="Keq" value="1.88166"/>
          <Constant key="Parameter_4595" name="KmADP" value="0.04997"/>
          <Constant key="Parameter_3619" name="KmATP" value="0.0600418"/>
          <Constant key="Parameter_4572" name="KmHCO3" value="2.6319"/>
          <Constant key="Parameter_4576" name="KmOAA" value="0.66966"/>
          <Constant key="Parameter_3604" name="KmPEP" value="0.0699833"/>
          <Constant key="Parameter_4586" name="Vmax" value="8.08777"/>
        </ListOfConstants>
        <KineticLaw function="Function_168" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1565">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1564">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1563">
              <SourceParameter reference="Parameter_4583"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1562">
              <SourceParameter reference="Parameter_4595"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1561">
              <SourceParameter reference="Parameter_3619"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1560">
              <SourceParameter reference="Parameter_4572"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1559">
              <SourceParameter reference="Parameter_4576"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1558">
              <SourceParameter reference="Parameter_3604"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1557">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1556">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1555">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1554">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1553">
              <SourceParameter reference="Parameter_4586"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_240" name="PPS" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_240">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:57:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
          <Product metabolite="Metabolite_98" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_118" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_99" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_10" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3612" name="KdAMP" value="1480"/>
          <Constant key="Parameter_3621" name="KdATPMgPPS" value="0.0549"/>
          <Constant key="Parameter_3625" name="KdMg" value="36.9"/>
          <Constant key="Parameter_3608" name="KdP" value="346"/>
          <Constant key="Parameter_3610" name="KdPEP" value="95.7"/>
          <Constant key="Parameter_3611" name="KdPYR" value="2740"/>
          <Constant key="Parameter_3620" name="KefADP" value="0.0283"/>
          <Constant key="Parameter_3615" name="KefAKG" value="0.274"/>
          <Constant key="Parameter_3606" name="KefATP" value="0.000628"/>
          <Constant key="Parameter_3614" name="KefOAA" value="0.796"/>
          <Constant key="Parameter_3613" name="Keq" value="200000"/>
          <Constant key="Parameter_3616" name="KmAMP" value="0.000384"/>
          <Constant key="Parameter_3623" name="KmATPMg" value="0.0549"/>
          <Constant key="Parameter_3642" name="KmP" value="84.4"/>
          <Constant key="Parameter_3645" name="KmPEP" value="20.7"/>
          <Constant key="Parameter_3609" name="KmPYR" value="0.229"/>
          <Constant key="Parameter_3596" name="Vmax" value="0.0163772"/>
          <Constant key="Parameter_3626" name="W" value="10"/>
          <Constant key="Parameter_3607" name="alpha" value="38900"/>
          <Constant key="Parameter_3647" name="KdADPMg" value="1.27771"/>
          <Constant key="Parameter_3644" name="KdATPMg" value="0.0847634"/>
        </ListOfConstants>
        <KineticLaw function="Function_169" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1597">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1596">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1595">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1594">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1593">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1592">
              <SourceParameter reference="Parameter_3612"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1591">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1590">
              <SourceParameter reference="Parameter_3621"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1589">
              <SourceParameter reference="Parameter_3625"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1588">
              <SourceParameter reference="Parameter_3608"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1587">
              <SourceParameter reference="Parameter_3610"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1586">
              <SourceParameter reference="Parameter_3611"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1585">
              <SourceParameter reference="Parameter_3620"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1584">
              <SourceParameter reference="Parameter_3615"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1583">
              <SourceParameter reference="Parameter_3606"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1582">
              <SourceParameter reference="Parameter_3614"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1581">
              <SourceParameter reference="Parameter_3613"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1580">
              <SourceParameter reference="Parameter_3616"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1579">
              <SourceParameter reference="Parameter_3623"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1578">
              <SourceParameter reference="Parameter_3642"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1577">
              <SourceParameter reference="Parameter_3645"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1576">
              <SourceParameter reference="Parameter_3609"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1575">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1574">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1573">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1572">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1571">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1570">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1569">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1568">
              <SourceParameter reference="Parameter_3596"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1567">
              <SourceParameter reference="Parameter_3626"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1566">
              <SourceParameter reference="Parameter_3607"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_241" name="MAE" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_241">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:56:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_104" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_102" stoichiometry="1"/>
          <Product metabolite="Metabolite_94" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_10" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3651" name="KefrACCOA" value="1.83336"/>
          <Constant key="Parameter_3646" name="KefrASP" value="0.362142"/>
          <Constant key="Parameter_3650" name="KefrATP" value="88.9752"/>
          <Constant key="Parameter_3648" name="KefrCOA" value="0.268"/>
          <Constant key="Parameter_3649" name="KeftACCOA" value="0.197"/>
          <Constant key="Parameter_3643" name="KeftASP" value="0.583"/>
          <Constant key="Parameter_3653" name="KeftATP" value="0.26"/>
          <Constant key="Parameter_3652" name="KeftCOA" value="0.268"/>
          <Constant key="Parameter_3655" name="KirNAD" value="0.636457"/>
          <Constant key="Parameter_3654" name="KitNAD" value="0.990398"/>
          <Constant key="Parameter_3656" name="KmrMAL" value="0.212913"/>
          <Constant key="Parameter_3658" name="KmrMg" value="0.191871"/>
          <Constant key="Parameter_3661" name="KmrMn" value="0.272568"/>
          <Constant key="Parameter_3660" name="KmrNAD" value="1.36636"/>
          <Constant key="Parameter_3657" name="KmtMAL" value="0.093"/>
          <Constant key="Parameter_4565" name="KmtMg" value="2.37681"/>
          <Constant key="Parameter_4568" name="KmtMn" value="0.410198"/>
          <Constant key="Parameter_4571" name="KmtNAD" value="0.108"/>
          <Constant key="Parameter_4564" name="L0" value="19.9"/>
          <Constant key="Parameter_3515" name="Vmax" value="6.64269"/>
          <Constant key="Parameter_3186" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_181" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1743">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1742">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1741">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1740">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1739">
              <SourceParameter reference="Parameter_3651"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1738">
              <SourceParameter reference="Parameter_3646"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1737">
              <SourceParameter reference="Parameter_3650"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1736">
              <SourceParameter reference="Parameter_3648"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1735">
              <SourceParameter reference="Parameter_3649"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1734">
              <SourceParameter reference="Parameter_3643"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1733">
              <SourceParameter reference="Parameter_3653"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1732">
              <SourceParameter reference="Parameter_3652"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1731">
              <SourceParameter reference="Parameter_3655"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1730">
              <SourceParameter reference="Parameter_3654"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1729">
              <SourceParameter reference="Parameter_3656"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1728">
              <SourceParameter reference="Parameter_3658"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1727">
              <SourceParameter reference="Parameter_3661"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1726">
              <SourceParameter reference="Parameter_3660"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1725">
              <SourceParameter reference="Parameter_3657"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1724">
              <SourceParameter reference="Parameter_4565"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1723">
              <SourceParameter reference="Parameter_4568"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1722">
              <SourceParameter reference="Parameter_4571"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1721">
              <SourceParameter reference="Parameter_4564"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1720">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1719">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1718">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1717">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1716">
              <SourceParameter reference="Parameter_3515"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1715">
              <SourceParameter reference="Parameter_3186"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_242" name="PDH" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_242">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:47:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_121" stoichiometry="1"/>
          <Product metabolite="Metabolite_102" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3445" name="Keq" value="3138.16"/>
          <Constant key="Parameter_3347" name="KmACCOA" value="10.174"/>
          <Constant key="Parameter_4578" name="KmCOA" value="0.00500461"/>
          <Constant key="Parameter_4577" name="KmHCO3" value="0.00545112"/>
          <Constant key="Parameter_3960" name="KmNAD" value="0.00999"/>
          <Constant key="Parameter_7565" name="KmNADH" value="6.63512"/>
          <Constant key="Parameter_3019" name="KmPYR" value="2"/>
          <Constant key="Parameter_7574" name="Vmax" value="961.706"/>
        </ListOfConstants>
        <KineticLaw function="Function_153" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1333">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1332">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1331">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1330">
              <SourceParameter reference="Parameter_3445"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1329">
              <SourceParameter reference="Parameter_3347"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1328">
              <SourceParameter reference="Parameter_4578"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1327">
              <SourceParameter reference="Parameter_4577"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1326">
              <SourceParameter reference="Parameter_3960"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1325">
              <SourceParameter reference="Parameter_7565"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1324">
              <SourceParameter reference="Parameter_3019"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1323">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1322">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1321">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1320">
              <SourceParameter reference="Parameter_7574"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_243" name="GLT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_243">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:45:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_121" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_116" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_118" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_102" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3233" name="KdACCOA0" value="0.699309"/>
          <Constant key="Parameter_3011" name="KdcsCIT" value="7.38128"/>
          <Constant key="Parameter_3260" name="KdcsCOA" value="0.00174282"/>
          <Constant key="Parameter_3231" name="KdcsOAA" value="0.154601"/>
          <Constant key="Parameter_3212" name="Keq" value="83067.1"/>
          <Constant key="Parameter_3244" name="Ki1AKG" value="0.0150083"/>
          <Constant key="Parameter_3239" name="Ki1NADH" value="0.000330313"/>
          <Constant key="Parameter_3252" name="Ki2AKG" value="0.256252"/>
          <Constant key="Parameter_3230" name="Ki2NADH" value="0.0504"/>
          <Constant key="Parameter_3237" name="KiATP" value="0.579939"/>
          <Constant key="Parameter_3241" name="KmACCOA0" value="0.119974"/>
          <Constant key="Parameter_3909" name="KmOAA0" value="0.00123458"/>
          <Constant key="Parameter_4054" name="KmcsCIT" value="1.15715"/>
          <Constant key="Parameter_3494" name="KmcsCOA" value="9.6344e-05"/>
          <Constant key="Parameter_3257" name="Vmax" value="57.0584"/>
        </ListOfConstants>
        <KineticLaw function="Function_155" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1367">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1366">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1365">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1364">
              <SourceParameter reference="Metabolite_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1363">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1362">
              <SourceParameter reference="Parameter_3233"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1361">
              <SourceParameter reference="Parameter_3011"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1360">
              <SourceParameter reference="Parameter_3260"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1359">
              <SourceParameter reference="Parameter_3231"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1358">
              <SourceParameter reference="Parameter_3212"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1357">
              <SourceParameter reference="Parameter_3244"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1356">
              <SourceParameter reference="Parameter_3239"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1355">
              <SourceParameter reference="Parameter_3252"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1354">
              <SourceParameter reference="Parameter_3230"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1353">
              <SourceParameter reference="Parameter_3237"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1352">
              <SourceParameter reference="Parameter_3241"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1351">
              <SourceParameter reference="Parameter_3909"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1350">
              <SourceParameter reference="Parameter_4054"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1349">
              <SourceParameter reference="Parameter_3494"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1348">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1347">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1346">
              <SourceParameter reference="Parameter_3257"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_244" name="ACN_1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_244">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T20:01:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_116" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_120" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_106" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7578" name="Keq" value="0.384503"/>
          <Constant key="Parameter_6858" name="Vmax" value="9.72413"/>
          <Constant key="Parameter_3234" name="KmACO_ACN" value="0.02001"/>
          <Constant key="Parameter_3240" name="KmCIT_ACN" value="0.0628882"/>
          <Constant key="Parameter_3248" name="KmICIT_ACN" value="9.31352"/>
        </ListOfConstants>
        <KineticLaw function="Function_183" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1923">
              <SourceParameter reference="Metabolite_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1988">
              <SourceParameter reference="Metabolite_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1989">
              <SourceParameter reference="Metabolite_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1921">
              <SourceParameter reference="Parameter_7578"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1751">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2002">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1991">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1788">
              <SourceParameter reference="Parameter_6858"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_245" name="ACN_2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_245">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:56:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_120" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_106" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_116" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3022" name="Keq" value="3.49183"/>
          <Constant key="Parameter_3249" name="Vmax" value="9.86571"/>
          <Constant key="Parameter_3250" name="KmACO_ACN" value="0.02001"/>
          <Constant key="Parameter_3686" name="KmCIT_ACN" value="0.0628882"/>
          <Constant key="Parameter_6860" name="KmICIT_ACN" value="9.31352"/>
        </ListOfConstants>
        <KineticLaw function="Function_184" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1790">
              <SourceParameter reference="Metabolite_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2018">
              <SourceParameter reference="Metabolite_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2017">
              <SourceParameter reference="Metabolite_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2016">
              <SourceParameter reference="Parameter_3022"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2015">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2014">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2013">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2012">
              <SourceParameter reference="Parameter_3249"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_246" name="ICD" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_246">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T09:23:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_106" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_118" stoichiometry="1"/>
          <Product metabolite="Metabolite_100" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7553" name="Keq" value="28.1631"/>
          <Constant key="Parameter_4065" name="KmAKG" value="0.038038"/>
          <Constant key="Parameter_3235" name="KmICIT" value="0.010989"/>
          <Constant key="Parameter_3232" name="KmNADP" value="0.005994"/>
          <Constant key="Parameter_7119" name="KmNADPH" value="0.000683333"/>
          <Constant key="Parameter_3238" name="kcat" value="2461.97"/>
        </ListOfConstants>
        <KineticLaw function="Function_162" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1487">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1486">
              <SourceParameter reference="Metabolite_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1485">
              <SourceParameter reference="Parameter_7553"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1484">
              <SourceParameter reference="Parameter_4065"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1483">
              <SourceParameter reference="Parameter_3235"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1482">
              <SourceParameter reference="Parameter_3232"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1481">
              <SourceParameter reference="Parameter_7119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1480">
              <SourceParameter reference="Metabolite_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1479">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1478">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1477">
              <SourceParameter reference="Parameter_3238"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_247" name="LPD" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_247">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T17:04:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_118" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_102" stoichiometry="1"/>
          <Product metabolite="Metabolite_87" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4376" name="KdAKG" value="14.9386"/>
          <Constant key="Parameter_3498" name="KmAKG" value="0.020002"/>
          <Constant key="Parameter_7579" name="KmCOA" value="0.0760076"/>
          <Constant key="Parameter_7576" name="KmNAD" value="0.0980098"/>
          <Constant key="Parameter_7566" name="Vmax" value="0.0684413"/>
          <Constant key="Parameter_7573" name="alpha" value="16.4304"/>
        </ListOfConstants>
        <KineticLaw function="Function_163" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1496">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1495">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1494">
              <SourceParameter reference="Parameter_4376"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1493">
              <SourceParameter reference="Parameter_3498"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1492">
              <SourceParameter reference="Parameter_7579"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1491">
              <SourceParameter reference="Parameter_7576"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1490">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1489">
              <SourceParameter reference="Parameter_7566"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1488">
              <SourceParameter reference="Parameter_7573"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_248" name="SK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_248">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:20:56Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_87" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
          <Product metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3236" name="Keq" value="1.15994"/>
          <Constant key="Parameter_7575" name="KmADP" value="0.00868475"/>
          <Constant key="Parameter_6838" name="KmATP" value="0.102321"/>
          <Constant key="Parameter_3464" name="KmCOA" value="0.255019"/>
          <Constant key="Parameter_3145" name="KmP" value="0.914709"/>
          <Constant key="Parameter_7564" name="KmSUC" value="0.800744"/>
          <Constant key="Parameter_4512" name="KmSUCCOA" value="0.0085"/>
          <Constant key="Parameter_7606" name="Vmax" value="76.8163"/>
        </ListOfConstants>
        <KineticLaw function="Function_160" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1468">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1467">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1466">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1465">
              <SourceParameter reference="Parameter_3236"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1464">
              <SourceParameter reference="Parameter_7575"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1463">
              <SourceParameter reference="Parameter_6838"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1462">
              <SourceParameter reference="Parameter_3464"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1461">
              <SourceParameter reference="Parameter_3145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1460">
              <SourceParameter reference="Parameter_7564"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1459">
              <SourceParameter reference="Parameter_4512"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1458">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1457">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1456">
              <SourceParameter reference="Metabolite_87"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1455">
              <SourceParameter reference="Parameter_7606"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_249" name="SDH" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_249">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T15:38:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_111" stoichiometry="1"/>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3468" name="KefFUM" value="0.067048"/>
          <Constant key="Parameter_3143" name="KefSUC" value="0.0322425"/>
          <Constant key="Parameter_3024" name="Keq" value="2250"/>
          <Constant key="Parameter_7585" name="KmFUM" value="1.36019"/>
          <Constant key="Parameter_7563" name="KmQ" value="0.00160718"/>
          <Constant key="Parameter_3327" name="KmQH2" value="0.00611663"/>
          <Constant key="Parameter_7600" name="KmSUC" value="0.805727"/>
          <Constant key="Parameter_3148" name="Vmax" value="1.56184"/>
        </ListOfConstants>
        <KineticLaw function="Function_185" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1752">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1992">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2243">
              <SourceParameter reference="Metabolite_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2242">
              <SourceParameter reference="Parameter_3468"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2241">
              <SourceParameter reference="Parameter_3143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2240">
              <SourceParameter reference="Parameter_3024"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2239">
              <SourceParameter reference="Parameter_7585"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2238">
              <SourceParameter reference="Parameter_7563"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2237">
              <SourceParameter reference="Parameter_3327"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2236">
              <SourceParameter reference="Parameter_7600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2235">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2234">
              <SourceParameter reference="Parameter_3148"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_250" name="FUMA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_250">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-07T12:23:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_111" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_104" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7571" name="Keq" value="4.99966"/>
          <Constant key="Parameter_7572" name="KmFUM" value="0.6"/>
          <Constant key="Parameter_7543" name="KmMAL" value="0.7"/>
          <Constant key="Parameter_3015" name="Vmax" value="53.3414"/>
        </ListOfConstants>
        <KineticLaw function="Function_133" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1139">
              <SourceParameter reference="Metabolite_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1138">
              <SourceParameter reference="Parameter_7571"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1137">
              <SourceParameter reference="Parameter_7572"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1136">
              <SourceParameter reference="Parameter_7543"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1135">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1134">
              <SourceParameter reference="Parameter_3015"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_251" name="MQO" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_251">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:57:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_104" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_92" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3474" name="Keq" value="9"/>
          <Constant key="Parameter_3154" name="KmMAL" value="0.435"/>
          <Constant key="Parameter_6845" name="KmOAA" value="75.8036"/>
          <Constant key="Parameter_3472" name="KmQ" value="0.0414"/>
          <Constant key="Parameter_3497" name="KmQH2" value="8.77942"/>
          <Constant key="Parameter_3127" name="Vmax" value="4.62283"/>
        </ListOfConstants>
        <KineticLaw function="Function_178" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1695">
              <SourceParameter reference="Parameter_3474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1694">
              <SourceParameter reference="Parameter_3154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1693">
              <SourceParameter reference="Parameter_6845"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1692">
              <SourceParameter reference="Parameter_3472"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1691">
              <SourceParameter reference="Parameter_3497"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1690">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1689">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1688">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1687">
              <SourceParameter reference="Metabolite_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1686">
              <SourceParameter reference="Parameter_3127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_252" name="MDH" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_252">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:59:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_92" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_104" stoichiometry="1"/>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_103" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_102" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3922" name="Keq" value="100000"/>
          <Constant key="Parameter_3155" name="KiNAD" value="0.0233122"/>
          <Constant key="Parameter_3138" name="KiNADH" value="0.000196981"/>
          <Constant key="Parameter_3471" name="KiOAA" value="2.46446"/>
          <Constant key="Parameter_3020" name="KmMAL" value="0.86"/>
          <Constant key="Parameter_3165" name="KmNAD" value="0.64"/>
          <Constant key="Parameter_3493" name="KmNADH" value="0.003"/>
          <Constant key="Parameter_3016" name="KmOAA" value="0.001"/>
          <Constant key="Parameter_3153" name="Vmax" value="6.11492"/>
        </ListOfConstants>
        <KineticLaw function="Function_179" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1708">
              <SourceParameter reference="Parameter_3922"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1707">
              <SourceParameter reference="Parameter_3155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1706">
              <SourceParameter reference="Parameter_3138"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1705">
              <SourceParameter reference="Parameter_3471"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1704">
              <SourceParameter reference="Parameter_3020"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1703">
              <SourceParameter reference="Parameter_3165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1702">
              <SourceParameter reference="Parameter_3493"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1701">
              <SourceParameter reference="Parameter_3016"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1700">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1699">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1698">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1697">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1696">
              <SourceParameter reference="Parameter_3153"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_253" name="ACEA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_253">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T10:03:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_106" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_107" stoichiometry="1"/>
          <Product metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_98" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_96" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3021" name="KdICITsuc" value="0.00489074"/>
          <Constant key="Parameter_3457" name="KdPEP" value="1.05105"/>
          <Constant key="Parameter_3473" name="KdPEPglx" value="0.0358555"/>
          <Constant key="Parameter_3491" name="KdPEPicit" value="0.164263"/>
          <Constant key="Parameter_3162" name="KdPGA3" value="0.8"/>
          <Constant key="Parameter_3455" name="KdSUC" value="0.53053"/>
          <Constant key="Parameter_3452" name="Keq" value="8.8088"/>
          <Constant key="Parameter_3131" name="KmGLX" value="0.13013"/>
          <Constant key="Parameter_3027" name="KmICIT" value="0.063063"/>
          <Constant key="Parameter_3146" name="KmSUC" value="0.58941"/>
          <Constant key="Parameter_3133" name="Vmax" value="1.52595"/>
        </ListOfConstants>
        <KineticLaw function="Function_134" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1155">
              <SourceParameter reference="Metabolite_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1154">
              <SourceParameter reference="Metabolite_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1153">
              <SourceParameter reference="Parameter_3021"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1152">
              <SourceParameter reference="Parameter_3457"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1151">
              <SourceParameter reference="Parameter_3473"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1150">
              <SourceParameter reference="Parameter_3491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1149">
              <SourceParameter reference="Parameter_3162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1148">
              <SourceParameter reference="Parameter_3455"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1147">
              <SourceParameter reference="Parameter_3452"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1146">
              <SourceParameter reference="Parameter_3131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1145">
              <SourceParameter reference="Parameter_3027"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1144">
              <SourceParameter reference="Parameter_3146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1143">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1142">
              <SourceParameter reference="Metabolite_96"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1141">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1140">
              <SourceParameter reference="Parameter_3133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_254" name="ACEB" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_254">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T11:32:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_121" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
          <Product metabolite="Metabolite_104" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3135" name="Keq" value="230000"/>
          <Constant key="Parameter_3144" name="KmACCOA" value="0.009"/>
          <Constant key="Parameter_7193" name="KmCOA" value="10.5652"/>
          <Constant key="Parameter_3167" name="KmGLX" value="0.021"/>
          <Constant key="Parameter_3168" name="KmMAL" value="15.0572"/>
          <Constant key="Parameter_3169" name="Vmax" value="0.352769"/>
        </ListOfConstants>
        <KineticLaw function="Function_143" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1219">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1218">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1217">
              <SourceParameter reference="Metabolite_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1216">
              <SourceParameter reference="Parameter_3135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1215">
              <SourceParameter reference="Parameter_3144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1214">
              <SourceParameter reference="Parameter_7193"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1213">
              <SourceParameter reference="Parameter_3167"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1212">
              <SourceParameter reference="Parameter_3168"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1211">
              <SourceParameter reference="Metabolite_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1210">
              <SourceParameter reference="Parameter_3169"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_255" name="ACEK_1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_255">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:48:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3166" name="Keq" value="888"/>
          <Constant key="Parameter_3170" name="k" value="1.25457"/>
        </ListOfConstants>
        <KineticLaw function="Function_144" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1225">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1224">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1223">
              <SourceParameter reference="Parameter_3166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1222">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1221">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1220">
              <SourceParameter reference="Parameter_3170"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_256" name="ACEK_2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_256">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:48:23Z</dcterms:W3CDTF>
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
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3125" name="Keq" value="400"/>
          <Constant key="Parameter_3171" name="k" value="0.0332"/>
        </ListOfConstants>
        <KineticLaw function="Function_145" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1230">
              <SourceParameter reference="Parameter_3125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1229">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1228">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1227">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1226">
              <SourceParameter reference="Parameter_3171"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_257" name="EDD" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_257">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T19:07:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_95" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3172" name="Keq" value="1000"/>
          <Constant key="Parameter_3173" name="KmKDPG" value="0.318316"/>
          <Constant key="Parameter_3174" name="KmPGN" value="0.6"/>
          <Constant key="Parameter_3175" name="Vmax" value="0.111359"/>
        </ListOfConstants>
        <KineticLaw function="Function_138" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1183">
              <SourceParameter reference="Metabolite_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1182">
              <SourceParameter reference="Parameter_3172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1181">
              <SourceParameter reference="Parameter_3173"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1180">
              <SourceParameter reference="Parameter_3174"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1179">
              <SourceParameter reference="Metabolite_95"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1178">
              <SourceParameter reference="Parameter_3175"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_258" name="EDA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_258">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T19:06:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_109" stoichiometry="1"/>
          <Product metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3176" name="Keq" value="0.5"/>
          <Constant key="Parameter_3177" name="KmGAP" value="86.678"/>
          <Constant key="Parameter_3178" name="KmKDPG" value="0.06"/>
          <Constant key="Parameter_3179" name="KmPYR" value="10"/>
          <Constant key="Parameter_3180" name="Vmax" value="0.0775241"/>
        </ListOfConstants>
        <KineticLaw function="Function_139" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1191">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1190">
              <SourceParameter reference="Metabolite_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1189">
              <SourceParameter reference="Parameter_3176"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1188">
              <SourceParameter reference="Parameter_3177"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1187">
              <SourceParameter reference="Parameter_3178"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1186">
              <SourceParameter reference="Parameter_3179"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1185">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1184">
              <SourceParameter reference="Parameter_3180"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_259" name="NDHI" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_259">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-26T16:30:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_102" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_34" stoichiometry="4"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_103" stoichiometry="1"/>
          <Product metabolite="Metabolite_92" stoichiometry="1"/>
          <Product metabolite="Metabolite_73" stoichiometry="4"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3181" name="Vmax" value="23.0735"/>
          <Constant key="Parameter_3182" name="KeqNDH" value="27.6193"/>
        </ListOfConstants>
        <KineticLaw function="Function_186" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2341">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2340">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2339">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2338">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1987">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2311">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2312">
              <SourceParameter reference="Metabolite_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2214">
              <SourceParameter reference="Parameter_3181"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_260" name="PNT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_260">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T13:54:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_100" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_102" stoichiometry="1"/>
          <Product metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3183" name="Keq" value="0.181891"/>
          <Constant key="Parameter_3184" name="k" value="2.49441"/>
        </ListOfConstants>
        <KineticLaw function="Function_140" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1197">
              <SourceParameter reference="Parameter_3183"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1196">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1195">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1194">
              <SourceParameter reference="Metabolite_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1193">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1192">
              <SourceParameter reference="Parameter_3184"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_261" name="ADK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_261">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:48:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="2"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3185" name="Keq" value="0.962758"/>
          <Constant key="Parameter_6899" name="k" value="0.242256"/>
        </ListOfConstants>
        <KineticLaw function="Function_141" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1202">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1201">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1200">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1199">
              <SourceParameter reference="Parameter_3185"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1198">
              <SourceParameter reference="Parameter_6899"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_262" name="ATP_SYN" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_262">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:48:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_73" stoichiometry="4"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_34" stoichiometry="4"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6903" name="Vmax" value="108.733"/>
          <Constant key="Parameter_6905" name="Keq" value="49.8315"/>
        </ListOfConstants>
        <KineticLaw function="Function_187" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2360">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2361">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2211">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2371">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2372">
              <SourceParameter reference="Parameter_6905"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2373">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2374">
              <SourceParameter reference="Parameter_6903"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_263" name="CYA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_263">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:49:01Z</dcterms:W3CDTF>
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
          <Product metabolite="Metabolite_11" stoichiometry="2"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6898" name="Keq" value="2591.19"/>
          <Constant key="Parameter_6904" name="k" value="0.00414418"/>
          <Constant key="Parameter_6900" name="KaeiiaP" value="0.180981"/>
        </ListOfConstants>
        <KineticLaw function="Function_188" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2382">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2383">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2384">
              <SourceParameter reference="Parameter_6900"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2385">
              <SourceParameter reference="Parameter_6898"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2386">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2387">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2388">
              <SourceParameter reference="Parameter_6904"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_264" name="DOS" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_264">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:49:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6897" name="Keq" value="674.242"/>
          <Constant key="Parameter_6901" name="k" value="0.00828"/>
        </ListOfConstants>
        <KineticLaw function="Function_146" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1234">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1233">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1232">
              <SourceParameter reference="Parameter_6897"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1231">
              <SourceParameter reference="Parameter_6901"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_265" name="ACK" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_265">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:48:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_119" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6895" name="Keq" value="174"/>
          <Constant key="Parameter_6896" name="KmACE" value="7"/>
          <Constant key="Parameter_6868" name="KmACP" value="0.16"/>
          <Constant key="Parameter_6894" name="KmADP" value="0.5"/>
          <Constant key="Parameter_3487" name="KmATP" value="0.07"/>
          <Constant key="Parameter_7348" name="Vmax" value="7.23"/>
        </ListOfConstants>
        <KineticLaw function="Function_147" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1245">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1244">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1243">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1242">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1241">
              <SourceParameter reference="Parameter_6895"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1240">
              <SourceParameter reference="Parameter_6896"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1239">
              <SourceParameter reference="Parameter_6868"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1238">
              <SourceParameter reference="Parameter_6894"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1237">
              <SourceParameter reference="Parameter_3487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1236">
              <SourceParameter reference="Parameter_7348"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1235">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_266" name="ACS" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_266">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-25T19:59:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_121" stoichiometry="1"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="2"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3520" name="KmACE" value="0.07"/>
          <Constant key="Parameter_3442" name="KmATP" value="0.1"/>
          <Constant key="Parameter_3206" name="KmCOA" value="0.01"/>
          <Constant key="Parameter_3516" name="Vmax" value="7.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_137" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1177">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1176">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1175">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1174">
              <SourceParameter reference="Parameter_3520"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1173">
              <SourceParameter reference="Parameter_3442"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1172">
              <SourceParameter reference="Parameter_3206"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1171">
              <SourceParameter reference="Parameter_3516"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1170">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_267" name="PTA" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_267">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-01T17:09:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_121" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
          <Product metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3562" name="Keq" value="0.0053952"/>
          <Constant key="Parameter_7260" name="KiACCOA" value="0.2"/>
          <Constant key="Parameter_3306" name="KiACP" value="0.2"/>
          <Constant key="Parameter_3919" name="KiCOA" value="0.029"/>
          <Constant key="Parameter_3482" name="KiP" value="13.54"/>
          <Constant key="Parameter_3450" name="KmACP" value="0.7"/>
          <Constant key="Parameter_3483" name="KmP" value="6.1"/>
          <Constant key="Parameter_7258" name="Vmax" value="2.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_148" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1257">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1256">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1255">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1254">
              <SourceParameter reference="Parameter_3562"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1253">
              <SourceParameter reference="Parameter_7260"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1252">
              <SourceParameter reference="Parameter_3306"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1251">
              <SourceParameter reference="Parameter_3919"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1250">
              <SourceParameter reference="Parameter_3482"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1249">
              <SourceParameter reference="Parameter_3450"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1248">
              <SourceParameter reference="Parameter_3483"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1247">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1246">
              <SourceParameter reference="Parameter_7258"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_268" name="PTS_0" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_268">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T12:14:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_98" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_84" stoichiometry="1"/>
          <Product metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7353" name="KmPEP" value="0.6"/>
          <Constant key="Parameter_3215" name="KmPYR" value="1"/>
          <Constant key="Parameter_3476" name="kF" value="12000"/>
          <Constant key="Parameter_7316" name="kR" value="8000"/>
        </ListOfConstants>
        <KineticLaw function="Function_149" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1265">
              <SourceParameter reference="Parameter_7353"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1264">
              <SourceParameter reference="Parameter_3215"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1263">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1262">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1261">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1260">
              <SourceParameter reference="Metabolite_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1259">
              <SourceParameter reference="Parameter_3476"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1258">
              <SourceParameter reference="Parameter_7316"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_269" name="PTS_1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_269">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:49:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_84" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
          <Product metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7337" name="k1" value="200000"/>
          <Constant key="Parameter_7324" name="k2" value="8000"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_7337"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_19"/>
              <SourceParameter reference="Metabolite_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_7324"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_18"/>
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_270" name="PTS_2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_270">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T10:24:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_83" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7331" name="k1" value="61000"/>
          <Constant key="Parameter_7381" name="k2" value="47000"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_7331"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_83"/>
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_7381"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_22"/>
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_271" name="PTS_3" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_271">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T12:14:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
          <Product metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7384" name="k1" value="11000"/>
          <Constant key="Parameter_7378" name="k2" value="4000"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Parameter_7384"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_21"/>
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Parameter_7378"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_20"/>
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_272" name="PTS_4" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_272">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T12:14:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_110" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7379" name="KmG6P" value="2125.91"/>
          <Constant key="Parameter_7377" name="KmGLC" value="0.02"/>
          <Constant key="Parameter_7338" name="kF" value="4000"/>
          <Constant key="Parameter_3912" name="kR" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_189" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2453">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2454">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2455">
              <SourceParameter reference="Parameter_7379"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2456">
              <SourceParameter reference="Parameter_7377"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2457">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2458">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2459">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2460">
              <SourceParameter reference="Parameter_7338"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2461">
              <SourceParameter reference="Parameter_3912"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_273" name="_GLC_FEED" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_273">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-09-30T23:49:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3502" name="FEED" value="0.23"/>
        </ListOfConstants>
        <KineticLaw function="Function_121" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_274" name="CYTBO" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_274">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T09:53:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_92" stoichiometry="2"/>
          <Substrate metabolite="Metabolite_34" stoichiometry="8"/>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="2"/>
          <Product metabolite="Metabolite_73" stoichiometry="8"/>
          <Product metabolite="Metabolite_35" stoichiometry="2"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3431" name="Vmax" value="8.54045"/>
          <Constant key="Parameter_7261" name="Keq" value="12.067"/>
        </ListOfConstants>
        <KineticLaw function="Function_190" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2472">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2473">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2474">
              <SourceParameter reference="Parameter_7261"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2475">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2476">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2477">
              <SourceParameter reference="Metabolite_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2478">
              <SourceParameter reference="Parameter_3431"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_275" name="SQR" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_275">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-15T13:54:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
          <Product metabolite="Metabolite_92" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3440" name="Keq" value="0.94033"/>
          <Constant key="Parameter_7355" name="Vmax" value="3.41617"/>
        </ListOfConstants>
        <KineticLaw function="Function_191" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2359">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2486">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2487">
              <SourceParameter reference="Parameter_3440"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2488">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2489">
              <SourceParameter reference="Metabolite_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2490">
              <SourceParameter reference="Parameter_7355"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="NDHII" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-17T08:01:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_102" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_103" stoichiometry="1"/>
          <Product metabolite="Metabolite_92" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3303" name="Vmax" value="30.8306"/>
          <Constant key="Parameter_7318" name="KeqNDH" value="27.6193"/>
        </ListOfConstants>
        <KineticLaw function="Function_192" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2497">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2498">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2499">
              <SourceParameter reference="Metabolite_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2500">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2501">
              <SourceParameter reference="Metabolite_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2502">
              <SourceParameter reference="Parameter_3303"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="GROWTH" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-21T14:35:01Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_110" stoichiometry="116"/>
          <Substrate metabolite="Metabolite_114" stoichiometry="204"/>
          <Substrate metabolite="Metabolite_96" stoichiometry="845"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1010"/>
          <Substrate metabolite="Metabolite_118" stoichiometry="610"/>
          <Substrate metabolite="Metabolite_94" stoichiometry="1601"/>
          <Substrate metabolite="Metabolite_91" stoichiometry="507"/>
          <Substrate metabolite="Metabolite_98" stoichiometry="293"/>
          <Substrate metabolite="Metabolite_109" stoichiometry="73"/>
          <Substrate metabolite="Metabolite_113" stoichiometry="40"/>
          <Substrate metabolite="Metabolite_100" stoichiometry="10169"/>
          <Substrate metabolite="Metabolite_121" stoichiometry="2118"/>
          <Substrate metabolite="Metabolite_103" stoichiometry="2004"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="30508"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_101" stoichiometry="10169"/>
          <Product metabolite="Metabolite_13" stoichiometry="2118"/>
          <Product metabolite="Metabolite_102" stoichiometry="2004"/>
          <Product metabolite="Metabolite_17" stoichiometry="30508"/>
          <Product metabolite="Metabolite_11" stoichiometry="30508"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7317" name="Vmax" value="9.74137"/>
          <Constant key="Parameter_3438" name="KmG6P" value="1.20911"/>
          <Constant key="Parameter_3466" name="KmE4P" value="1.63298"/>
          <Constant key="Parameter_4396" name="KmPGA3" value="0.0764619"/>
          <Constant key="Parameter_7356" name="KmOAA" value="0.0248351"/>
          <Constant key="Parameter_7292" name="KmAKG" value="5.11989"/>
          <Constant key="Parameter_7320" name="KmPYR" value="0.00463904"/>
          <Constant key="Parameter_3480" name="KmR5P" value="0.021234"/>
          <Constant key="Parameter_3219" name="KmPEP" value="0.457734"/>
          <Constant key="Parameter_7373" name="KmGAP" value="0.024854"/>
          <Constant key="Parameter_7380" name="KmF6P" value="0.366423"/>
          <Constant key="Parameter_3150" name="KmNADPH" value="3.59774"/>
          <Constant key="Parameter_3140" name="KmACCOA" value="0.0494404"/>
          <Constant key="Parameter_3132" name="KmNAD" value="2.82239"/>
          <Constant key="Parameter_3137" name="KmATP" value="0.0468266"/>
        </ListOfConstants>
        <KineticLaw function="Function_193" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2532">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2533">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2534">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2535">
              <SourceParameter reference="Metabolite_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2536">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2537">
              <SourceParameter reference="Metabolite_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2538">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2539">
              <SourceParameter reference="Parameter_3140"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2540">
              <SourceParameter reference="Parameter_7292"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2541">
              <SourceParameter reference="Parameter_3137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2542">
              <SourceParameter reference="Parameter_3466"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2543">
              <SourceParameter reference="Parameter_7380"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2544">
              <SourceParameter reference="Parameter_3438"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2545">
              <SourceParameter reference="Parameter_7373"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2546">
              <SourceParameter reference="Parameter_3132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2547">
              <SourceParameter reference="Parameter_3150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2548">
              <SourceParameter reference="Parameter_7356"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2549">
              <SourceParameter reference="Parameter_3219"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2550">
              <SourceParameter reference="Parameter_4396"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2551">
              <SourceParameter reference="Parameter_7320"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2552">
              <SourceParameter reference="Parameter_3480"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2553">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2554">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2555">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2556">
              <SourceParameter reference="Metabolite_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2557">
              <SourceParameter reference="Metabolite_96"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2558">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2559">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2560">
              <SourceParameter reference="Parameter_7317"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="ATP_MAINTENANCE" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-21T14:43:37Z</dcterms:W3CDTF>
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
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3149" name="Vmax" value="1.30166"/>
          <Constant key="Parameter_3911" name="Keq" value="3.63369"/>
        </ListOfConstants>
        <KineticLaw function="Function_194" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2449">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2514">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2516">
              <SourceParameter reference="Parameter_3911"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2524">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2523">
              <SourceParameter reference="Parameter_3149"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="XCH_GLC" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-23T16:07:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3917" name="Vmax" value="100"/>
          <Constant key="Parameter_3429" name="Km" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_195" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2509">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2526">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2518">
              <SourceParameter reference="Parameter_3429"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2527">
              <SourceParameter reference="Parameter_3917"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="PIT" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-23T17:08:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_73" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3317" name="Vmax" value="7.146"/>
          <Constant key="Parameter_3310" name="KmPp" value="0.025"/>
          <Constant key="Parameter_3916" name="Kr" value="0.1"/>
          <Constant key="Parameter_3319" name="KmP" value="12.18"/>
        </ListOfConstants>
        <KineticLaw function="Function_196" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2517">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1873">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2515">
              <SourceParameter reference="Parameter_3319"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2590">
              <SourceParameter reference="Parameter_3310"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2591">
              <SourceParameter reference="Parameter_3916"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2592">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2593">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2594">
              <SourceParameter reference="Parameter_3317"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="XCH_P" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-10-31T12:45:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4537" name="Vmax" value="100"/>
          <Constant key="Parameter_4574" name="Km" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_197" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2512">
              <SourceParameter reference="Parameter_4574"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2450">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2511">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2471">
              <SourceParameter reference="Parameter_4537"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="XCH_ACE1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:04:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3425" name="Vmax" value="100"/>
          <Constant key="Parameter_3422" name="Km" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_198" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2607">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2608">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2609">
              <SourceParameter reference="Parameter_3422"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2610">
              <SourceParameter reference="Parameter_3425"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="_ACE_OUT" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:06:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_72" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4581" name="k1" value="5.556e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4581"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="XCH_ACE2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-03T00:13:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_72" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3417" name="Vmax" value="100"/>
          <Constant key="Parameter_3478" name="Km" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_199" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2617">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2618">
              <SourceParameter reference="Metabolite_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2619">
              <SourceParameter reference="Parameter_3478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2620">
              <SourceParameter reference="Parameter_3417"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="GL6P_HYDROLYSIS" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2015-01-22T11:03:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_108" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_95" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4559" name="KGl6Phydrol" value="0.000167"/>
          <Constant key="Parameter_3426" name="KeqGl6Phydrol" value="42.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_200" unitType="Default" scalingCompartment="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2625">
              <SourceParameter reference="Metabolite_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2626">
              <SourceParameter reference="Parameter_4559"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2627">
              <SourceParameter reference="Parameter_3426"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2628">
              <SourceParameter reference="Metabolite_95"/>
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
<dcterms:W3CDTF>2020-12-31T20:27:50Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm]" value="1" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular]" value="100" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_periplasm]" value="0.25" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ACCOA]" value="9.3188500472593433e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ACO]" value="1.9361125444683825e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ACP]" value="8.666378473260628e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[AKG]" value="3.6004644357762718e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[BPG]" value="3.9391041609320784e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[CIT]" value="5.3916684731737211e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[DAP]" value="2.6322427250896398e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[E4P]" value="7.9070636586315055e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[F6P]" value="1.5763913773508562e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[FDP]" value="1.6970893240712528e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[FUM]" value="1.2834098550368952e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[G6P]" value="5.185833657867476e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[GAP]" value="7.0569337264898736e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[GL6P]" value="1.9642083954843328e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[GLX]" value="5.3057529521748193e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ICIT]" value="6.3703870979411943e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[KDPG]" value="5.2282820509269959e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MAL]" value="6.2157783571093376e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[NAD]" value="8.5005138856911005e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[NADH]" value="9.5424726399159763e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[NADP]" value="1.0107388316032156e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[NADPH]" value="5.3695136640245924e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[OAA]" value="7.6986756119322837e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[PEP]" value="6.0043064209875586e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[PGA2]" value="2.2781589357519195e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[PGA3]" value="4.1930620362333775e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[PGN]" value="7.9251068054338011e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[PYR]" value="1.4265938662786027e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[Q]" value="1.9639237646493431e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[QH2]" value="4.0582170902518143e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[R5P]" value="6.4341457787768078e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[RU5P]" value="2.0585242819087797e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[S7P]" value="8.5505157243436532e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[SUC]" value="1.3011174628192792e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[SUCCOA]" value="2.4743724285400568e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[X5P]" value="3.0473064429987037e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ei]" value="2.011474769284559e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[eiP]" value="3.8428259614974003e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[eiia]" value="8.5525581092101509e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[eiiaP]" value="2.8940514576334143e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[eiicb]" value="28419065370125704" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[eiicbP]" value="2.063314294739305e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[hpr]" value="1.151504442009088e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[hprP]" value="3.1621128280980024e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[icd]" value="3.2684822623544294e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[icdP]" value="3.0988284544346845e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[tal]" value="1.6747273025880269e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[talC3]" value="3.4458117818428338e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[tkt]" value="8.329103862527103e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[tktC2]" value="3.3825882087407387e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ADP]" value="3.6031448158158684e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[AMP]" value="1.1216446002177787e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ATP]" value="1.5490148252183458e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[CAMP]" value="5.5592239657333948e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[COA]" value="3.0110704285000001e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[HCO3]" value="8.4309971997999995e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[P]" value="5.8799562299070281e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MG]" value="6.0221408570000002e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MgADP]" value="1.581915527356805e+20" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MgATP]" value="1.4279748240200082e+21" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MgFDP]" value="2.4920548077404594e+19" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ASP]" value="7.0459048026900005e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[CYS]" value="5.1188197284500005e+19" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[MN]" value="1.8066422571000001e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[Hin]" value="19043681497464356" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[H2O]" value="6.0221408570000002e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[O2]" value="1.26464957997e+20" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[FAD]" value="1.5291063195155248e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[FADH2]" value="4.493034537947174e+20" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_cytoplasm],Vector=Metabolites[ACE]" value="1.1243796302389098e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular],Vector=Metabolites[GLCx]" value="1.6323005538749296e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular],Vector=Metabolites[Px]" value="6.0221408570000002e+23" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[extracellular],Vector=Metabolites[ACEx]" value="1.1231315598723326e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_periplasm],Vector=Metabolites[Hout]" value="8091475925615462" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_periplasm],Vector=Metabolites[GLCp]" value="6.0723801629007526e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_periplasm],Vector=Metabolites[Pp]" value="1.5029536374696158e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Compartments[cell_periplasm],Vector=Metabolites[ACEp]" value="28093889876228876" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[FEED]" value="0.23000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdADPMg]" value="1.2777099999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdATPMg]" value="0.084763400000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdFDPMg]" value="5.8099999999999996" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmICIT_ACN]" value="9.3135200000000005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmCIT_ACN]" value="0.062888200000000005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmACO_ACN]" value="0.02001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KeqNDH]" value="27.619299999999999" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=Keq" value="0.35999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=KmF6P" value="0.14699999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=KmG6P" value="0.28000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=KmPEP" value="1.9990000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=Vmax" value="2.32456" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGI],ParameterGroup=Parameters,Parameter=KmPGN" value="0.51595800000000003" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KefrADP" value="0.073526400000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KefrPEP" value="19.98" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KeftADP" value="9.0090000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KeftPEP" value="0.26025999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=Keq" value="1998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KirADP" value="54.945" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KirATP" value="2.4975000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KirF6P" value="1.84615" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KirFDP" value="0.045954000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KitADP" value="80.079999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KitATP" value="0.014014" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KitF6P" value="0.0085685599999999994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KitFDP" value="50.5505" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmrADP" value="0.69000899999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmrATPMg" value="8.1218700000000002e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmrF6P" value="2.0520500000000001e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmrFDP" value="10.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmtADP" value="2.0019999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmtATPMg" value="3.34334" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmtF6P" value="32.966999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=KmtFDP" value="9.9900000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=L0" value="14.085100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=Vmax" value="0.185253" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=Wr" value="0.023704099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=Wt" value="0.146735" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PFK],ParameterGroup=Parameters,Parameter=n" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=Keq" value="0.18981000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=KmDAP" value="0.13000999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=KmFDP" value="0.12012" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=KmGAP" value="0.13000999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=KmPEP" value="0.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBA],ParameterGroup=Parameters,Parameter=Vmax" value="21.697800000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[TPI]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[TPI],ParameterGroup=Parameters,Parameter=Keq" value="0.27020300000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[TPI],ParameterGroup=Parameters,Parameter=KmDAP" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[TPI],ParameterGroup=Parameters,Parameter=KmGAP" value="1.8930100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[TPI],ParameterGroup=Parameters,Parameter=Vmax" value="24.1843" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=Keq" value="20" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=KmBPG" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=KmGAP" value="2.4726499999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=KmNAD" value="0.0110454" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=KmNADH" value="3.6979700000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=KmP" value="0.017000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GDH],ParameterGroup=Parameters,Parameter=Vmax" value="8.6657299999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=Keq" value="99.992500000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=KmADPMg" value="0.085416000000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=KmATPMg" value="3.4773700000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=KmBPG" value="0.0113296" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=KmPGA3" value="2.45722" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGK],ParameterGroup=Parameters,Parameter=Vmax" value="16.108899999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GPM]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GPM],ParameterGroup=Parameters,Parameter=Keq" value="0.56581800000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GPM],ParameterGroup=Parameters,Parameter=KmPGA2" value="1.9153" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GPM],ParameterGroup=Parameters,Parameter=KmPGA3" value="0.115" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GPM],ParameterGroup=Parameters,Parameter=Vmax" value="10.993399999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ENO]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ENO],ParameterGroup=Parameters,Parameter=Keq" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ENO],ParameterGroup=Parameters,Parameter=KmPEP" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ENO],ParameterGroup=Parameters,Parameter=KmPGA2" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ENO],ParameterGroup=Parameters,Parameter=Vmax" value="11.7189" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrFDP" value="0.44914900000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrG6P" value="0.158746" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrGL6P" value="0.150482" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrR5P" value="9.3325399999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrRU5P" value="1.5359100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrS7P" value="0.078595499999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KefrX5P" value="0.67737400000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KeftATP" value="3.6911700000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KeftSUCCOA" value="8.2640600000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KirADP" value="0.51758499999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KirATP" value="96.033299999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KirPEP" value="0.18105599999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KirPYR" value="15.1403" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KirPyrATP" value="230.78100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KitADP" value="0.224911" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KitATP" value="0.039564000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KitPEP" value="0.46567199999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KitPYR" value="0.24990000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KitPyrATP" value="11.3691" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KmrADPMg" value="0.32614399999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KmrPEP" value="5.5636800000000005e-07" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KmtADPMg" value="0.054677999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=KmtPEP" value="0.11475" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=L0" value="50.4818" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=Vmax" value="0.74716000000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PYK],ParameterGroup=Parameters,Parameter=n" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KdG6P" value="0.192" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KdGL6P" value="0.02" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=Keq" value="60000000000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KmG6P" value="0.11852500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KmGL6P" value="0.328629" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KmNADP" value="0.027400000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=KmNADPH" value="0.016799999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ZWF],ParameterGroup=Parameters,Parameter=Vmax" value="0.26579999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL],ParameterGroup=Parameters,Parameter=Keq" value="42.757199999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL],ParameterGroup=Parameters,Parameter=KiG6P" value="2.0001000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL],ParameterGroup=Parameters,Parameter=KmGL6P" value="0.022977000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL],ParameterGroup=Parameters,Parameter=KmPGN" value="9.9900000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PGL],ParameterGroup=Parameters,Parameter=Vmax" value="11.5967" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KdHCO3" value="58.895099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KdHCO3NADPH" value="9.7256999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KdNADP" value="0.116989" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KdNADPH" value="0.00340034" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KdRu5P" value="0.044004399999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KefATP" value="0.065006499999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KefFbP" value="0.0129987" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KefNADPATP" value="0.139986" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KefNADPFbP" value="0.0051994800000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=Keq" value="49.962000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KmHCO3" value="6.41899" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KmNADP" value="0.049000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KmNADPH" value="68.382800000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KmPGN" value="0.092999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=KmRU5P" value="45.197699999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GND],ParameterGroup=Parameters,Parameter=Vmax" value="4.0810500000000003" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPE],ParameterGroup=Parameters,Parameter=Keq" value="1.5015000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPE],ParameterGroup=Parameters,Parameter=KmRU5P" value="0.87252200000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPE],ParameterGroup=Parameters,Parameter=KmX5P" value="0.89360700000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPE],ParameterGroup=Parameters,Parameter=Vmax" value="6.0010300000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI],ParameterGroup=Parameters,Parameter=Keq" value="0.33009300000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI],ParameterGroup=Parameters,Parameter=KmE4P" value="0.67066999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI],ParameterGroup=Parameters,Parameter=KmR5P" value="3.0971500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI],ParameterGroup=Parameters,Parameter=KmRU5P" value="4.4026300000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[RPI],ParameterGroup=Parameters,Parameter=Vmax" value="8" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[X5P_GAP_TKT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[X5P_GAP_TKT],ParameterGroup=Parameters,Parameter=Keq" value="1.0009999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[X5P_GAP_TKT],ParameterGroup=Parameters,Parameter=kcat" value="40" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_E4P_TKT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_E4P_TKT],ParameterGroup=Parameters,Parameter=Keq" value="0.50049999999999994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_E4P_TKT],ParameterGroup=Parameters,Parameter=kcat" value="40.0002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_R5P_TKT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_R5P_TKT],ParameterGroup=Parameters,Parameter=Keq" value="0.33033000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_R5P_TKT],ParameterGroup=Parameters,Parameter=kcat" value="199.97900000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_GAP_TAL]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_GAP_TAL],ParameterGroup=Parameters,Parameter=Keq" value="0.11011" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[F6P_GAP_TAL],ParameterGroup=Parameters,Parameter=kcat" value="119.992" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_E4P_TAL]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_E4P_TAL],ParameterGroup=Parameters,Parameter=Keq" value="26.6266" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[S7P_E4P_TAL],ParameterGroup=Parameters,Parameter=kcat" value="99.999099999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirAMP" value="0.0012212200000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirAMPFDP" value="0.25625599999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirF6P" value="1.1211199999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirF6PMg" value="0.38461499999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirFDP" value="1.35327" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirFDPMg" value="0.75924000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirFDPMgMg" value="0.35635600000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirP" value="3.16316" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirPF6P" value="6.6053800000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirPF6PMg" value="48.448399999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KirPMg" value="0.85599999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitAMP" value="0.00025500000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitAMPFDP" value="690" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitF6P" value="0.30399999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitF6PMg" value="315" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitFDP" value="0.043101" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitFDPMg" value="0.0064200000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitFDPMgMg" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitP" value="0.64200000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitPF6P" value="0.0068900000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitPF6PMg" value="16.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KitPMg" value="539" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KmrFDP" value="0.063614100000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KmrMg" value="0.039038999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KmtFDP" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KmtMg" value="55.055" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=L0" value="0.00081499999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=Vmax" value="0.215583" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=n" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FBP],ParameterGroup=Parameters,Parameter=KdFDPMg" value="5.8099999999999996" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdFDPMg],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KdrOAA" value="4.3540400000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KdrPEP" value="655.59100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KdtOAA" value="17.912700000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KdtPEP" value="0.012199099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrACCOA" value="0.14002899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrASP" value="0.389183" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrCIT" value="34.427700000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrCYS" value="0.00044884299999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrFDP" value="9.9912600000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrFDPACCOA" value="0.015625099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrFUM" value="2.7475000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrMAL" value="0.23002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KefrSUC" value="22.9834" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftACCOA" value="1.2759799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftASP" value="27.472899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftCIT" value="0.52194499999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftCYS" value="0.97737399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftFDP" value="13.2064" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftFDPACCOA" value="47.756300000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftFUM" value="9.7611899999999991" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftMAL" value="0.73728300000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KeftSUC" value="107.18000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=Keq" value="149.70500000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmrHCO3" value="0.0021981100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmrOAA" value="13.046900000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmrP" value="0.66335599999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmrPEP" value="3.2008899999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmtHCO3" value="0.00220031" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmtOAA" value="6.8099499999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmtP" value="0.28513100000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=KmtPEP" value="5.1249700000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=L0" value="6.3720899999999997e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=Vmax" value="21.439" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPC],ParameterGroup=Parameters,Parameter=n" value="4.00319" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=Keq" value="1.8816600000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=KmADP" value="0.049970000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=KmATP" value="0.060041799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=KmHCO3" value="2.6318999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=KmOAA" value="0.66966000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=KmPEP" value="0.069983299999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PCK],ParameterGroup=Parameters,Parameter=Vmax" value="8.0877700000000008" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdAMP" value="1480" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdATPMgPPS" value="0.054899999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdMg" value="36.899999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdP" value="346" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdPEP" value="95.700000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdPYR" value="2740" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KefADP" value="0.028299999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KefAKG" value="0.27400000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KefATP" value="0.00062799999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KefOAA" value="0.79600000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=Keq" value="200000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KmAMP" value="0.00038400000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KmATPMg" value="0.054899999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KmP" value="84.400000000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KmPEP" value="20.699999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KmPYR" value="0.22900000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=Vmax" value="0.016377200000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=W" value="10" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=alpha" value="38900" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdADPMg" value="1.2777099999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdADPMg],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PPS],ParameterGroup=Parameters,Parameter=KdATPMg" value="0.084763400000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KdATPMg],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KefrACCOA" value="1.8333600000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KefrASP" value="0.36214200000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KefrATP" value="88.975200000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KefrCOA" value="0.26800000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KeftACCOA" value="0.19700000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KeftASP" value="0.58299999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KeftATP" value="0.26000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KeftCOA" value="0.26800000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KirNAD" value="0.63645700000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KitNAD" value="0.990398" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmrMAL" value="0.21291299999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmrMg" value="0.19187100000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmrMn" value="0.27256799999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmrNAD" value="1.36636" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmtMAL" value="0.092999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmtMg" value="2.3768099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmtMn" value="0.41019800000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=KmtNAD" value="0.108" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=L0" value="19.899999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=Vmax" value="6.64269" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MAE],ParameterGroup=Parameters,Parameter=n" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=Keq" value="3138.1599999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmACCOA" value="10.173999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmCOA" value="0.0050046099999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmHCO3" value="0.0054511200000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmNAD" value="0.0099900000000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmNADH" value="6.6351199999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=KmPYR" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PDH],ParameterGroup=Parameters,Parameter=Vmax" value="961.70600000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KdACCOA0" value="0.69930899999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KdcsCIT" value="7.3812800000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KdcsCOA" value="0.00174282" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KdcsOAA" value="0.15460099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Keq" value="83067.100000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Ki1AKG" value="0.0150083" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Ki1NADH" value="0.00033031299999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Ki2AKG" value="0.25625199999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Ki2NADH" value="0.0504" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KiATP" value="0.57993899999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KmACCOA0" value="0.119974" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KmOAA0" value="0.0012345800000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KmcsCIT" value="1.1571499999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=KmcsCOA" value="9.6343999999999998e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GLT],ParameterGroup=Parameters,Parameter=Vmax" value="57.058399999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1],ParameterGroup=Parameters,Parameter=Keq" value="0.38450299999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1],ParameterGroup=Parameters,Parameter=Vmax" value="9.7241300000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1],ParameterGroup=Parameters,Parameter=KmACO_ACN" value="0.02001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmACO_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1],ParameterGroup=Parameters,Parameter=KmCIT_ACN" value="0.062888200000000005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmCIT_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_1],ParameterGroup=Parameters,Parameter=KmICIT_ACN" value="9.3135200000000005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmICIT_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2],ParameterGroup=Parameters,Parameter=Keq" value="3.4918300000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2],ParameterGroup=Parameters,Parameter=Vmax" value="9.86571" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2],ParameterGroup=Parameters,Parameter=KmACO_ACN" value="0.02001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmACO_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2],ParameterGroup=Parameters,Parameter=KmCIT_ACN" value="0.062888200000000005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmCIT_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACN_2],ParameterGroup=Parameters,Parameter=KmICIT_ACN" value="9.3135200000000005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KmICIT_ACN],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=Keq" value="28.1631" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=KmAKG" value="0.038038000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=KmICIT" value="0.010989000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=KmNADP" value="0.0059940000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=KmNADPH" value="0.00068333300000000005" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ICD],ParameterGroup=Parameters,Parameter=kcat" value="2461.9699999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=KdAKG" value="14.938599999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=KmAKG" value="0.020001999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=KmCOA" value="0.076007599999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=KmNAD" value="0.098009799999999994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=Vmax" value="0.068441299999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[LPD],ParameterGroup=Parameters,Parameter=alpha" value="16.430399999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=Keq" value="1.15994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmADP" value="0.0086847499999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmATP" value="0.102321" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmCOA" value="0.255019" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmP" value="0.91470899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmSUC" value="0.80074400000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=KmSUCCOA" value="0.0085000000000000006" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SK],ParameterGroup=Parameters,Parameter=Vmax" value="76.816299999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KefFUM" value="0.067047999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KefSUC" value="0.0322425" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=Keq" value="2250" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KmFUM" value="1.36019" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KmQ" value="0.0016071799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KmQH2" value="0.0061166299999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=KmSUC" value="0.80572699999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SDH],ParameterGroup=Parameters,Parameter=Vmax" value="1.5618399999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FUMA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FUMA],ParameterGroup=Parameters,Parameter=Keq" value="4.9996600000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FUMA],ParameterGroup=Parameters,Parameter=KmFUM" value="0.59999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FUMA],ParameterGroup=Parameters,Parameter=KmMAL" value="0.69999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[FUMA],ParameterGroup=Parameters,Parameter=Vmax" value="53.3414" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=Keq" value="9" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=KmMAL" value="0.435" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=KmOAA" value="75.803600000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=KmQ" value="0.041399999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=KmQH2" value="8.77942" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MQO],ParameterGroup=Parameters,Parameter=Vmax" value="4.6228300000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=Keq" value="100000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KiNAD" value="0.023312200000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KiNADH" value="0.00019698099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KiOAA" value="2.4644599999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KmMAL" value="0.85999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KmNAD" value="0.64000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KmNADH" value="0.0030000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=KmOAA" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[MDH],ParameterGroup=Parameters,Parameter=Vmax" value="6.1149199999999997" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdICITsuc" value="0.0048907400000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdPEP" value="1.05105" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdPEPglx" value="0.035855499999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdPEPicit" value="0.16426299999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdPGA3" value="0.80000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KdSUC" value="0.53052999999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=Keq" value="8.8087999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KmGLX" value="0.13013" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KmICIT" value="0.063062999999999994" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=KmSUC" value="0.58940999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEA],ParameterGroup=Parameters,Parameter=Vmax" value="1.5259499999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=Keq" value="230000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=KmACCOA" value="0.0089999999999999993" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=KmCOA" value="10.565200000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=KmGLX" value="0.021000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=KmMAL" value="15.0572" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEB],ParameterGroup=Parameters,Parameter=Vmax" value="0.352769" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_1],ParameterGroup=Parameters,Parameter=Keq" value="888" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_1],ParameterGroup=Parameters,Parameter=k" value="1.25457" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_2],ParameterGroup=Parameters,Parameter=Keq" value="400" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACEK_2],ParameterGroup=Parameters,Parameter=k" value="0.0332" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDD]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDD],ParameterGroup=Parameters,Parameter=Keq" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDD],ParameterGroup=Parameters,Parameter=KmKDPG" value="0.31831599999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDD],ParameterGroup=Parameters,Parameter=KmPGN" value="0.59999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDD],ParameterGroup=Parameters,Parameter=Vmax" value="0.111359" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA],ParameterGroup=Parameters,Parameter=Keq" value="0.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA],ParameterGroup=Parameters,Parameter=KmGAP" value="86.677999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA],ParameterGroup=Parameters,Parameter=KmKDPG" value="0.059999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA],ParameterGroup=Parameters,Parameter=KmPYR" value="10" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[EDA],ParameterGroup=Parameters,Parameter=Vmax" value="0.077524099999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHI]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHI],ParameterGroup=Parameters,Parameter=Vmax" value="23.073499999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHI],ParameterGroup=Parameters,Parameter=KeqNDH" value="27.619299999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KeqNDH],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PNT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PNT],ParameterGroup=Parameters,Parameter=Keq" value="0.181891" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PNT],ParameterGroup=Parameters,Parameter=k" value="2.4944099999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ADK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ADK],ParameterGroup=Parameters,Parameter=Keq" value="0.962758" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ADK],ParameterGroup=Parameters,Parameter=k" value="0.242256" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_SYN]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_SYN],ParameterGroup=Parameters,Parameter=Vmax" value="108.733" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_SYN],ParameterGroup=Parameters,Parameter=Keq" value="49.831499999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYA],ParameterGroup=Parameters,Parameter=Keq" value="2591.1900000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYA],ParameterGroup=Parameters,Parameter=k" value="0.0041441799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYA],ParameterGroup=Parameters,Parameter=KaeiiaP" value="0.180981" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[DOS]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[DOS],ParameterGroup=Parameters,Parameter=Keq" value="674.24199999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[DOS],ParameterGroup=Parameters,Parameter=k" value="0.0082799999999999992" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=Keq" value="174" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=KmACE" value="7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=KmACP" value="0.16" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=KmADP" value="0.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=KmATP" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACK],ParameterGroup=Parameters,Parameter=Vmax" value="7.2300000000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACS]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACS],ParameterGroup=Parameters,Parameter=KmACE" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACS],ParameterGroup=Parameters,Parameter=KmATP" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACS],ParameterGroup=Parameters,Parameter=KmCOA" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ACS],ParameterGroup=Parameters,Parameter=Vmax" value="7.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=Keq" value="0.0053952000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KiACCOA" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KiACP" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KiCOA" value="0.029000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KiP" value="13.539999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KmACP" value="0.69999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=KmP" value="6.0999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTA],ParameterGroup=Parameters,Parameter=Vmax" value="2.7000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_0]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_0],ParameterGroup=Parameters,Parameter=KmPEP" value="0.59999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_0],ParameterGroup=Parameters,Parameter=KmPYR" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_0],ParameterGroup=Parameters,Parameter=kF" value="12000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_0],ParameterGroup=Parameters,Parameter=kR" value="8000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_1],ParameterGroup=Parameters,Parameter=k1" value="200000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_1],ParameterGroup=Parameters,Parameter=k2" value="8000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_2],ParameterGroup=Parameters,Parameter=k1" value="61000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_2],ParameterGroup=Parameters,Parameter=k2" value="47000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_3],ParameterGroup=Parameters,Parameter=k1" value="11000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_3],ParameterGroup=Parameters,Parameter=k2" value="4000" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_4],ParameterGroup=Parameters,Parameter=KmG6P" value="2125.9099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_4],ParameterGroup=Parameters,Parameter=KmGLC" value="0.02" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_4],ParameterGroup=Parameters,Parameter=kF" value="4000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PTS_4],ParameterGroup=Parameters,Parameter=kR" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[_GLC_FEED]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[_GLC_FEED],ParameterGroup=Parameters,Parameter=FEED" value="0.23000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[FEED],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYTBO]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYTBO],ParameterGroup=Parameters,Parameter=Vmax" value="8.5404499999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[CYTBO],ParameterGroup=Parameters,Parameter=Keq" value="12.067" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SQR]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SQR],ParameterGroup=Parameters,Parameter=Keq" value="0.94033" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[SQR],ParameterGroup=Parameters,Parameter=Vmax" value="3.4161700000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHII]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHII],ParameterGroup=Parameters,Parameter=Vmax" value="30.8306" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[NDHII],ParameterGroup=Parameters,Parameter=KeqNDH" value="27.619299999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Values[KeqNDH],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=Vmax" value="9.7413699999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmG6P" value="1.2091099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmE4P" value="1.6329800000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmPGA3" value="0.076461899999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmOAA" value="0.024835099999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmAKG" value="5.1198899999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmPYR" value="0.0046390399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmR5P" value="0.021233999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmPEP" value="0.45773399999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmGAP" value="0.024854000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmF6P" value="0.366423" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmNADPH" value="3.5977399999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmACCOA" value="0.049440400000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmNAD" value="2.82239" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GROWTH],ParameterGroup=Parameters,Parameter=KmATP" value="0.046826600000000003" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_MAINTENANCE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_MAINTENANCE],ParameterGroup=Parameters,Parameter=Vmax" value="1.30166" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[ATP_MAINTENANCE],ParameterGroup=Parameters,Parameter=Keq" value="3.6336900000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_GLC]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_GLC],ParameterGroup=Parameters,Parameter=Vmax" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_GLC],ParameterGroup=Parameters,Parameter=Km" value="10" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PIT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PIT],ParameterGroup=Parameters,Parameter=Vmax" value="7.1459999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PIT],ParameterGroup=Parameters,Parameter=KmPp" value="0.025000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PIT],ParameterGroup=Parameters,Parameter=Kr" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[PIT],ParameterGroup=Parameters,Parameter=KmP" value="12.18" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_P],ParameterGroup=Parameters,Parameter=Vmax" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_P],ParameterGroup=Parameters,Parameter=Km" value="10" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE1],ParameterGroup=Parameters,Parameter=Vmax" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE1],ParameterGroup=Parameters,Parameter=Km" value="10" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[_ACE_OUT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[_ACE_OUT],ParameterGroup=Parameters,Parameter=k1" value="5.5560000000000003e-05" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE2],ParameterGroup=Parameters,Parameter=Vmax" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[XCH_ACE2],ParameterGroup=Parameters,Parameter=Km" value="10" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GL6P_HYDROLYSIS]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GL6P_HYDROLYSIS],ParameterGroup=Parameters,Parameter=KGl6Phydrol" value="0.00016699999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=Millard2017 - E. coli central carbon and energy metabolism,Vector=Reactions[GL6P_HYDROLYSIS],ParameterGroup=Parameters,Parameter=KeqGl6Phydrol" value="42.799999999999997" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_73"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_93"/>
      <StateTemplateVariable objectReference="Metabolite_103"/>
      <StateTemplateVariable objectReference="Metabolite_94"/>
      <StateTemplateVariable objectReference="Metabolite_109"/>
      <StateTemplateVariable objectReference="Metabolite_101"/>
      <StateTemplateVariable objectReference="Metabolite_113"/>
      <StateTemplateVariable objectReference="Metabolite_121"/>
      <StateTemplateVariable objectReference="Metabolite_98"/>
      <StateTemplateVariable objectReference="Metabolite_95"/>
      <StateTemplateVariable objectReference="Metabolite_104"/>
      <StateTemplateVariable objectReference="Metabolite_88"/>
      <StateTemplateVariable objectReference="Metabolite_99"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_90"/>
      <StateTemplateVariable objectReference="Metabolite_110"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_106"/>
      <StateTemplateVariable objectReference="Metabolite_115"/>
      <StateTemplateVariable objectReference="Metabolite_83"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_72"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_96"/>
      <StateTemplateVariable objectReference="Metabolite_85"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_89"/>
      <StateTemplateVariable objectReference="Metabolite_120"/>
      <StateTemplateVariable objectReference="Metabolite_108"/>
      <StateTemplateVariable objectReference="Metabolite_87"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_114"/>
      <StateTemplateVariable objectReference="Metabolite_97"/>
      <StateTemplateVariable objectReference="Metabolite_105"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_111"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_86"/>
      <StateTemplateVariable objectReference="Metabolite_119"/>
      <StateTemplateVariable objectReference="Metabolite_117"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_107"/>
      <StateTemplateVariable objectReference="Metabolite_91"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_116"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_118"/>
      <StateTemplateVariable objectReference="Metabolite_112"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_92"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_84"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_100"/>
      <StateTemplateVariable objectReference="Metabolite_102"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 5.8799562299070281e+21 8091475925615462 3.6031448158158684e+20 1.9639237646493431e+20 8.5005138856911005e+20 1.4265938662786027e+20 7.0569337264898736e+19 1.0107388316032156e+20 1.5763913773508562e+20 9.3188500472593433e+19 6.0043064209875586e+20 7.9251068054338011e+19 6.2157783571093376e+20 1.3011174628192792e+20 7.6986756119322837e+19 1.1243796302389098e+17 8.329103862527103e+18 2.0585242819087797e+20 5.185833657867476e+20 1.1216446002177787e+20 6.3703870979411943e+19 2.6322427250896398e+20 8.5525581092101509e+18 1.6323005538749296e+21 1.1231315598723326e+19 1.5029536374696158e+21 4.1930620362333775e+20 2.011474769284559e+17 3.2684822623544294e+17 8.5505157243436532e+19 1.9361125444683825e+19 1.9642083954843328e+18 2.4743724285400568e+19 1.5291063195155248e+20 7.9070636586315055e+19 2.2781589357519195e+20 5.2282820509269959e+19 28093889876228876 1.2834098550368952e+20 28419065370125704 3.0473064429987037e+20 8.666378473260628e+18 3.9391041609320784e+19 6.0723801629007526e+17 5.3057529521748193e+18 6.4341457787768078e+19 3.1621128280980024e+18 3.4458117818428338e+19 5.3916684731737211e+19 5.5592239657333948e+20 3.6004644357762718e+20 1.6970893240712528e+20 1.5490148252183458e+21 4.493034537947174e+20 1.151504442009088e+17 2.8940514576334143e+20 4.0582170902518143e+20 1.6747273025880269e+18 3.0988284544346845e+19 3.8428259614974003e+18 2.063314294739305e+17 5.3695136640245924e+19 9.5424726399159763e+19 3.3825882087407387e+19 1.581915527356805e+20 1.4279748240200082e+21 2.4920548077404594e+19 3.0110704285000001e+20 8.4309971997999995e+20 6.0221408570000002e+20 7.0459048026900005e+20 5.1188197284500005e+19 1.8066422571000001e+20 19043681497464356 6.0221408570000002e+20 1.26464957997e+20 6.0221408570000002e+23 1 100 0.25 0.23000000000000001 1.2777099999999999 0.084763400000000003 5.8099999999999996 9.3135200000000005 0.062888200000000005 0.02001 27.619299999999999 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_15" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_27" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_23" target="" append="1" confirmOverwrite="1"/>
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
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_26" name="Scan" type="scan" scheduled="true" updateModel="false">
      <Report reference="Report_40" target="Ecoli_mca.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="6"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Number of steps" type="unsignedInteger" value="100"/>
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
    <Task key="Task_25" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_24" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_18" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_22" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_40" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_15"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_15" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_19" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_13" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_17" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
    <Task key="Task_16" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_41" target="" append="1" confirmOverwrite="1"/>
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
    <Report key="Report_9" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_23" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_13" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_41" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_40" name="Speed test" taskType="metabolicControlAnalysis" separator="&#x09;" precision="8">
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
