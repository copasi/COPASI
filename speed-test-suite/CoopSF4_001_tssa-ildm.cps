<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2021-01-02T19:22:17Z -->
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
    <Function key="Function_74" name="transcr 3 inh 9 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(1+A5/(A5+Ka5))^na5*(1+A6/(A6+Ka6))^na6*(1+A7/(A7+Ka7))^na7*(1+A8/(A8+Ka8))^na8*(1+A9/(A9+Ka9))^na9*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_895" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_894" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_893" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_892" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_891" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_890" name="A6" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_889" name="A7" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_888" name="A8" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_887" name="A9" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_886" name="I1" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_885" name="I2" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_884" name="I3" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_883" name="V" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_882" name="Ka1" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_881" name="na1" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_880" name="Ka2" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_879" name="na2" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_878" name="Ka3" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_387" name="na3" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_386" name="Ka4" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_385" name="na4" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_384" name="Ka5" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_383" name="na5" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_382" name="Ka6" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_381" name="na6" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_380" name="Ka7" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_379" name="na7" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_378" name="Ka8" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_377" name="na8" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_376" name="Ka9" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_375" name="na9" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_374" name="Ki1" order="31" role="constant"/>
        <ParameterDescription key="FunctionParameter_373" name="ni1" order="32" role="constant"/>
        <ParameterDescription key="FunctionParameter_372" name="Ki2" order="33" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="ni2" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_370" name="Ki3" order="35" role="constant"/>
        <ParameterDescription key="FunctionParameter_369" name="ni3" order="36" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="transcr 2 inh 5 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(1+A5/(A5+Ka5))^na5*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_415" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_414" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_413" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_412" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_411" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_410" name="I1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_409" name="I2" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_408" name="V" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_407" name="Ka1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_406" name="na1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_405" name="Ka2" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_404" name="na2" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_403" name="Ka3" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_402" name="na3" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_401" name="Ka4" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_400" name="na4" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_399" name="Ka5" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_398" name="na5" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_397" name="Ki1" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_396" name="ni1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_395" name="Ki2" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_394" name="ni2" order="21" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="transcr 7 inh 8 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(1+A5/(A5+Ka5))^na5*(1+A6/(A6+Ka6))^na6*(1+A7/(A7+Ka7))^na7*(1+A8/(A8+Ka8))^na8*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3*(Ki4/(I4+Ki4))^ni4*(Ki5/(I5+Ki5))^ni5*(Ki6/(I6+Ki6))^ni6*(Ki7/(I7+Ki7))^ni7
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_422" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_421" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_420" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_419" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_418" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_417" name="A6" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_416" name="A7" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_368" name="A8" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_367" name="I1" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_366" name="I2" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_365" name="I3" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_364" name="I4" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_363" name="I5" order="12" role="modifier"/>
        <ParameterDescription key="FunctionParameter_362" name="I6" order="13" role="modifier"/>
        <ParameterDescription key="FunctionParameter_361" name="I7" order="14" role="modifier"/>
        <ParameterDescription key="FunctionParameter_360" name="V" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_388" name="Ka1" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_389" name="na1" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_390" name="Ka2" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_391" name="na2" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_392" name="Ka3" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_393" name="na3" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_423" name="Ka4" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_424" name="na4" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_425" name="Ka5" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_426" name="na5" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_427" name="Ka6" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_428" name="na6" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_429" name="Ka7" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_430" name="na7" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_431" name="Ka8" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_432" name="na8" order="31" role="constant"/>
        <ParameterDescription key="FunctionParameter_433" name="Ki1" order="32" role="constant"/>
        <ParameterDescription key="FunctionParameter_434" name="ni1" order="33" role="constant"/>
        <ParameterDescription key="FunctionParameter_435" name="Ki2" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_436" name="ni2" order="35" role="constant"/>
        <ParameterDescription key="FunctionParameter_437" name="Ki3" order="36" role="constant"/>
        <ParameterDescription key="FunctionParameter_438" name="ni3" order="37" role="constant"/>
        <ParameterDescription key="FunctionParameter_439" name="Ki4" order="38" role="constant"/>
        <ParameterDescription key="FunctionParameter_440" name="ni4" order="39" role="constant"/>
        <ParameterDescription key="FunctionParameter_441" name="Ki5" order="40" role="constant"/>
        <ParameterDescription key="FunctionParameter_442" name="ni5" order="41" role="constant"/>
        <ParameterDescription key="FunctionParameter_443" name="Ki6" order="42" role="constant"/>
        <ParameterDescription key="FunctionParameter_444" name="ni6" order="43" role="constant"/>
        <ParameterDescription key="FunctionParameter_445" name="Ki7" order="44" role="constant"/>
        <ParameterDescription key="FunctionParameter_446" name="ni7" order="45" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="transcr 1 inh 3 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(Ki1/(I1+Ki1))^ni1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_897" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_896" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_488" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_501" name="I1" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_502" name="V" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_487" name="Ka1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_486" name="na1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_485" name="Ka2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_484" name="na2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_483" name="Ka3" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_482" name="na3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_481" name="Ki1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_480" name="ni1" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="transcr 5 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3*(Ki4/(I4+Ki4))^ni4*(Ki5/(I5+Ki5))^ni5
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_467" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_468" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_469" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_470" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_471" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_472" name="I2" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_473" name="I3" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_474" name="I4" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_475" name="I5" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_476" name="V" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_477" name="Ka1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_478" name="na1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_479" name="Ka2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_466" name="na2" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_465" name="Ka3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_464" name="na3" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_463" name="Ka4" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_462" name="na4" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_461" name="Ki1" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_460" name="ni1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_459" name="Ki2" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_458" name="ni2" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_457" name="Ki3" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_456" name="ni3" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_455" name="Ki4" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_454" name="ni4" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_453" name="Ki5" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_452" name="ni5" order="27" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="transcr 0 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_920" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_919" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_918" name="Ka1" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_917" name="na1" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="transcr 2 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_913" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_914" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_915" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_916" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_912" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_911" name="I2" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_910" name="V" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_909" name="Ka1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_908" name="na1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_907" name="Ka2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_906" name="na2" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_905" name="Ka3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_904" name="na3" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_903" name="Ka4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_902" name="na4" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_901" name="Ki1" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_900" name="ni1" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_899" name="Ki2" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_898" name="ni2" order="18" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="transcr 3 inh 5 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(1+A5/(A5+Ka5))^na5*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_934" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_933" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_932" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_931" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_930" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_929" name="I1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_928" name="I2" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_927" name="I3" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_926" name="V" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_925" name="Ka1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_924" name="na1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_923" name="Ka2" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_922" name="na2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_921" name="Ka3" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_451" name="na3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_450" name="Ka4" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_449" name="na4" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_448" name="Ka5" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_447" name="na5" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_935" name="Ki1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_936" name="ni1" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_937" name="Ki2" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_938" name="ni2" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_939" name="Ki3" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_940" name="ni3" order="24" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_82" name="transcr 0 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_965" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_964" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_963" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_962" name="Ka1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_961" name="na1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_960" name="Ka2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_959" name="na2" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_83" name="transcr 3 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_83">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_952" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_953" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_954" name="I1" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_955" name="I2" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_956" name="I3" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_957" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_958" name="Ka1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_951" name="na1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_950" name="Ka2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_949" name="na2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_948" name="Ki1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_947" name="ni1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_946" name="Ki2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_945" name="ni2" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_944" name="Ki3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_943" name="ni3" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_84" name="transcr 1 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(Ki1/(I1+Ki1))^ni1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_979" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_978" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_977" name="Ki1" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_976" name="ni1" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_85" name="transcr 1 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_85">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3*(1+A4/(A4+Ka4))^na4*(Ki1/(I1+Ki1))^ni1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_972" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_973" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_974" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_975" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_971" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_970" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_969" name="Ka1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_968" name="na1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_967" name="Ka2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_966" name="na2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_941" name="Ka3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_942" name="na3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_980" name="Ka4" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_981" name="na4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_982" name="Ki1" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_983" name="ni1" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_86" name="transcr 2 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_86">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_999" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_998" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_997" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_996" name="Ki1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_995" name="ni1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_994" name="Ki2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_993" name="ni2" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_87" name="transcr 5 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_87">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3*(Ki4/(I4+Ki4))^ni4*(Ki5/(I5+Ki5))^ni5
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_986" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_987" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_988" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_989" name="I4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_990" name="I5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_991" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_992" name="Ki1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_985" name="ni1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_984" name="Ki2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1000" name="ni2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1001" name="Ki3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1002" name="ni3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1003" name="Ki4" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_1004" name="ni4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_1005" name="Ki5" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_1006" name="ni5" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_88" name="transcr 0 inh 3 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_88">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(1+A3/(A3+Ka3))^na3
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1022" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1021" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1020" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1019" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1018" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1017" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1016" name="Ka2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1015" name="na2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1014" name="Ka3" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1013" name="na3" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_89" name="transcr 0 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_89">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1026" name="V" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_90" name="transcr 1 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_90">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(Ki1/(I1+Ki1))^ni1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1025" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1024" name="I1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1023" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_1007" name="Ka1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1008" name="na1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1009" name="Ki1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1010" name="ni1" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_91" name="transcr 1 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_91">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(1+A2/(A2+Ka2))^na2*(Ki1/(I1+Ki1))^ni1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1031" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1030" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1029" name="I1" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1028" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1027" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1012" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1011" name="Ka2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1032" name="na2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1033" name="Ki1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1034" name="ni1" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="transcr 4 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_92">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3*(Ki4/(I4+Ki4))^ni4
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1044" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1043" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1042" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1041" name="I4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1040" name="V" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1039" name="Ki1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1038" name="ni1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1037" name="Ki2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1036" name="ni2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1035" name="Ki3" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_1045" name="ni3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_1046" name="Ki4" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_1047" name="ni4" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="transcr 2 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_93">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(1+A1/(A1+Ka1))^na1*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1060" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1059" name="I1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1058" name="I2" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1057" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1056" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1055" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1054" name="Ki1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1053" name="ni1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1052" name="Ki2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1051" name="ni2" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="transcr 3 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_94">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        V*(Ki1/(I1+Ki1))^ni1*(Ki2/(I2+Ki2))^ni2*(Ki3/(I3+Ki3))^ni3
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_1067" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1066" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1065" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_1064" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_1063" name="Ki1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_1062" name="ni1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_1061" name="Ki2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_1048" name="ni2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_1049" name="Ki3" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_1050" name="ni3" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="wt CoopSF41b - Perturbation 1 - G56 10x induction" simulationType="time" timeUnit="min" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="nmol" type="deterministic" avogadroConstant="6.0221408570000002e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_1">
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <dcterms:description>Mendes, Sha, Ye (2003) Artificial gene networks for objective comparison of analysis algorithms. Bioinformatics S2:122-129</dcterms:description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:doi:10.1093/bioinformatics/btg1069"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
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
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
<h1>CoopSF4_001, from AGN data set</h1>
<p>This model is based on CoopSF4_001, from the AGN dataset. The topology
was kept the same, but the kinetic constants were altered to obtain a
network wiht rich dynamics. CoopSF4_001 is a scale-free gene network 
with 100 genes and 200 total input connections. The model has 100 
variables and 400 parameters.</p>
<p>Here the initial condition is that G56 is now transcribed at 10x its basal rate.</p>
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cell" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Compartment_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_34" name="G1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="G2" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="G3" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="G4" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="G5" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="G6" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="G7" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="G8" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="G9" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="G10" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="G11" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="G12" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="G13" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="G14" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="G15" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="G16" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="G17" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_0" name="G18" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="G19" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="G20" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_2">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="G21" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="G22" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_4">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_122" name="G23" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_122">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_123" name="G24" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_123">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_124" name="G25" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_124">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_125" name="G26" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_125">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_126" name="G27" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_126">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_127" name="G28" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_127">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_128" name="G29" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_128">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_129" name="G30" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_129">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_130" name="G31" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_130">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_131" name="G32" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_131">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_132" name="G33" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_132">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_133" name="G34" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_133">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_134" name="G35" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_134">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_135" name="G36" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_135">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_136" name="G37" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_136">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_137" name="G38" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_137">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_138" name="G39" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_138">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_139" name="G40" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_139">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_140" name="G41" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_140">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_141" name="G42" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_141">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_142" name="G43" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_142">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_143" name="G44" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_143">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_144" name="G45" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_144">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_145" name="G46" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_145">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_146" name="G47" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_146">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_147" name="G48" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_147">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_148" name="G49" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_148">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_149" name="G50" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_149">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_150" name="G51" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_150">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_151" name="G52" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_151">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_152" name="G53" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_152">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_153" name="G54" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_153">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_154" name="G55" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_154">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_155" name="G56" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_155">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_156" name="G57" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_156">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_157" name="G58" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_157">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_158" name="G59" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_158">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_159" name="G60" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_159">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_160" name="G61" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_160">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_161" name="G62" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_161">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_162" name="G63" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_162">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_163" name="G64" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_163">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_164" name="G65" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_164">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_165" name="G66" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_165">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_166" name="G67" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_166">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_167" name="G68" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_167">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_168" name="G69" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_168">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_169" name="G70" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_169">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_170" name="G71" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_170">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_171" name="G72" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_171">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_172" name="G73" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_172">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_173" name="G74" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_173">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_174" name="G75" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_174">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_175" name="G76" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_175">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_176" name="G77" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_176">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_177" name="G78" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_177">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_178" name="G79" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_178">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_179" name="G80" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_179">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_180" name="G81" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_180">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_181" name="G82" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_181">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_182" name="G83" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_182">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_183" name="G84" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_183">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_184" name="G85" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_184">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_185" name="G86" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_185">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_186" name="G87" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_186">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_187" name="G88" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_187">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_188" name="G89" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_188">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_189" name="G90" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_189">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_190" name="G91" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_190">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_191" name="G92" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_191">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_192" name="G93" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_192">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_193" name="G94" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_193">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_194" name="G95" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_194">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_195" name="G96" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_195">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_196" name="G97" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_196">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_197" name="G98" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_197">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_198" name="G99" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_198">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_199" name="G100" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_199">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_25" name="G1 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_177" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_176" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_139" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_160" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7993" name="V" value="5.8"/>
          <Constant key="Parameter_2982" name="Ka1" value="0.4"/>
          <Constant key="Parameter_2969" name="na1" value="4"/>
          <Constant key="Parameter_7989" name="Ka2" value="1e-06"/>
          <Constant key="Parameter_2967" name="na2" value="2.2"/>
          <Constant key="Parameter_2970" name="Ka3" value="42.4453"/>
          <Constant key="Parameter_7988" name="na3" value="4"/>
          <Constant key="Parameter_2979" name="Ka4" value="0.01"/>
          <Constant key="Parameter_5121" name="na4" value="4"/>
          <Constant key="Parameter_5126" name="Ka5" value="2"/>
          <Constant key="Parameter_5037" name="na5" value="4"/>
          <Constant key="Parameter_2980" name="Ka6" value="4e-05"/>
          <Constant key="Parameter_5124" name="na6" value="4"/>
          <Constant key="Parameter_2826" name="Ka7" value="0.01"/>
          <Constant key="Parameter_3695" name="na7" value="4"/>
          <Constant key="Parameter_5069" name="Ka8" value="0.01"/>
          <Constant key="Parameter_5066" name="na8" value="4"/>
          <Constant key="Parameter_5047" name="Ka9" value="0.01"/>
          <Constant key="Parameter_5030" name="na9" value="4"/>
          <Constant key="Parameter_5034" name="Ki1" value="0.008"/>
          <Constant key="Parameter_5038" name="ni1" value="4"/>
          <Constant key="Parameter_5043" name="Ki2" value="8.5"/>
          <Constant key="Parameter_5027" name="ni2" value="2.6"/>
          <Constant key="Parameter_5025" name="Ki3" value="123"/>
          <Constant key="Parameter_5035" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_74" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_895">
              <SourceParameter reference="Metabolite_177"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_894">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_893">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_892">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_891">
              <SourceParameter reference="Metabolite_176"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_890">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_889">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_888">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_887">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_886">
              <SourceParameter reference="Metabolite_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_885">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_884">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_883">
              <SourceParameter reference="Parameter_7993"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_882">
              <SourceParameter reference="Parameter_2982"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_881">
              <SourceParameter reference="Parameter_2969"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_880">
              <SourceParameter reference="Parameter_7989"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_879">
              <SourceParameter reference="Parameter_2967"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_878">
              <SourceParameter reference="Parameter_2970"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="Parameter_7988"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="Parameter_2979"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Parameter_5121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="Parameter_5126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="Parameter_5037"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="Parameter_2980"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="Parameter_5124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="Parameter_2826"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="Parameter_3695"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Parameter_5069"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="Parameter_5066"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="Parameter_5047"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Parameter_5030"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="Parameter_5034"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="Parameter_5038"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="Parameter_5043"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="Parameter_5027"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="Parameter_5025"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Parameter_5035"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="G1 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4287" name="k1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4287"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="G2 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_172" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_162" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_26" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4288" name="V" value="12300"/>
          <Constant key="Parameter_4284" name="Ka1" value="0.003"/>
          <Constant key="Parameter_5064" name="na1" value="4"/>
          <Constant key="Parameter_6504" name="Ka2" value="0.607897"/>
          <Constant key="Parameter_6508" name="na2" value="4"/>
          <Constant key="Parameter_6463" name="Ka3" value="0.152614"/>
          <Constant key="Parameter_4512" name="na3" value="4"/>
          <Constant key="Parameter_6503" name="Ka4" value="0.235689"/>
          <Constant key="Parameter_4338" name="na4" value="4"/>
          <Constant key="Parameter_6501" name="Ka5" value="12"/>
          <Constant key="Parameter_4506" name="na5" value="4"/>
          <Constant key="Parameter_4502" name="Ki1" value="0.490247"/>
          <Constant key="Parameter_6497" name="ni1" value="4"/>
          <Constant key="Parameter_6494" name="Ki2" value="0.000721363"/>
          <Constant key="Parameter_6464" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_75" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_415">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_414">
              <SourceParameter reference="Metabolite_172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_413">
              <SourceParameter reference="Metabolite_162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_412">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_411">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_410">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_409">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_408">
              <SourceParameter reference="Parameter_4288"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_407">
              <SourceParameter reference="Parameter_4284"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_406">
              <SourceParameter reference="Parameter_5064"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_405">
              <SourceParameter reference="Parameter_6504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_404">
              <SourceParameter reference="Parameter_6508"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_403">
              <SourceParameter reference="Parameter_6463"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_402">
              <SourceParameter reference="Parameter_4512"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_401">
              <SourceParameter reference="Parameter_6503"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_400">
              <SourceParameter reference="Parameter_4338"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_399">
              <SourceParameter reference="Parameter_6501"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_398">
              <SourceParameter reference="Parameter_4506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_397">
              <SourceParameter reference="Parameter_4502"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_396">
              <SourceParameter reference="Parameter_6497"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_395">
              <SourceParameter reference="Parameter_6494"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_394">
              <SourceParameter reference="Parameter_6464"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="G2 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6507" name="k1" value="0.031"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6507"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="G3 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_190" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_184" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_164" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_122" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_144" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_145" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_150" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_154" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_196" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6506" name="V" value="49"/>
          <Constant key="Parameter_6505" name="Ka1" value="12.243"/>
          <Constant key="Parameter_6512" name="na1" value="4"/>
          <Constant key="Parameter_6511" name="Ka2" value="3.25203e-08"/>
          <Constant key="Parameter_6510" name="na2" value="4"/>
          <Constant key="Parameter_6509" name="Ka3" value="5.673e-06"/>
          <Constant key="Parameter_6516" name="na3" value="4"/>
          <Constant key="Parameter_6515" name="Ka4" value="0.877014"/>
          <Constant key="Parameter_6514" name="na4" value="4"/>
          <Constant key="Parameter_6459" name="Ka5" value="0.008"/>
          <Constant key="Parameter_6457" name="na5" value="4"/>
          <Constant key="Parameter_6458" name="Ka6" value="1.73921e-12"/>
          <Constant key="Parameter_6460" name="na6" value="4"/>
          <Constant key="Parameter_6455" name="Ka7" value="7.1734"/>
          <Constant key="Parameter_6499" name="na7" value="4"/>
          <Constant key="Parameter_6513" name="Ka8" value="0.246835"/>
          <Constant key="Parameter_6520" name="na8" value="4"/>
          <Constant key="Parameter_6519" name="Ki1" value="4.74523e-07"/>
          <Constant key="Parameter_6518" name="ni1" value="4"/>
          <Constant key="Parameter_6517" name="Ki2" value="2.37538"/>
          <Constant key="Parameter_6524" name="ni2" value="4"/>
          <Constant key="Parameter_6523" name="Ki3" value="3.69e-05"/>
          <Constant key="Parameter_6522" name="ni3" value="4"/>
          <Constant key="Parameter_6521" name="Ki4" value="31962"/>
          <Constant key="Parameter_6528" name="ni4" value="4"/>
          <Constant key="Parameter_6527" name="Ki5" value="10.2279"/>
          <Constant key="Parameter_6526" name="ni5" value="4"/>
          <Constant key="Parameter_6525" name="Ki6" value="0.000391"/>
          <Constant key="Parameter_6532" name="ni6" value="4"/>
          <Constant key="Parameter_6531" name="Ki7" value="3.90854"/>
          <Constant key="Parameter_6530" name="ni7" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_76" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="Metabolite_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="Metabolite_184"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_418">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_417">
              <SourceParameter reference="Metabolite_164"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_416">
              <SourceParameter reference="Metabolite_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Metabolite_144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="Metabolite_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="Metabolite_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Metabolite_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="Metabolite_196"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="Parameter_6506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="Parameter_6505"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_389">
              <SourceParameter reference="Parameter_6512"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_390">
              <SourceParameter reference="Parameter_6511"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_391">
              <SourceParameter reference="Parameter_6510"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_392">
              <SourceParameter reference="Parameter_6509"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_393">
              <SourceParameter reference="Parameter_6516"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="Parameter_6515"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="Parameter_6514"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="Parameter_6459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="Parameter_6457"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="Parameter_6458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="Parameter_6460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="Parameter_6455"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="Parameter_6499"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="Parameter_6513"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="Parameter_6520"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="Parameter_6519"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="Parameter_6518"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="Parameter_6517"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="Parameter_6524"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Parameter_6523"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Parameter_6522"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Parameter_6521"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="Parameter_6528"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Parameter_6527"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Parameter_6526"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="Parameter_6525"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Parameter_6532"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="Parameter_6531"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Parameter_6530"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="G3 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6529" name="k1" value="0.008"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6529"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="G4 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_22" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_156" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_155" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6536" name="V" value="33"/>
          <Constant key="Parameter_6535" name="Ka1" value="0.122081"/>
          <Constant key="Parameter_6534" name="na1" value="3"/>
          <Constant key="Parameter_6533" name="Ka2" value="1.41285e-06"/>
          <Constant key="Parameter_6540" name="na2" value="3"/>
          <Constant key="Parameter_6538" name="Ka3" value="5.36239e-05"/>
          <Constant key="Parameter_6539" name="na3" value="3"/>
          <Constant key="Parameter_6537" name="Ki1" value="0.0184689"/>
          <Constant key="Parameter_6444" name="ni1" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_77" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_897">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_896">
              <SourceParameter reference="Metabolite_156"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="Metabolite_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_501">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_502">
              <SourceParameter reference="Parameter_6536"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Parameter_6535"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="Parameter_6534"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="Parameter_6533"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="Parameter_6540"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="Parameter_6538"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Parameter_6539"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="Parameter_6537"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Parameter_6444"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="G4 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6443" name="k1" value="0.06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6443"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="G5 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_17">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_190" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_124" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_192" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_155" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_173" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_174" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_149" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6546" name="V" value="43"/>
          <Constant key="Parameter_6545" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6544" name="na1" value="4"/>
          <Constant key="Parameter_6543" name="Ka2" value="0.12"/>
          <Constant key="Parameter_6550" name="na2" value="4"/>
          <Constant key="Parameter_6549" name="Ka3" value="0.01"/>
          <Constant key="Parameter_6548" name="na3" value="4"/>
          <Constant key="Parameter_6547" name="Ka4" value="0.07"/>
          <Constant key="Parameter_6554" name="na4" value="4"/>
          <Constant key="Parameter_6552" name="Ki1" value="23"/>
          <Constant key="Parameter_6551" name="ni1" value="4"/>
          <Constant key="Parameter_6542" name="Ki2" value="2.3e-05"/>
          <Constant key="Parameter_6553" name="ni2" value="4"/>
          <Constant key="Parameter_6541" name="Ki3" value="0.43"/>
          <Constant key="Parameter_6442" name="ni3" value="4"/>
          <Constant key="Parameter_6441" name="Ki4" value="0.143"/>
          <Constant key="Parameter_6562" name="ni4" value="4"/>
          <Constant key="Parameter_6561" name="Ki5" value="0.0004"/>
          <Constant key="Parameter_6560" name="ni5" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_78" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="Metabolite_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="Metabolite_192"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="Metabolite_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Metabolite_173"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="Metabolite_174"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="Metabolite_149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="Parameter_6546"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Parameter_6545"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Parameter_6544"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="Parameter_6543"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="Parameter_6550"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="Parameter_6549"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Parameter_6548"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="Parameter_6547"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Parameter_6554"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Parameter_6552"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="Parameter_6551"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="Parameter_6542"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="Parameter_6553"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Parameter_6541"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="Parameter_6442"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="Parameter_6441"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="Parameter_6562"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Parameter_6561"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="Parameter_6560"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="G5 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_16">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6559" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6559"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="G6 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_15">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6566" name="V" value="1.2"/>
          <Constant key="Parameter_6565" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6564" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6566"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6565"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6564"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_0" name="G6 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6563" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6563"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="G7 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_20" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_128" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_199" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_181" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6570" name="V" value="23"/>
          <Constant key="Parameter_6569" name="Ka1" value="6e-05"/>
          <Constant key="Parameter_6568" name="na1" value="4"/>
          <Constant key="Parameter_6567" name="Ka2" value="0.01"/>
          <Constant key="Parameter_6574" name="na2" value="4"/>
          <Constant key="Parameter_6573" name="Ka3" value="0.01"/>
          <Constant key="Parameter_6572" name="na3" value="4"/>
          <Constant key="Parameter_6571" name="Ka4" value="0.01"/>
          <Constant key="Parameter_6578" name="na4" value="4"/>
          <Constant key="Parameter_6577" name="Ki1" value="5"/>
          <Constant key="Parameter_6576" name="ni1" value="4"/>
          <Constant key="Parameter_6575" name="Ki2" value="0.01"/>
          <Constant key="Parameter_6582" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_80" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_913">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_914">
              <SourceParameter reference="Metabolite_128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_915">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_916">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_912">
              <SourceParameter reference="Metabolite_199"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_911">
              <SourceParameter reference="Metabolite_181"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_910">
              <SourceParameter reference="Parameter_6570"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_909">
              <SourceParameter reference="Parameter_6569"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_908">
              <SourceParameter reference="Parameter_6568"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_907">
              <SourceParameter reference="Parameter_6567"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_906">
              <SourceParameter reference="Parameter_6574"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_905">
              <SourceParameter reference="Parameter_6573"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_904">
              <SourceParameter reference="Parameter_6572"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_903">
              <SourceParameter reference="Parameter_6571"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_902">
              <SourceParameter reference="Parameter_6578"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_901">
              <SourceParameter reference="Parameter_6577"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_900">
              <SourceParameter reference="Parameter_6576"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_899">
              <SourceParameter reference="Parameter_6575"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_898">
              <SourceParameter reference="Parameter_6582"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="G7 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_2">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6581" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6581"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="G8 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_198" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_183" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_141" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_194" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6580" name="V" value="5.3"/>
          <Constant key="Parameter_6579" name="Ka1" value="0.1"/>
          <Constant key="Parameter_6586" name="na1" value="4"/>
          <Constant key="Parameter_6585" name="Ka2" value="19"/>
          <Constant key="Parameter_6584" name="na2" value="4"/>
          <Constant key="Parameter_6583" name="Ka3" value="0.811048"/>
          <Constant key="Parameter_6590" name="na3" value="3"/>
          <Constant key="Parameter_6589" name="Ka4" value="20"/>
          <Constant key="Parameter_6588" name="na4" value="4"/>
          <Constant key="Parameter_6587" name="Ka5" value="0.01"/>
          <Constant key="Parameter_6594" name="na5" value="4"/>
          <Constant key="Parameter_6593" name="Ki1" value="0.08"/>
          <Constant key="Parameter_6592" name="ni1" value="4"/>
          <Constant key="Parameter_6591" name="Ki2" value="1.7"/>
          <Constant key="Parameter_6598" name="ni2" value="3"/>
          <Constant key="Parameter_6597" name="Ki3" value="0.1"/>
          <Constant key="Parameter_6596" name="ni3" value="3.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_81" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_934">
              <SourceParameter reference="Metabolite_198"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_933">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_932">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_931">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_930">
              <SourceParameter reference="Metabolite_183"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_929">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_928">
              <SourceParameter reference="Metabolite_194"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_927">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_926">
              <SourceParameter reference="Parameter_6580"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_925">
              <SourceParameter reference="Parameter_6579"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_924">
              <SourceParameter reference="Parameter_6586"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_923">
              <SourceParameter reference="Parameter_6585"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_922">
              <SourceParameter reference="Parameter_6584"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_921">
              <SourceParameter reference="Parameter_6583"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="Parameter_6590"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="Parameter_6589"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="Parameter_6588"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="Parameter_6587"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Parameter_6594"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_935">
              <SourceParameter reference="Parameter_6593"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_936">
              <SourceParameter reference="Parameter_6592"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_937">
              <SourceParameter reference="Parameter_6591"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_938">
              <SourceParameter reference="Parameter_6598"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_939">
              <SourceParameter reference="Parameter_6597"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_940">
              <SourceParameter reference="Parameter_6596"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="G8 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_4">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6595" name="k1" value="2.53"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6595"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_216" name="G9 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_216">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_182" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6602" name="V" value="1"/>
          <Constant key="Parameter_6601" name="Ka1" value="0.05"/>
          <Constant key="Parameter_6600" name="na1" value="4"/>
          <Constant key="Parameter_6599" name="Ka2" value="0.02"/>
          <Constant key="Parameter_6606" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_965">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_964">
              <SourceParameter reference="Metabolite_182"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_963">
              <SourceParameter reference="Parameter_6602"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_962">
              <SourceParameter reference="Parameter_6601"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_961">
              <SourceParameter reference="Parameter_6600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_960">
              <SourceParameter reference="Parameter_6599"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_959">
              <SourceParameter reference="Parameter_6606"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_217" name="G9 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_217">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6605" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6605"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_218" name="G10 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_218">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_166" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_137" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_129" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_125" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6604" name="V" value="6"/>
          <Constant key="Parameter_6603" name="Ka1" value="1e-08"/>
          <Constant key="Parameter_6610" name="na1" value="4"/>
          <Constant key="Parameter_6609" name="Ka2" value="0.01"/>
          <Constant key="Parameter_6608" name="na2" value="4"/>
          <Constant key="Parameter_6607" name="Ki1" value="0.3"/>
          <Constant key="Parameter_6558" name="ni1" value="4"/>
          <Constant key="Parameter_6557" name="Ki2" value="0.01"/>
          <Constant key="Parameter_6556" name="ni2" value="4"/>
          <Constant key="Parameter_6617" name="Ki3" value="1e-05"/>
          <Constant key="Parameter_6616" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_83" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_952">
              <SourceParameter reference="Metabolite_166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_953">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_954">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_955">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_956">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_957">
              <SourceParameter reference="Parameter_6604"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_958">
              <SourceParameter reference="Parameter_6603"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_951">
              <SourceParameter reference="Parameter_6610"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_950">
              <SourceParameter reference="Parameter_6609"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_949">
              <SourceParameter reference="Parameter_6608"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_948">
              <SourceParameter reference="Parameter_6607"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_947">
              <SourceParameter reference="Parameter_6558"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_946">
              <SourceParameter reference="Parameter_6557"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_945">
              <SourceParameter reference="Parameter_6556"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_944">
              <SourceParameter reference="Parameter_6617"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_943">
              <SourceParameter reference="Parameter_6616"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_219" name="G10 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_219">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6615" name="k1" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6615"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_220" name="G11 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_220">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6614" name="V" value="27"/>
          <Constant key="Parameter_6621" name="Ki1" value="5.4"/>
          <Constant key="Parameter_6620" name="ni1" value="2.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_6614"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_6621"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_6620"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_221" name="G11 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_221">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6619" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6619"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_222" name="G12 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_222">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6618" name="V" value="1.2"/>
          <Constant key="Parameter_6625" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6624" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6618"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6625"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6624"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_223" name="G12 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_223">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6623" name="k1" value="1.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6623"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_224" name="G13 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_224">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_170" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_130" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6622" name="V" value="3.6"/>
          <Constant key="Parameter_6629" name="Ka1" value="1e-06"/>
          <Constant key="Parameter_6628" name="na1" value="4"/>
          <Constant key="Parameter_6627" name="Ka2" value="0.8"/>
          <Constant key="Parameter_6626" name="na2" value="4"/>
          <Constant key="Parameter_6633" name="Ka3" value="1e-06"/>
          <Constant key="Parameter_6632" name="na3" value="4"/>
          <Constant key="Parameter_6631" name="Ka4" value="2e-06"/>
          <Constant key="Parameter_6630" name="na4" value="4"/>
          <Constant key="Parameter_6637" name="Ki1" value="0.032"/>
          <Constant key="Parameter_6636" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_85" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_972">
              <SourceParameter reference="Metabolite_170"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_973">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_974">
              <SourceParameter reference="Metabolite_130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_975">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_971">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_970">
              <SourceParameter reference="Parameter_6622"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_969">
              <SourceParameter reference="Parameter_6629"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_968">
              <SourceParameter reference="Parameter_6628"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_967">
              <SourceParameter reference="Parameter_6627"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_966">
              <SourceParameter reference="Parameter_6626"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_941">
              <SourceParameter reference="Parameter_6633"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_942">
              <SourceParameter reference="Parameter_6632"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_980">
              <SourceParameter reference="Parameter_6631"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_981">
              <SourceParameter reference="Parameter_6630"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_982">
              <SourceParameter reference="Parameter_6637"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_983">
              <SourceParameter reference="Parameter_6636"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_225" name="G13 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_225">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6635" name="k1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6635"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_226" name="G14 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_226">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6634" name="V" value="1.6"/>
          <Constant key="Parameter_6641" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6640" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6634"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6641"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6640"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_227" name="G14 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_227">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6639" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6639"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_228" name="G15 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_228">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_175" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6638" name="V" value="3"/>
          <Constant key="Parameter_6645" name="Ki1" value="12"/>
          <Constant key="Parameter_6644" name="ni1" value="4"/>
          <Constant key="Parameter_6643" name="Ki2" value="58"/>
          <Constant key="Parameter_6642" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_175"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_6638"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_6645"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_6644"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_6643"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_6642"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_229" name="G15 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_229">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6613" name="k1" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6613"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_230" name="G16 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_230">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_140" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_162" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_197" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6612" name="V" value="7"/>
          <Constant key="Parameter_6651" name="Ki1" value="933"/>
          <Constant key="Parameter_6650" name="ni1" value="4"/>
          <Constant key="Parameter_6649" name="Ki2" value="21"/>
          <Constant key="Parameter_6648" name="ni2" value="4"/>
          <Constant key="Parameter_6655" name="Ki3" value="235"/>
          <Constant key="Parameter_6654" name="ni3" value="4"/>
          <Constant key="Parameter_6653" name="Ki4" value="1000"/>
          <Constant key="Parameter_6652" name="ni4" value="4"/>
          <Constant key="Parameter_6659" name="Ki5" value="0.503603"/>
          <Constant key="Parameter_6658" name="ni5" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_87" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_986">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_987">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_988">
              <SourceParameter reference="Metabolite_140"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_989">
              <SourceParameter reference="Metabolite_162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_990">
              <SourceParameter reference="Metabolite_197"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_991">
              <SourceParameter reference="Parameter_6612"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_992">
              <SourceParameter reference="Parameter_6651"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_985">
              <SourceParameter reference="Parameter_6650"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_984">
              <SourceParameter reference="Parameter_6649"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1000">
              <SourceParameter reference="Parameter_6648"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1001">
              <SourceParameter reference="Parameter_6655"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1002">
              <SourceParameter reference="Parameter_6654"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1003">
              <SourceParameter reference="Parameter_6653"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1004">
              <SourceParameter reference="Parameter_6652"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1005">
              <SourceParameter reference="Parameter_6659"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1006">
              <SourceParameter reference="Parameter_6658"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_231" name="G16 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_231">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6657" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6657"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_232" name="G17 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_232">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_144" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_148" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_177" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6656" name="V" value="1"/>
          <Constant key="Parameter_6663" name="Ka1" value="231"/>
          <Constant key="Parameter_6662" name="na1" value="4"/>
          <Constant key="Parameter_6661" name="Ka2" value="189"/>
          <Constant key="Parameter_6660" name="na2" value="4"/>
          <Constant key="Parameter_6667" name="Ka3" value="0.01"/>
          <Constant key="Parameter_6666" name="na3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_88" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1022">
              <SourceParameter reference="Metabolite_144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1021">
              <SourceParameter reference="Metabolite_148"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1020">
              <SourceParameter reference="Metabolite_177"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1019">
              <SourceParameter reference="Parameter_6656"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1018">
              <SourceParameter reference="Parameter_6663"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1017">
              <SourceParameter reference="Parameter_6662"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1016">
              <SourceParameter reference="Parameter_6661"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1015">
              <SourceParameter reference="Parameter_6660"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1014">
              <SourceParameter reference="Parameter_6667"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1013">
              <SourceParameter reference="Parameter_6666"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_233" name="G17 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_233">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6665" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6665"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_234" name="G18 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_234">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6664" name="V" value="100"/>
          <Constant key="Parameter_6647" name="Ki1" value="43"/>
          <Constant key="Parameter_6672" name="ni1" value="4"/>
          <Constant key="Parameter_6671" name="Ki2" value="0.01"/>
          <Constant key="Parameter_6670" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_6664"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_6647"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_6672"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_6671"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_6670"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_235" name="G18 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_235">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6669" name="k1" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6669"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_236" name="G19 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_236">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_124" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6676" name="V" value="1"/>
          <Constant key="Parameter_6675" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6674" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6676"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6675"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6674"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_237" name="G19 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_237">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6673" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6673"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_238" name="G20 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_238">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_190" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6680" name="V" value="12.3"/>
          <Constant key="Parameter_6679" name="Ki1" value="7.43"/>
          <Constant key="Parameter_6678" name="ni1" value="4"/>
          <Constant key="Parameter_6677" name="Ki2" value="4.6"/>
          <Constant key="Parameter_6684" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_6680"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_6679"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_6678"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_6677"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_6684"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_239" name="G20 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_239">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6683" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6683"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_240" name="G21 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_240">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_147" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_157" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_165" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_193" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6682" name="V" value="0.6"/>
          <Constant key="Parameter_6681" name="Ka1" value="5.87104"/>
          <Constant key="Parameter_6688" name="na1" value="4"/>
          <Constant key="Parameter_6687" name="Ka2" value="165.852"/>
          <Constant key="Parameter_6686" name="na2" value="4"/>
          <Constant key="Parameter_6685" name="Ka3" value="3.58648"/>
          <Constant key="Parameter_6668" name="na3" value="4"/>
          <Constant key="Parameter_6693" name="Ka4" value="386.19"/>
          <Constant key="Parameter_6692" name="na4" value="4"/>
          <Constant key="Parameter_6691" name="Ki1" value="11.405"/>
          <Constant key="Parameter_6690" name="ni1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_85" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_972">
              <SourceParameter reference="Metabolite_147"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_973">
              <SourceParameter reference="Metabolite_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_974">
              <SourceParameter reference="Metabolite_165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_975">
              <SourceParameter reference="Metabolite_193"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_971">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_970">
              <SourceParameter reference="Parameter_6682"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_969">
              <SourceParameter reference="Parameter_6681"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_968">
              <SourceParameter reference="Parameter_6688"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_967">
              <SourceParameter reference="Parameter_6687"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_966">
              <SourceParameter reference="Parameter_6686"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_941">
              <SourceParameter reference="Parameter_6685"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_942">
              <SourceParameter reference="Parameter_6668"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_980">
              <SourceParameter reference="Parameter_6693"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_981">
              <SourceParameter reference="Parameter_6692"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_982">
              <SourceParameter reference="Parameter_6691"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_983">
              <SourceParameter reference="Parameter_6690"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_241" name="G21 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_241">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6697" name="k1" value="5.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6697"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_242" name="G22 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_242">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6696" name="V" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6696"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_243" name="G22 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_243">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6695" name="k1" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6695"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_244" name="G23 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_244">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_122" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6694" name="V" value="1"/>
          <Constant key="Parameter_6701" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6700" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6694"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6701"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6700"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_245" name="G23 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_245">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_122" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6699" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6699"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_122"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_246" name="G24 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_246">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6698" name="V" value="1"/>
          <Constant key="Parameter_6705" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6703" name="na1" value="4"/>
          <Constant key="Parameter_6704" name="Ka2" value="0.01"/>
          <Constant key="Parameter_6702" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_965">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_964">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_963">
              <SourceParameter reference="Parameter_6698"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_962">
              <SourceParameter reference="Parameter_6705"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_961">
              <SourceParameter reference="Parameter_6703"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_960">
              <SourceParameter reference="Parameter_6704"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_959">
              <SourceParameter reference="Parameter_6702"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_247" name="G24 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_247">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6689" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6689"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_123"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_248" name="G25 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_248">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_124" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6755" name="V" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6755"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_249" name="G25 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_249">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_124" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6646" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6646"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_250" name="G26 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_250">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_186" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_198" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6708" name="V" value="3"/>
          <Constant key="Parameter_6711" name="Ka1" value="0.02"/>
          <Constant key="Parameter_6710" name="na1" value="4"/>
          <Constant key="Parameter_6709" name="Ki1" value="0.05"/>
          <Constant key="Parameter_6730" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_186"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_198"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_6708"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_6711"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_6710"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_6709"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_6730"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_251" name="G26 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_251">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6743" name="k1" value="1.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6743"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_252" name="G27 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_252">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_126" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6732" name="V" value="1"/>
          <Constant key="Parameter_6729" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6745" name="na1" value="4"/>
          <Constant key="Parameter_6731" name="Ki1" value="2323"/>
          <Constant key="Parameter_6726" name="ni1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_6732"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_6729"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_6745"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_6731"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_6726"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_253" name="G27 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_253">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_126" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6727" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6727"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_126"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_254" name="G28 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_254">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_127" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6750" name="V" value="15"/>
          <Constant key="Parameter_6733" name="Ki1" value="3.2"/>
          <Constant key="Parameter_6741" name="ni1" value="4"/>
          <Constant key="Parameter_6725" name="Ki2" value="8.4"/>
          <Constant key="Parameter_6744" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_6750"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_6733"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_6741"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_6725"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_6744"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_255" name="G28 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_255">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_127" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6738" name="k1" value="0.07"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6738"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_256" name="G29 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_256">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_128" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_137" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_195" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6742" name="V" value="1.2"/>
          <Constant key="Parameter_6721" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6720" name="na1" value="4"/>
          <Constant key="Parameter_6734" name="Ka2" value="12"/>
          <Constant key="Parameter_6739" name="na2" value="4"/>
          <Constant key="Parameter_6707" name="Ki1" value="163"/>
          <Constant key="Parameter_6724" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_91" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1031">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1030">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1029">
              <SourceParameter reference="Metabolite_195"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1028">
              <SourceParameter reference="Parameter_6742"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1027">
              <SourceParameter reference="Parameter_6721"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1012">
              <SourceParameter reference="Parameter_6720"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1011">
              <SourceParameter reference="Parameter_6734"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1032">
              <SourceParameter reference="Parameter_6739"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1033">
              <SourceParameter reference="Parameter_6707"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1034">
              <SourceParameter reference="Parameter_6724"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_257" name="G29 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_257">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_128" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6735" name="k1" value="0.134"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6735"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_128"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_258" name="G30 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_258">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_129" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6736" name="V" value="1"/>
          <Constant key="Parameter_6737" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6740" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6736"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6737"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6740"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_259" name="G30 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_259">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_129" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6749" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6749"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_260" name="G31 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_260">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_130" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_132" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_160" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_196" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6706" name="V" value="14"/>
          <Constant key="Parameter_6748" name="Ki1" value="5.3"/>
          <Constant key="Parameter_6746" name="ni1" value="4"/>
          <Constant key="Parameter_6747" name="Ki2" value="3"/>
          <Constant key="Parameter_6752" name="ni2" value="4"/>
          <Constant key="Parameter_6754" name="Ki3" value="15"/>
          <Constant key="Parameter_6715" name="ni3" value="4"/>
          <Constant key="Parameter_6759" name="Ki4" value="0.15"/>
          <Constant key="Parameter_6713" name="ni4" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_92" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1044">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1043">
              <SourceParameter reference="Metabolite_132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1042">
              <SourceParameter reference="Metabolite_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1041">
              <SourceParameter reference="Metabolite_196"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1040">
              <SourceParameter reference="Parameter_6706"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1039">
              <SourceParameter reference="Parameter_6748"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1038">
              <SourceParameter reference="Parameter_6746"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1037">
              <SourceParameter reference="Parameter_6747"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1036">
              <SourceParameter reference="Parameter_6752"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1035">
              <SourceParameter reference="Parameter_6754"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1045">
              <SourceParameter reference="Parameter_6715"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1046">
              <SourceParameter reference="Parameter_6759"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1047">
              <SourceParameter reference="Parameter_6713"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_261" name="G31 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_261">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_130" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6712" name="k1" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6712"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_130"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_262" name="G32 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_262">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_131" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4438" name="V" value="9"/>
          <Constant key="Parameter_4446" name="Ki1" value="36"/>
          <Constant key="Parameter_4578" name="ni1" value="2"/>
          <Constant key="Parameter_4440" name="Ki2" value="42"/>
          <Constant key="Parameter_4442" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4438"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4446"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4578"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4440"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4442"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_263" name="G32 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_263">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_131" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4452" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4452"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_131"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_264" name="G33 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_264">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_132" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_129" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_147" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4445" name="V" value="1"/>
          <Constant key="Parameter_4449" name="Ki1" value="23"/>
          <Constant key="Parameter_4447" name="ni1" value="4"/>
          <Constant key="Parameter_4444" name="Ki2" value="12"/>
          <Constant key="Parameter_4443" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_147"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4445"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4449"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4447"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4444"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4443"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_265" name="G33 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_265">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_132" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4386" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4386"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_132"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_266" name="G34 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_266">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_182" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_179" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4396" name="V" value="45"/>
          <Constant key="Parameter_4389" name="Ka1" value="0.2"/>
          <Constant key="Parameter_4393" name="na1" value="4"/>
          <Constant key="Parameter_4391" name="Ki1" value="0.05"/>
          <Constant key="Parameter_4388" name="ni1" value="4"/>
          <Constant key="Parameter_4387" name="Ki2" value="532"/>
          <Constant key="Parameter_4394" name="ni2" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_93" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1060">
              <SourceParameter reference="Metabolite_182"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1059">
              <SourceParameter reference="Metabolite_179"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1058">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1057">
              <SourceParameter reference="Parameter_4396"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1056">
              <SourceParameter reference="Parameter_4389"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1055">
              <SourceParameter reference="Parameter_4393"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1054">
              <SourceParameter reference="Parameter_4391"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1053">
              <SourceParameter reference="Parameter_4388"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1052">
              <SourceParameter reference="Parameter_4387"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1051">
              <SourceParameter reference="Parameter_4394"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_267" name="G34 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_267">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4399" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4399"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_268" name="G35 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_268">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_134" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_129" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_130" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4402" name="V" value="1"/>
          <Constant key="Parameter_4398" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4395" name="na1" value="4"/>
          <Constant key="Parameter_4397" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4392" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4402"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4398"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4395"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4397"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4392"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_269" name="G35 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_269">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_134" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4403" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4403"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_134"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_270" name="G36 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_270">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_135" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4404" name="V" value="5"/>
          <Constant key="Parameter_4405" name="Ka1" value="0.62"/>
          <Constant key="Parameter_4406" name="na1" value="4"/>
          <Constant key="Parameter_4408" name="Ki1" value="20.2"/>
          <Constant key="Parameter_4401" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4404"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4405"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4406"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4408"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4401"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_271" name="G36 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_271">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_135" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4400" name="k1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4400"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_135"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_272" name="G37 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_272">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_136" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4450" name="V" value="8.5"/>
          <Constant key="Parameter_4455" name="Ki1" value="1351"/>
          <Constant key="Parameter_4458" name="ni1" value="4"/>
          <Constant key="Parameter_4454" name="Ki2" value="16.8"/>
          <Constant key="Parameter_4451" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4450"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4455"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4454"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4451"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_273" name="G37 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_273">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_136" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4453" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4453"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_136"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_274" name="G38 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_274">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4448" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4448"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_275" name="G38 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_275">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4459" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_276" name="G39 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_276">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_138" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4456" name="V" value="7"/>
          <Constant key="Parameter_4457" name="Ki1" value="87"/>
          <Constant key="Parameter_4407" name="ni1" value="4"/>
          <Constant key="Parameter_4412" name="Ki2" value="0.14"/>
          <Constant key="Parameter_4410" name="ni2" value="1.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4456"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4457"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4407"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4412"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4410"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_277" name="G39 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_277">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_138" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4415" name="k1" value="0.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4415"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_138"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_278" name="G40 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_278">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_148" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4411" name="V" value="1"/>
          <Constant key="Parameter_4414" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4409" name="na1" value="4"/>
          <Constant key="Parameter_4420" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4421" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_148"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4411"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4414"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4409"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4420"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4421"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_279" name="G40 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_279">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4418" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4418"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_280" name="G41 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_280">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_140" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4419" name="V" value="1"/>
          <Constant key="Parameter_4416" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4417" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4419"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4416"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4417"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_281" name="G41 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_281">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_140" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4413" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4413"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_140"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_282" name="G42 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_282">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_141" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_179" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4423" name="V" value="2.6"/>
          <Constant key="Parameter_4425" name="Ki1" value="0.82"/>
          <Constant key="Parameter_4427" name="ni1" value="4"/>
          <Constant key="Parameter_4432" name="Ki2" value="0.36"/>
          <Constant key="Parameter_4424" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_179"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4423"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4425"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4427"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4432"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4424"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_283" name="G42 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_283">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_141" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4422" name="k1" value="0.11"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4422"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_284" name="G43 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_284">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_142" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_122" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4426" name="V" value="1"/>
          <Constant key="Parameter_4428" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4252" name="na1" value="4"/>
          <Constant key="Parameter_4431" name="Ka2" value="0.01"/>
          <Constant key="Parameter_4253" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_965">
              <SourceParameter reference="Metabolite_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_964">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_963">
              <SourceParameter reference="Parameter_4426"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_962">
              <SourceParameter reference="Parameter_4428"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_961">
              <SourceParameter reference="Parameter_4252"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_960">
              <SourceParameter reference="Parameter_4431"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_959">
              <SourceParameter reference="Parameter_4253"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_285" name="G43 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_285">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_142" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4433" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4433"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_142"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_286" name="G44 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_286">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_124" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4430" name="V" value="1.9"/>
          <Constant key="Parameter_4429" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4361" name="na1" value="4"/>
          <Constant key="Parameter_4362" name="Ki1" value="15"/>
          <Constant key="Parameter_4363" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4430"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4429"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4361"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4362"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4363"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_287" name="G44 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_287">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4364" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4364"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_143"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_288" name="G45 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_288">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_144" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_158" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4366" name="V" value="1"/>
          <Constant key="Parameter_4359" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4358" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4366"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4359"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4358"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_289" name="G45 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_289">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_144" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4365" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4365"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_144"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_290" name="G46 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_290">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_186" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4370" name="V" value="1"/>
          <Constant key="Parameter_4368" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4373" name="na1" value="4"/>
          <Constant key="Parameter_4369" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4372" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_186"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4370"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4368"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4373"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4369"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4372"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_291" name="G46 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_291">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4367" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4367"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_145"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_292" name="G47 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_292">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_146" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4344" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4344"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_293" name="G47 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_293">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_146" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4354" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4354"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_294" name="G48 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_294">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_147" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_152" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_189" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_191" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4347" name="V" value="3.1"/>
          <Constant key="Parameter_4351" name="Ki1" value="243"/>
          <Constant key="Parameter_4349" name="ni1" value="4"/>
          <Constant key="Parameter_4346" name="Ki2" value="0.001"/>
          <Constant key="Parameter_4345" name="ni2" value="4"/>
          <Constant key="Parameter_4352" name="Ki3" value="43"/>
          <Constant key="Parameter_4357" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_94" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1067">
              <SourceParameter reference="Metabolite_152"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1066">
              <SourceParameter reference="Metabolite_189"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1065">
              <SourceParameter reference="Metabolite_191"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1064">
              <SourceParameter reference="Parameter_4347"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1063">
              <SourceParameter reference="Parameter_4351"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1062">
              <SourceParameter reference="Parameter_4349"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1061">
              <SourceParameter reference="Parameter_4346"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1048">
              <SourceParameter reference="Parameter_4345"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1049">
              <SourceParameter reference="Parameter_4352"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1050">
              <SourceParameter reference="Parameter_4357"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_295" name="G48 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_295">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_147" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4360" name="k1" value="1.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4360"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_147"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_296" name="G49 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_296">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_148" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_167" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4356" name="V" value="1"/>
          <Constant key="Parameter_4353" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4355" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_167"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4356"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4353"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4355"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_297" name="G49 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_297">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_148" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4350" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4350"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_148"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_298" name="G50 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_298">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_149" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4378" name="V" value="1"/>
          <Constant key="Parameter_4379" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4376" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4378"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4379"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4376"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_299" name="G50 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_299">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_149" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4377" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4377"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_149"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_300" name="G51 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_300">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_150" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4374" name="V" value="1"/>
          <Constant key="Parameter_4375" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4371" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4374"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4375"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4371"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_301" name="G51 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_301">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_150" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4381" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4381"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_150"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_302" name="G52 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_302">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4383" name="V" value="1"/>
          <Constant key="Parameter_4385" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4390" name="ni1" value="4"/>
          <Constant key="Parameter_4382" name="Ki2" value="0.01"/>
          <Constant key="Parameter_4380" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4383"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4385"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4390"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4382"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4380"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_303" name="G52 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_303">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4384" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4384"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_304" name="G53 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_304">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_152" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4579" name="V" value="1"/>
          <Constant key="Parameter_4575" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4574" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4579"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4575"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4574"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_305" name="G53 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_305">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_152" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4580" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4580"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_152"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_306" name="G54 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_306">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_153" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_125" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4584" name="V" value="1"/>
          <Constant key="Parameter_4577" name="Ki1" value="1e-05"/>
          <Constant key="Parameter_4582" name="ni1" value="2"/>
          <Constant key="Parameter_4581" name="Ki2" value="4300"/>
          <Constant key="Parameter_4585" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4584"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4577"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4582"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4581"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4585"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_307" name="G54 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_307">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_153" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4583" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4583"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_153"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_308" name="G55 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_308">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_154" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_125" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_167" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4588" name="V" value="1.6"/>
          <Constant key="Parameter_4589" name="Ki1" value="0.1"/>
          <Constant key="Parameter_4596" name="ni1" value="4"/>
          <Constant key="Parameter_4590" name="Ki2" value="0.07"/>
          <Constant key="Parameter_4586" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_167"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4588"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4589"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4596"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4590"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4586"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_309" name="G55 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_309">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_154" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4587" name="k1" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4587"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_154"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_310" name="G56 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_310">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_155" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4591" name="V" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4591"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_311" name="G56 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_311">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_155" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4593" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4593"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_155"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_312" name="G57 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_312">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_156" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4600" name="V" value="1"/>
          <Constant key="Parameter_4598" name="Ki1" value="1"/>
          <Constant key="Parameter_4599" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4598"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4599"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_313" name="G57 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_313">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_156" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4592" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4592"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_156"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_314" name="G58 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_314">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_157" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4601" name="V" value="23"/>
          <Constant key="Parameter_4597" name="Ki1" value="234"/>
          <Constant key="Parameter_4594" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4601"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4597"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4594"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_315" name="G58 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_315">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_157" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4595" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4595"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_157"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_316" name="G59 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_316">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_158" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4603" name="V" value="1"/>
          <Constant key="Parameter_4602" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4242" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4603"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4602"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4242"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_317" name="G59 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_317">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_158" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4070" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4070"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_158"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_318" name="G60 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_318">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_159" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4251" name="V" value="4"/>
          <Constant key="Parameter_4247" name="Ka1" value="0.005"/>
          <Constant key="Parameter_4240" name="na1" value="4"/>
          <Constant key="Parameter_4250" name="Ki1" value="8"/>
          <Constant key="Parameter_4243" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4251"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4247"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4240"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4250"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4243"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_319" name="G60 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_319">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_159" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4258" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4258"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_159"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_320" name="G61 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_320">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_160" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4249" name="V" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4249"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_321" name="G61 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_321">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_160" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4248" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4248"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_160"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_322" name="G62 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_322">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_161" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_154" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4246" name="V" value="3.2"/>
          <Constant key="Parameter_4071" name="Ki1" value="0.1"/>
          <Constant key="Parameter_4254" name="ni1" value="4"/>
          <Constant key="Parameter_4245" name="Ki2" value="0.4"/>
          <Constant key="Parameter_4255" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4246"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4071"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4254"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4245"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4255"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_323" name="G62 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_323">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_161" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4608" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4608"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_161"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_324" name="G63 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_324">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_162" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4605" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4605"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_325" name="G63 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_325">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_162" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4604" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4604"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_162"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_326" name="G64 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_326">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_163" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_124" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4606" name="V" value="1"/>
          <Constant key="Parameter_4611" name="Ki1" value="23"/>
          <Constant key="Parameter_4614" name="ni1" value="4"/>
          <Constant key="Parameter_4607" name="Ki2" value="1"/>
          <Constant key="Parameter_4609" name="ni2" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4606"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4611"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4614"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4607"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4609"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_327" name="G64 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_327">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_163" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4622" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4622"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_163"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_328" name="G65 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_328">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_164" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_168" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4613" name="V" value="1"/>
          <Constant key="Parameter_4435" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4615" name="ni1" value="4"/>
          <Constant key="Parameter_4610" name="Ki2" value="5.1"/>
          <Constant key="Parameter_4434" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_168"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4613"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4435"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4615"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4610"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4434"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_329" name="G65 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_329">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_164" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4612" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4612"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_164"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_330" name="G66 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_330">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_165" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4621" name="V" value="1"/>
          <Constant key="Parameter_4623" name="Ka1" value="0.0001"/>
          <Constant key="Parameter_4620" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4621"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4623"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4620"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_331" name="G66 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_331">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_165" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4619" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4619"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_165"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_332" name="G67 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_332">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_166" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4618" name="V" value="0.3"/>
          <Constant key="Parameter_4629" name="Ki1" value="8.2"/>
          <Constant key="Parameter_4625" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4618"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4629"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4625"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_333" name="G67 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_333">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_166" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4626" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4626"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_166"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_334" name="G68 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_334">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_167" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4628" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4628"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_335" name="G68 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_335">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_167" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4624" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4624"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_167"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_336" name="G69 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_336">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_168" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_18" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4631" name="V" value="3"/>
          <Constant key="Parameter_4627" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4634" name="na1" value="4"/>
          <Constant key="Parameter_4635" name="Ki1" value="2"/>
          <Constant key="Parameter_4632" name="ni1" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4631"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4627"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4634"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4635"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4632"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_337" name="G69 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_337">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_168" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4630" name="k1" value="2.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4630"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_168"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_338" name="G70 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_338">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_169" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_26" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4638" name="V" value="1.4"/>
          <Constant key="Parameter_4637" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4640" name="na1" value="4"/>
          <Constant key="Parameter_4636" name="Ki1" value="123"/>
          <Constant key="Parameter_4633" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4638"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4637"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4640"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_4636"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_4633"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_339" name="G70 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_339">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_169" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4644" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4644"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_169"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_340" name="G71 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_340">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_170" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_129" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_194" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4646" name="V" value="1"/>
          <Constant key="Parameter_4641" name="Ki1" value="0.08"/>
          <Constant key="Parameter_4643" name="ni1" value="4"/>
          <Constant key="Parameter_4642" name="Ki2" value="56"/>
          <Constant key="Parameter_4639" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_194"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4646"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4641"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4643"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4642"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4639"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_341" name="G71 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_341">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_170" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4652" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4652"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_170"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_342" name="G72 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_342">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_171" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_150" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4645" name="V" value="1"/>
          <Constant key="Parameter_4647" name="Ki1" value="2.3"/>
          <Constant key="Parameter_4653" name="ni1" value="4"/>
          <Constant key="Parameter_4648" name="Ki2" value="2.4"/>
          <Constant key="Parameter_4650" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_999">
              <SourceParameter reference="Metabolite_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_998">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_997">
              <SourceParameter reference="Parameter_4645"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_996">
              <SourceParameter reference="Parameter_4647"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_995">
              <SourceParameter reference="Parameter_4653"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_994">
              <SourceParameter reference="Parameter_4648"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_993">
              <SourceParameter reference="Parameter_4650"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_343" name="G72 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_343">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_171" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4649" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4649"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_171"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_344" name="G73 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_344">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_172" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4660" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4660"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_345" name="G73 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_345">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_172" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4655" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4655"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_172"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_346" name="G74 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_346">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_173" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4670" name="V" value="1"/>
          <Constant key="Parameter_4662" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4664" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4670"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4662"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4664"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_347" name="G74 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_347">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_173" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4658" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4658"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_173"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_348" name="G75 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_348">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_174" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4656" name="V" value="1"/>
          <Constant key="Parameter_4665" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4659" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4656"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4665"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4659"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_349" name="G75 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_349">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_174" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4663" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4663"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_174"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_350" name="G76 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_350">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_175" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4657" name="V" value="1"/>
          <Constant key="Parameter_4661" name="Ka1" value="6e-09"/>
          <Constant key="Parameter_4651" name="na1" value="3.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_4657"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_4661"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_4651"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_351" name="G76 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_351">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_175" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4654" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4654"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_175"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_352" name="G77 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_352">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_176" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4668" name="V" value="1"/>
          <Constant key="Parameter_4666" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4667" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_4668"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_4666"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_4667"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_353" name="G77 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_353">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_176" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4676" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4676"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_176"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_354" name="G78 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_354">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_177" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4671" name="V" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_4671"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_355" name="G78 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_355">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_177" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4669" name="k1" value="2.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4669"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_177"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_356" name="G79 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_356">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_178" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7087" name="V" value="1"/>
          <Constant key="Parameter_4617" name="Ka1" value="0.01"/>
          <Constant key="Parameter_7101" name="na1" value="4"/>
          <Constant key="Parameter_7097" name="Ka2" value="0.01"/>
          <Constant key="Parameter_7096" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_965">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_964">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_963">
              <SourceParameter reference="Parameter_7087"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_962">
              <SourceParameter reference="Parameter_4617"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_961">
              <SourceParameter reference="Parameter_7101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_960">
              <SourceParameter reference="Parameter_7097"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_959">
              <SourceParameter reference="Parameter_7096"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_357" name="G79 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_357">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_178" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4616" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4616"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_178"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_358" name="G80 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_358">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_179" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7091" name="V" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_7091"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_359" name="G80 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_359">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_179" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7092" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_7092"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_179"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_360" name="G81 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_360">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_180" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_148" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4674" name="V" value="1"/>
          <Constant key="Parameter_4672" name="Ka1" value="0.001"/>
          <Constant key="Parameter_4673" name="na1" value="4"/>
          <Constant key="Parameter_7095" name="Ki1" value="1"/>
          <Constant key="Parameter_7094" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_148"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_4674"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_4672"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_4673"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_7095"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_7094"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_361" name="G81 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_361">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_180" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7106" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_7106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_180"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_362" name="G82 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_362">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_181" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_160" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7098" name="V" value="1"/>
          <Constant key="Parameter_7102" name="Ka1" value="0.01"/>
          <Constant key="Parameter_7088" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_7098"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_7102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_7088"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_363" name="G82 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_363">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_181" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7093" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_7093"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_181"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_364" name="G83 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_364">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_182" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6785" name="V" value="1.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6785"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_365" name="G83 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_365">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_182" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6784" name="k1" value="1.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6784"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_182"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_366" name="G84 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_366">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_183" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6829" name="V" value="1"/>
          <Constant key="Parameter_6822" name="Ki1" value="1.5"/>
          <Constant key="Parameter_6823" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_6829"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_6822"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_6823"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_367" name="G84 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_367">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_183" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6817" name="k1" value="2.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6817"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_183"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_368" name="G85 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_368">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_184" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6828" name="V" value="1"/>
          <Constant key="Parameter_6827" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6826" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6828"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6827"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6826"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_369" name="G85 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_369">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_184" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6833" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6833"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_184"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_370" name="G86 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_370">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_185" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_122" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6832" name="V" value="1"/>
          <Constant key="Parameter_6831" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6830" name="na1" value="4"/>
          <Constant key="Parameter_6837" name="Ka2" value="0.01"/>
          <Constant key="Parameter_6836" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_965">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_964">
              <SourceParameter reference="Metabolite_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_963">
              <SourceParameter reference="Parameter_6832"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_962">
              <SourceParameter reference="Parameter_6831"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_961">
              <SourceParameter reference="Parameter_6830"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_960">
              <SourceParameter reference="Parameter_6837"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_959">
              <SourceParameter reference="Parameter_6836"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_371" name="G86 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_371">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_185" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6835" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6835"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_185"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_372" name="G87 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_372">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_186" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6834" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6834"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_373" name="G87 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_373">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_186" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6841" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6841"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_186"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_374" name="G88 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_374">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_187" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_184" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6840" name="V" value="1"/>
          <Constant key="Parameter_6839" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6780" name="na1" value="4"/>
          <Constant key="Parameter_6786" name="Ki1" value="0.01"/>
          <Constant key="Parameter_6776" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_184"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_6840"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_6839"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_6780"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_6786"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_6776"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_375" name="G88 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_375">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_187" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6787" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6787"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_187"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_376" name="G89 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_376">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_188" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_177" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6781" name="V" value="1.3"/>
          <Constant key="Parameter_6824" name="Ka1" value="0.001"/>
          <Constant key="Parameter_6838" name="na1" value="4"/>
          <Constant key="Parameter_6845" name="Ki1" value="0.1"/>
          <Constant key="Parameter_6844" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_177"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_6781"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_6824"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_6838"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_6845"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_6844"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_377" name="G89 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_377">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_188" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6843" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6843"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_188"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_378" name="G90 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_378">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_189" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_122" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_199" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6842" name="V" value="1"/>
          <Constant key="Parameter_6821" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6850" name="na1" value="4"/>
          <Constant key="Parameter_6849" name="Ki1" value="0.01"/>
          <Constant key="Parameter_6848" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1025">
              <SourceParameter reference="Metabolite_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1024">
              <SourceParameter reference="Metabolite_199"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1023">
              <SourceParameter reference="Parameter_6842"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1007">
              <SourceParameter reference="Parameter_6821"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1008">
              <SourceParameter reference="Parameter_6850"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1009">
              <SourceParameter reference="Parameter_6849"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1010">
              <SourceParameter reference="Parameter_6848"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_379" name="G90 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_379">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_189" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6847" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6847"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_189"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_380" name="G91 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_380">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_190" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6854" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6854"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_381" name="G91 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_381">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_190" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6853" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6853"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_190"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_382" name="G92 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_382">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_191" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_162" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6852" name="V" value="1"/>
          <Constant key="Parameter_6851" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6858" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6852"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6851"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6858"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_383" name="G92 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_383">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_191" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6857" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6857"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_191"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_384" name="G93 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_384">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_192" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6856" name="V" value="1"/>
          <Constant key="Parameter_6855" name="Ki1" value="0.01"/>
          <Constant key="Parameter_6862" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_6856"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_6855"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_6862"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_385" name="G93 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_385">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_192" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6861" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6861"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_192"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_386" name="G94 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_386">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_193" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6860" name="V" value="2.1"/>
          <Constant key="Parameter_6859" name="Ka1" value="2"/>
          <Constant key="Parameter_6866" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6860"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6859"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6866"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_387" name="G94 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_387">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_193" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6865" name="k1" value="1.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6865"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_193"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_388" name="G95 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_388">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_194" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6864" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6864"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_389" name="G95 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_389">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_194" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6863" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6863"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_194"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_390" name="G96 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_390">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_195" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6846" name="V" value="1"/>
          <Constant key="Parameter_6811" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6872" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_920">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_919">
              <SourceParameter reference="Parameter_6846"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_918">
              <SourceParameter reference="Parameter_6811"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_917">
              <SourceParameter reference="Parameter_6872"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_391" name="G96 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_391">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_195" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6871" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6871"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_195"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_392" name="G97 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_392">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_196" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_174" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6870" name="V" value="1"/>
          <Constant key="Parameter_6869" name="Ki1" value="0.01"/>
          <Constant key="Parameter_6876" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_174"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_6870"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_6869"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_6876"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_393" name="G97 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_393">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_196" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6875" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6875"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_196"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_394" name="G98 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_394">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_197" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_146" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6874" name="V" value="1"/>
          <Constant key="Parameter_6873" name="Ki1" value="0.7"/>
          <Constant key="Parameter_6880" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_979">
              <SourceParameter reference="Metabolite_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_978">
              <SourceParameter reference="Parameter_6874"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_977">
              <SourceParameter reference="Parameter_6873"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_976">
              <SourceParameter reference="Parameter_6880"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_395" name="G98 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_395">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_197" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6879" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6879"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_197"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_396" name="G99 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_396">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_198" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6878" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6878"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_397" name="G99 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_397">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_198" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6877" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6877"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_198"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_398" name="G100 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_398">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_199" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6884" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_1026">
              <SourceParameter reference="Parameter_6884"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_399" name="G100 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_399">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_199" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6883" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6883"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_199"/>
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
<dcterms:W3CDTF>2021-01-02T19:19:54Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G1]" value="22691800000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G2]" value="6986120000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G3]" value="323777000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G4]" value="606782000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G5]" value="4.67668e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G6]" value="11556400000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G7]" value="79403100000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G8]" value="3461590000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G9]" value="9345020000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G10]" value="2107670000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G11]" value="105972000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G12]" value="10451600000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G13]" value="8.6059e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G14]" value="15328999999999998" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G15]" value="3343310000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G16]" value="680574000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G17]" value="15146300000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G18]" value="84046500000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G19]" value="9552270000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G20]" value="544044000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G21]" value="716033000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G22]" value="2258300000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G23]" value="734847000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G24]" value="4101590000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G25]" value="1385090000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G26]" value="75204900000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G27]" value="9580630000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G28]" value="1106850000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G29]" value="79386700000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G30]" value="634179000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G31]" value="1339090000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G32]" value="9514160000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G33]" value="428401000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G34]" value="1811810000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G35]" value="4235300000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G36]" value="312045000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G37]" value="2563850000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G38]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G39]" value="43403000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G40]" value="9601060000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G41]" value="9623350000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G42]" value="131696000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G43]" value="1.49162e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G44]" value="35353900000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G45]" value="9601010000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G46]" value="90980900" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G47]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G48]" value="297703000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G49]" value="9446040000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G50]" value="602938999999999.88" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G51]" value="9475700000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G52]" value="2363190" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G53]" value="9627770000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G54]" value="3307079999999.9995" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G55]" value="21951800000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G56]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G57]" value="600921000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G58]" value="39816100000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G59]" value="3361290000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G60]" value="516061000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G61]" value="240886000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G62]" value="115577000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G63]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G64]" value="601452000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G65]" value="1172960000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G66]" value="3646700000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G67]" value="1650550000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G68]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G69]" value="11544000000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G70]" value="178620000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G71]" value="13941900000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G72]" value="39550200000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G73]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G74]" value="3564099.9999999995" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G75]" value="2913890" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G76]" value="5534100000000001" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G77]" value="601490000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G78]" value="124596000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G79]" value="604326000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G80]" value="481771000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G81]" value="124064000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G82]" value="9173930000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G83]" value="766454000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G84]" value="14969800000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G85]" value="9635180000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G86]" value="1.49162e+17" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G87]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G88]" value="634107" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G89]" value="19111300" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G90]" value="91098400" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G91]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G92]" value="9446040000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G93]" value="601490000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G94]" value="19356400000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G95]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G96]" value="9623020000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G97]" value="602213000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G98]" value="17312000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G99]" value="602214000000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G100]" value="602214000000000" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=V" value="5.7999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="9.9999999999999995e-07" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na2" value="2.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="42.445300000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka5" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na5" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka6" value="4.0000000000000003e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na6" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka7" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na7" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka8" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na8" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ka9" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=na9" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.0080000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="8.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="2.6000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="123" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G1 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.2" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=V" value="12300" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.0030000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.60789700000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="0.152614" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="0.23568900000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ka5" value="12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=na5" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.49024699999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.00072136300000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G2 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.031" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=V" value="49" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="12.243" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="3.2520299999999999e-08" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="5.6729999999999997e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="0.87701399999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka5" value="0.0080000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na5" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka6" value="1.73921e-12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na6" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka7" value="7.1734" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na7" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ka8" value="0.246835" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=na8" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="4.7452300000000002e-07" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="2.3753799999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="3.6900000000000002e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki4" value="31962" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki5" value="10.2279" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni5" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki6" value="0.00039100000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni6" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=Ki7" value="3.9085399999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 synthesis],ParameterGroup=Parameters,Parameter=ni7" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G3 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.0080000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=V" value="33" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.122081" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=na1" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="1.4128499999999999e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=na2" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="5.36239e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=na3" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.0184689" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="3" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G4 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.059999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=V" value="43" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="23" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="2.3e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="0.42999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ki4" value="0.14299999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=ni4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=Ki5" value="0.00040000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 synthesis],ParameterGroup=Parameters,Parameter=ni5" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G5 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G6 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=V" value="23" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="6.0000000000000002e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G7 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=V" value="5.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="19" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="0.81104799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=na3" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="20" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ka5" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=na5" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.080000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="1.7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="3.5" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G8 degradation],ParameterGroup=Parameters,Parameter=k1" value="2.5299999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.050000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.02" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G9 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=V" value="6" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="1e-08" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.29999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G10 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.69999999999999996" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 synthesis],ParameterGroup=Parameters,Parameter=V" value="27" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="5.4000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="2.3999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G11 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G12 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.1000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=V" value="3.6000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="9.9999999999999995e-07" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.80000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="9.9999999999999995e-07" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="1.9999999999999999e-06" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.032000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G13 degradation],ParameterGroup=Parameters,Parameter=k1" value="2.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.6000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G14 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis],ParameterGroup=Parameters,Parameter=V" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="58" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G15 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.29999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=V" value="7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="933" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="21" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="235" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=Ki4" value="1000" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=ni4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=Ki5" value="0.50360300000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 synthesis],ParameterGroup=Parameters,Parameter=ni5" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G16 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="231" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="189" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G17 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis],ParameterGroup=Parameters,Parameter=V" value="100" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="43" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G18 degradation],ParameterGroup=Parameters,Parameter=k1" value="30" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G19 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis],ParameterGroup=Parameters,Parameter=V" value="12.300000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="7.4299999999999997" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="4.5999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G20 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.050000000000000003" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=V" value="0.59999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="5.8710399999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="165.852" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=Ka3" value="3.5864799999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=na3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=Ka4" value="386.19" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=na4" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="11.404999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="2.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G21 degradation],ParameterGroup=Parameters,Parameter=k1" value="5.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G22 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G22 synthesis],ParameterGroup=Parameters,Parameter=V" value="3" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G22 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G22 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.80000000000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G23 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G24 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G25 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G25 synthesis],ParameterGroup=Parameters,Parameter=V" value="2.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G25 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G25 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis],ParameterGroup=Parameters,Parameter=V" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.02" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.050000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G26 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.8999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="2323" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="2.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G27 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis],ParameterGroup=Parameters,Parameter=V" value="15" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="3.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="8.4000000000000004" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G28 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="163" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G29 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.13400000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G30 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=V" value="14" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="5.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="15" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=Ki4" value="0.14999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 synthesis],ParameterGroup=Parameters,Parameter=ni4" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G31 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.69999999999999996" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis],ParameterGroup=Parameters,Parameter=V" value="9" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="36" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="42" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G32 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="23" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="12" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G33 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=V" value="45" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.20000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.050000000000000003" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="532" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="3" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G34 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G35 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis],ParameterGroup=Parameters,Parameter=V" value="5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.62" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="20.199999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G36 degradation],ParameterGroup=Parameters,Parameter=k1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis],ParameterGroup=Parameters,Parameter=V" value="8.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="1351" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="16.800000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G37 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G38 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G38 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G38 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G38 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis],ParameterGroup=Parameters,Parameter=V" value="7" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="87" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.14000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="1.5" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G39 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.040000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G40 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G41 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis],ParameterGroup=Parameters,Parameter=V" value="2.6000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.81999999999999995" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.35999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G42 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.11" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G43 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.8999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="15" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G44 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G45 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G46 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G47 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G47 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G47 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G47 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=V" value="3.1000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="243" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=Ki3" value="43" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 synthesis],ParameterGroup=Parameters,Parameter=ni3" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G48 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.3999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G49 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G50 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G51 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G52 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G53 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="4300" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G54 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.6000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.070000000000000007" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G55 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.80000000000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G56 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G56 synthesis],ParameterGroup=Parameters,Parameter=V" value="10" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G56 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G56 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G57 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 synthesis],ParameterGroup=Parameters,Parameter=V" value="23" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="234" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G58 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G59 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis],ParameterGroup=Parameters,Parameter=V" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.0050000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="8" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G60 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G61 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G61 synthesis],ParameterGroup=Parameters,Parameter=V" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G61 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G61 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis],ParameterGroup=Parameters,Parameter=V" value="3.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G62 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G63 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G63 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G63 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G63 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="23" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="2" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G64 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="5.0999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G65 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.0001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G66 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 synthesis],ParameterGroup=Parameters,Parameter=V" value="0.29999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="8.1999999999999993" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G67 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G68 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G68 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G68 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G68 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis],ParameterGroup=Parameters,Parameter=V" value="3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="3" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G69 degradation],ParameterGroup=Parameters,Parameter=k1" value="2.5" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.3999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="123" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G70 degradation],ParameterGroup=Parameters,Parameter=k1" value="0.40000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.080000000000000002" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="56" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G71 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="2.2999999999999998" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis],ParameterGroup=Parameters,Parameter=Ki2" value="2.3999999999999999" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 synthesis],ParameterGroup=Parameters,Parameter=ni2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G72 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G73 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G73 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G73 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G73 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G74 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G75 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="6e-09" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 synthesis],ParameterGroup=Parameters,Parameter=na1" value="3.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G76 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G77 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G78 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G78 synthesis],ParameterGroup=Parameters,Parameter=V" value="0.59999999999999998" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G78 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G78 degradation],ParameterGroup=Parameters,Parameter=k1" value="2.8999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G79 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G80 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G80 synthesis],ParameterGroup=Parameters,Parameter=V" value="0.80000000000000004" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G80 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G80 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G81 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G82 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G83 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G83 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.3999999999999999" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G83 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G83 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.1000000000000001" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="1.5" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G84 degradation],ParameterGroup=Parameters,Parameter=k1" value="2.2000000000000002" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G85 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis],ParameterGroup=Parameters,Parameter=Ka2" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 synthesis],ParameterGroup=Parameters,Parameter=na2" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G86 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G87 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G87 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G87 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G87 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G88 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis],ParameterGroup=Parameters,Parameter=V" value="1.3" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.10000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G89 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G90 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G91 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G91 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G91 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G91 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G92 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G93 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 synthesis],ParameterGroup=Parameters,Parameter=V" value="2.1000000000000001" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="2" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G94 degradation],ParameterGroup=Parameters,Parameter=k1" value="1.04" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G95 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G95 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G95 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G95 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 synthesis],ParameterGroup=Parameters,Parameter=Ka1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 synthesis],ParameterGroup=Parameters,Parameter=na1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G96 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.01" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G97 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 synthesis],ParameterGroup=Parameters,Parameter=Ki1" value="0.69999999999999996" type="ReactionParameter" simulationType="fixed"/>
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 synthesis],ParameterGroup=Parameters,Parameter=ni1" value="4" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G98 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G99 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G99 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G99 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G99 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G100 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G100 synthesis],ParameterGroup=Parameters,Parameter=V" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G100 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Reactions[G100 degradation],ParameterGroup=Parameters,Parameter=k1" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_122"/>
      <StateTemplateVariable objectReference="Metabolite_123"/>
      <StateTemplateVariable objectReference="Metabolite_124"/>
      <StateTemplateVariable objectReference="Metabolite_125"/>
      <StateTemplateVariable objectReference="Metabolite_126"/>
      <StateTemplateVariable objectReference="Metabolite_127"/>
      <StateTemplateVariable objectReference="Metabolite_128"/>
      <StateTemplateVariable objectReference="Metabolite_129"/>
      <StateTemplateVariable objectReference="Metabolite_130"/>
      <StateTemplateVariable objectReference="Metabolite_131"/>
      <StateTemplateVariable objectReference="Metabolite_132"/>
      <StateTemplateVariable objectReference="Metabolite_133"/>
      <StateTemplateVariable objectReference="Metabolite_134"/>
      <StateTemplateVariable objectReference="Metabolite_135"/>
      <StateTemplateVariable objectReference="Metabolite_136"/>
      <StateTemplateVariable objectReference="Metabolite_137"/>
      <StateTemplateVariable objectReference="Metabolite_138"/>
      <StateTemplateVariable objectReference="Metabolite_139"/>
      <StateTemplateVariable objectReference="Metabolite_140"/>
      <StateTemplateVariable objectReference="Metabolite_141"/>
      <StateTemplateVariable objectReference="Metabolite_142"/>
      <StateTemplateVariable objectReference="Metabolite_143"/>
      <StateTemplateVariable objectReference="Metabolite_144"/>
      <StateTemplateVariable objectReference="Metabolite_145"/>
      <StateTemplateVariable objectReference="Metabolite_146"/>
      <StateTemplateVariable objectReference="Metabolite_147"/>
      <StateTemplateVariable objectReference="Metabolite_148"/>
      <StateTemplateVariable objectReference="Metabolite_149"/>
      <StateTemplateVariable objectReference="Metabolite_150"/>
      <StateTemplateVariable objectReference="Metabolite_151"/>
      <StateTemplateVariable objectReference="Metabolite_152"/>
      <StateTemplateVariable objectReference="Metabolite_153"/>
      <StateTemplateVariable objectReference="Metabolite_154"/>
      <StateTemplateVariable objectReference="Metabolite_155"/>
      <StateTemplateVariable objectReference="Metabolite_156"/>
      <StateTemplateVariable objectReference="Metabolite_157"/>
      <StateTemplateVariable objectReference="Metabolite_158"/>
      <StateTemplateVariable objectReference="Metabolite_159"/>
      <StateTemplateVariable objectReference="Metabolite_160"/>
      <StateTemplateVariable objectReference="Metabolite_161"/>
      <StateTemplateVariable objectReference="Metabolite_162"/>
      <StateTemplateVariable objectReference="Metabolite_163"/>
      <StateTemplateVariable objectReference="Metabolite_164"/>
      <StateTemplateVariable objectReference="Metabolite_165"/>
      <StateTemplateVariable objectReference="Metabolite_166"/>
      <StateTemplateVariable objectReference="Metabolite_167"/>
      <StateTemplateVariable objectReference="Metabolite_168"/>
      <StateTemplateVariable objectReference="Metabolite_169"/>
      <StateTemplateVariable objectReference="Metabolite_170"/>
      <StateTemplateVariable objectReference="Metabolite_171"/>
      <StateTemplateVariable objectReference="Metabolite_172"/>
      <StateTemplateVariable objectReference="Metabolite_173"/>
      <StateTemplateVariable objectReference="Metabolite_174"/>
      <StateTemplateVariable objectReference="Metabolite_175"/>
      <StateTemplateVariable objectReference="Metabolite_176"/>
      <StateTemplateVariable objectReference="Metabolite_177"/>
      <StateTemplateVariable objectReference="Metabolite_178"/>
      <StateTemplateVariable objectReference="Metabolite_179"/>
      <StateTemplateVariable objectReference="Metabolite_180"/>
      <StateTemplateVariable objectReference="Metabolite_181"/>
      <StateTemplateVariable objectReference="Metabolite_182"/>
      <StateTemplateVariable objectReference="Metabolite_183"/>
      <StateTemplateVariable objectReference="Metabolite_184"/>
      <StateTemplateVariable objectReference="Metabolite_185"/>
      <StateTemplateVariable objectReference="Metabolite_186"/>
      <StateTemplateVariable objectReference="Metabolite_187"/>
      <StateTemplateVariable objectReference="Metabolite_188"/>
      <StateTemplateVariable objectReference="Metabolite_189"/>
      <StateTemplateVariable objectReference="Metabolite_190"/>
      <StateTemplateVariable objectReference="Metabolite_191"/>
      <StateTemplateVariable objectReference="Metabolite_192"/>
      <StateTemplateVariable objectReference="Metabolite_193"/>
      <StateTemplateVariable objectReference="Metabolite_194"/>
      <StateTemplateVariable objectReference="Metabolite_195"/>
      <StateTemplateVariable objectReference="Metabolite_196"/>
      <StateTemplateVariable objectReference="Metabolite_197"/>
      <StateTemplateVariable objectReference="Metabolite_198"/>
      <StateTemplateVariable objectReference="Metabolite_199"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 22691800000000000 6986120000000 323777000000 606782000000000 4.67668e+17 11556400000000000 79403100000 3461590000 9345020000000000 2107670000000000 105972000000 10451600000000000 8.6059e+18 15328999999999998 3343310000000000 680574000000000 15146300000000000 84046500000000 9552270000000000 544044000 716033000000000 2258300000000000 734847000000000 4101590000000000 1385090000000000 75204900000 9580630000000000 1106850000000 79386700000000000 634179000000000 1339090000000 9514160000000 428401000000000 1811810000 4235300000000000 312045000 2563850000 602214000000000 43403000000000 9601060000000000 9623350000000000 131696000000000 1.49162e+17 35353900000000000 9601010000000000 90980900 602214000000000 297703000000000 9446040000000000 602938999999999.88 9475700000000000 2363190 9627770000000000 3307079999999.9995 21951800000 602214000000000 600921000000000 39816100000000 3361290000000000 516061000000000 240886000000000 115577000 602214000000000 601452000000 1172960000000 3646700000000000 1650550000000 602214000000000 11544000000000000 178620000 13941900000 39550200000 602214000000000 3564099.9999999995 2913890 5534100000000001 601490000000000 124596000000000 604326000000000 481771000000000 124064000000 9173930000000000 766454000000000 14969800000 9635180000000000 1.49162e+17 602214000000000 634107 19111300 91098400 602214000000000 9446040000000000 601490000000000 19356400000000000 602214000000000 9623020000000000 602213000000000 17312000000000 602214000000000 602214000000000 1 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_27" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_24" target="../../Test/CopasiTestSSReport.txt" append="0" confirmOverwrite="0"/>
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
      <Report reference="Report_9" target="../../Test/100GeneTestDyn.dat" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="20"/>
        <Parameter name="StepSize" type="float" value="10"/>
        <Parameter name="Duration" type="float" value="200"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="200"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Stochastic">
        <Parameter name="Max Internal Steps" type="integer" value="1000000"/>
        <Parameter name="Use Random Seed" type="bool" value="0"/>
        <Parameter name="Random Seed" type="unsignedInteger" value="1"/>
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-14"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
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
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_19" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_20" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_21" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_22" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
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
    <Task key="Task_23" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="true" updateModel="false">
      <Report reference="Report_21" target="CoopSF4_001_tssa-ildm.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="4"/>
        <Parameter name="StepSize" type="float" value="25"/>
        <Parameter name="Duration" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="0.0001"/>
        <Parameter name="Integrate Reduced Model" type="bool" value="1"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Adams Max Order" type="unsignedInteger" value="12"/>
        <Parameter name="BDF Max Order" type="unsignedInteger" value="5"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_24" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
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
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="100000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_15" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_27"/>
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
    <Report key="Report_24" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters"/>
      </Table>
    </Report>
    <Report key="Report_9" name="report" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Trajectory plot
        </body>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Reference=Time"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G3],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G4],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G5],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G6],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G7],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G8],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G9],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G10],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G11],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G12],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G13],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G14],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G15],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G16],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G17],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G18],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G19],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G20],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G21],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G22],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G23],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G24],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G25],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G26],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G27],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G28],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G29],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G30],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G31],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G32],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G33],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G34],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G35],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G36],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G37],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G38],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G39],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G40],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G41],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G42],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G43],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G44],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G45],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G46],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G47],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G48],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G49],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G50],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G51],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G52],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G53],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G54],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G55],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G56],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G57],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G58],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G59],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G60],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G61],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G62],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G63],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G64],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G65],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G66],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G67],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G68],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G69],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G70],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G71],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G72],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G73],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G74],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G75],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G76],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G77],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G78],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G79],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G80],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G81],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G82],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G83],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G84],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G85],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G86],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G87],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G88],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G89],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G90],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G91],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G92],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G93],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G94],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G95],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G96],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G97],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G98],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G99],Reference=Concentration"/>
        <Object cn="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell],Vector=Metabolites[G100],Reference=Concentration"/>
      </Table>
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
    <Report key="Report_14" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_15" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_17" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_18" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_20" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_21" name="Speed test" taskType="scan" separator="&#x09;" precision="8">
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_65" name="minute" symbol="min">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-02T17:57:38Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        60*s
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
